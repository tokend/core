//
// Created by artem on 11.06.19.
//

#include "ManageSignerOp.h"
#include "../src/unmarshaler.h"

using namespace xdr;

bool
UpdateSignerData::to_bytes(xdr::marshaler& m)
{

}

bool
UpdateSignerData::from_bytes(xdr::unmarshaler& u)
{
    u.from_bytes(publicKey);
    u.from_bytes(roleID);
    u.from_bytes(weight);
    u.from_bytes(identity);
    u.from_bytes(details);
    u.from_bytes(ext);
}