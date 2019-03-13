// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <lib/xdrpp/xdrpp/printer.h>
#include <transactions/review_request/ReviewIssuanceCreationRequestOpFrame.h>
#include <main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>
#include <crypto/SHA.h>
#include <transactions/SignatureValidatorImpl.h>
#include "ChangeAssetPreIssuerOpFrame.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AssetHelperLegacy.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

ChangeAssetPreIssuerOpFrame::ChangeAssetPreIssuerOpFrame(Operation const& op,
                                                         OperationResult& res,
                                                         TransactionFrame&
                                                         parentTx)
    : ManageAssetOpFrame(op, res, parentTx)
    , mAssetChangePreissuedSigner(mManageAsset.request.changePreissuedSigner())
{
}

bool
ChangeAssetPreIssuerOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                          std::vector<OperationCondition>& result) const
{
    // will be handled on signer level
    return true;
}

bool
ChangeAssetPreIssuerOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                        std::vector<SignerRequirement>& result) const
{
    // only asset pre issuer can change asset pre issuer
    return true;
}

bool ChangeAssetPreIssuerOpFrame::doApply(Application& app, LedgerDelta& delta,
                                          LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    auto assetFrame = AssetHelperLegacy::Instance()->
        loadAsset(mAssetChangePreissuedSigner.code, db, &delta);
    if (!assetFrame)
    {
        innerResult().code(ManageAssetResultCode::ASSET_NOT_FOUND);
        return false;
    }

    if (assetFrame->getPreIssuedAssetSigner() == mAssetChangePreissuedSigner.accountID)
    {
        innerResult().code(ManageAssetResultCode::INVALID_PRE_ISSUER);
        return false;
    }

    if (!isSignatureValid(assetFrame, ledgerManager.getLedgerVersion()))
    {
        innerResult().code(ManageAssetResultCode::INVALID_SIGNATURE);
        return false;
    }

    auto& assetEntry = assetFrame->getAsset();
    assetEntry.preissuedAssetSigner = mAssetChangePreissuedSigner.accountID;
    AssetHelperLegacy::Instance()->storeChange(delta, db, assetFrame->mEntry);
    innerResult().code(ManageAssetResultCode::SUCCESS);
    innerResult().success().requestID = 0;
    innerResult().success().fulfilled = true;
    return true;
}

bool ChangeAssetPreIssuerOpFrame::doCheckValid(Application& app)
{
    return true;
}

string ChangeAssetPreIssuerOpFrame::getAssetCode() const
{
    return mAssetChangePreissuedSigner.code;
}

Hash
ChangeAssetPreIssuerOpFrame::getSignatureData(AssetCode const & assetCode,
                                              AccountID const& newPreIssuer)
{
    std::string rawSignatureData = assetCode + ":" + PubKeyUtils::toStrKey(newPreIssuer);
    return Hash(sha256(rawSignatureData));
}

bool
ChangeAssetPreIssuerOpFrame::isSignatureValid(AssetFrame::pointer asset,
                                              LedgerVersion version)
{
    auto signatureData = getSignatureData(mAssetChangePreissuedSigner.code,
            mAssetChangePreissuedSigner.accountID);
    auto signatureValidator = SignatureValidatorImpl(signatureData, {mAssetChangePreissuedSigner.signature});

    const int VALID_SIGNATURES_REQUIRED = 1;
    SignatureValidator::Result result = signatureValidator.check({ asset->getPreIssuedAssetSigner() }, VALID_SIGNATURES_REQUIRED, version);
    return result == SignatureValidator::Result::SUCCESS;
}
}
