// -*- C++ -*-
// Automatically generated from Stellar-reviewable-request-issuance.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_REVIEWABLE_REQUEST_ISSUANCE_H_INCLUDED__
#define __XDR_STELLAR_REVIEWABLE_REQUEST_ISSUANCE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct PreIssuanceRequest {
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
  DecoratedSignature signature{};
  string64 reference{};
  longstring creatorDetails{};
  _ext_t ext{};

  PreIssuanceRequest() = default;
  template<typename _asset_T,
           typename _amount_T,
           typename _signature_T,
           typename _reference_T,
           typename _creatorDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<DecoratedSignature, _signature_T>::value
                          && std::is_constructible<string64, _reference_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PreIssuanceRequest(_asset_T &&_asset,
                              _amount_T &&_amount,
                              _signature_T &&_signature,
                              _reference_T &&_reference,
                              _creatorDetails_T &&_creatorDetails,
                              _ext_T &&_ext)
    : asset(std::forward<_asset_T>(_asset)),
      amount(std::forward<_amount_T>(_amount)),
      signature(std::forward<_signature_T>(_signature)),
      reference(std::forward<_reference_T>(_reference)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PreIssuanceRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PreIssuanceRequest::_ext_t;
  using case_type = ::stellar::PreIssuanceRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::PreIssuanceRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PreIssuanceRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PreIssuanceRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::PreIssuanceRequest>
  : xdr_struct_base<field_ptr<::stellar::PreIssuanceRequest,
                              decltype(::stellar::PreIssuanceRequest::asset),
                              &::stellar::PreIssuanceRequest::asset>,
                    field_ptr<::stellar::PreIssuanceRequest,
                              decltype(::stellar::PreIssuanceRequest::amount),
                              &::stellar::PreIssuanceRequest::amount>,
                    field_ptr<::stellar::PreIssuanceRequest,
                              decltype(::stellar::PreIssuanceRequest::signature),
                              &::stellar::PreIssuanceRequest::signature>,
                    field_ptr<::stellar::PreIssuanceRequest,
                              decltype(::stellar::PreIssuanceRequest::reference),
                              &::stellar::PreIssuanceRequest::reference>,
                    field_ptr<::stellar::PreIssuanceRequest,
                              decltype(::stellar::PreIssuanceRequest::creatorDetails),
                              &::stellar::PreIssuanceRequest::creatorDetails>,
                    field_ptr<::stellar::PreIssuanceRequest,
                              decltype(::stellar::PreIssuanceRequest::ext),
                              &::stellar::PreIssuanceRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PreIssuanceRequest &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.signature, "signature");
    archive(ar, obj.reference, "reference");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PreIssuanceRequest &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.signature, "signature");
    archive(ar, obj.reference, "reference");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct IssuanceRequest {
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
  BalanceID receiver{};
  longstring creatorDetails{};
  Fee fee{};
  _ext_t ext{};

  IssuanceRequest() = default;
  template<typename _asset_T,
           typename _amount_T,
           typename _receiver_T,
           typename _creatorDetails_T,
           typename _fee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<BalanceID, _receiver_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<Fee, _fee_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit IssuanceRequest(_asset_T &&_asset,
                           _amount_T &&_amount,
                           _receiver_T &&_receiver,
                           _creatorDetails_T &&_creatorDetails,
                           _fee_T &&_fee,
                           _ext_T &&_ext)
    : asset(std::forward<_asset_T>(_asset)),
      amount(std::forward<_amount_T>(_amount)),
      receiver(std::forward<_receiver_T>(_receiver)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
      fee(std::forward<_fee_T>(_fee)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::IssuanceRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::IssuanceRequest::_ext_t;
  using case_type = ::stellar::IssuanceRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::IssuanceRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::IssuanceRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::IssuanceRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::IssuanceRequest>
  : xdr_struct_base<field_ptr<::stellar::IssuanceRequest,
                              decltype(::stellar::IssuanceRequest::asset),
                              &::stellar::IssuanceRequest::asset>,
                    field_ptr<::stellar::IssuanceRequest,
                              decltype(::stellar::IssuanceRequest::amount),
                              &::stellar::IssuanceRequest::amount>,
                    field_ptr<::stellar::IssuanceRequest,
                              decltype(::stellar::IssuanceRequest::receiver),
                              &::stellar::IssuanceRequest::receiver>,
                    field_ptr<::stellar::IssuanceRequest,
                              decltype(::stellar::IssuanceRequest::creatorDetails),
                              &::stellar::IssuanceRequest::creatorDetails>,
                    field_ptr<::stellar::IssuanceRequest,
                              decltype(::stellar::IssuanceRequest::fee),
                              &::stellar::IssuanceRequest::fee>,
                    field_ptr<::stellar::IssuanceRequest,
                              decltype(::stellar::IssuanceRequest::ext),
                              &::stellar::IssuanceRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::IssuanceRequest &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.receiver, "receiver");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::IssuanceRequest &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.receiver, "receiver");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_REVIEWABLE_REQUEST_ISSUANCE_H_INCLUDED__
