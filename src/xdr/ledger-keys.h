// -*- C++ -*-
// Automatically generated from ledger-keys.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_KEYS_H_INCLUDED__
#define __XDR_LEDGER_KEYS_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct LedgerKey : xdr::xdr_abstract {
  struct _account_t  : xdr::xdr_abstract {
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

    AccountID accountID{};
    _ext_t ext{};

    _account_t() = default;
    template<typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _account_t(_accountID_T &&_accountID,
                        _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
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
  struct _signer_t  : xdr::xdr_abstract {
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
    _ext_t ext{};

    _signer_t() = default;
    template<typename _pubKey_T,
             typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<PublicKey, _pubKey_T>::value
                            && std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _signer_t(_pubKey_T &&_pubKey,
                       _accountID_T &&_accountID,
                       _ext_T &&_ext)
      : pubKey(std::forward<_pubKey_T>(_pubKey)),
        accountID(std::forward<_accountID_T>(_accountID)),
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
  struct _feeState_t  : xdr::xdr_abstract {
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

    Hash hash{};
    int64 lowerBound{};
    int64 upperBound{};
    _ext_t ext{};

    _feeState_t() = default;
    template<typename _hash_T,
             typename _lowerBound_T,
             typename _upperBound_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<Hash, _hash_T>::value
                            && std::is_constructible<int64, _lowerBound_T>::value
                            && std::is_constructible<int64, _upperBound_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _feeState_t(_hash_T &&_hash,
                         _lowerBound_T &&_lowerBound,
                         _upperBound_T &&_upperBound,
                         _ext_T &&_ext)
      : hash(std::forward<_hash_T>(_hash)),
        lowerBound(std::forward<_lowerBound_T>(_lowerBound)),
        upperBound(std::forward<_upperBound_T>(_upperBound)),
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
  struct _balance_t  : xdr::xdr_abstract {
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

    BalanceID balanceID{};
    _ext_t ext{};

    _balance_t() = default;
    template<typename _balanceID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<BalanceID, _balanceID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _balance_t(_balanceID_T &&_balanceID,
                        _ext_T &&_ext)
      : balanceID(std::forward<_balanceID_T>(_balanceID)),
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
  struct _asset_t  : xdr::xdr_abstract {
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

    AssetCode code{};
    _ext_t ext{};

    _asset_t() = default;
    template<typename _code_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AssetCode, _code_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _asset_t(_code_T &&_code,
                      _ext_T &&_ext)
      : code(std::forward<_code_T>(_code)),
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
  struct _reference_t  : xdr::xdr_abstract {
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

    AccountID sender{};
    string64 reference{};
    _ext_t ext{};

    _reference_t() = default;
    template<typename _sender_T,
             typename _reference_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _sender_T>::value
                            && std::is_constructible<string64, _reference_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _reference_t(_sender_T &&_sender,
                          _reference_T &&_reference,
                          _ext_T &&_ext)
      : sender(std::forward<_sender_T>(_sender)),
        reference(std::forward<_reference_T>(_reference)),
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
  struct _stats_t  : xdr::xdr_abstract {
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

    AccountID accountID{};
    _ext_t ext{};

    _stats_t() = default;
    template<typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _stats_t(_accountID_T &&_accountID,
                      _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
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
  struct _accountLimits_t  : xdr::xdr_abstract {
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

    AccountID accountID{};
    _ext_t ext{};

    _accountLimits_t() = default;
    template<typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _accountLimits_t(_accountID_T &&_accountID,
                              _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
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
  struct _assetPair_t  : xdr::xdr_abstract {
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

    AssetCode base{};
    AssetCode quote{};
    _ext_t ext{};

    _assetPair_t() = default;
    template<typename _base_T,
             typename _quote_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AssetCode, _base_T>::value
                            && std::is_constructible<AssetCode, _quote_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _assetPair_t(_base_T &&_base,
                          _quote_T &&_quote,
                          _ext_T &&_ext)
      : base(std::forward<_base_T>(_base)),
        quote(std::forward<_quote_T>(_quote)),
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
  struct _offer_t  : xdr::xdr_abstract {
    uint64 offerID{};
    AccountID ownerID{};

    _offer_t() = default;
    template<typename _offerID_T,
             typename _ownerID_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _offerID_T>::value
                            && std::is_constructible<AccountID, _ownerID_T>::value
                           >::type>
    explicit _offer_t(_offerID_T &&_offerID,
                      _ownerID_T &&_ownerID)
      : offerID(std::forward<_offerID_T>(_offerID)),
        ownerID(std::forward<_ownerID_T>(_ownerID)) {}
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
  struct _reviewableRequest_t  : xdr::xdr_abstract {
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
    _ext_t ext{};

    _reviewableRequest_t() = default;
    template<typename _requestID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _reviewableRequest_t(_requestID_T &&_requestID,
                                  _ext_T &&_ext)
      : requestID(std::forward<_requestID_T>(_requestID)),
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
  struct _externalSystemAccountID_t  : xdr::xdr_abstract {
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

    AccountID accountID{};
    int32 externalSystemType{};
    _ext_t ext{};

    _externalSystemAccountID_t() = default;
    template<typename _accountID_T,
             typename _externalSystemType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<int32, _externalSystemType_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _externalSystemAccountID_t(_accountID_T &&_accountID,
                                        _externalSystemType_T &&_externalSystemType,
                                        _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
        externalSystemType(std::forward<_externalSystemType_T>(_externalSystemType)),
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
  struct _sale_t  : xdr::xdr_abstract {
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

    uint64 saleID{};
    _ext_t ext{};

    _sale_t() = default;
    template<typename _saleID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _saleID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _sale_t(_saleID_T &&_saleID,
                     _ext_T &&_ext)
      : saleID(std::forward<_saleID_T>(_saleID)),
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
  struct _keyValue_t  : xdr::xdr_abstract {
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

    longstring key{};
    _ext_t ext{};

    _keyValue_t() = default;
    template<typename _key_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<longstring, _key_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _keyValue_t(_key_T &&_key,
                         _ext_T &&_ext)
      : key(std::forward<_key_T>(_key)),
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
  struct _accountKYC_t  : xdr::xdr_abstract {
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

    AccountID accountID{};
    _ext_t ext{};

    _accountKYC_t() = default;
    template<typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _accountKYC_t(_accountID_T &&_accountID,
                           _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
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
  struct _externalSystemAccountIDPoolEntry_t  : xdr::xdr_abstract {
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

    uint64 poolEntryID{};
    _ext_t ext{};

    _externalSystemAccountIDPoolEntry_t() = default;
    template<typename _poolEntryID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _poolEntryID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _externalSystemAccountIDPoolEntry_t(_poolEntryID_T &&_poolEntryID,
                                                 _ext_T &&_ext)
      : poolEntryID(std::forward<_poolEntryID_T>(_poolEntryID)),
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
  struct _limitsV2_t  : xdr::xdr_abstract {
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

    uint64 id{};
    _ext_t ext{};

    _limitsV2_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _limitsV2_t(_id_T &&_id,
                         _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _statisticsV2_t  : xdr::xdr_abstract {
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

    uint64 id{};
    _ext_t ext{};

    _statisticsV2_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _statisticsV2_t(_id_T &&_id,
                             _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _pendingStatistics_t  : xdr::xdr_abstract {
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

    uint64 statisticsID{};
    uint64 requestID{};
    _ext_t ext{};

    _pendingStatistics_t() = default;
    template<typename _statisticsID_T,
             typename _requestID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _statisticsID_T>::value
                            && std::is_constructible<uint64, _requestID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _pendingStatistics_t(_statisticsID_T &&_statisticsID,
                                  _requestID_T &&_requestID,
                                  _ext_T &&_ext)
      : statisticsID(std::forward<_statisticsID_T>(_statisticsID)),
        requestID(std::forward<_requestID_T>(_requestID)),
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
  struct _contract_t  : xdr::xdr_abstract {
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

    uint64 contractID{};
    _ext_t ext{};

    _contract_t() = default;
    template<typename _contractID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _contractID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _contract_t(_contractID_T &&_contractID,
                         _ext_T &&_ext)
      : contractID(std::forward<_contractID_T>(_contractID)),
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
  struct _atomicSwapAsk_t  : xdr::xdr_abstract {
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

    uint64 id{};
    _ext_t ext{};

    _atomicSwapAsk_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _atomicSwapAsk_t(_id_T &&_id,
                              _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _accountRole_t  : xdr::xdr_abstract {
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

    uint64 id{};
    _ext_t ext{};

    _accountRole_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _accountRole_t(_id_T &&_id,
                            _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _accountRule_t  : xdr::xdr_abstract {
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

    uint64 id{};
    _ext_t ext{};

    _accountRule_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _accountRule_t(_id_T &&_id,
                            _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _signerRole_t  : xdr::xdr_abstract {
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

    uint64 id{};
    _ext_t ext{};

    _signerRole_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _signerRole_t(_id_T &&_id,
                           _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _signerRule_t  : xdr::xdr_abstract {
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

    uint64 id{};
    _ext_t ext{};

    _signerRule_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _signerRule_t(_id_T &&_id,
                           _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _stamp_t  : xdr::xdr_abstract {
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

    Hash ledgerHash{};
    Hash licenseHash{};
    _ext_t ext{};

    _stamp_t() = default;
    template<typename _ledgerHash_T,
             typename _licenseHash_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<Hash, _ledgerHash_T>::value
                            && std::is_constructible<Hash, _licenseHash_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _stamp_t(_ledgerHash_T &&_ledgerHash,
                      _licenseHash_T &&_licenseHash,
                      _ext_T &&_ext)
      : ledgerHash(std::forward<_ledgerHash_T>(_ledgerHash)),
        licenseHash(std::forward<_licenseHash_T>(_licenseHash)),
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
  struct _license_t  : xdr::xdr_abstract {
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

    Hash licenseHash{};
    _ext_t ext{};

    _license_t() = default;
    template<typename _licenseHash_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<Hash, _licenseHash_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _license_t(_licenseHash_T &&_licenseHash,
                        _ext_T &&_ext)
      : licenseHash(std::forward<_licenseHash_T>(_licenseHash)),
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
  struct _poll_t  : xdr::xdr_abstract {
    uint64 id{};
    EmptyExt ext{};

    _poll_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _poll_t(_id_T &&_id,
                     _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _vote_t  : xdr::xdr_abstract {
    uint64 pollID{};
    AccountID voterID{};
    EmptyExt ext{};

    _vote_t() = default;
    template<typename _pollID_T,
             typename _voterID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _pollID_T>::value
                            && std::is_constructible<AccountID, _voterID_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _vote_t(_pollID_T &&_pollID,
                     _voterID_T &&_voterID,
                     _ext_T &&_ext)
      : pollID(std::forward<_pollID_T>(_pollID)),
        voterID(std::forward<_voterID_T>(_voterID)),
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
  struct _accountSpecificRule_t  : xdr::xdr_abstract {
    uint64 id{};
    EmptyExt ext{};

    _accountSpecificRule_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _accountSpecificRule_t(_id_T &&_id,
                                    _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _swap_t  : xdr::xdr_abstract {
    uint64 id{};
    EmptyExt ext{};

    _swap_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _swap_t(_id_T &&_id,
                     _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _data_t  : xdr::xdr_abstract {
    uint64 id{};
    EmptyExt ext{};

    _data_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _data_t(_id_T &&_id,
                     _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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
  struct _deferredPayment_t  : xdr::xdr_abstract {
    uint64 id{};
    EmptyExt ext{};

    _deferredPayment_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _deferredPayment_t(_id_T &&_id,
                                _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
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

  using _xdr_case_type = xdr::xdr_traits<LedgerEntryType>::case_type;
private:
  _xdr_case_type type_;
  union {
    _account_t account_;
    _signer_t signer_;
    _feeState_t feeState_;
    _balance_t balance_;
    _asset_t asset_;
    _reference_t reference_;
    _stats_t stats_;
    _accountLimits_t accountLimits_;
    _assetPair_t assetPair_;
    _offer_t offer_;
    _reviewableRequest_t reviewableRequest_;
    _externalSystemAccountID_t externalSystemAccountID_;
    _sale_t sale_;
    _keyValue_t keyValue_;
    _accountKYC_t accountKYC_;
    _externalSystemAccountIDPoolEntry_t externalSystemAccountIDPoolEntry_;
    _limitsV2_t limitsV2_;
    _statisticsV2_t statisticsV2_;
    _pendingStatistics_t pendingStatistics_;
    _contract_t contract_;
    _atomicSwapAsk_t atomicSwapAsk_;
    _accountRole_t accountRole_;
    _accountRule_t accountRule_;
    _signerRole_t signerRole_;
    _signerRule_t signerRule_;
    _stamp_t stamp_;
    _license_t license_;
    _poll_t poll_;
    _vote_t vote_;
    _accountSpecificRule_t accountSpecificRule_;
    _swap_t swap_;
    _data_t data_;
    _deferredPayment_t deferredPayment_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerEntryType> &_xdr_case_values() {
    static const std::vector<LedgerEntryType> _xdr_disc_vec {
      LedgerEntryType::ACCOUNT,
      LedgerEntryType::SIGNER,
      LedgerEntryType::FEE,
      LedgerEntryType::BALANCE,
      LedgerEntryType::ASSET,
      LedgerEntryType::REFERENCE_ENTRY,
      LedgerEntryType::STATISTICS,
      LedgerEntryType::ACCOUNT_LIMITS,
      LedgerEntryType::ASSET_PAIR,
      LedgerEntryType::OFFER_ENTRY,
      LedgerEntryType::REVIEWABLE_REQUEST,
      LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID,
      LedgerEntryType::SALE,
      LedgerEntryType::KEY_VALUE,
      LedgerEntryType::ACCOUNT_KYC,
      LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY,
      LedgerEntryType::LIMITS_V2,
      LedgerEntryType::STATISTICS_V2,
      LedgerEntryType::PENDING_STATISTICS,
      LedgerEntryType::CONTRACT,
      LedgerEntryType::ATOMIC_SWAP_ASK,
      LedgerEntryType::ACCOUNT_ROLE,
      LedgerEntryType::ACCOUNT_RULE,
      LedgerEntryType::SIGNER_ROLE,
      LedgerEntryType::SIGNER_RULE,
      LedgerEntryType::STAMP,
      LedgerEntryType::LICENSE,
      LedgerEntryType::POLL,
      LedgerEntryType::VOTE,
      LedgerEntryType::ACCOUNT_SPECIFIC_RULE,
      LedgerEntryType::SWAP,
      LedgerEntryType::DATA,
      LedgerEntryType::DEFERRED_PAYMENT
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LedgerEntryType::ACCOUNT ? 1
      : which == (int32_t)LedgerEntryType::SIGNER ? 2
      : which == (int32_t)LedgerEntryType::FEE ? 3
      : which == (int32_t)LedgerEntryType::BALANCE ? 4
      : which == (int32_t)LedgerEntryType::ASSET ? 5
      : which == (int32_t)LedgerEntryType::REFERENCE_ENTRY ? 6
      : which == (int32_t)LedgerEntryType::STATISTICS ? 7
      : which == (int32_t)LedgerEntryType::ACCOUNT_LIMITS ? 8
      : which == (int32_t)LedgerEntryType::ASSET_PAIR ? 9
      : which == (int32_t)LedgerEntryType::OFFER_ENTRY ? 10
      : which == (int32_t)LedgerEntryType::REVIEWABLE_REQUEST ? 11
      : which == (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID ? 12
      : which == (int32_t)LedgerEntryType::SALE ? 13
      : which == (int32_t)LedgerEntryType::KEY_VALUE ? 14
      : which == (int32_t)LedgerEntryType::ACCOUNT_KYC ? 15
      : which == (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY ? 16
      : which == (int32_t)LedgerEntryType::LIMITS_V2 ? 17
      : which == (int32_t)LedgerEntryType::STATISTICS_V2 ? 18
      : which == (int32_t)LedgerEntryType::PENDING_STATISTICS ? 19
      : which == (int32_t)LedgerEntryType::CONTRACT ? 20
      : which == (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK ? 21
      : which == (int32_t)LedgerEntryType::ACCOUNT_ROLE ? 22
      : which == (int32_t)LedgerEntryType::ACCOUNT_RULE ? 23
      : which == (int32_t)LedgerEntryType::SIGNER_ROLE ? 24
      : which == (int32_t)LedgerEntryType::SIGNER_RULE ? 25
      : which == (int32_t)LedgerEntryType::STAMP ? 26
      : which == (int32_t)LedgerEntryType::LICENSE ? 27
      : which == (int32_t)LedgerEntryType::POLL ? 28
      : which == (int32_t)LedgerEntryType::VOTE ? 29
      : which == (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE ? 30
      : which == (int32_t)LedgerEntryType::SWAP ? 31
      : which == (int32_t)LedgerEntryType::DATA ? 32
      : which == (int32_t)LedgerEntryType::DEFERRED_PAYMENT ? 33
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LedgerEntryType::ACCOUNT:
      _f(&LedgerKey::account_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SIGNER:
      _f(&LedgerKey::signer_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::FEE:
      _f(&LedgerKey::feeState_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::BALANCE:
      _f(&LedgerKey::balance_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ASSET:
      _f(&LedgerKey::asset_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
      _f(&LedgerKey::reference_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::STATISTICS:
      _f(&LedgerKey::stats_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
      _f(&LedgerKey::accountLimits_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
      _f(&LedgerKey::assetPair_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
      _f(&LedgerKey::offer_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
      _f(&LedgerKey::reviewableRequest_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
      _f(&LedgerKey::externalSystemAccountID_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SALE:
      _f(&LedgerKey::sale_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::KEY_VALUE:
      _f(&LedgerKey::keyValue_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
      _f(&LedgerKey::accountKYC_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
      _f(&LedgerKey::externalSystemAccountIDPoolEntry_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::LIMITS_V2:
      _f(&LedgerKey::limitsV2_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
      _f(&LedgerKey::statisticsV2_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
      _f(&LedgerKey::pendingStatistics_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::CONTRACT:
      _f(&LedgerKey::contract_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
      _f(&LedgerKey::atomicSwapAsk_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
      _f(&LedgerKey::accountRole_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
      _f(&LedgerKey::accountRule_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
      _f(&LedgerKey::signerRole_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
      _f(&LedgerKey::signerRule_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::STAMP:
      _f(&LedgerKey::stamp_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::LICENSE:
      _f(&LedgerKey::license_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::POLL:
      _f(&LedgerKey::poll_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::VOTE:
      _f(&LedgerKey::vote_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
      _f(&LedgerKey::accountSpecificRule_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SWAP:
      _f(&LedgerKey::swap_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::DATA:
      _f(&LedgerKey::data_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
      _f(&LedgerKey::deferredPayment_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in LedgerKey");
    if (fnum != _xdr_field_number(type_)) {
      this->~LedgerKey();
      type_ = which;switch (type_)
{
      case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) _account_t{};
break;
      case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t{};
break;
      case (int32_t)LedgerEntryType::FEE:
new(&feeState_) _feeState_t{};
break;
      case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) _balance_t{};
break;
      case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t{};
break;
      case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) _reference_t{};
break;
      case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) _stats_t{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) _accountLimits_t{};
break;
      case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) _assetPair_t{};
break;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t{};
break;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t{};
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) _externalSystemAccountID_t{};
break;
      case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t{};
break;
      case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) _accountKYC_t{};
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) _externalSystemAccountIDPoolEntry_t{};
break;
      case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) _limitsV2_t{};
break;
      case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) _statisticsV2_t{};
break;
      case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) _pendingStatistics_t{};
break;
      case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) _contract_t{};
break;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) _accountRole_t{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) _accountRule_t{};
break;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t{};
break;
      case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t{};
break;
      case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) _stamp_t{};
break;
      case (int32_t)LedgerEntryType::LICENSE:
new(&license_) _license_t{};
break;
      case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t{};
break;
      case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) _accountSpecificRule_t{};
break;
      case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t{};
break;
      case (int32_t)LedgerEntryType::DATA:
new(&data_) _data_t{};
break;
      case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) _deferredPayment_t{};
break;
}

    }
    else
      type_ = which;
  }
  explicit LedgerKey(LedgerEntryType which = LedgerEntryType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) _account_t{};
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t{};
break;
    case (int32_t)LedgerEntryType::FEE:
new(&feeState_) _feeState_t{};
break;
    case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) _balance_t{};
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t{};
break;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) _reference_t{};
break;
    case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) _stats_t{};
break;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) _accountLimits_t{};
break;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) _assetPair_t{};
break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t{};
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t{};
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) _externalSystemAccountID_t{};
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t{};
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t{};
break;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) _accountKYC_t{};
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) _externalSystemAccountIDPoolEntry_t{};
break;
    case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) _limitsV2_t{};
break;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) _statisticsV2_t{};
break;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) _pendingStatistics_t{};
break;
    case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) _contract_t{};
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t{};
break;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) _accountRole_t{};
break;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) _accountRule_t{};
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t{};
break;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t{};
break;
    case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) _stamp_t{};
break;
    case (int32_t)LedgerEntryType::LICENSE:
new(&license_) _license_t{};
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t{};
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t{};
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) _accountSpecificRule_t{};
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t{};
break;
    case (int32_t)LedgerEntryType::DATA:
new(&data_) _data_t{};
break;
    case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) _deferredPayment_t{};
break;
}

  }
  LedgerKey(const LedgerKey &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) _account_t(source.account_);
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t(source.signer_);
break;
    case (int32_t)LedgerEntryType::FEE:
new(&feeState_) _feeState_t(source.feeState_);
break;
    case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) _balance_t(source.balance_);
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(source.asset_);
break;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) _reference_t(source.reference_);
break;
    case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) _stats_t(source.stats_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) _accountLimits_t(source.accountLimits_);
break;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) _assetPair_t(source.assetPair_);
break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t(source.offer_);
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(source.reviewableRequest_);
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) _externalSystemAccountID_t(source.externalSystemAccountID_);
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t(source.sale_);
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t(source.keyValue_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) _accountKYC_t(source.accountKYC_);
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) _externalSystemAccountIDPoolEntry_t(source.externalSystemAccountIDPoolEntry_);
break;
    case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) _limitsV2_t(source.limitsV2_);
break;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) _statisticsV2_t(source.statisticsV2_);
break;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) _pendingStatistics_t(source.pendingStatistics_);
break;
    case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) _contract_t(source.contract_);
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t(source.atomicSwapAsk_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) _accountRole_t(source.accountRole_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) _accountRule_t(source.accountRule_);
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t(source.signerRole_);
break;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t(source.signerRule_);
break;
    case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) _stamp_t(source.stamp_);
break;
    case (int32_t)LedgerEntryType::LICENSE:
new(&license_) _license_t(source.license_);
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t(source.poll_);
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t(source.vote_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) _accountSpecificRule_t(source.accountSpecificRule_);
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t(source.swap_);
break;
    case (int32_t)LedgerEntryType::DATA:
new(&data_) _data_t(source.data_);
break;
    case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) _deferredPayment_t(source.deferredPayment_);
break;
}

  }
  LedgerKey(LedgerKey &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) _account_t(std::move(source.account_));
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t(std::move(source.signer_));
break;
    case (int32_t)LedgerEntryType::FEE:
new(&feeState_) _feeState_t(std::move(source.feeState_));
break;
    case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) _balance_t(std::move(source.balance_));
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(std::move(source.asset_));
break;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) _reference_t(std::move(source.reference_));
break;
    case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) _stats_t(std::move(source.stats_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) _accountLimits_t(std::move(source.accountLimits_));
break;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) _assetPair_t(std::move(source.assetPair_));
break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t(std::move(source.offer_));
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(std::move(source.reviewableRequest_));
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) _externalSystemAccountID_t(std::move(source.externalSystemAccountID_));
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t(std::move(source.sale_));
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t(std::move(source.keyValue_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) _accountKYC_t(std::move(source.accountKYC_));
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) _externalSystemAccountIDPoolEntry_t(std::move(source.externalSystemAccountIDPoolEntry_));
break;
    case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) _limitsV2_t(std::move(source.limitsV2_));
break;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) _statisticsV2_t(std::move(source.statisticsV2_));
break;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) _pendingStatistics_t(std::move(source.pendingStatistics_));
break;
    case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) _contract_t(std::move(source.contract_));
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t(std::move(source.atomicSwapAsk_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) _accountRole_t(std::move(source.accountRole_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) _accountRule_t(std::move(source.accountRule_));
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t(std::move(source.signerRole_));
break;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t(std::move(source.signerRule_));
break;
    case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) _stamp_t(std::move(source.stamp_));
break;
    case (int32_t)LedgerEntryType::LICENSE:
new(&license_) _license_t(std::move(source.license_));
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t(std::move(source.poll_));
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t(std::move(source.vote_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) _accountSpecificRule_t(std::move(source.accountSpecificRule_));
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t(std::move(source.swap_));
break;
    case (int32_t)LedgerEntryType::DATA:
new(&data_) _data_t(std::move(source.data_));
break;
    case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) _deferredPayment_t(std::move(source.deferredPayment_));
break;
}

  }
  ~LedgerKey() {
switch (type_)
{
  case (int32_t)LedgerEntryType::ACCOUNT:
account_.~_account_t();
break;
  case (int32_t)LedgerEntryType::SIGNER:
signer_.~_signer_t();
break;
  case (int32_t)LedgerEntryType::FEE:
feeState_.~_feeState_t();
break;
  case (int32_t)LedgerEntryType::BALANCE:
balance_.~_balance_t();
break;
  case (int32_t)LedgerEntryType::ASSET:
asset_.~_asset_t();
break;
  case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
reference_.~_reference_t();
break;
  case (int32_t)LedgerEntryType::STATISTICS:
stats_.~_stats_t();
break;
  case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
accountLimits_.~_accountLimits_t();
break;
  case (int32_t)LedgerEntryType::ASSET_PAIR:
assetPair_.~_assetPair_t();
break;
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
offer_.~_offer_t();
break;
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_.~_reviewableRequest_t();
break;
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
externalSystemAccountID_.~_externalSystemAccountID_t();
break;
  case (int32_t)LedgerEntryType::SALE:
sale_.~_sale_t();
break;
  case (int32_t)LedgerEntryType::KEY_VALUE:
keyValue_.~_keyValue_t();
break;
  case (int32_t)LedgerEntryType::ACCOUNT_KYC:
accountKYC_.~_accountKYC_t();
break;
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
externalSystemAccountIDPoolEntry_.~_externalSystemAccountIDPoolEntry_t();
break;
  case (int32_t)LedgerEntryType::LIMITS_V2:
limitsV2_.~_limitsV2_t();
break;
  case (int32_t)LedgerEntryType::STATISTICS_V2:
statisticsV2_.~_statisticsV2_t();
break;
  case (int32_t)LedgerEntryType::PENDING_STATISTICS:
pendingStatistics_.~_pendingStatistics_t();
break;
  case (int32_t)LedgerEntryType::CONTRACT:
contract_.~_contract_t();
break;
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
atomicSwapAsk_.~_atomicSwapAsk_t();
break;
  case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
accountRole_.~_accountRole_t();
break;
  case (int32_t)LedgerEntryType::ACCOUNT_RULE:
accountRule_.~_accountRule_t();
break;
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
signerRole_.~_signerRole_t();
break;
  case (int32_t)LedgerEntryType::SIGNER_RULE:
signerRule_.~_signerRule_t();
break;
  case (int32_t)LedgerEntryType::STAMP:
stamp_.~_stamp_t();
break;
  case (int32_t)LedgerEntryType::LICENSE:
license_.~_license_t();
break;
  case (int32_t)LedgerEntryType::POLL:
poll_.~_poll_t();
break;
  case (int32_t)LedgerEntryType::VOTE:
vote_.~_vote_t();
break;
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
accountSpecificRule_.~_accountSpecificRule_t();
break;
  case (int32_t)LedgerEntryType::SWAP:
swap_.~_swap_t();
break;
  case (int32_t)LedgerEntryType::DATA:
data_.~_data_t();
break;
  case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
deferredPayment_.~_deferredPayment_t();
break;
}
}

  LedgerKey &operator=(const LedgerKey &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
account_ = source.account_;
break;
    case (int32_t)LedgerEntryType::SIGNER:
signer_ = source.signer_;
break;
    case (int32_t)LedgerEntryType::FEE:
feeState_ = source.feeState_;
break;
    case (int32_t)LedgerEntryType::BALANCE:
balance_ = source.balance_;
break;
    case (int32_t)LedgerEntryType::ASSET:
asset_ = source.asset_;
break;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
reference_ = source.reference_;
break;
    case (int32_t)LedgerEntryType::STATISTICS:
stats_ = source.stats_;
break;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
accountLimits_ = source.accountLimits_;
break;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
assetPair_ = source.assetPair_;
break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
offer_ = source.offer_;
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_ = source.reviewableRequest_;
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
externalSystemAccountID_ = source.externalSystemAccountID_;
break;
    case (int32_t)LedgerEntryType::SALE:
sale_ = source.sale_;
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
keyValue_ = source.keyValue_;
break;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
accountKYC_ = source.accountKYC_;
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
externalSystemAccountIDPoolEntry_ = source.externalSystemAccountIDPoolEntry_;
break;
    case (int32_t)LedgerEntryType::LIMITS_V2:
limitsV2_ = source.limitsV2_;
break;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
statisticsV2_ = source.statisticsV2_;
break;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
pendingStatistics_ = source.pendingStatistics_;
break;
    case (int32_t)LedgerEntryType::CONTRACT:
contract_ = source.contract_;
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
atomicSwapAsk_ = source.atomicSwapAsk_;
break;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
accountRole_ = source.accountRole_;
break;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
accountRule_ = source.accountRule_;
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
signerRole_ = source.signerRole_;
break;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
signerRule_ = source.signerRule_;
break;
    case (int32_t)LedgerEntryType::STAMP:
stamp_ = source.stamp_;
break;
    case (int32_t)LedgerEntryType::LICENSE:
license_ = source.license_;
break;
    case (int32_t)LedgerEntryType::POLL:
poll_ = source.poll_;
break;
    case (int32_t)LedgerEntryType::VOTE:
vote_ = source.vote_;
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
accountSpecificRule_ = source.accountSpecificRule_;
break;
    case (int32_t)LedgerEntryType::SWAP:
swap_ = source.swap_;
break;
    case (int32_t)LedgerEntryType::DATA:
data_ = source.data_;
break;
    case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
deferredPayment_ = source.deferredPayment_;
break;
}
}
else {this->~LedgerKey();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) _account_t(source.account_);
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t(source.signer_);
break;
    case (int32_t)LedgerEntryType::FEE:
new(&feeState_) _feeState_t(source.feeState_);
break;
    case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) _balance_t(source.balance_);
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(source.asset_);
break;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) _reference_t(source.reference_);
break;
    case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) _stats_t(source.stats_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) _accountLimits_t(source.accountLimits_);
break;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) _assetPair_t(source.assetPair_);
break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t(source.offer_);
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(source.reviewableRequest_);
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) _externalSystemAccountID_t(source.externalSystemAccountID_);
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t(source.sale_);
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t(source.keyValue_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) _accountKYC_t(source.accountKYC_);
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) _externalSystemAccountIDPoolEntry_t(source.externalSystemAccountIDPoolEntry_);
break;
    case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) _limitsV2_t(source.limitsV2_);
break;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) _statisticsV2_t(source.statisticsV2_);
break;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) _pendingStatistics_t(source.pendingStatistics_);
break;
    case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) _contract_t(source.contract_);
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t(source.atomicSwapAsk_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) _accountRole_t(source.accountRole_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) _accountRule_t(source.accountRule_);
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t(source.signerRole_);
break;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t(source.signerRule_);
break;
    case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) _stamp_t(source.stamp_);
break;
    case (int32_t)LedgerEntryType::LICENSE:
new(&license_) _license_t(source.license_);
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t(source.poll_);
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t(source.vote_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) _accountSpecificRule_t(source.accountSpecificRule_);
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t(source.swap_);
break;
    case (int32_t)LedgerEntryType::DATA:
new(&data_) _data_t(source.data_);
break;
    case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) _deferredPayment_t(source.deferredPayment_);
break;
}
}
    return *this;
  }
  LedgerKey &operator=(LedgerKey &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
account_ = std::move(source.account_);
break;
    case (int32_t)LedgerEntryType::SIGNER:
signer_ = std::move(source.signer_);
break;
    case (int32_t)LedgerEntryType::FEE:
feeState_ = std::move(source.feeState_);
break;
    case (int32_t)LedgerEntryType::BALANCE:
balance_ = std::move(source.balance_);
break;
    case (int32_t)LedgerEntryType::ASSET:
asset_ = std::move(source.asset_);
break;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
reference_ = std::move(source.reference_);
break;
    case (int32_t)LedgerEntryType::STATISTICS:
stats_ = std::move(source.stats_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
accountLimits_ = std::move(source.accountLimits_);
break;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
assetPair_ = std::move(source.assetPair_);
break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
offer_ = std::move(source.offer_);
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_ = std::move(source.reviewableRequest_);
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
externalSystemAccountID_ = std::move(source.externalSystemAccountID_);
break;
    case (int32_t)LedgerEntryType::SALE:
sale_ = std::move(source.sale_);
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
keyValue_ = std::move(source.keyValue_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
accountKYC_ = std::move(source.accountKYC_);
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
externalSystemAccountIDPoolEntry_ = std::move(source.externalSystemAccountIDPoolEntry_);
break;
    case (int32_t)LedgerEntryType::LIMITS_V2:
limitsV2_ = std::move(source.limitsV2_);
break;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
statisticsV2_ = std::move(source.statisticsV2_);
break;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
pendingStatistics_ = std::move(source.pendingStatistics_);
break;
    case (int32_t)LedgerEntryType::CONTRACT:
contract_ = std::move(source.contract_);
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
atomicSwapAsk_ = std::move(source.atomicSwapAsk_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
accountRole_ = std::move(source.accountRole_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
accountRule_ = std::move(source.accountRule_);
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
signerRole_ = std::move(source.signerRole_);
break;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
signerRule_ = std::move(source.signerRule_);
break;
    case (int32_t)LedgerEntryType::STAMP:
stamp_ = std::move(source.stamp_);
break;
    case (int32_t)LedgerEntryType::LICENSE:
license_ = std::move(source.license_);
break;
    case (int32_t)LedgerEntryType::POLL:
poll_ = std::move(source.poll_);
break;
    case (int32_t)LedgerEntryType::VOTE:
vote_ = std::move(source.vote_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
accountSpecificRule_ = std::move(source.accountSpecificRule_);
break;
    case (int32_t)LedgerEntryType::SWAP:
swap_ = std::move(source.swap_);
break;
    case (int32_t)LedgerEntryType::DATA:
data_ = std::move(source.data_);
break;
    case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
deferredPayment_ = std::move(source.deferredPayment_);
break;
}
}
else {this->~LedgerKey();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) _account_t(std::move(source.account_));
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t(std::move(source.signer_));
break;
    case (int32_t)LedgerEntryType::FEE:
new(&feeState_) _feeState_t(std::move(source.feeState_));
break;
    case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) _balance_t(std::move(source.balance_));
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(std::move(source.asset_));
break;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) _reference_t(std::move(source.reference_));
break;
    case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) _stats_t(std::move(source.stats_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) _accountLimits_t(std::move(source.accountLimits_));
break;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) _assetPair_t(std::move(source.assetPair_));
break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t(std::move(source.offer_));
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(std::move(source.reviewableRequest_));
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) _externalSystemAccountID_t(std::move(source.externalSystemAccountID_));
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t(std::move(source.sale_));
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t(std::move(source.keyValue_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) _accountKYC_t(std::move(source.accountKYC_));
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) _externalSystemAccountIDPoolEntry_t(std::move(source.externalSystemAccountIDPoolEntry_));
break;
    case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) _limitsV2_t(std::move(source.limitsV2_));
break;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) _statisticsV2_t(std::move(source.statisticsV2_));
break;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) _pendingStatistics_t(std::move(source.pendingStatistics_));
break;
    case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) _contract_t(std::move(source.contract_));
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t(std::move(source.atomicSwapAsk_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) _accountRole_t(std::move(source.accountRole_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) _accountRule_t(std::move(source.accountRule_));
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t(std::move(source.signerRole_));
break;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t(std::move(source.signerRule_));
break;
    case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) _stamp_t(std::move(source.stamp_));
break;
    case (int32_t)LedgerEntryType::LICENSE:
new(&license_) _license_t(std::move(source.license_));
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t(std::move(source.poll_));
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t(std::move(source.vote_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) _accountSpecificRule_t(std::move(source.accountSpecificRule_));
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t(std::move(source.swap_));
break;
    case (int32_t)LedgerEntryType::DATA:
new(&data_) _data_t(std::move(source.data_));
break;
    case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) _deferredPayment_t(std::move(source.deferredPayment_));
break;
}
}
    return *this;
  }

  LedgerEntryType type() const { return LedgerEntryType(type_); }
  LedgerKey &type(LedgerEntryType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _account_t &account() {
    if (_xdr_field_number(type_) == 1)
      return account_;
    throw xdr::xdr_wrong_union("LedgerKey: account accessed when not selected");
  }
  const _account_t &account() const {
    if (_xdr_field_number(type_) == 1)
      return account_;
    throw xdr::xdr_wrong_union("LedgerKey: account accessed when not selected");
  }
  _signer_t &signer() {
    if (_xdr_field_number(type_) == 2)
      return signer_;
    throw xdr::xdr_wrong_union("LedgerKey: signer accessed when not selected");
  }
  const _signer_t &signer() const {
    if (_xdr_field_number(type_) == 2)
      return signer_;
    throw xdr::xdr_wrong_union("LedgerKey: signer accessed when not selected");
  }
  _feeState_t &feeState() {
    if (_xdr_field_number(type_) == 3)
      return feeState_;
    throw xdr::xdr_wrong_union("LedgerKey: feeState accessed when not selected");
  }
  const _feeState_t &feeState() const {
    if (_xdr_field_number(type_) == 3)
      return feeState_;
    throw xdr::xdr_wrong_union("LedgerKey: feeState accessed when not selected");
  }
  _balance_t &balance() {
    if (_xdr_field_number(type_) == 4)
      return balance_;
    throw xdr::xdr_wrong_union("LedgerKey: balance accessed when not selected");
  }
  const _balance_t &balance() const {
    if (_xdr_field_number(type_) == 4)
      return balance_;
    throw xdr::xdr_wrong_union("LedgerKey: balance accessed when not selected");
  }
  _asset_t &asset() {
    if (_xdr_field_number(type_) == 5)
      return asset_;
    throw xdr::xdr_wrong_union("LedgerKey: asset accessed when not selected");
  }
  const _asset_t &asset() const {
    if (_xdr_field_number(type_) == 5)
      return asset_;
    throw xdr::xdr_wrong_union("LedgerKey: asset accessed when not selected");
  }
  _reference_t &reference() {
    if (_xdr_field_number(type_) == 6)
      return reference_;
    throw xdr::xdr_wrong_union("LedgerKey: reference accessed when not selected");
  }
  const _reference_t &reference() const {
    if (_xdr_field_number(type_) == 6)
      return reference_;
    throw xdr::xdr_wrong_union("LedgerKey: reference accessed when not selected");
  }
  _stats_t &stats() {
    if (_xdr_field_number(type_) == 7)
      return stats_;
    throw xdr::xdr_wrong_union("LedgerKey: stats accessed when not selected");
  }
  const _stats_t &stats() const {
    if (_xdr_field_number(type_) == 7)
      return stats_;
    throw xdr::xdr_wrong_union("LedgerKey: stats accessed when not selected");
  }
  _accountLimits_t &accountLimits() {
    if (_xdr_field_number(type_) == 8)
      return accountLimits_;
    throw xdr::xdr_wrong_union("LedgerKey: accountLimits accessed when not selected");
  }
  const _accountLimits_t &accountLimits() const {
    if (_xdr_field_number(type_) == 8)
      return accountLimits_;
    throw xdr::xdr_wrong_union("LedgerKey: accountLimits accessed when not selected");
  }
  _assetPair_t &assetPair() {
    if (_xdr_field_number(type_) == 9)
      return assetPair_;
    throw xdr::xdr_wrong_union("LedgerKey: assetPair accessed when not selected");
  }
  const _assetPair_t &assetPair() const {
    if (_xdr_field_number(type_) == 9)
      return assetPair_;
    throw xdr::xdr_wrong_union("LedgerKey: assetPair accessed when not selected");
  }
  _offer_t &offer() {
    if (_xdr_field_number(type_) == 10)
      return offer_;
    throw xdr::xdr_wrong_union("LedgerKey: offer accessed when not selected");
  }
  const _offer_t &offer() const {
    if (_xdr_field_number(type_) == 10)
      return offer_;
    throw xdr::xdr_wrong_union("LedgerKey: offer accessed when not selected");
  }
  _reviewableRequest_t &reviewableRequest() {
    if (_xdr_field_number(type_) == 11)
      return reviewableRequest_;
    throw xdr::xdr_wrong_union("LedgerKey: reviewableRequest accessed when not selected");
  }
  const _reviewableRequest_t &reviewableRequest() const {
    if (_xdr_field_number(type_) == 11)
      return reviewableRequest_;
    throw xdr::xdr_wrong_union("LedgerKey: reviewableRequest accessed when not selected");
  }
  _externalSystemAccountID_t &externalSystemAccountID() {
    if (_xdr_field_number(type_) == 12)
      return externalSystemAccountID_;
    throw xdr::xdr_wrong_union("LedgerKey: externalSystemAccountID accessed when not selected");
  }
  const _externalSystemAccountID_t &externalSystemAccountID() const {
    if (_xdr_field_number(type_) == 12)
      return externalSystemAccountID_;
    throw xdr::xdr_wrong_union("LedgerKey: externalSystemAccountID accessed when not selected");
  }
  _sale_t &sale() {
    if (_xdr_field_number(type_) == 13)
      return sale_;
    throw xdr::xdr_wrong_union("LedgerKey: sale accessed when not selected");
  }
  const _sale_t &sale() const {
    if (_xdr_field_number(type_) == 13)
      return sale_;
    throw xdr::xdr_wrong_union("LedgerKey: sale accessed when not selected");
  }
  _keyValue_t &keyValue() {
    if (_xdr_field_number(type_) == 14)
      return keyValue_;
    throw xdr::xdr_wrong_union("LedgerKey: keyValue accessed when not selected");
  }
  const _keyValue_t &keyValue() const {
    if (_xdr_field_number(type_) == 14)
      return keyValue_;
    throw xdr::xdr_wrong_union("LedgerKey: keyValue accessed when not selected");
  }
  _accountKYC_t &accountKYC() {
    if (_xdr_field_number(type_) == 15)
      return accountKYC_;
    throw xdr::xdr_wrong_union("LedgerKey: accountKYC accessed when not selected");
  }
  const _accountKYC_t &accountKYC() const {
    if (_xdr_field_number(type_) == 15)
      return accountKYC_;
    throw xdr::xdr_wrong_union("LedgerKey: accountKYC accessed when not selected");
  }
  _externalSystemAccountIDPoolEntry_t &externalSystemAccountIDPoolEntry() {
    if (_xdr_field_number(type_) == 16)
      return externalSystemAccountIDPoolEntry_;
    throw xdr::xdr_wrong_union("LedgerKey: externalSystemAccountIDPoolEntry accessed when not selected");
  }
  const _externalSystemAccountIDPoolEntry_t &externalSystemAccountIDPoolEntry() const {
    if (_xdr_field_number(type_) == 16)
      return externalSystemAccountIDPoolEntry_;
    throw xdr::xdr_wrong_union("LedgerKey: externalSystemAccountIDPoolEntry accessed when not selected");
  }
  _limitsV2_t &limitsV2() {
    if (_xdr_field_number(type_) == 17)
      return limitsV2_;
    throw xdr::xdr_wrong_union("LedgerKey: limitsV2 accessed when not selected");
  }
  const _limitsV2_t &limitsV2() const {
    if (_xdr_field_number(type_) == 17)
      return limitsV2_;
    throw xdr::xdr_wrong_union("LedgerKey: limitsV2 accessed when not selected");
  }
  _statisticsV2_t &statisticsV2() {
    if (_xdr_field_number(type_) == 18)
      return statisticsV2_;
    throw xdr::xdr_wrong_union("LedgerKey: statisticsV2 accessed when not selected");
  }
  const _statisticsV2_t &statisticsV2() const {
    if (_xdr_field_number(type_) == 18)
      return statisticsV2_;
    throw xdr::xdr_wrong_union("LedgerKey: statisticsV2 accessed when not selected");
  }
  _pendingStatistics_t &pendingStatistics() {
    if (_xdr_field_number(type_) == 19)
      return pendingStatistics_;
    throw xdr::xdr_wrong_union("LedgerKey: pendingStatistics accessed when not selected");
  }
  const _pendingStatistics_t &pendingStatistics() const {
    if (_xdr_field_number(type_) == 19)
      return pendingStatistics_;
    throw xdr::xdr_wrong_union("LedgerKey: pendingStatistics accessed when not selected");
  }
  _contract_t &contract() {
    if (_xdr_field_number(type_) == 20)
      return contract_;
    throw xdr::xdr_wrong_union("LedgerKey: contract accessed when not selected");
  }
  const _contract_t &contract() const {
    if (_xdr_field_number(type_) == 20)
      return contract_;
    throw xdr::xdr_wrong_union("LedgerKey: contract accessed when not selected");
  }
  _atomicSwapAsk_t &atomicSwapAsk() {
    if (_xdr_field_number(type_) == 21)
      return atomicSwapAsk_;
    throw xdr::xdr_wrong_union("LedgerKey: atomicSwapAsk accessed when not selected");
  }
  const _atomicSwapAsk_t &atomicSwapAsk() const {
    if (_xdr_field_number(type_) == 21)
      return atomicSwapAsk_;
    throw xdr::xdr_wrong_union("LedgerKey: atomicSwapAsk accessed when not selected");
  }
  _accountRole_t &accountRole() {
    if (_xdr_field_number(type_) == 22)
      return accountRole_;
    throw xdr::xdr_wrong_union("LedgerKey: accountRole accessed when not selected");
  }
  const _accountRole_t &accountRole() const {
    if (_xdr_field_number(type_) == 22)
      return accountRole_;
    throw xdr::xdr_wrong_union("LedgerKey: accountRole accessed when not selected");
  }
  _accountRule_t &accountRule() {
    if (_xdr_field_number(type_) == 23)
      return accountRule_;
    throw xdr::xdr_wrong_union("LedgerKey: accountRule accessed when not selected");
  }
  const _accountRule_t &accountRule() const {
    if (_xdr_field_number(type_) == 23)
      return accountRule_;
    throw xdr::xdr_wrong_union("LedgerKey: accountRule accessed when not selected");
  }
  _signerRole_t &signerRole() {
    if (_xdr_field_number(type_) == 24)
      return signerRole_;
    throw xdr::xdr_wrong_union("LedgerKey: signerRole accessed when not selected");
  }
  const _signerRole_t &signerRole() const {
    if (_xdr_field_number(type_) == 24)
      return signerRole_;
    throw xdr::xdr_wrong_union("LedgerKey: signerRole accessed when not selected");
  }
  _signerRule_t &signerRule() {
    if (_xdr_field_number(type_) == 25)
      return signerRule_;
    throw xdr::xdr_wrong_union("LedgerKey: signerRule accessed when not selected");
  }
  const _signerRule_t &signerRule() const {
    if (_xdr_field_number(type_) == 25)
      return signerRule_;
    throw xdr::xdr_wrong_union("LedgerKey: signerRule accessed when not selected");
  }
  _stamp_t &stamp() {
    if (_xdr_field_number(type_) == 26)
      return stamp_;
    throw xdr::xdr_wrong_union("LedgerKey: stamp accessed when not selected");
  }
  const _stamp_t &stamp() const {
    if (_xdr_field_number(type_) == 26)
      return stamp_;
    throw xdr::xdr_wrong_union("LedgerKey: stamp accessed when not selected");
  }
  _license_t &license() {
    if (_xdr_field_number(type_) == 27)
      return license_;
    throw xdr::xdr_wrong_union("LedgerKey: license accessed when not selected");
  }
  const _license_t &license() const {
    if (_xdr_field_number(type_) == 27)
      return license_;
    throw xdr::xdr_wrong_union("LedgerKey: license accessed when not selected");
  }
  _poll_t &poll() {
    if (_xdr_field_number(type_) == 28)
      return poll_;
    throw xdr::xdr_wrong_union("LedgerKey: poll accessed when not selected");
  }
  const _poll_t &poll() const {
    if (_xdr_field_number(type_) == 28)
      return poll_;
    throw xdr::xdr_wrong_union("LedgerKey: poll accessed when not selected");
  }
  _vote_t &vote() {
    if (_xdr_field_number(type_) == 29)
      return vote_;
    throw xdr::xdr_wrong_union("LedgerKey: vote accessed when not selected");
  }
  const _vote_t &vote() const {
    if (_xdr_field_number(type_) == 29)
      return vote_;
    throw xdr::xdr_wrong_union("LedgerKey: vote accessed when not selected");
  }
  _accountSpecificRule_t &accountSpecificRule() {
    if (_xdr_field_number(type_) == 30)
      return accountSpecificRule_;
    throw xdr::xdr_wrong_union("LedgerKey: accountSpecificRule accessed when not selected");
  }
  const _accountSpecificRule_t &accountSpecificRule() const {
    if (_xdr_field_number(type_) == 30)
      return accountSpecificRule_;
    throw xdr::xdr_wrong_union("LedgerKey: accountSpecificRule accessed when not selected");
  }
  _swap_t &swap() {
    if (_xdr_field_number(type_) == 31)
      return swap_;
    throw xdr::xdr_wrong_union("LedgerKey: swap accessed when not selected");
  }
  const _swap_t &swap() const {
    if (_xdr_field_number(type_) == 31)
      return swap_;
    throw xdr::xdr_wrong_union("LedgerKey: swap accessed when not selected");
  }
  _data_t &data() {
    if (_xdr_field_number(type_) == 32)
      return data_;
    throw xdr::xdr_wrong_union("LedgerKey: data accessed when not selected");
  }
  const _data_t &data() const {
    if (_xdr_field_number(type_) == 32)
      return data_;
    throw xdr::xdr_wrong_union("LedgerKey: data accessed when not selected");
  }
  _deferredPayment_t &deferredPayment() {
    if (_xdr_field_number(type_) == 33)
      return deferredPayment_;
    throw xdr::xdr_wrong_union("LedgerKey: deferredPayment accessed when not selected");
  }
  const _deferredPayment_t &deferredPayment() const {
    if (_xdr_field_number(type_) == 33)
      return deferredPayment_;
    throw xdr::xdr_wrong_union("LedgerKey: deferredPayment accessed when not selected");
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

#endif // !__XDR_LEDGER_KEYS_H_INCLUDED__
