#pragma once


namespace xdr
{
class unmarshaler;
class marshaler;
class measurer;

struct xdr_abstract
{
    xdr_abstract() = default;

    virtual bool
    from_bytes(unmarshaler& u) = 0;

    virtual bool
    to_bytes(marshaler& m) const = 0;

    virtual void
    count_size(measurer& s) const = 0;

    virtual bool
    operator==(xdr_abstract const& other) const = 0;

    virtual bool
    operator<(xdr_abstract const& other) const = 0;

// just not allow to build on big endian machines
#if XDRPP_WORDS_BIGENDIAN
    virtual bool
    swap() = 0;
#endif
};

}