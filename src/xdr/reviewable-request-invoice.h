// -*- C++ -*-
// Automatically generated from reviewable-request-invoice.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_REVIEWABLE_REQUEST_INVOICE_H_INCLUDED__
#define __XDR_REVIEWABLE_REQUEST_INVOICE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct InvoiceRequest  : xdr::xdr_abstract {
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

  AssetCode asset{};
  uint64 amount{};
  BalanceID senderBalance{};
  BalanceID receiverBalance{};
  xdr::pointer<uint64> contractID{};
  bool isApproved{};
  longstring creatorDetails{};
  _ext_t ext{};

  InvoiceRequest() = default;
  template<typename _asset_T,
           typename _amount_T,
           typename _senderBalance_T,
           typename _receiverBalance_T,
           typename _contractID_T,
           typename _isApproved_T,
           typename _creatorDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<BalanceID, _senderBalance_T>::value
                          && std::is_constructible<BalanceID, _receiverBalance_T>::value
                          && std::is_constructible<xdr::pointer<uint64>, _contractID_T>::value
                          && std::is_constructible<bool, _isApproved_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit InvoiceRequest(_asset_T &&_asset,
                          _amount_T &&_amount,
                          _senderBalance_T &&_senderBalance,
                          _receiverBalance_T &&_receiverBalance,
                          _contractID_T &&_contractID,
                          _isApproved_T &&_isApproved,
                          _creatorDetails_T &&_creatorDetails,
                          _ext_T &&_ext)
    : asset(std::forward<_asset_T>(_asset)),
      amount(std::forward<_amount_T>(_amount)),
      senderBalance(std::forward<_senderBalance_T>(_senderBalance)),
      receiverBalance(std::forward<_receiverBalance_T>(_receiverBalance)),
      contractID(std::forward<_contractID_T>(_contractID)),
      isApproved(std::forward<_isApproved_T>(_isApproved)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
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

#endif // !__XDR_REVIEWABLE_REQUEST_INVOICE_H_INCLUDED__
