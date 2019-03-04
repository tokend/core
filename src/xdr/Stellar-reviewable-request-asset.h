// -*- C++ -*-
// Automatically generated from Stellar-reviewable-request-asset.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_REVIEWABLE_REQUEST_ASSET_H_INCLUDED__
#define __XDR_STELLAR_REVIEWABLE_REQUEST_ASSET_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct AssetCreationRequest {
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

  AssetCode code{};
  AccountID preissuedAssetSigner{};
  uint64 maxIssuanceAmount{};
  uint64 initialPreissuedAmount{};
  uint32 policies{};
  longstring creatorDetails{};
  uint64 type{};
  uint32 sequenceNumber{};
  uint32 trailingDigitsCount{};
  _ext_t ext{};

  AssetCreationRequest() = default;
  template<typename _code_T,
           typename _preissuedAssetSigner_T,
           typename _maxIssuanceAmount_T,
           typename _initialPreissuedAmount_T,
           typename _policies_T,
           typename _creatorDetails_T,
           typename _type_T,
           typename _sequenceNumber_T,
           typename _trailingDigitsCount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _code_T>::value
                          && std::is_constructible<AccountID, _preissuedAssetSigner_T>::value
                          && std::is_constructible<uint64, _maxIssuanceAmount_T>::value
                          && std::is_constructible<uint64, _initialPreissuedAmount_T>::value
                          && std::is_constructible<uint32, _policies_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<uint64, _type_T>::value
                          && std::is_constructible<uint32, _sequenceNumber_T>::value
                          && std::is_constructible<uint32, _trailingDigitsCount_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AssetCreationRequest(_code_T &&_code,
                                _preissuedAssetSigner_T &&_preissuedAssetSigner,
                                _maxIssuanceAmount_T &&_maxIssuanceAmount,
                                _initialPreissuedAmount_T &&_initialPreissuedAmount,
                                _policies_T &&_policies,
                                _creatorDetails_T &&_creatorDetails,
                                _type_T &&_type,
                                _sequenceNumber_T &&_sequenceNumber,
                                _trailingDigitsCount_T &&_trailingDigitsCount,
                                _ext_T &&_ext)
    : code(std::forward<_code_T>(_code)),
      preissuedAssetSigner(std::forward<_preissuedAssetSigner_T>(_preissuedAssetSigner)),
      maxIssuanceAmount(std::forward<_maxIssuanceAmount_T>(_maxIssuanceAmount)),
      initialPreissuedAmount(std::forward<_initialPreissuedAmount_T>(_initialPreissuedAmount)),
      policies(std::forward<_policies_T>(_policies)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
      type(std::forward<_type_T>(_type)),
      sequenceNumber(std::forward<_sequenceNumber_T>(_sequenceNumber)),
      trailingDigitsCount(std::forward<_trailingDigitsCount_T>(_trailingDigitsCount)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AssetCreationRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AssetCreationRequest::_ext_t;
  using case_type = ::stellar::AssetCreationRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AssetCreationRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetCreationRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetCreationRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AssetCreationRequest>
  : xdr_struct_base<field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::code),
                              &::stellar::AssetCreationRequest::code>,
                    field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::preissuedAssetSigner),
                              &::stellar::AssetCreationRequest::preissuedAssetSigner>,
                    field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::maxIssuanceAmount),
                              &::stellar::AssetCreationRequest::maxIssuanceAmount>,
                    field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::initialPreissuedAmount),
                              &::stellar::AssetCreationRequest::initialPreissuedAmount>,
                    field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::policies),
                              &::stellar::AssetCreationRequest::policies>,
                    field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::creatorDetails),
                              &::stellar::AssetCreationRequest::creatorDetails>,
                    field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::type),
                              &::stellar::AssetCreationRequest::type>,
                    field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::sequenceNumber),
                              &::stellar::AssetCreationRequest::sequenceNumber>,
                    field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::trailingDigitsCount),
                              &::stellar::AssetCreationRequest::trailingDigitsCount>,
                    field_ptr<::stellar::AssetCreationRequest,
                              decltype(::stellar::AssetCreationRequest::ext),
                              &::stellar::AssetCreationRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetCreationRequest &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.preissuedAssetSigner, "preissuedAssetSigner");
    archive(ar, obj.maxIssuanceAmount, "maxIssuanceAmount");
    archive(ar, obj.initialPreissuedAmount, "initialPreissuedAmount");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.type, "type");
    archive(ar, obj.sequenceNumber, "sequenceNumber");
    archive(ar, obj.trailingDigitsCount, "trailingDigitsCount");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetCreationRequest &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.preissuedAssetSigner, "preissuedAssetSigner");
    archive(ar, obj.maxIssuanceAmount, "maxIssuanceAmount");
    archive(ar, obj.initialPreissuedAmount, "initialPreissuedAmount");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.type, "type");
    archive(ar, obj.sequenceNumber, "sequenceNumber");
    archive(ar, obj.trailingDigitsCount, "trailingDigitsCount");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct AssetUpdateRequest {
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

  AssetCode code{};
  longstring creatorDetails{};
  uint32 policies{};
  uint32 sequenceNumber{};
  _ext_t ext{};

  AssetUpdateRequest() = default;
  template<typename _code_T,
           typename _creatorDetails_T,
           typename _policies_T,
           typename _sequenceNumber_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _code_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<uint32, _policies_T>::value
                          && std::is_constructible<uint32, _sequenceNumber_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AssetUpdateRequest(_code_T &&_code,
                              _creatorDetails_T &&_creatorDetails,
                              _policies_T &&_policies,
                              _sequenceNumber_T &&_sequenceNumber,
                              _ext_T &&_ext)
    : code(std::forward<_code_T>(_code)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
      policies(std::forward<_policies_T>(_policies)),
      sequenceNumber(std::forward<_sequenceNumber_T>(_sequenceNumber)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AssetUpdateRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AssetUpdateRequest::_ext_t;
  using case_type = ::stellar::AssetUpdateRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AssetUpdateRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetUpdateRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetUpdateRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AssetUpdateRequest>
  : xdr_struct_base<field_ptr<::stellar::AssetUpdateRequest,
                              decltype(::stellar::AssetUpdateRequest::code),
                              &::stellar::AssetUpdateRequest::code>,
                    field_ptr<::stellar::AssetUpdateRequest,
                              decltype(::stellar::AssetUpdateRequest::creatorDetails),
                              &::stellar::AssetUpdateRequest::creatorDetails>,
                    field_ptr<::stellar::AssetUpdateRequest,
                              decltype(::stellar::AssetUpdateRequest::policies),
                              &::stellar::AssetUpdateRequest::policies>,
                    field_ptr<::stellar::AssetUpdateRequest,
                              decltype(::stellar::AssetUpdateRequest::sequenceNumber),
                              &::stellar::AssetUpdateRequest::sequenceNumber>,
                    field_ptr<::stellar::AssetUpdateRequest,
                              decltype(::stellar::AssetUpdateRequest::ext),
                              &::stellar::AssetUpdateRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetUpdateRequest &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.sequenceNumber, "sequenceNumber");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetUpdateRequest &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.sequenceNumber, "sequenceNumber");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct AssetChangePreissuedSigner {
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

  AssetCode code{};
  AccountID accountID{};
  DecoratedSignature signature{};
  _ext_t ext{};

  AssetChangePreissuedSigner() = default;
  template<typename _code_T,
           typename _accountID_T,
           typename _signature_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _code_T>::value
                          && std::is_constructible<AccountID, _accountID_T>::value
                          && std::is_constructible<DecoratedSignature, _signature_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AssetChangePreissuedSigner(_code_T &&_code,
                                      _accountID_T &&_accountID,
                                      _signature_T &&_signature,
                                      _ext_T &&_ext)
    : code(std::forward<_code_T>(_code)),
      accountID(std::forward<_accountID_T>(_accountID)),
      signature(std::forward<_signature_T>(_signature)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AssetChangePreissuedSigner::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AssetChangePreissuedSigner::_ext_t;
  using case_type = ::stellar::AssetChangePreissuedSigner::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AssetChangePreissuedSigner::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetChangePreissuedSigner::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetChangePreissuedSigner::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AssetChangePreissuedSigner>
  : xdr_struct_base<field_ptr<::stellar::AssetChangePreissuedSigner,
                              decltype(::stellar::AssetChangePreissuedSigner::code),
                              &::stellar::AssetChangePreissuedSigner::code>,
                    field_ptr<::stellar::AssetChangePreissuedSigner,
                              decltype(::stellar::AssetChangePreissuedSigner::accountID),
                              &::stellar::AssetChangePreissuedSigner::accountID>,
                    field_ptr<::stellar::AssetChangePreissuedSigner,
                              decltype(::stellar::AssetChangePreissuedSigner::signature),
                              &::stellar::AssetChangePreissuedSigner::signature>,
                    field_ptr<::stellar::AssetChangePreissuedSigner,
                              decltype(::stellar::AssetChangePreissuedSigner::ext),
                              &::stellar::AssetChangePreissuedSigner::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetChangePreissuedSigner &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.signature, "signature");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetChangePreissuedSigner &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.signature, "signature");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_REVIEWABLE_REQUEST_ASSET_H_INCLUDED__
