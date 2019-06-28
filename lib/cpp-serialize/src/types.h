#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include "xdr_abstract.h"


namespace xdr
{

template <typename T>
bool
operator==(xdr_abstract& a, xdr_abstract& b);

template <typename T>
bool
operator<(xdr_abstract& a, xdr_abstract& b);

struct xdr_runtime_error : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

struct xdr_bad_discriminant : xdr_runtime_error
{
    using xdr_runtime_error::xdr_runtime_error;
};

struct xdr_wrong_union : std::logic_error
{
    using std::logic_error::logic_error;
};

static constexpr const uint32_t XDR_MAX_LEN = 0xfffffffc;

template<typename T, uint32_t N>
struct xarray : std::array<T, size_t(N)>
{
    using array = std::array<T, size_t(N)>;
    xarray()
    {
        array::fill(T{});
    }
    xarray(const xarray &) = default;
    xarray &operator=(const xarray &) = default;

    void resize(uint32_t n)
    {
    }

};

template<uint32_t N = XDR_MAX_LEN>
struct xstring : std::string
{
    using string = std::string;
    using string::operator=;

#if !MSVC
    xstring() = default;
    xstring(const xstring &) = default;
    xstring(xstring &&) = default;
    xstring &operator=(const xstring &) = default;
    xstring &operator=(xstring &&) = default;
#endif // !MSVC

    template<typename...Args>
    xstring(Args&&...args) : string(std::forward<Args>(args)...)
    {
        //validate();
    }

#define ASSIGN_LIKE(method)					\
  template<typename...Args> xstring &method(Args&&...args) {	\
    string::method(std::forward<Args>(args)...);		\
    return *this;						\
  }
    ASSIGN_LIKE(operator=)
    ASSIGN_LIKE(operator+=)
    ASSIGN_LIKE(append)
    ASSIGN_LIKE(push_back)
    ASSIGN_LIKE(assign)
    ASSIGN_LIKE(insert)
    ASSIGN_LIKE(replace)
    ASSIGN_LIKE(swap)
#undef ASSIGN_LIKE
};

template <uint32_t N>
struct opaque_array : xarray<uint8_t, N>
{

};

template<typename T, uint32_t N = XDR_MAX_LEN>
struct xvector : std::vector<T>
{
    using vector = std::vector<T>;
    using vector::vector;

    void resize(uint32_t n)
    {
        //check_size(n);
        vector::resize(n);
    }

    static constexpr uint32_t
    max_size()
    {
        return N;
    }

    void
    append(const T *elems, std::size_t n)
    {
        //check_size(this->size() + n)
        this->insert(this->end(), elems, elems + n);
    }
};
template <uint32_t N = XDR_MAX_LEN>
using opaque_vec = xvector<uint8_t, N>;

template <typename T>
struct pointer : std::unique_ptr<T>
{
    using std::unique_ptr<T>::unique_ptr;

    pointer() = default;
    pointer(const pointer &p) : std::unique_ptr<T>(p ? new T(*p) : nullptr) {}
    pointer &operator=(const pointer &up)
    {
        if (const T *tp = up.get())
        {
            if (T *selfp = this->get())
            {
                *selfp = *tp;
            }
            else
                this->reset(new T(*tp));
        }
        else
            this->reset();
        return *this;
    }

    T&
    activate()
    {
        if (!*this)
        {
            this->reset(new T{});
        }

        return *this->get();
    }

    friend bool
    operator==(const pointer &a, const pointer &b)
    {
        return (!a && !b) || (a && b && (*a == *b));
    }
};

inline uint32_t
size32(std::size_t s)
{
    uint32_t r {uint32_t(s)};
    assert(s == r);
    return r;
}

}
