#pragma once

#include "../src/xdr_abstract.h"
#include "types.h"

using namespace xdr;

class UpdateSignerData : public xdr_abstract
{
public:
    PublicKey publicKey;
    uint64 roleID;
    uint32 weight;
    uint32 identity;

    longstring details;

    EmptyExt ext;

    bool
    operator==(xdr_abstract const& other) override { return  true; }

private:
    bool
    from_bytes(unmarshaler& u) override;

    bool
    to_bytes(marshaler& m) override;
};


class ManageSignerOp
{

};

