// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-asset.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_ASSET_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_ASSET_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

enum class ManageAssetAction : std::int32_t {
  CREATE_ASSET_CREATION_REQUEST = 0,
  CREATE_ASSET_UPDATE_REQUEST = 1,
  CANCEL_ASSET_REQUEST = 2,
  CHANGE_PREISSUED_ASSET_SIGNER = 3,
  UPDATE_MAX_ISSUANCE = 4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetAction>
  : xdr_integral_base<::stellar::ManageAssetAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAssetAction val) {
    switch (val) {
    case ::stellar::ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
      return "CREATE_ASSET_CREATION_REQUEST";
    case ::stellar::ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
      return "CREATE_ASSET_UPDATE_REQUEST";
    case ::stellar::ManageAssetAction::CANCEL_ASSET_REQUEST:
      return "CANCEL_ASSET_REQUEST";
    case ::stellar::ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
      return "CHANGE_PREISSUED_ASSET_SIGNER";
    case ::stellar::ManageAssetAction::UPDATE_MAX_ISSUANCE:
      return "UPDATE_MAX_ISSUANCE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAssetAction::CREATE_ASSET_CREATION_REQUEST,
      (int32_t)::stellar::ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST,
      (int32_t)::stellar::ManageAssetAction::CANCEL_ASSET_REQUEST,
      (int32_t)::stellar::ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER,
      (int32_t)::stellar::ManageAssetAction::UPDATE_MAX_ISSUANCE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CancelAssetRequest {
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

  _ext_t ext{};

  CancelAssetRequest() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CancelAssetRequest(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CancelAssetRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CancelAssetRequest::_ext_t;
  using case_type = ::stellar::CancelAssetRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CancelAssetRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CancelAssetRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CancelAssetRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CancelAssetRequest>
  : xdr_struct_base<field_ptr<::stellar::CancelAssetRequest,
                              decltype(::stellar::CancelAssetRequest::ext),
                              &::stellar::CancelAssetRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CancelAssetRequest &obj) {
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CancelAssetRequest &obj) {
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct UpdateMaxIssuance {
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

  AssetCode assetCode{};
  uint64 maxIssuanceAmount{};
  _ext_t ext{};

  UpdateMaxIssuance() = default;
  template<typename _assetCode_T,
           typename _maxIssuanceAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _assetCode_T>::value
                          && std::is_constructible<uint64, _maxIssuanceAmount_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit UpdateMaxIssuance(_assetCode_T &&_assetCode,
                             _maxIssuanceAmount_T &&_maxIssuanceAmount,
                             _ext_T &&_ext)
    : assetCode(std::forward<_assetCode_T>(_assetCode)),
      maxIssuanceAmount(std::forward<_maxIssuanceAmount_T>(_maxIssuanceAmount)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UpdateMaxIssuance::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::UpdateMaxIssuance::_ext_t;
  using case_type = ::stellar::UpdateMaxIssuance::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::UpdateMaxIssuance::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UpdateMaxIssuance::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UpdateMaxIssuance::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::UpdateMaxIssuance>
  : xdr_struct_base<field_ptr<::stellar::UpdateMaxIssuance,
                              decltype(::stellar::UpdateMaxIssuance::assetCode),
                              &::stellar::UpdateMaxIssuance::assetCode>,
                    field_ptr<::stellar::UpdateMaxIssuance,
                              decltype(::stellar::UpdateMaxIssuance::maxIssuanceAmount),
                              &::stellar::UpdateMaxIssuance::maxIssuanceAmount>,
                    field_ptr<::stellar::UpdateMaxIssuance,
                              decltype(::stellar::UpdateMaxIssuance::ext),
                              &::stellar::UpdateMaxIssuance::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UpdateMaxIssuance &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.maxIssuanceAmount, "maxIssuanceAmount");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UpdateMaxIssuance &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.maxIssuanceAmount, "maxIssuanceAmount");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageAssetOp {
  struct _request_t {
    struct _createAssetCreationRequest_t {
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

      AssetCreationRequest createAsset{};
      xdr::pointer<uint32> allTasks{};
      _ext_t ext{};

      _createAssetCreationRequest_t() = default;
      template<typename _createAsset_T,
               typename _allTasks_T,
               typename _ext_T,
               typename = typename
               std::enable_if<std::is_constructible<AssetCreationRequest, _createAsset_T>::value
                              && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                              && std::is_constructible<_ext_t, _ext_T>::value
                             >::type>
      explicit _createAssetCreationRequest_t(_createAsset_T &&_createAsset,
                                             _allTasks_T &&_allTasks,
                                             _ext_T &&_ext)
        : createAsset(std::forward<_createAsset_T>(_createAsset)),
          allTasks(std::forward<_allTasks_T>(_allTasks)),
          ext(std::forward<_ext_T>(_ext)) {}
    };
    struct _createAssetUpdateRequest_t {
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

      AssetUpdateRequest updateAsset{};
      xdr::pointer<uint32> allTasks{};
      _ext_t ext{};

      _createAssetUpdateRequest_t() = default;
      template<typename _updateAsset_T,
               typename _allTasks_T,
               typename _ext_T,
               typename = typename
               std::enable_if<std::is_constructible<AssetUpdateRequest, _updateAsset_T>::value
                              && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                              && std::is_constructible<_ext_t, _ext_T>::value
                             >::type>
      explicit _createAssetUpdateRequest_t(_updateAsset_T &&_updateAsset,
                                           _allTasks_T &&_allTasks,
                                           _ext_T &&_ext)
        : updateAsset(std::forward<_updateAsset_T>(_updateAsset)),
          allTasks(std::forward<_allTasks_T>(_allTasks)),
          ext(std::forward<_ext_T>(_ext)) {}
    };

    using _xdr_case_type = xdr::xdr_traits<ManageAssetAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      _createAssetCreationRequest_t createAssetCreationRequest_;
      _createAssetUpdateRequest_t createAssetUpdateRequest_;
      CancelAssetRequest cancelRequest_;
      AssetChangePreissuedSigner changePreissuedSigner_;
      UpdateMaxIssuance updateMaxIssuance_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageAssetAction> &_xdr_case_values() {
      static const std::vector<ManageAssetAction> _xdr_disc_vec {
        ManageAssetAction::CREATE_ASSET_CREATION_REQUEST,
        ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST,
        ManageAssetAction::CANCEL_ASSET_REQUEST,
        ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER,
        ManageAssetAction::UPDATE_MAX_ISSUANCE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST ? 1
        : which == (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST ? 2
        : which == (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST ? 3
        : which == (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER ? 4
        : which == (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE ? 5
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
        _f(&_request_t::createAssetCreationRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
        _f(&_request_t::createAssetUpdateRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
        _f(&_request_t::cancelRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
        _f(&_request_t::changePreissuedSigner_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
        _f(&_request_t::updateMaxIssuance_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _request_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_request_t();
        action_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      else
        action_ = which;
    }
    explicit _request_t(ManageAssetAction which = ManageAssetAction{}) : action_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
    }
    _request_t(const _request_t &source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
    }
    _request_t(_request_t &&source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                        std::move(source));
    }
    ~_request_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
    _request_t &operator=(const _request_t &source) {
      if (_xdr_field_number(action_)
          == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
      else {
        this->~_request_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
      }
      action_ = source.action_;
      return *this;
    }
    _request_t &operator=(_request_t &&source) {
      if (_xdr_field_number(action_)
           == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                          std::move(source));
      else {
        this->~_request_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                          std::move(source));
      }
      action_ = source.action_;
      return *this;
    }

    ManageAssetAction action() const { return ManageAssetAction(action_); }
    _request_t &action(ManageAssetAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    _createAssetCreationRequest_t &createAssetCreationRequest() {
      if (_xdr_field_number(action_) == 1)
        return createAssetCreationRequest_;
      throw xdr::xdr_wrong_union("_request_t: createAssetCreationRequest accessed when not selected");
    }
    const _createAssetCreationRequest_t &createAssetCreationRequest() const {
      if (_xdr_field_number(action_) == 1)
        return createAssetCreationRequest_;
      throw xdr::xdr_wrong_union("_request_t: createAssetCreationRequest accessed when not selected");
    }
    _createAssetUpdateRequest_t &createAssetUpdateRequest() {
      if (_xdr_field_number(action_) == 2)
        return createAssetUpdateRequest_;
      throw xdr::xdr_wrong_union("_request_t: createAssetUpdateRequest accessed when not selected");
    }
    const _createAssetUpdateRequest_t &createAssetUpdateRequest() const {
      if (_xdr_field_number(action_) == 2)
        return createAssetUpdateRequest_;
      throw xdr::xdr_wrong_union("_request_t: createAssetUpdateRequest accessed when not selected");
    }
    CancelAssetRequest &cancelRequest() {
      if (_xdr_field_number(action_) == 3)
        return cancelRequest_;
      throw xdr::xdr_wrong_union("_request_t: cancelRequest accessed when not selected");
    }
    const CancelAssetRequest &cancelRequest() const {
      if (_xdr_field_number(action_) == 3)
        return cancelRequest_;
      throw xdr::xdr_wrong_union("_request_t: cancelRequest accessed when not selected");
    }
    AssetChangePreissuedSigner &changePreissuedSigner() {
      if (_xdr_field_number(action_) == 4)
        return changePreissuedSigner_;
      throw xdr::xdr_wrong_union("_request_t: changePreissuedSigner accessed when not selected");
    }
    const AssetChangePreissuedSigner &changePreissuedSigner() const {
      if (_xdr_field_number(action_) == 4)
        return changePreissuedSigner_;
      throw xdr::xdr_wrong_union("_request_t: changePreissuedSigner accessed when not selected");
    }
    UpdateMaxIssuance &updateMaxIssuance() {
      if (_xdr_field_number(action_) == 5)
        return updateMaxIssuance_;
      throw xdr::xdr_wrong_union("_request_t: updateMaxIssuance accessed when not selected");
    }
    const UpdateMaxIssuance &updateMaxIssuance() const {
      if (_xdr_field_number(action_) == 5)
        return updateMaxIssuance_;
      throw xdr::xdr_wrong_union("_request_t: updateMaxIssuance accessed when not selected");
    }
  };
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

  uint64 requestID{};
  _request_t request{};
  _ext_t ext{};

  ManageAssetOp() = default;
  template<typename _requestID_T,
           typename _request_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<_request_t, _request_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageAssetOp(_requestID_T &&_requestID,
                         _request_T &&_request,
                         _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      request(std::forward<_request_T>(_request)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t;
  using case_type = ::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t>
  : xdr_struct_base<field_ptr<::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t,
                              decltype(::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::createAsset),
                              &::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::createAsset>,
                    field_ptr<::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t,
                              decltype(::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::allTasks),
                              &::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::allTasks>,
                    field_ptr<::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t,
                              decltype(::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::ext),
                              &::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t &obj) {
    archive(ar, obj.createAsset, "createAsset");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetOp::_request_t::_createAssetCreationRequest_t &obj) {
    archive(ar, obj.createAsset, "createAsset");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t;
  using case_type = ::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t>
  : xdr_struct_base<field_ptr<::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t,
                              decltype(::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::updateAsset),
                              &::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::updateAsset>,
                    field_ptr<::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t,
                              decltype(::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::allTasks),
                              &::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::allTasks>,
                    field_ptr<::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t,
                              decltype(::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::ext),
                              &::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t &obj) {
    archive(ar, obj.updateAsset, "updateAsset");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetOp::_request_t::_createAssetUpdateRequest_t &obj) {
    archive(ar, obj.updateAsset, "updateAsset");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageAssetOp::_request_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageAssetOp::_request_t;
  using case_type = ::stellar::ManageAssetOp::_request_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createAssetCreationRequest";
    case 2:
      return "createAssetUpdateRequest";
    case 3:
      return "cancelRequest";
    case 4:
      return "changePreissuedSigner";
    case 5:
      return "updateMaxIssuance";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageAssetOp::_request_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _request_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetOp::_request_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _request_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetOp::_request_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageAssetOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageAssetOp::_ext_t;
  using case_type = ::stellar::ManageAssetOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageAssetOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageAssetOp>
  : xdr_struct_base<field_ptr<::stellar::ManageAssetOp,
                              decltype(::stellar::ManageAssetOp::requestID),
                              &::stellar::ManageAssetOp::requestID>,
                    field_ptr<::stellar::ManageAssetOp,
                              decltype(::stellar::ManageAssetOp::request),
                              &::stellar::ManageAssetOp::request>,
                    field_ptr<::stellar::ManageAssetOp,
                              decltype(::stellar::ManageAssetOp::ext),
                              &::stellar::ManageAssetOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetOp &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.request, "request");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetOp &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.request, "request");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class ManageAssetResultCode : std::int32_t {
  SUCCESS = 0,
  REQUEST_NOT_FOUND = -1,
  INVALID_SIGNATURE = -2,
  ASSET_ALREADY_EXISTS = -3,
  INVALID_MAX_ISSUANCE_AMOUNT = -4,
  INVALID_CODE = -5,
  INVALID_PRE_ISSUER = -6,
  INVALID_POLICIES = -7,
  ASSET_NOT_FOUND = -8,
  REQUEST_ALREADY_EXISTS = -9,
  STATS_ASSET_ALREADY_EXISTS = -10,
  INITIAL_PREISSUED_EXCEEDS_MAX_ISSUANCE = -11,
  INVALID_CREATOR_DETAILS = -12,
  INVALID_TRAILING_DIGITS_COUNT = -13,
  INVALID_PREISSUED_AMOUNT_PRECISION = -14,
  INVALID_MAX_ISSUANCE_AMOUNT_PRECISION = -15,
  ASSET_CREATE_TASKS_NOT_FOUND = -16,
  ASSET_UPDATE_TASKS_NOT_FOUND = -17,
  NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE = -18,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetResultCode>
  : xdr_integral_base<::stellar::ManageAssetResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAssetResultCode val) {
    switch (val) {
    case ::stellar::ManageAssetResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageAssetResultCode::REQUEST_NOT_FOUND:
      return "REQUEST_NOT_FOUND";
    case ::stellar::ManageAssetResultCode::INVALID_SIGNATURE:
      return "INVALID_SIGNATURE";
    case ::stellar::ManageAssetResultCode::ASSET_ALREADY_EXISTS:
      return "ASSET_ALREADY_EXISTS";
    case ::stellar::ManageAssetResultCode::INVALID_MAX_ISSUANCE_AMOUNT:
      return "INVALID_MAX_ISSUANCE_AMOUNT";
    case ::stellar::ManageAssetResultCode::INVALID_CODE:
      return "INVALID_CODE";
    case ::stellar::ManageAssetResultCode::INVALID_PRE_ISSUER:
      return "INVALID_PRE_ISSUER";
    case ::stellar::ManageAssetResultCode::INVALID_POLICIES:
      return "INVALID_POLICIES";
    case ::stellar::ManageAssetResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    case ::stellar::ManageAssetResultCode::REQUEST_ALREADY_EXISTS:
      return "REQUEST_ALREADY_EXISTS";
    case ::stellar::ManageAssetResultCode::STATS_ASSET_ALREADY_EXISTS:
      return "STATS_ASSET_ALREADY_EXISTS";
    case ::stellar::ManageAssetResultCode::INITIAL_PREISSUED_EXCEEDS_MAX_ISSUANCE:
      return "INITIAL_PREISSUED_EXCEEDS_MAX_ISSUANCE";
    case ::stellar::ManageAssetResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::ManageAssetResultCode::INVALID_TRAILING_DIGITS_COUNT:
      return "INVALID_TRAILING_DIGITS_COUNT";
    case ::stellar::ManageAssetResultCode::INVALID_PREISSUED_AMOUNT_PRECISION:
      return "INVALID_PREISSUED_AMOUNT_PRECISION";
    case ::stellar::ManageAssetResultCode::INVALID_MAX_ISSUANCE_AMOUNT_PRECISION:
      return "INVALID_MAX_ISSUANCE_AMOUNT_PRECISION";
    case ::stellar::ManageAssetResultCode::ASSET_CREATE_TASKS_NOT_FOUND:
      return "ASSET_CREATE_TASKS_NOT_FOUND";
    case ::stellar::ManageAssetResultCode::ASSET_UPDATE_TASKS_NOT_FOUND:
      return "ASSET_UPDATE_TASKS_NOT_FOUND";
    case ::stellar::ManageAssetResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE:
      return "NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAssetResultCode::SUCCESS,
      (int32_t)::stellar::ManageAssetResultCode::REQUEST_NOT_FOUND,
      (int32_t)::stellar::ManageAssetResultCode::INVALID_SIGNATURE,
      (int32_t)::stellar::ManageAssetResultCode::ASSET_ALREADY_EXISTS,
      (int32_t)::stellar::ManageAssetResultCode::INVALID_MAX_ISSUANCE_AMOUNT,
      (int32_t)::stellar::ManageAssetResultCode::INVALID_CODE,
      (int32_t)::stellar::ManageAssetResultCode::INVALID_PRE_ISSUER,
      (int32_t)::stellar::ManageAssetResultCode::INVALID_POLICIES,
      (int32_t)::stellar::ManageAssetResultCode::ASSET_NOT_FOUND,
      (int32_t)::stellar::ManageAssetResultCode::REQUEST_ALREADY_EXISTS,
      (int32_t)::stellar::ManageAssetResultCode::STATS_ASSET_ALREADY_EXISTS,
      (int32_t)::stellar::ManageAssetResultCode::INITIAL_PREISSUED_EXCEEDS_MAX_ISSUANCE,
      (int32_t)::stellar::ManageAssetResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::ManageAssetResultCode::INVALID_TRAILING_DIGITS_COUNT,
      (int32_t)::stellar::ManageAssetResultCode::INVALID_PREISSUED_AMOUNT_PRECISION,
      (int32_t)::stellar::ManageAssetResultCode::INVALID_MAX_ISSUANCE_AMOUNT_PRECISION,
      (int32_t)::stellar::ManageAssetResultCode::ASSET_CREATE_TASKS_NOT_FOUND,
      (int32_t)::stellar::ManageAssetResultCode::ASSET_UPDATE_TASKS_NOT_FOUND,
      (int32_t)::stellar::ManageAssetResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageAssetSuccess {
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

  uint64 requestID{};
  bool fulfilled{};
  _ext_t ext{};

  ManageAssetSuccess() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageAssetSuccess(_requestID_T &&_requestID,
                              _fulfilled_T &&_fulfilled,
                              _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetSuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageAssetSuccess::_ext_t;
  using case_type = ::stellar::ManageAssetSuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageAssetSuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetSuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetSuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageAssetSuccess>
  : xdr_struct_base<field_ptr<::stellar::ManageAssetSuccess,
                              decltype(::stellar::ManageAssetSuccess::requestID),
                              &::stellar::ManageAssetSuccess::requestID>,
                    field_ptr<::stellar::ManageAssetSuccess,
                              decltype(::stellar::ManageAssetSuccess::fulfilled),
                              &::stellar::ManageAssetSuccess::fulfilled>,
                    field_ptr<::stellar::ManageAssetSuccess,
                              decltype(::stellar::ManageAssetSuccess::ext),
                              &::stellar::ManageAssetSuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageAssetResult {
  using _xdr_case_type = xdr::xdr_traits<ManageAssetResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageAssetSuccess success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageAssetResultCode> &_xdr_case_values() {
    static const std::vector<ManageAssetResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageAssetResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageAssetResultCode::SUCCESS:
      _f(&ManageAssetResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageAssetResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageAssetResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageAssetResult(ManageAssetResultCode which = ManageAssetResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageAssetResult(const ManageAssetResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageAssetResult(ManageAssetResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageAssetResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageAssetResult &operator=(const ManageAssetResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageAssetResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageAssetResult &operator=(ManageAssetResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageAssetResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageAssetResultCode code() const { return ManageAssetResultCode(code_); }
  ManageAssetResult &code(ManageAssetResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageAssetSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAssetResult: success accessed when not selected");
  }
  const ManageAssetSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAssetResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageAssetResult;
  using case_type = ::stellar::ManageAssetResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageAssetResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageAssetResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageAssetResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_OPERATION_MANAGE_ASSET_H_INCLUDED__
