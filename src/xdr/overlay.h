// -*- C++ -*-
// Automatically generated from overlay.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OVERLAY_H_INCLUDED__
#define __XDR_OVERLAY_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger.h"

namespace stellar {

enum class ErrorCode : std::int32_t {
  MISC = 0,
  DATA = 1,
  CONF = 2,
  AUTH = 3,
  LOAD = 4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ErrorCode>
  : xdr_integral_base<::stellar::ErrorCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ErrorCode val) {
    switch (val) {
    case ::stellar::ErrorCode::MISC:
      return "MISC";
    case ::stellar::ErrorCode::DATA:
      return "DATA";
    case ::stellar::ErrorCode::CONF:
      return "CONF";
    case ::stellar::ErrorCode::AUTH:
      return "AUTH";
    case ::stellar::ErrorCode::LOAD:
      return "LOAD";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ErrorCode::MISC,
      (int32_t)::stellar::ErrorCode::DATA,
      (int32_t)::stellar::ErrorCode::CONF,
      (int32_t)::stellar::ErrorCode::AUTH,
      (int32_t)::stellar::ErrorCode::LOAD
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct Error  : xdr::xdr_abstract {
  ErrorCode code{};
  xdr::xstring<100> msg{};

  Error() = default;
  template<typename _code_T,
           typename _msg_T,
           typename = typename
           std::enable_if<std::is_constructible<ErrorCode, _code_T>::value
                          && std::is_constructible<xdr::xstring<100>, _msg_T>::value
                         >::type>
  explicit Error(_code_T &&_code,
                 _msg_T &&_msg)
    : code(std::forward<_code_T>(_code)),
      msg(std::forward<_msg_T>(_msg)) {}
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

struct AuthCert  : xdr::xdr_abstract {
  Curve25519Public pubkey{};
  uint64 expiration{};
  Signature sig{};

  AuthCert() = default;
  template<typename _pubkey_T,
           typename _expiration_T,
           typename _sig_T,
           typename = typename
           std::enable_if<std::is_constructible<Curve25519Public, _pubkey_T>::value
                          && std::is_constructible<uint64, _expiration_T>::value
                          && std::is_constructible<Signature, _sig_T>::value
                         >::type>
  explicit AuthCert(_pubkey_T &&_pubkey,
                    _expiration_T &&_expiration,
                    _sig_T &&_sig)
    : pubkey(std::forward<_pubkey_T>(_pubkey)),
      expiration(std::forward<_expiration_T>(_expiration)),
      sig(std::forward<_sig_T>(_sig)) {}
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

struct Hello  : xdr::xdr_abstract {
  uint32 ledgerVersion{};
  uint32 overlayVersion{};
  uint32 overlayMinVersion{};
  Hash networkID{};
  xdr::xstring<100> versionStr{};
  std::int32_t listeningPort{};
  NodeID peerID{};
  AuthCert cert{};
  uint256 nonce{};

  Hello() = default;
  template<typename _ledgerVersion_T,
           typename _overlayVersion_T,
           typename _overlayMinVersion_T,
           typename _networkID_T,
           typename _versionStr_T,
           typename _listeningPort_T,
           typename _peerID_T,
           typename _cert_T,
           typename _nonce_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerVersion_T>::value
                          && std::is_constructible<uint32, _overlayVersion_T>::value
                          && std::is_constructible<uint32, _overlayMinVersion_T>::value
                          && std::is_constructible<Hash, _networkID_T>::value
                          && std::is_constructible<xdr::xstring<100>, _versionStr_T>::value
                          && std::is_constructible<std::int32_t, _listeningPort_T>::value
                          && std::is_constructible<NodeID, _peerID_T>::value
                          && std::is_constructible<AuthCert, _cert_T>::value
                          && std::is_constructible<uint256, _nonce_T>::value
                         >::type>
  explicit Hello(_ledgerVersion_T &&_ledgerVersion,
                 _overlayVersion_T &&_overlayVersion,
                 _overlayMinVersion_T &&_overlayMinVersion,
                 _networkID_T &&_networkID,
                 _versionStr_T &&_versionStr,
                 _listeningPort_T &&_listeningPort,
                 _peerID_T &&_peerID,
                 _cert_T &&_cert,
                 _nonce_T &&_nonce)
    : ledgerVersion(std::forward<_ledgerVersion_T>(_ledgerVersion)),
      overlayVersion(std::forward<_overlayVersion_T>(_overlayVersion)),
      overlayMinVersion(std::forward<_overlayMinVersion_T>(_overlayMinVersion)),
      networkID(std::forward<_networkID_T>(_networkID)),
      versionStr(std::forward<_versionStr_T>(_versionStr)),
      listeningPort(std::forward<_listeningPort_T>(_listeningPort)),
      peerID(std::forward<_peerID_T>(_peerID)),
      cert(std::forward<_cert_T>(_cert)),
      nonce(std::forward<_nonce_T>(_nonce)) {}
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

struct Auth  : xdr::xdr_abstract {
  std::int32_t unused{};

  Auth() = default;
  template<typename _unused_T,
           typename = typename
           std::enable_if<std::is_constructible<std::int32_t, _unused_T>::value
                         >::type>
  explicit Auth(_unused_T &&_unused)
    : unused(std::forward<_unused_T>(_unused)) {}
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

enum class IPAddrType : std::int32_t {
  IPv4 = 0,
  IPv6 = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::IPAddrType>
  : xdr_integral_base<::stellar::IPAddrType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::IPAddrType val) {
    switch (val) {
    case ::stellar::IPAddrType::IPv4:
      return "IPv4";
    case ::stellar::IPAddrType::IPv6:
      return "IPv6";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::IPAddrType::IPv4,
      (int32_t)::stellar::IPAddrType::IPv6
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct PeerAddress  : xdr::xdr_abstract {
  struct _ip_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<IPAddrType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      xdr::opaque_array<4> ipv4_;
      xdr::opaque_array<16> ipv6_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<IPAddrType> &_xdr_case_values() {
      static const std::vector<IPAddrType> _xdr_disc_vec {
        IPAddrType::IPv4,
        IPAddrType::IPv6
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)IPAddrType::IPv4 ? 1
        : which == (int32_t)IPAddrType::IPv6 ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)IPAddrType::IPv4:
        _f(&_ip_t::ipv4_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)IPAddrType::IPv6:
        _f(&_ip_t::ipv6_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _ip_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_ip_t();
        type_ = which;switch (type_)
{
        case (int32_t)IPAddrType::IPv4:
new(&ipv4_) xdr::opaque_array<4>{};
break;
        case (int32_t)IPAddrType::IPv6:
new(&ipv6_) xdr::opaque_array<16>{};
break;
}

      }
      else
        type_ = which;
    }
    explicit _ip_t(IPAddrType which = IPAddrType{}) : type_((int32_t)which) {
      switch (type_)
{
      case (int32_t)IPAddrType::IPv4:
new(&ipv4_) xdr::opaque_array<4>{};
break;
      case (int32_t)IPAddrType::IPv6:
new(&ipv6_) xdr::opaque_array<16>{};
break;
}

    }
    _ip_t(const _ip_t &source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)IPAddrType::IPv4:
new(&ipv4_) xdr::opaque_array<4>(source.ipv4_);
break;
      case (int32_t)IPAddrType::IPv6:
new(&ipv6_) xdr::opaque_array<16>(source.ipv6_);
break;
}

    }
    _ip_t(_ip_t &&source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)IPAddrType::IPv4:
new(&ipv4_) xdr::opaque_array<4>(std::move(source.ipv4_));
break;
      case (int32_t)IPAddrType::IPv6:
new(&ipv6_) xdr::opaque_array<16>(std::move(source.ipv6_));
break;
}

    }
    ~_ip_t() {
switch (type_)
{
    case (int32_t)IPAddrType::IPv4:
ipv4_.~opaque_array<4>();
break;
    case (int32_t)IPAddrType::IPv6:
ipv6_.~opaque_array<16>();
break;
}
}

    _ip_t &operator=(const _ip_t &source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)IPAddrType::IPv4:
ipv4_ = source.ipv4_;
break;
      case (int32_t)IPAddrType::IPv6:
ipv6_ = source.ipv6_;
break;
}
}
else {this->~_ip_t();
      type_ = source.type_;
switch (type_)
{
      case (int32_t)IPAddrType::IPv4:
new(&ipv4_) xdr::opaque_array<4>(source.ipv4_);
break;
      case (int32_t)IPAddrType::IPv6:
new(&ipv6_) xdr::opaque_array<16>(source.ipv6_);
break;
}
}
      return *this;
    }
    _ip_t &operator=(_ip_t &&source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)IPAddrType::IPv4:
ipv4_ = std::move(source.ipv4_);
break;
      case (int32_t)IPAddrType::IPv6:
ipv6_ = std::move(source.ipv6_);
break;
}
}
else {this->~_ip_t();
      type_ = std::move(source.type_);
switch (type_)
{
      case (int32_t)IPAddrType::IPv4:
new(&ipv4_) xdr::opaque_array<4>(std::move(source.ipv4_));
break;
      case (int32_t)IPAddrType::IPv6:
new(&ipv6_) xdr::opaque_array<16>(std::move(source.ipv6_));
break;
}
}
      return *this;
    }

    IPAddrType type() const { return IPAddrType(type_); }
    _ip_t &type(IPAddrType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    xdr::opaque_array<4> &ipv4() {
      if (_xdr_field_number(type_) == 1)
        return ipv4_;
      throw xdr::xdr_wrong_union("_ip_t: ipv4 accessed when not selected");
    }
    const xdr::opaque_array<4> &ipv4() const {
      if (_xdr_field_number(type_) == 1)
        return ipv4_;
      throw xdr::xdr_wrong_union("_ip_t: ipv4 accessed when not selected");
    }
    xdr::opaque_array<16> &ipv6() {
      if (_xdr_field_number(type_) == 2)
        return ipv6_;
      throw xdr::xdr_wrong_union("_ip_t: ipv6 accessed when not selected");
    }
    const xdr::opaque_array<16> &ipv6() const {
      if (_xdr_field_number(type_) == 2)
        return ipv6_;
      throw xdr::xdr_wrong_union("_ip_t: ipv6 accessed when not selected");
    }bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
    bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

  };

  _ip_t ip{};
  uint32 port{};
  uint32 numFailures{};

  PeerAddress() = default;
  template<typename _ip_T,
           typename _port_T,
           typename _numFailures_T,
           typename = typename
           std::enable_if<std::is_constructible<_ip_t, _ip_T>::value
                          && std::is_constructible<uint32, _port_T>::value
                          && std::is_constructible<uint32, _numFailures_T>::value
                         >::type>
  explicit PeerAddress(_ip_T &&_ip,
                       _port_T &&_port,
                       _numFailures_T &&_numFailures)
    : ip(std::forward<_ip_T>(_ip)),
      port(std::forward<_port_T>(_port)),
      numFailures(std::forward<_numFailures_T>(_numFailures)) {}
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

enum class MessageType : std::int32_t {
  ERROR_MSG = 0,
  AUTH = 2,
  DONT_HAVE = 3,
  GET_PEERS = 4,
  PEERS = 5,
  GET_TX_SET = 6,
  TX_SET = 7,
  TRANSACTION = 8,
  GET_SCP_QUORUMSET = 9,
  SCP_QUORUMSET = 10,
  SCP_MESSAGE = 11,
  GET_SCP_STATE = 12,
  HELLO = 13,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::MessageType>
  : xdr_integral_base<::stellar::MessageType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::MessageType val) {
    switch (val) {
    case ::stellar::MessageType::ERROR_MSG:
      return "ERROR_MSG";
    case ::stellar::MessageType::AUTH:
      return "AUTH";
    case ::stellar::MessageType::DONT_HAVE:
      return "DONT_HAVE";
    case ::stellar::MessageType::GET_PEERS:
      return "GET_PEERS";
    case ::stellar::MessageType::PEERS:
      return "PEERS";
    case ::stellar::MessageType::GET_TX_SET:
      return "GET_TX_SET";
    case ::stellar::MessageType::TX_SET:
      return "TX_SET";
    case ::stellar::MessageType::TRANSACTION:
      return "TRANSACTION";
    case ::stellar::MessageType::GET_SCP_QUORUMSET:
      return "GET_SCP_QUORUMSET";
    case ::stellar::MessageType::SCP_QUORUMSET:
      return "SCP_QUORUMSET";
    case ::stellar::MessageType::SCP_MESSAGE:
      return "SCP_MESSAGE";
    case ::stellar::MessageType::GET_SCP_STATE:
      return "GET_SCP_STATE";
    case ::stellar::MessageType::HELLO:
      return "HELLO";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::MessageType::ERROR_MSG,
      (int32_t)::stellar::MessageType::AUTH,
      (int32_t)::stellar::MessageType::DONT_HAVE,
      (int32_t)::stellar::MessageType::GET_PEERS,
      (int32_t)::stellar::MessageType::PEERS,
      (int32_t)::stellar::MessageType::GET_TX_SET,
      (int32_t)::stellar::MessageType::TX_SET,
      (int32_t)::stellar::MessageType::TRANSACTION,
      (int32_t)::stellar::MessageType::GET_SCP_QUORUMSET,
      (int32_t)::stellar::MessageType::SCP_QUORUMSET,
      (int32_t)::stellar::MessageType::SCP_MESSAGE,
      (int32_t)::stellar::MessageType::GET_SCP_STATE,
      (int32_t)::stellar::MessageType::HELLO
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct DontHave  : xdr::xdr_abstract {
  MessageType type{};
  uint256 reqHash{};

  DontHave() = default;
  template<typename _type_T,
           typename _reqHash_T,
           typename = typename
           std::enable_if<std::is_constructible<MessageType, _type_T>::value
                          && std::is_constructible<uint256, _reqHash_T>::value
                         >::type>
  explicit DontHave(_type_T &&_type,
                    _reqHash_T &&_reqHash)
    : type(std::forward<_type_T>(_type)),
      reqHash(std::forward<_reqHash_T>(_reqHash)) {}
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

struct StellarMessage : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<MessageType>::case_type;
private:
  _xdr_case_type type_;
  union {
    Error error_;
    Hello hello_;
    Auth auth_;
    DontHave dontHave_;
    xdr::xvector<PeerAddress> peers_;
    uint256 txSetHash_;
    TransactionSet txSet_;
    TransactionEnvelope transaction_;
    uint256 qSetHash_;
    SCPQuorumSet qSet_;
    SCPEnvelope envelope_;
    uint32 getSCPLedgerSeq_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<MessageType> &_xdr_case_values() {
    static const std::vector<MessageType> _xdr_disc_vec {
      MessageType::ERROR_MSG,
      MessageType::HELLO,
      MessageType::AUTH,
      MessageType::DONT_HAVE,
      MessageType::GET_PEERS,
      MessageType::PEERS,
      MessageType::GET_TX_SET,
      MessageType::TX_SET,
      MessageType::TRANSACTION,
      MessageType::GET_SCP_QUORUMSET,
      MessageType::SCP_QUORUMSET,
      MessageType::SCP_MESSAGE,
      MessageType::GET_SCP_STATE
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)MessageType::ERROR_MSG ? 1
      : which == (int32_t)MessageType::HELLO ? 2
      : which == (int32_t)MessageType::AUTH ? 3
      : which == (int32_t)MessageType::DONT_HAVE ? 4
      : which == (int32_t)MessageType::GET_PEERS ? 0
      : which == (int32_t)MessageType::PEERS ? 5
      : which == (int32_t)MessageType::GET_TX_SET ? 6
      : which == (int32_t)MessageType::TX_SET ? 7
      : which == (int32_t)MessageType::TRANSACTION ? 8
      : which == (int32_t)MessageType::GET_SCP_QUORUMSET ? 9
      : which == (int32_t)MessageType::SCP_QUORUMSET ? 10
      : which == (int32_t)MessageType::SCP_MESSAGE ? 11
      : which == (int32_t)MessageType::GET_SCP_STATE ? 12
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)MessageType::ERROR_MSG:
      _f(&StellarMessage::error_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::HELLO:
      _f(&StellarMessage::hello_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::AUTH:
      _f(&StellarMessage::auth_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::DONT_HAVE:
      _f(&StellarMessage::dontHave_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::GET_PEERS:
      return true;
    case (int32_t)MessageType::PEERS:
      _f(&StellarMessage::peers_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::GET_TX_SET:
      _f(&StellarMessage::txSetHash_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::TX_SET:
      _f(&StellarMessage::txSet_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::TRANSACTION:
      _f(&StellarMessage::transaction_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::GET_SCP_QUORUMSET:
      _f(&StellarMessage::qSetHash_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::SCP_QUORUMSET:
      _f(&StellarMessage::qSet_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::SCP_MESSAGE:
      _f(&StellarMessage::envelope_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MessageType::GET_SCP_STATE:
      _f(&StellarMessage::getSCPLedgerSeq_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in StellarMessage");
    if (fnum != _xdr_field_number(type_)) {
      this->~StellarMessage();
      type_ = which;switch (type_)
{
      case (int32_t)MessageType::ERROR_MSG:
new(&error_) Error{};
break;
      case (int32_t)MessageType::HELLO:
new(&hello_) Hello{};
break;
      case (int32_t)MessageType::AUTH:
new(&auth_) Auth{};
break;
      case (int32_t)MessageType::DONT_HAVE:
new(&dontHave_) DontHave{};
break;
      case (int32_t)MessageType::GET_PEERS:
        break;
      case (int32_t)MessageType::PEERS:
new(&peers_) xdr::xvector<PeerAddress>{};
break;
      case (int32_t)MessageType::GET_TX_SET:
new(&txSetHash_) uint256{};
break;
      case (int32_t)MessageType::TX_SET:
new(&txSet_) TransactionSet{};
break;
      case (int32_t)MessageType::TRANSACTION:
new(&transaction_) TransactionEnvelope{};
break;
      case (int32_t)MessageType::GET_SCP_QUORUMSET:
new(&qSetHash_) uint256{};
break;
      case (int32_t)MessageType::SCP_QUORUMSET:
new(&qSet_) SCPQuorumSet{};
break;
      case (int32_t)MessageType::SCP_MESSAGE:
new(&envelope_) SCPEnvelope{};
break;
      case (int32_t)MessageType::GET_SCP_STATE:
new(&getSCPLedgerSeq_) uint32{};
break;
}

    }
    else
      type_ = which;
  }
  explicit StellarMessage(MessageType which = MessageType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)MessageType::ERROR_MSG:
new(&error_) Error{};
break;
    case (int32_t)MessageType::HELLO:
new(&hello_) Hello{};
break;
    case (int32_t)MessageType::AUTH:
new(&auth_) Auth{};
break;
    case (int32_t)MessageType::DONT_HAVE:
new(&dontHave_) DontHave{};
break;
    case (int32_t)MessageType::GET_PEERS:
      break;
    case (int32_t)MessageType::PEERS:
new(&peers_) xdr::xvector<PeerAddress>{};
break;
    case (int32_t)MessageType::GET_TX_SET:
new(&txSetHash_) uint256{};
break;
    case (int32_t)MessageType::TX_SET:
new(&txSet_) TransactionSet{};
break;
    case (int32_t)MessageType::TRANSACTION:
new(&transaction_) TransactionEnvelope{};
break;
    case (int32_t)MessageType::GET_SCP_QUORUMSET:
new(&qSetHash_) uint256{};
break;
    case (int32_t)MessageType::SCP_QUORUMSET:
new(&qSet_) SCPQuorumSet{};
break;
    case (int32_t)MessageType::SCP_MESSAGE:
new(&envelope_) SCPEnvelope{};
break;
    case (int32_t)MessageType::GET_SCP_STATE:
new(&getSCPLedgerSeq_) uint32{};
break;
}

  }
  StellarMessage(const StellarMessage &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)MessageType::ERROR_MSG:
new(&error_) Error(source.error_);
break;
    case (int32_t)MessageType::HELLO:
new(&hello_) Hello(source.hello_);
break;
    case (int32_t)MessageType::AUTH:
new(&auth_) Auth(source.auth_);
break;
    case (int32_t)MessageType::DONT_HAVE:
new(&dontHave_) DontHave(source.dontHave_);
break;
    case (int32_t)MessageType::GET_PEERS:
      break;
    case (int32_t)MessageType::PEERS:
new(&peers_) xdr::xvector<PeerAddress>(source.peers_);
break;
    case (int32_t)MessageType::GET_TX_SET:
new(&txSetHash_) uint256(source.txSetHash_);
break;
    case (int32_t)MessageType::TX_SET:
new(&txSet_) TransactionSet(source.txSet_);
break;
    case (int32_t)MessageType::TRANSACTION:
new(&transaction_) TransactionEnvelope(source.transaction_);
break;
    case (int32_t)MessageType::GET_SCP_QUORUMSET:
new(&qSetHash_) uint256(source.qSetHash_);
break;
    case (int32_t)MessageType::SCP_QUORUMSET:
new(&qSet_) SCPQuorumSet(source.qSet_);
break;
    case (int32_t)MessageType::SCP_MESSAGE:
new(&envelope_) SCPEnvelope(source.envelope_);
break;
    case (int32_t)MessageType::GET_SCP_STATE:
new(&getSCPLedgerSeq_) uint32(source.getSCPLedgerSeq_);
break;
}

  }
  StellarMessage(StellarMessage &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)MessageType::ERROR_MSG:
new(&error_) Error(std::move(source.error_));
break;
    case (int32_t)MessageType::HELLO:
new(&hello_) Hello(std::move(source.hello_));
break;
    case (int32_t)MessageType::AUTH:
new(&auth_) Auth(std::move(source.auth_));
break;
    case (int32_t)MessageType::DONT_HAVE:
new(&dontHave_) DontHave(std::move(source.dontHave_));
break;
    case (int32_t)MessageType::GET_PEERS:
      break;
    case (int32_t)MessageType::PEERS:
new(&peers_) xdr::xvector<PeerAddress>(std::move(source.peers_));
break;
    case (int32_t)MessageType::GET_TX_SET:
new(&txSetHash_) uint256(std::move(source.txSetHash_));
break;
    case (int32_t)MessageType::TX_SET:
new(&txSet_) TransactionSet(std::move(source.txSet_));
break;
    case (int32_t)MessageType::TRANSACTION:
new(&transaction_) TransactionEnvelope(std::move(source.transaction_));
break;
    case (int32_t)MessageType::GET_SCP_QUORUMSET:
new(&qSetHash_) uint256(std::move(source.qSetHash_));
break;
    case (int32_t)MessageType::SCP_QUORUMSET:
new(&qSet_) SCPQuorumSet(std::move(source.qSet_));
break;
    case (int32_t)MessageType::SCP_MESSAGE:
new(&envelope_) SCPEnvelope(std::move(source.envelope_));
break;
    case (int32_t)MessageType::GET_SCP_STATE:
new(&getSCPLedgerSeq_) uint32(std::move(source.getSCPLedgerSeq_));
break;
}

  }
  ~StellarMessage() {
switch (type_)
{
  case (int32_t)MessageType::ERROR_MSG:
error_.~Error();
break;
  case (int32_t)MessageType::HELLO:
hello_.~Hello();
break;
  case (int32_t)MessageType::AUTH:
auth_.~Auth();
break;
  case (int32_t)MessageType::DONT_HAVE:
dontHave_.~DontHave();
break;
  case (int32_t)MessageType::GET_PEERS:
    break;
  case (int32_t)MessageType::PEERS:
peers_.~xvector<PeerAddress>();
break;
  case (int32_t)MessageType::GET_TX_SET:
txSetHash_.~uint256();
break;
  case (int32_t)MessageType::TX_SET:
txSet_.~TransactionSet();
break;
  case (int32_t)MessageType::TRANSACTION:
transaction_.~TransactionEnvelope();
break;
  case (int32_t)MessageType::GET_SCP_QUORUMSET:
qSetHash_.~uint256();
break;
  case (int32_t)MessageType::SCP_QUORUMSET:
qSet_.~SCPQuorumSet();
break;
  case (int32_t)MessageType::SCP_MESSAGE:
envelope_.~SCPEnvelope();
break;
  case (int32_t)MessageType::GET_SCP_STATE:
getSCPLedgerSeq_.~uint32();
break;
}
}

  StellarMessage &operator=(const StellarMessage &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)MessageType::ERROR_MSG:
error_ = source.error_;
break;
    case (int32_t)MessageType::HELLO:
hello_ = source.hello_;
break;
    case (int32_t)MessageType::AUTH:
auth_ = source.auth_;
break;
    case (int32_t)MessageType::DONT_HAVE:
dontHave_ = source.dontHave_;
break;
    case (int32_t)MessageType::GET_PEERS:
      break;
    case (int32_t)MessageType::PEERS:
peers_ = source.peers_;
break;
    case (int32_t)MessageType::GET_TX_SET:
txSetHash_ = source.txSetHash_;
break;
    case (int32_t)MessageType::TX_SET:
txSet_ = source.txSet_;
break;
    case (int32_t)MessageType::TRANSACTION:
transaction_ = source.transaction_;
break;
    case (int32_t)MessageType::GET_SCP_QUORUMSET:
qSetHash_ = source.qSetHash_;
break;
    case (int32_t)MessageType::SCP_QUORUMSET:
qSet_ = source.qSet_;
break;
    case (int32_t)MessageType::SCP_MESSAGE:
envelope_ = source.envelope_;
break;
    case (int32_t)MessageType::GET_SCP_STATE:
getSCPLedgerSeq_ = source.getSCPLedgerSeq_;
break;
}
}
else {this->~StellarMessage();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)MessageType::ERROR_MSG:
new(&error_) Error(source.error_);
break;
    case (int32_t)MessageType::HELLO:
new(&hello_) Hello(source.hello_);
break;
    case (int32_t)MessageType::AUTH:
new(&auth_) Auth(source.auth_);
break;
    case (int32_t)MessageType::DONT_HAVE:
new(&dontHave_) DontHave(source.dontHave_);
break;
    case (int32_t)MessageType::GET_PEERS:
      break;
    case (int32_t)MessageType::PEERS:
new(&peers_) xdr::xvector<PeerAddress>(source.peers_);
break;
    case (int32_t)MessageType::GET_TX_SET:
new(&txSetHash_) uint256(source.txSetHash_);
break;
    case (int32_t)MessageType::TX_SET:
new(&txSet_) TransactionSet(source.txSet_);
break;
    case (int32_t)MessageType::TRANSACTION:
new(&transaction_) TransactionEnvelope(source.transaction_);
break;
    case (int32_t)MessageType::GET_SCP_QUORUMSET:
new(&qSetHash_) uint256(source.qSetHash_);
break;
    case (int32_t)MessageType::SCP_QUORUMSET:
new(&qSet_) SCPQuorumSet(source.qSet_);
break;
    case (int32_t)MessageType::SCP_MESSAGE:
new(&envelope_) SCPEnvelope(source.envelope_);
break;
    case (int32_t)MessageType::GET_SCP_STATE:
new(&getSCPLedgerSeq_) uint32(source.getSCPLedgerSeq_);
break;
}
}
    return *this;
  }
  StellarMessage &operator=(StellarMessage &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)MessageType::ERROR_MSG:
error_ = std::move(source.error_);
break;
    case (int32_t)MessageType::HELLO:
hello_ = std::move(source.hello_);
break;
    case (int32_t)MessageType::AUTH:
auth_ = std::move(source.auth_);
break;
    case (int32_t)MessageType::DONT_HAVE:
dontHave_ = std::move(source.dontHave_);
break;
    case (int32_t)MessageType::GET_PEERS:
      break;
    case (int32_t)MessageType::PEERS:
peers_ = std::move(source.peers_);
break;
    case (int32_t)MessageType::GET_TX_SET:
txSetHash_ = std::move(source.txSetHash_);
break;
    case (int32_t)MessageType::TX_SET:
txSet_ = std::move(source.txSet_);
break;
    case (int32_t)MessageType::TRANSACTION:
transaction_ = std::move(source.transaction_);
break;
    case (int32_t)MessageType::GET_SCP_QUORUMSET:
qSetHash_ = std::move(source.qSetHash_);
break;
    case (int32_t)MessageType::SCP_QUORUMSET:
qSet_ = std::move(source.qSet_);
break;
    case (int32_t)MessageType::SCP_MESSAGE:
envelope_ = std::move(source.envelope_);
break;
    case (int32_t)MessageType::GET_SCP_STATE:
getSCPLedgerSeq_ = std::move(source.getSCPLedgerSeq_);
break;
}
}
else {this->~StellarMessage();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)MessageType::ERROR_MSG:
new(&error_) Error(std::move(source.error_));
break;
    case (int32_t)MessageType::HELLO:
new(&hello_) Hello(std::move(source.hello_));
break;
    case (int32_t)MessageType::AUTH:
new(&auth_) Auth(std::move(source.auth_));
break;
    case (int32_t)MessageType::DONT_HAVE:
new(&dontHave_) DontHave(std::move(source.dontHave_));
break;
    case (int32_t)MessageType::GET_PEERS:
      break;
    case (int32_t)MessageType::PEERS:
new(&peers_) xdr::xvector<PeerAddress>(std::move(source.peers_));
break;
    case (int32_t)MessageType::GET_TX_SET:
new(&txSetHash_) uint256(std::move(source.txSetHash_));
break;
    case (int32_t)MessageType::TX_SET:
new(&txSet_) TransactionSet(std::move(source.txSet_));
break;
    case (int32_t)MessageType::TRANSACTION:
new(&transaction_) TransactionEnvelope(std::move(source.transaction_));
break;
    case (int32_t)MessageType::GET_SCP_QUORUMSET:
new(&qSetHash_) uint256(std::move(source.qSetHash_));
break;
    case (int32_t)MessageType::SCP_QUORUMSET:
new(&qSet_) SCPQuorumSet(std::move(source.qSet_));
break;
    case (int32_t)MessageType::SCP_MESSAGE:
new(&envelope_) SCPEnvelope(std::move(source.envelope_));
break;
    case (int32_t)MessageType::GET_SCP_STATE:
new(&getSCPLedgerSeq_) uint32(std::move(source.getSCPLedgerSeq_));
break;
}
}
    return *this;
  }

  MessageType type() const { return MessageType(type_); }
  StellarMessage &type(MessageType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  Error &error() {
    if (_xdr_field_number(type_) == 1)
      return error_;
    throw xdr::xdr_wrong_union("StellarMessage: error accessed when not selected");
  }
  const Error &error() const {
    if (_xdr_field_number(type_) == 1)
      return error_;
    throw xdr::xdr_wrong_union("StellarMessage: error accessed when not selected");
  }
  Hello &hello() {
    if (_xdr_field_number(type_) == 2)
      return hello_;
    throw xdr::xdr_wrong_union("StellarMessage: hello accessed when not selected");
  }
  const Hello &hello() const {
    if (_xdr_field_number(type_) == 2)
      return hello_;
    throw xdr::xdr_wrong_union("StellarMessage: hello accessed when not selected");
  }
  Auth &auth() {
    if (_xdr_field_number(type_) == 3)
      return auth_;
    throw xdr::xdr_wrong_union("StellarMessage: auth accessed when not selected");
  }
  const Auth &auth() const {
    if (_xdr_field_number(type_) == 3)
      return auth_;
    throw xdr::xdr_wrong_union("StellarMessage: auth accessed when not selected");
  }
  DontHave &dontHave() {
    if (_xdr_field_number(type_) == 4)
      return dontHave_;
    throw xdr::xdr_wrong_union("StellarMessage: dontHave accessed when not selected");
  }
  const DontHave &dontHave() const {
    if (_xdr_field_number(type_) == 4)
      return dontHave_;
    throw xdr::xdr_wrong_union("StellarMessage: dontHave accessed when not selected");
  }
  xdr::xvector<PeerAddress> &peers() {
    if (_xdr_field_number(type_) == 5)
      return peers_;
    throw xdr::xdr_wrong_union("StellarMessage: peers accessed when not selected");
  }
  const xdr::xvector<PeerAddress> &peers() const {
    if (_xdr_field_number(type_) == 5)
      return peers_;
    throw xdr::xdr_wrong_union("StellarMessage: peers accessed when not selected");
  }
  uint256 &txSetHash() {
    if (_xdr_field_number(type_) == 6)
      return txSetHash_;
    throw xdr::xdr_wrong_union("StellarMessage: txSetHash accessed when not selected");
  }
  const uint256 &txSetHash() const {
    if (_xdr_field_number(type_) == 6)
      return txSetHash_;
    throw xdr::xdr_wrong_union("StellarMessage: txSetHash accessed when not selected");
  }
  TransactionSet &txSet() {
    if (_xdr_field_number(type_) == 7)
      return txSet_;
    throw xdr::xdr_wrong_union("StellarMessage: txSet accessed when not selected");
  }
  const TransactionSet &txSet() const {
    if (_xdr_field_number(type_) == 7)
      return txSet_;
    throw xdr::xdr_wrong_union("StellarMessage: txSet accessed when not selected");
  }
  TransactionEnvelope &transaction() {
    if (_xdr_field_number(type_) == 8)
      return transaction_;
    throw xdr::xdr_wrong_union("StellarMessage: transaction accessed when not selected");
  }
  const TransactionEnvelope &transaction() const {
    if (_xdr_field_number(type_) == 8)
      return transaction_;
    throw xdr::xdr_wrong_union("StellarMessage: transaction accessed when not selected");
  }
  uint256 &qSetHash() {
    if (_xdr_field_number(type_) == 9)
      return qSetHash_;
    throw xdr::xdr_wrong_union("StellarMessage: qSetHash accessed when not selected");
  }
  const uint256 &qSetHash() const {
    if (_xdr_field_number(type_) == 9)
      return qSetHash_;
    throw xdr::xdr_wrong_union("StellarMessage: qSetHash accessed when not selected");
  }
  SCPQuorumSet &qSet() {
    if (_xdr_field_number(type_) == 10)
      return qSet_;
    throw xdr::xdr_wrong_union("StellarMessage: qSet accessed when not selected");
  }
  const SCPQuorumSet &qSet() const {
    if (_xdr_field_number(type_) == 10)
      return qSet_;
    throw xdr::xdr_wrong_union("StellarMessage: qSet accessed when not selected");
  }
  SCPEnvelope &envelope() {
    if (_xdr_field_number(type_) == 11)
      return envelope_;
    throw xdr::xdr_wrong_union("StellarMessage: envelope accessed when not selected");
  }
  const SCPEnvelope &envelope() const {
    if (_xdr_field_number(type_) == 11)
      return envelope_;
    throw xdr::xdr_wrong_union("StellarMessage: envelope accessed when not selected");
  }
  uint32 &getSCPLedgerSeq() {
    if (_xdr_field_number(type_) == 12)
      return getSCPLedgerSeq_;
    throw xdr::xdr_wrong_union("StellarMessage: getSCPLedgerSeq accessed when not selected");
  }
  const uint32 &getSCPLedgerSeq() const {
    if (_xdr_field_number(type_) == 12)
      return getSCPLedgerSeq_;
    throw xdr::xdr_wrong_union("StellarMessage: getSCPLedgerSeq accessed when not selected");
  }bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

struct AuthenticatedMessage : xdr::xdr_abstract {
  struct _v0_t  : xdr::xdr_abstract {
    uint64 sequence{};
    StellarMessage message{};
    HmacSha256Mac mac{};

    _v0_t() = default;
    template<typename _sequence_T,
             typename _message_T,
             typename _mac_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _sequence_T>::value
                            && std::is_constructible<StellarMessage, _message_T>::value
                            && std::is_constructible<HmacSha256Mac, _mac_T>::value
                           >::type>
    explicit _v0_t(_sequence_T &&_sequence,
                   _message_T &&_message,
                   _mac_T &&_mac)
      : sequence(std::forward<_sequence_T>(_sequence)),
        message(std::forward<_message_T>(_message)),
        mac(std::forward<_mac_T>(_mac)) {}
    bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
    bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

  };

  using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
private:
  _xdr_case_type v_;
  union {
    _v0_t v0_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerVersion> &_xdr_case_values() {
    static const std::vector<LedgerVersion> _xdr_disc_vec {
      LedgerVersion::EMPTY_VERSION
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      _f(&AuthenticatedMessage::v0_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in AuthenticatedMessage");
    if (fnum != _xdr_field_number(v_)) {
      this->~AuthenticatedMessage();
      v_ = which;switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) _v0_t{};
break;
}

    }
    else
      v_ = which;
  }
  explicit AuthenticatedMessage(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) _v0_t{};
break;
}

  }
  AuthenticatedMessage(const AuthenticatedMessage &source) : v_(source.v_) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) _v0_t(source.v0_);
break;
}

  }
  AuthenticatedMessage(AuthenticatedMessage &&source) : v_(source.v_) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) _v0_t(std::move(source.v0_));
break;
}

  }
  ~AuthenticatedMessage() {
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
v0_.~_v0_t();
break;
}
}

  AuthenticatedMessage &operator=(const AuthenticatedMessage &source) {
    if (v_ == source.v_)
{
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
v0_ = source.v0_;
break;
}
}
else {this->~AuthenticatedMessage();
    v_ = source.v_;
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) _v0_t(source.v0_);
break;
}
}
    return *this;
  }
  AuthenticatedMessage &operator=(AuthenticatedMessage &&source) {
    if (v_ == source.v_)
{
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
v0_ = std::move(source.v0_);
break;
}
}
else {this->~AuthenticatedMessage();
    v_ = std::move(source.v_);
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) _v0_t(std::move(source.v0_));
break;
}
}
    return *this;
  }

  LedgerVersion v() const { return LedgerVersion(v_); }
  AuthenticatedMessage &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _v0_t &v0() {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("AuthenticatedMessage: v0 accessed when not selected");
  }
  const _v0_t &v0() const {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("AuthenticatedMessage: v0 accessed when not selected");
  }bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

}

#endif // !__XDR_OVERLAY_H_INCLUDED__
