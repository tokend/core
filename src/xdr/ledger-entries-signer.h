// -*- C++ -*-
// Automatically generated from ledger-entries-signer.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_SIGNER_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_SIGNER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct SignerEntry  : xdr::xdr_abstract {
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
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
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}

    _ext_t &operator=(const _ext_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }
bool
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

  PublicKey pubKey{};
  AccountID accountID{};
  uint32 weight{};
  uint32 identity{};
  longstring details{};
  uint64 roleID{};
  _ext_t ext{};

  SignerEntry() = default;
  template<typename _pubKey_T,
           typename _accountID_T,
           typename _weight_T,
           typename _identity_T,
           typename _details_T,
           typename _roleID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<PublicKey, _pubKey_T>::value
                          && std::is_constructible<AccountID, _accountID_T>::value
                          && std::is_constructible<uint32, _weight_T>::value
                          && std::is_constructible<uint32, _identity_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<uint64, _roleID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SignerEntry(_pubKey_T &&_pubKey,
                       _accountID_T &&_accountID,
                       _weight_T &&_weight,
                       _identity_T &&_identity,
                       _details_T &&_details,
                       _roleID_T &&_roleID,
                       _ext_T &&_ext)
    : pubKey(std::forward<_pubKey_T>(_pubKey)),
      accountID(std::forward<_accountID_T>(_accountID)),
      weight(std::forward<_weight_T>(_weight)),
      identity(std::forward<_identity_T>(_identity)),
      details(std::forward<_details_T>(_details)),
      roleID(std::forward<_roleID_T>(_roleID)),
      ext(std::forward<_ext_T>(_ext)) {}
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

}

#endif // !__XDR_LEDGER_ENTRIES_SIGNER_H_INCLUDED__
