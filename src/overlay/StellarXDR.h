#pragma once
#include "xdr/Tokend-ledger-entries.h"
#include "xdr/Tokend-ledger.h"
#include "xdr/Tokend-overlay.h"
#include "xdr/Tokend-transaction.h"
#include "xdr/Tokend-types.h"

namespace stellar
{

std::string xdr_printer(const PublicKey& pk);
}
