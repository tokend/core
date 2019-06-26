#include "marshal.h"

namespace xdr
{

void
message_t::shrink(std::size_t newsize)
{
    if (newsize > size_)
        throw std::out_of_range("message_t::shrink new size bigger than old");
    size_ = newsize;
    *reinterpret_cast<std::uint32_t *>(raw_data()) =
            swap32le(size32(newsize) | 0x80000000);
}

msg_ptr
message_t::alloc(std::size_t size)
{
    assert(size < 0x80000000);
    void *raw = operator new(offsetof(message_t, buf_[size + 4]));
    if (!raw)
        throw std::bad_alloc();
    message_t *m = new (raw) message_t (size);
    *reinterpret_cast<std::uint32_t *>(m->raw_data()) =
            swap32le(size32(size) | 0x80000000);
    return msg_ptr(m);
}


}