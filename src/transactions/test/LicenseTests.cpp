// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#include "main/Application.h"
#include "util/Timer.h"
#include "main/Config.h"
#include "overlay/LoopbackPeer.h"
#include "test/test.h"
#include "TxTests.h"
#include "ledger/LedgerDeltaImpl.h"
#include "test_helper/StampTestHelper.h"
#include "test_helper/LicenseTestHelper.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("license", "[tx][license]")
{
    auto wiredKey = SecretKey::random();
    auto wiredKeys = std::vector<SecretKey>{wiredKey};
    auto devWiredKey = SecretKey::random();
    auto devWiredKeys = std::vector<SecretKey>{devWiredKey};

    Config cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    cfg.WIRED_KEYS.emplace_back(wiredKey.getPublicKey());
    cfg.DEV_LICENSE_KEYS.emplace_back(devWiredKey.getPublicKey());
    VirtualClock clock;
    auto const appPtr = Application::create(clock, cfg);
    auto& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);
    LedgerDeltaImpl delta(app.getLedgerManager().getCurrentLedgerHeader(),
                          app.getDatabase());

    StampTestHelper stampTestHelper(testManager);
    LicenseTestHelper licenseTestHelper(testManager);
    auto root = Account{getRoot(), Salt(0)};

    SECTION("Success")
    {
        uint64_t adminCount = 10;
        uint64_t dueDate = 1000;
        auto stampResult = stampTestHelper.applyStamp(root);
        auto stampSuccess = stampResult.success();
        auto licenseResult = licenseTestHelper.applyLicenseOp(root,
                                                              wiredKeys,
                                                              stampSuccess.ledgerHash,
                                                              stampSuccess.licenseHash,
                                                              adminCount,
                                                              dueDate
        );

        SECTION("prolongation")
        {
            uint64_t adminCount = 12;
            uint64_t dueDate = 2000;
            auto stampResult = stampTestHelper.applyStamp(root);
            auto stampSuccess = stampResult.success();
            licenseTestHelper.applyLicenseOp(root,
                                             wiredKeys,
                                             stampSuccess.ledgerHash,
                                             stampSuccess.licenseHash,
                                             adminCount,
                                             dueDate
            );
        }
    }

    SECTION("With dev keys")
    {
        uint64_t adminCount = 10;
        uint64_t dueDate = 1000;
        auto stampResult = stampTestHelper.applyStamp(root);
        auto stampSuccess = stampResult.success();
        auto licenseResult = licenseTestHelper.applyLicenseOp(root,
                                                              devWiredKeys,
                                                              stampSuccess.ledgerHash,
                                                              stampSuccess.licenseHash,
                                                              adminCount,
                                                              dueDate
        );

        SECTION("prolongation")
        {
            uint64_t adminCount = 12;
            uint64_t dueDate = 2000;
            auto stampResult = stampTestHelper.applyStamp(root);
            auto stampSuccess = stampResult.success();
            licenseTestHelper.applyLicenseOp(root,
                                             devWiredKeys,
                                             stampSuccess.ledgerHash,
                                             stampSuccess.licenseHash,
                                             adminCount,
                                             dueDate
            );
        }
    }

    SECTION("Bad due date")
    {
        uint64_t adminCount = 10;
        uint64_t dueDate = 100L;
        testManager->advanceToTime(1000);
        auto stampResult = stampTestHelper.applyStamp(root);
        auto stampSuccess = stampResult.success();
        auto licenseResult = licenseTestHelper.applyLicenseOp(root,
                                                              wiredKeys,
                                                              stampSuccess.ledgerHash,
                                                              stampSuccess.licenseHash,
                                                              adminCount,
                                                              dueDate,
                                                              LicenseResultCode::INVALID_DUE_DATE
        );
    }
    SECTION("Bad signature")
    {
        auto wiredKey = SecretKey::random();
        auto wiredKeys = std::vector<SecretKey>{wiredKey};
        uint64_t adminCount = 10;
        uint64_t dueDate = 1650928145L;
        auto stampResult = stampTestHelper.applyStamp(root);
        auto stampSuccess = stampResult.success();
        auto licenseResult = licenseTestHelper.applyLicenseOp(root,
                                                              wiredKeys,
                                                              stampSuccess.ledgerHash,
                                                              stampSuccess.licenseHash,
                                                              adminCount,
                                                              dueDate,
                                                              LicenseResultCode::INVALID_SIGNATURE
        );
    }

    SECTION("Bad stamp")
    {
        uint64_t adminCount = 10;
        uint64_t dueDate = 1650928145L;
        auto stampResult = stampTestHelper.applyStamp(root);
        auto stampSuccess = stampResult.success();

        Hash ledgerHash, licenseHash;

        auto licenseResult = licenseTestHelper.applyLicenseOp(root,
                                                              wiredKeys,
                                                              ledgerHash,
                                                              licenseHash,
                                                              adminCount,
                                                              dueDate,
                                                              LicenseResultCode::INVALID_STAMP
        );
    }

    SECTION("Too many signatures")
    {
        uint64_t adminCount = 10;
        uint64_t dueDate = 1650928145L;
        auto stampResult = stampTestHelper.applyStamp(root);
        auto stampSuccess = stampResult.success();

        Hash ledgerHash, licenseHash;

        auto licenseResult = licenseTestHelper.applyLicenseOp(
            root, {wiredKey, wiredKey}, ledgerHash, licenseHash, adminCount,
            dueDate, LicenseResultCode::EXTRA_SIGNATURES);
    }

}
