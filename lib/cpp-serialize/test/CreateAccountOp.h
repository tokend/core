#pragma once

#include <bits/unique_ptr.h>
#include "../src/xdr_abstract.h"
#include "types.h"
#include "ManageSignerOp.h"
#include <vector>

using namespace xdr;

class CreateAccountOp : public xdr_abstract
{
public:
    AccountID destination;
    std::unique_ptr<AccountID> referrer;
    uint64 roleID;

    std::vector<UpdateSignerData> signersData;


    using CreateAccountOpExt = EmptyExt;
    CreateAccountOpExt ext;

    bool
    operator==(xdr_abstract const& other) override;

private:
    bool
    from_bytes(unmarshaler& u) override;

    bool
    to_bytes(marshaler& m) override;

};

