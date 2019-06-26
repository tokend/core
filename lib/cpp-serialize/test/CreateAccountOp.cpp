//
// Created by artem on 11.06.19.
//

#include <iostream>
#include "CreateAccountOp.h"
#include "../src/unmarshaler.h"
#include "../src/unmarshaler.t.hpp"

using namespace xdr;


bool
CreateAccountOp::to_bytes(xdr::marshaler& m)
{

    return true;
}

bool
CreateAccountOp::from_bytes(xdr::unmarshaler& u)
{
    u.from_bytes(destination);
    u.from_bytes(referrer);
    u.from_bytes(roleID);
    u.from_bytes(signersData);
    u.from_bytes(ext);

    return true;
}

bool CreateAccountOp::operator==(xdr_abstract const &other)
{
    std::cout << typeid(*this).name() << std::endl;
    std::cout << typeid(this).name() << std::endl;
    std::cout << typeid(other).name() << std::endl;
    std::cout << typeid(&other).name() << std::endl;

    if (typeid(*this) != typeid(other))
    {
        return false;
    }

    auto& op = dynamic_cast<CreateAccountOp const&>(other);

    std::cout << typeid(&op).name() << std::endl;
    std::cout << typeid(op).name() << std::endl;


    return true;
}
/*

bool
CreateAccountOp::operator==(CreateAccountOp const &other)
{
    if ((this->referrer == nullptr) && (other.referrer == nullptr))
    {

    }

    return (this->destination == other.destination) && ()
}
*/

