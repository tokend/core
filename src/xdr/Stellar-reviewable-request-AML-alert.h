// -*- C++ -*-
// Automatically generated from Stellar-reviewable-request-AML-alert.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_REVIEWABLE_REQUEST_AML_ALERT_H_INCLUDED__
#define __XDR_STELLAR_REVIEWABLE_REQUEST_AML_ALERT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct AMLAlertRequest {
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

  BalanceID balanceID{};
  uint64 amount{};
  longstring creatorDetails{};
  _ext_t ext{};

  AMLAlertRequest() = default;
  template<typename _balanceID_T,
           typename _amount_T,
           typename _creatorDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _balanceID_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AMLAlertRequest(_balanceID_T &&_balanceID,
                           _amount_T &&_amount,
                           _creatorDetails_T &&_creatorDetails,
                           _ext_T &&_ext)
    : balanceID(std::forward<_balanceID_T>(_balanceID)),
      amount(std::forward<_amount_T>(_amount)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AMLAlertRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AMLAlertRequest::_ext_t;
  using case_type = ::stellar::AMLAlertRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AMLAlertRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AMLAlertRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AMLAlertRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AMLAlertRequest>
  : xdr_struct_base<field_ptr<::stellar::AMLAlertRequest,
                              decltype(::stellar::AMLAlertRequest::balanceID),
                              &::stellar::AMLAlertRequest::balanceID>,
                    field_ptr<::stellar::AMLAlertRequest,
                              decltype(::stellar::AMLAlertRequest::amount),
                              &::stellar::AMLAlertRequest::amount>,
                    field_ptr<::stellar::AMLAlertRequest,
                              decltype(::stellar::AMLAlertRequest::creatorDetails),
                              &::stellar::AMLAlertRequest::creatorDetails>,
                    field_ptr<::stellar::AMLAlertRequest,
                              decltype(::stellar::AMLAlertRequest::ext),
                              &::stellar::AMLAlertRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AMLAlertRequest &obj) {
    archive(ar, obj.balanceID, "balanceID");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AMLAlertRequest &obj) {
    archive(ar, obj.balanceID, "balanceID");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_REVIEWABLE_REQUEST_AML_ALERT_H_INCLUDED__
