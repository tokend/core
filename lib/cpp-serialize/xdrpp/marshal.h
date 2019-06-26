#pragma once

#include "../src/measurer.h"
#include "../src/marshaler.h"
#include "../src/unmarshaler.h"
#include "../src/types.h"
#include "../src/marshaler.t.hpp"
#include "../src/unmarshaler.t.hpp"
#include "../src/measurer.t.hpp"
#include "message.h"
#include "types.h"


namespace xdr
{
using xdr_get = unmarshaler;

using xdr_put = marshaler;

template<typename T> size_t
xdr_size(T const& t)
{
    xdr::measurer m;
    m.count_size(t);

    return m.get_size();
}

inline std::size_t
xdr_argpack_size()
{
    return 0;
}

template<typename T, typename...Args>
inline std::size_t
xdr_argpack_size(const T &t, const Args &...a)
{
    return xdr_size(t) + xdr_argpack_size(a...);
}

template<typename...Args>
opaque_vec<>
xdr_to_opaque(const Args &...args)
{
    opaque_vec<> m (opaque_vec<>::size_type {xdr_argpack_size(args...)});
    xdr_put p (m.data(), m.data()+m.size());
    xdr_argpack_archive(p, args...);
    //assert(p. == p.e_); use done
    return m;
}

inline void
xdr_argpack_archive(xdr_get &)
{
}

template<typename T, typename...Args> inline void
xdr_argpack_archive(xdr_get &g, T &&t, Args &&...args)
{
    if (!g.from_bytes(t))
    {
        throw std::runtime_error(g.get_error());
    }
    xdr_argpack_archive(g, std::forward<Args>(args)...);
}

inline void
xdr_argpack_archive(xdr_put &)
{
}

template<typename T, typename...Args> inline void
xdr_argpack_archive(xdr_put &g, T &&t, Args &&...args)
{
    if (!g.to_bytes(t))
    {
        throw std::runtime_error(g.get_error());
    }
    xdr_argpack_archive(g, std::forward<Args>(args)...);
}

template<typename Bytes, typename...Args>
void
xdr_from_opaque(const Bytes &m, Args &...args)
{
    xdr_get g(m.data(), m.data()+m.size());
    xdr_argpack_archive(g, args...);
    g.done();
}

template<typename...Args>
msg_ptr
xdr_to_msg(const Args &...args)
{
    msg_ptr m (message_t::alloc(xdr_argpack_size(args...)));
    xdr_put p (m->data(), m->end());
    xdr_argpack_archive(p, args...);
    //assert(p.p_ == p.e_); use done
    return m;
}

template<typename...Args>
void
xdr_from_msg(const msg_ptr &m, Args &...args)
{
    xdr_get g(m->data(), m->end());
    xdr_argpack_archive(g, args...);
    g.done();
}

}