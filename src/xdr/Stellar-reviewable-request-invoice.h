// -*- C++ -*-
// Automatically generated from Stellar-reviewable-request-invoice.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_REVIEWABLE_REQUEST_INVOICE_H_INCLUDED__
#define __XDR_STELLAR_REVIEWABLE_REQUEST_INVOICE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct InvoiceRequest {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InvoiceRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::InvoiceRequest::_ext_t;
  using case_type = ::stellar::InvoiceRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::InvoiceRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InvoiceRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InvoiceRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::InvoiceRequest>
  : xdr_struct_base<field_ptr<::stellar::InvoiceRequest,
                              decltype(::stellar::InvoiceRequest::asset),
                              &::stellar::InvoiceRequest::asset>,
                    field_ptr<::stellar::InvoiceRequest,
                              decltype(::stellar::InvoiceRequest::amount),
                              &::stellar::InvoiceRequest::amount>,
                    field_ptr<::stellar::InvoiceRequest,
                              decltype(::stellar::InvoiceRequest::senderBalance),
                              &::stellar::InvoiceRequest::senderBalance>,
                    field_ptr<::stellar::InvoiceRequest,
                              decltype(::stellar::InvoiceRequest::receiverBalance),
                              &::stellar::InvoiceRequest::receiverBalance>,
                    field_ptr<::stellar::InvoiceRequest,
                              decltype(::stellar::InvoiceRequest::contractID),
                              &::stellar::InvoiceRequest::contractID>,
                    field_ptr<::stellar::InvoiceRequest,
                              decltype(::stellar::InvoiceRequest::isApproved),
                              &::stellar::InvoiceRequest::isApproved>,
                    field_ptr<::stellar::InvoiceRequest,
                              decltype(::stellar::InvoiceRequest::creatorDetails),
                              &::stellar::InvoiceRequest::creatorDetails>,
                    field_ptr<::stellar::InvoiceRequest,
                              decltype(::stellar::InvoiceRequest::ext),
                              &::stellar::InvoiceRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InvoiceRequest &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.senderBalance, "senderBalance");
    archive(ar, obj.receiverBalance, "receiverBalance");
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.isApproved, "isApproved");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InvoiceRequest &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.senderBalance, "senderBalance");
    archive(ar, obj.receiverBalance, "receiverBalance");
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.isApproved, "isApproved");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_REVIEWABLE_REQUEST_INVOICE_H_INCLUDED__
