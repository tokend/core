// -*- C++ -*-
// Automatically generated from operation-manage-asset.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_ASSET_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_ASSET_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

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
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct CancelAssetRequest  : xdr::xdr_abstract {
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

  _ext_t ext{};

  CancelAssetRequest() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CancelAssetRequest(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
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

struct UpdateMaxIssuance  : xdr::xdr_abstract {
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

struct ManageAssetOp  : xdr::xdr_abstract {
  struct _request_t : xdr::xdr_abstract {
    struct _createAssetCreationRequest_t  : xdr::xdr_abstract {
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
    struct _createAssetUpdateRequest_t  : xdr::xdr_abstract {
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
    static constexpr const bool _xdr_has_default_case = false;
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
    static constexpr int _xdr_field_number(_xdr_case_type which) {
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
        action_ = which;switch (action_)
{
        case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
new(&createAssetCreationRequest_) _createAssetCreationRequest_t{};
break;
        case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
new(&createAssetUpdateRequest_) _createAssetUpdateRequest_t{};
break;
        case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
new(&cancelRequest_) CancelAssetRequest{};
break;
        case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
new(&changePreissuedSigner_) AssetChangePreissuedSigner{};
break;
        case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
new(&updateMaxIssuance_) UpdateMaxIssuance{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _request_t(ManageAssetAction which = ManageAssetAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
new(&createAssetCreationRequest_) _createAssetCreationRequest_t{};
break;
      case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
new(&createAssetUpdateRequest_) _createAssetUpdateRequest_t{};
break;
      case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
new(&cancelRequest_) CancelAssetRequest{};
break;
      case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
new(&changePreissuedSigner_) AssetChangePreissuedSigner{};
break;
      case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
new(&updateMaxIssuance_) UpdateMaxIssuance{};
break;
}

    }
    _request_t(const _request_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
new(&createAssetCreationRequest_) _createAssetCreationRequest_t(source.createAssetCreationRequest_);
break;
      case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
new(&createAssetUpdateRequest_) _createAssetUpdateRequest_t(source.createAssetUpdateRequest_);
break;
      case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
new(&cancelRequest_) CancelAssetRequest(source.cancelRequest_);
break;
      case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
new(&changePreissuedSigner_) AssetChangePreissuedSigner(source.changePreissuedSigner_);
break;
      case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
new(&updateMaxIssuance_) UpdateMaxIssuance(source.updateMaxIssuance_);
break;
}

    }
    _request_t(_request_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
new(&createAssetCreationRequest_) _createAssetCreationRequest_t(std::move(source.createAssetCreationRequest_));
break;
      case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
new(&createAssetUpdateRequest_) _createAssetUpdateRequest_t(std::move(source.createAssetUpdateRequest_));
break;
      case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
new(&cancelRequest_) CancelAssetRequest(std::move(source.cancelRequest_));
break;
      case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
new(&changePreissuedSigner_) AssetChangePreissuedSigner(std::move(source.changePreissuedSigner_));
break;
      case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
new(&updateMaxIssuance_) UpdateMaxIssuance(std::move(source.updateMaxIssuance_));
break;
}

    }
    ~_request_t() {
switch (action_)
{
    case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
createAssetCreationRequest_.~_createAssetCreationRequest_t();
break;
    case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
createAssetUpdateRequest_.~_createAssetUpdateRequest_t();
break;
    case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
cancelRequest_.~CancelAssetRequest();
break;
    case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
changePreissuedSigner_.~AssetChangePreissuedSigner();
break;
    case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
updateMaxIssuance_.~UpdateMaxIssuance();
break;
}
}

    _request_t &operator=(const _request_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
createAssetCreationRequest_ = source.createAssetCreationRequest_;
break;
      case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
createAssetUpdateRequest_ = source.createAssetUpdateRequest_;
break;
      case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
cancelRequest_ = source.cancelRequest_;
break;
      case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
changePreissuedSigner_ = source.changePreissuedSigner_;
break;
      case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
updateMaxIssuance_ = source.updateMaxIssuance_;
break;
}
}
else {this->~_request_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
new(&createAssetCreationRequest_) _createAssetCreationRequest_t(source.createAssetCreationRequest_);
break;
      case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
new(&createAssetUpdateRequest_) _createAssetUpdateRequest_t(source.createAssetUpdateRequest_);
break;
      case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
new(&cancelRequest_) CancelAssetRequest(source.cancelRequest_);
break;
      case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
new(&changePreissuedSigner_) AssetChangePreissuedSigner(source.changePreissuedSigner_);
break;
      case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
new(&updateMaxIssuance_) UpdateMaxIssuance(source.updateMaxIssuance_);
break;
}
}
      return *this;
    }
    _request_t &operator=(_request_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
createAssetCreationRequest_ = std::move(source.createAssetCreationRequest_);
break;
      case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
createAssetUpdateRequest_ = std::move(source.createAssetUpdateRequest_);
break;
      case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
cancelRequest_ = std::move(source.cancelRequest_);
break;
      case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
changePreissuedSigner_ = std::move(source.changePreissuedSigner_);
break;
      case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
updateMaxIssuance_ = std::move(source.updateMaxIssuance_);
break;
}
}
else {this->~_request_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
new(&createAssetCreationRequest_) _createAssetCreationRequest_t(std::move(source.createAssetCreationRequest_));
break;
      case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
new(&createAssetUpdateRequest_) _createAssetUpdateRequest_t(std::move(source.createAssetUpdateRequest_));
break;
      case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
new(&cancelRequest_) CancelAssetRequest(std::move(source.cancelRequest_));
break;
      case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
new(&changePreissuedSigner_) AssetChangePreissuedSigner(std::move(source.changePreissuedSigner_));
break;
      case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
new(&updateMaxIssuance_) UpdateMaxIssuance(std::move(source.updateMaxIssuance_));
break;
}
}
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
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct ManageAssetSuccess  : xdr::xdr_abstract {
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

struct ManageAssetResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ManageAssetResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageAssetSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageAssetResultCode> &_xdr_case_values() {
    static const std::vector<ManageAssetResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;switch (code_)
{
      case (int32_t)ManageAssetResultCode::SUCCESS:
new(&success_) ManageAssetSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageAssetResult(ManageAssetResultCode which = ManageAssetResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageAssetResultCode::SUCCESS:
new(&success_) ManageAssetSuccess{};
break;
    default:
      break;
}

  }
  ManageAssetResult(const ManageAssetResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAssetResultCode::SUCCESS:
new(&success_) ManageAssetSuccess(source.success_);
break;
    default:
      break;
}

  }
  ManageAssetResult(ManageAssetResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAssetResultCode::SUCCESS:
new(&success_) ManageAssetSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageAssetResult() {
switch (code_)
{
  case (int32_t)ManageAssetResultCode::SUCCESS:
success_.~ManageAssetSuccess();
break;
  default:
    break;
}
}

  ManageAssetResult &operator=(const ManageAssetResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAssetResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageAssetResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageAssetResultCode::SUCCESS:
new(&success_) ManageAssetSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageAssetResult &operator=(ManageAssetResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAssetResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageAssetResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageAssetResultCode::SUCCESS:
new(&success_) ManageAssetSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
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

#endif // !__XDR_OPERATION_MANAGE_ASSET_H_INCLUDED__
