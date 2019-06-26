#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <cstring>
#include <sys/socket.h>

namespace xdr {

class message_t;
using msg_ptr = std::unique_ptr<message_t>;

class message_t
{
    std::unique_ptr<sockaddr> peer_;
    std::size_t size_;
    alignas(std::uint32_t) char buf_[4];
    message_t(std::size_t size) : size_(size) {}
public:
    std::size_t size() const { return size_; }
    void shrink(std::size_t newsize);
    char *data() { return buf_ + 4; }
    const char *data() const { return buf_ + 4; }
    const uint32_t word(std::ptrdiff_t i) const {
        return reinterpret_cast<const uint32_t *>(data())[i];
    }

    char *end() { return buf_ + 4 + size_; }
    const char *end() const { return buf_ + 4 + size_; }

    char *raw_data() { return buf_; }
    const char *raw_data() const { return buf_; }

    std::size_t raw_size() const { return size_ + 4; }


    const sockaddr *peer() const { return peer_.get(); }

    std::unique_ptr<sockaddr> &&unique_peer() { return std::move(peer_); }


    static msg_ptr alloc(std::size_t size);
};

static_assert(std::is_standard_layout<message_t>::value,
              "message_t should be standard layout");


}

