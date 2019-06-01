#pragma once
#include "xdr/ledger-entries.h"
#include "xdr/ledger.h"
#include "xdr/overlay.h"
#include "xdr/transaction.h"
#include "xdr/types.h"

namespace stellar
{

std::string xdr_printer(const PublicKey& pk);
}
