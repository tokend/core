// -*- C++ -*-
// Automatically generated from operation-manage-contract.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_CONTRACT_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_CONTRACT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

enum class ManageContractAction : std::int32_t {
  ADD_DETAILS = 0,
  CONFIRM_COMPLETED = 1,
  START_DISPUTE = 2,
  RESOLVE_DISPUTE = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractAction>
  : xdr_integral_base<::stellar::ManageContractAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageContractAction val) {
    switch (val) {
    case ::stellar::ManageContractAction::ADD_DETAILS:
      return "ADD_DETAILS";
    case ::stellar::ManageContractAction::CONFIRM_COMPLETED:
      return "CONFIRM_COMPLETED";
    case ::stellar::ManageContractAction::START_DISPUTE:
      return "START_DISPUTE";
    case ::stellar::ManageContractAction::RESOLVE_DISPUTE:
      return "RESOLVE_DISPUTE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageContractAction::ADD_DETAILS,
      (int32_t)::stellar::ManageContractAction::CONFIRM_COMPLETED,
      (int32_t)::stellar::ManageContractAction::START_DISPUTE,
      (int32_t)::stellar::ManageContractAction::RESOLVE_DISPUTE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageContractOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageContractAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      longstring details_;
      longstring disputeReason_;
      bool isRevert_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageContractAction> &_xdr_case_values() {
      static const std::vector<ManageContractAction> _xdr_disc_vec {
        ManageContractAction::ADD_DETAILS,
        ManageContractAction::CONFIRM_COMPLETED,
        ManageContractAction::START_DISPUTE,
        ManageContractAction::RESOLVE_DISPUTE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageContractAction::ADD_DETAILS ? 1
        : which == (int32_t)ManageContractAction::CONFIRM_COMPLETED ? 0
        : which == (int32_t)ManageContractAction::START_DISPUTE ? 2
        : which == (int32_t)ManageContractAction::RESOLVE_DISPUTE ? 3
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageContractAction::ADD_DETAILS:
        _f(&_data_t::details_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        return true;
      case (int32_t)ManageContractAction::START_DISPUTE:
        _f(&_data_t::disputeReason_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
        _f(&_data_t::isRevert_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _data_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_data_t();
        action_ = which;switch (action_)
{
        case (int32_t)ManageContractAction::ADD_DETAILS:
new(&details_) longstring{};
break;
        case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
          break;
        case (int32_t)ManageContractAction::START_DISPUTE:
new(&disputeReason_) longstring{};
break;
        case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
new(&isRevert_) bool{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageContractAction which = ManageContractAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageContractAction::ADD_DETAILS:
new(&details_) longstring{};
break;
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        break;
      case (int32_t)ManageContractAction::START_DISPUTE:
new(&disputeReason_) longstring{};
break;
      case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
new(&isRevert_) bool{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageContractAction::ADD_DETAILS:
new(&details_) longstring(source.details_);
break;
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        break;
      case (int32_t)ManageContractAction::START_DISPUTE:
new(&disputeReason_) longstring(source.disputeReason_);
break;
      case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
new(&isRevert_) bool(source.isRevert_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageContractAction::ADD_DETAILS:
new(&details_) longstring(std::move(source.details_));
break;
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        break;
      case (int32_t)ManageContractAction::START_DISPUTE:
new(&disputeReason_) longstring(std::move(source.disputeReason_));
break;
      case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
new(&isRevert_) bool(std::move(source.isRevert_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageContractAction::ADD_DETAILS:
details_.~longstring();
break;
    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
      break;
    case (int32_t)ManageContractAction::START_DISPUTE:
disputeReason_.~longstring();
break;
    case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
using Bool = bool;
isRevert_.~Bool();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageContractAction::ADD_DETAILS:
details_ = source.details_;
break;
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        break;
      case (int32_t)ManageContractAction::START_DISPUTE:
disputeReason_ = source.disputeReason_;
break;
      case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
isRevert_ = source.isRevert_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageContractAction::ADD_DETAILS:
new(&details_) longstring(source.details_);
break;
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        break;
      case (int32_t)ManageContractAction::START_DISPUTE:
new(&disputeReason_) longstring(source.disputeReason_);
break;
      case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
new(&isRevert_) bool(source.isRevert_);
break;
}
}
      return *this;
    }
    _data_t &operator=(_data_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageContractAction::ADD_DETAILS:
details_ = std::move(source.details_);
break;
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        break;
      case (int32_t)ManageContractAction::START_DISPUTE:
disputeReason_ = std::move(source.disputeReason_);
break;
      case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
isRevert_ = std::move(source.isRevert_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageContractAction::ADD_DETAILS:
new(&details_) longstring(std::move(source.details_));
break;
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        break;
      case (int32_t)ManageContractAction::START_DISPUTE:
new(&disputeReason_) longstring(std::move(source.disputeReason_));
break;
      case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
new(&isRevert_) bool(std::move(source.isRevert_));
break;
}
}
      return *this;
    }

    ManageContractAction action() const { return ManageContractAction(action_); }
    _data_t &action(ManageContractAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    longstring &details() {
      if (_xdr_field_number(action_) == 1)
        return details_;
      throw xdr::xdr_wrong_union("_data_t: details accessed when not selected");
    }
    const longstring &details() const {
      if (_xdr_field_number(action_) == 1)
        return details_;
      throw xdr::xdr_wrong_union("_data_t: details accessed when not selected");
    }
    longstring &disputeReason() {
      if (_xdr_field_number(action_) == 2)
        return disputeReason_;
      throw xdr::xdr_wrong_union("_data_t: disputeReason accessed when not selected");
    }
    const longstring &disputeReason() const {
      if (_xdr_field_number(action_) == 2)
        return disputeReason_;
      throw xdr::xdr_wrong_union("_data_t: disputeReason accessed when not selected");
    }
    bool &isRevert() {
      if (_xdr_field_number(action_) == 3)
        return isRevert_;
      throw xdr::xdr_wrong_union("_data_t: isRevert accessed when not selected");
    }
    const bool &isRevert() const {
      if (_xdr_field_number(action_) == 3)
        return isRevert_;
      throw xdr::xdr_wrong_union("_data_t: isRevert accessed when not selected");
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

  uint64 contractID{};
  _data_t data{};
  _ext_t ext{};

  ManageContractOp() = default;
  template<typename _contractID_T,
           typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _contractID_T>::value
                          && std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageContractOp(_contractID_T &&_contractID,
                            _data_T &&_data,
                            _ext_T &&_ext)
    : contractID(std::forward<_contractID_T>(_contractID)),
      data(std::forward<_data_T>(_data)),
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

enum class ManageContractResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  NOT_FOUND = -2,
  NOT_ALLOWED = -3,
  DETAILS_TOO_LONG = -4,
  DISPUTE_REASON_TOO_LONG = -5,
  ALREADY_CONFIRMED = -6,
  INVOICE_NOT_APPROVED = -7,
  DISPUTE_ALREADY_STARTED = -8,
  CUSTOMER_BALANCE_OVERFLOW = -9,
  INCORRECT_PRECISION = -10,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractResultCode>
  : xdr_integral_base<::stellar::ManageContractResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageContractResultCode val) {
    switch (val) {
    case ::stellar::ManageContractResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageContractResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageContractResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageContractResultCode::NOT_ALLOWED:
      return "NOT_ALLOWED";
    case ::stellar::ManageContractResultCode::DETAILS_TOO_LONG:
      return "DETAILS_TOO_LONG";
    case ::stellar::ManageContractResultCode::DISPUTE_REASON_TOO_LONG:
      return "DISPUTE_REASON_TOO_LONG";
    case ::stellar::ManageContractResultCode::ALREADY_CONFIRMED:
      return "ALREADY_CONFIRMED";
    case ::stellar::ManageContractResultCode::INVOICE_NOT_APPROVED:
      return "INVOICE_NOT_APPROVED";
    case ::stellar::ManageContractResultCode::DISPUTE_ALREADY_STARTED:
      return "DISPUTE_ALREADY_STARTED";
    case ::stellar::ManageContractResultCode::CUSTOMER_BALANCE_OVERFLOW:
      return "CUSTOMER_BALANCE_OVERFLOW";
    case ::stellar::ManageContractResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageContractResultCode::SUCCESS,
      (int32_t)::stellar::ManageContractResultCode::MALFORMED,
      (int32_t)::stellar::ManageContractResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageContractResultCode::NOT_ALLOWED,
      (int32_t)::stellar::ManageContractResultCode::DETAILS_TOO_LONG,
      (int32_t)::stellar::ManageContractResultCode::DISPUTE_REASON_TOO_LONG,
      (int32_t)::stellar::ManageContractResultCode::ALREADY_CONFIRMED,
      (int32_t)::stellar::ManageContractResultCode::INVOICE_NOT_APPROVED,
      (int32_t)::stellar::ManageContractResultCode::DISPUTE_ALREADY_STARTED,
      (int32_t)::stellar::ManageContractResultCode::CUSTOMER_BALANCE_OVERFLOW,
      (int32_t)::stellar::ManageContractResultCode::INCORRECT_PRECISION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageContractResponse  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageContractAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      bool isCompleted_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = true;
    static const std::vector<ManageContractAction> &_xdr_case_values() {
      static const std::vector<ManageContractAction> _xdr_disc_vec {};
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageContractAction::CONFIRM_COMPLETED ? 1
        : 0;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        _f(&_data_t::isCompleted_, std::forward<_A>(_a)...);
        return true;
      default:
        return true;
      }
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _data_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_data_t();
        action_ = which;switch (action_)
{
        case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
new(&isCompleted_) bool{};
break;
        default:
          break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageContractAction which = ManageContractAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
new(&isCompleted_) bool{};
break;
      default:
        break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
new(&isCompleted_) bool(source.isCompleted_);
break;
      default:
        break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
new(&isCompleted_) bool(std::move(source.isCompleted_));
break;
      default:
        break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
using Bool = bool;
isCompleted_.~Bool();
break;
    default:
      break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
isCompleted_ = source.isCompleted_;
break;
      default:
        break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
new(&isCompleted_) bool(source.isCompleted_);
break;
      default:
        break;
}
}
      return *this;
    }
    _data_t &operator=(_data_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
isCompleted_ = std::move(source.isCompleted_);
break;
      default:
        break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
new(&isCompleted_) bool(std::move(source.isCompleted_));
break;
      default:
        break;
}
}
      return *this;
    }

    ManageContractAction action() const { return ManageContractAction(action_); }
    _data_t &action(ManageContractAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    bool &isCompleted() {
      if (_xdr_field_number(action_) == 1)
        return isCompleted_;
      throw xdr::xdr_wrong_union("_data_t: isCompleted accessed when not selected");
    }
    const bool &isCompleted() const {
      if (_xdr_field_number(action_) == 1)
        return isCompleted_;
      throw xdr::xdr_wrong_union("_data_t: isCompleted accessed when not selected");
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

  _data_t data{};
  _ext_t ext{};

  ManageContractResponse() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageContractResponse(_data_T &&_data,
                                  _ext_T &&_ext)
    : data(std::forward<_data_T>(_data)),
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

struct ManageContractResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ManageContractResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageContractResponse response_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageContractResultCode> &_xdr_case_values() {
    static const std::vector<ManageContractResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageContractResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageContractResultCode::SUCCESS:
      _f(&ManageContractResult::response_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageContractResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageContractResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageContractResultCode::SUCCESS:
new(&response_) ManageContractResponse{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageContractResult(ManageContractResultCode which = ManageContractResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageContractResultCode::SUCCESS:
new(&response_) ManageContractResponse{};
break;
    default:
      break;
}

  }
  ManageContractResult(const ManageContractResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageContractResultCode::SUCCESS:
new(&response_) ManageContractResponse(source.response_);
break;
    default:
      break;
}

  }
  ManageContractResult(ManageContractResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageContractResultCode::SUCCESS:
new(&response_) ManageContractResponse(std::move(source.response_));
break;
    default:
      break;
}

  }
  ~ManageContractResult() {
switch (code_)
{
  case (int32_t)ManageContractResultCode::SUCCESS:
response_.~ManageContractResponse();
break;
  default:
    break;
}
}

  ManageContractResult &operator=(const ManageContractResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageContractResultCode::SUCCESS:
response_ = source.response_;
break;
    default:
      break;
}
}
else {this->~ManageContractResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageContractResultCode::SUCCESS:
new(&response_) ManageContractResponse(source.response_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageContractResult &operator=(ManageContractResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageContractResultCode::SUCCESS:
response_ = std::move(source.response_);
break;
    default:
      break;
}
}
else {this->~ManageContractResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageContractResultCode::SUCCESS:
new(&response_) ManageContractResponse(std::move(source.response_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageContractResultCode code() const { return ManageContractResultCode(code_); }
  ManageContractResult &code(ManageContractResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageContractResponse &response() {
    if (_xdr_field_number(code_) == 1)
      return response_;
    throw xdr::xdr_wrong_union("ManageContractResult: response accessed when not selected");
  }
  const ManageContractResponse &response() const {
    if (_xdr_field_number(code_) == 1)
      return response_;
    throw xdr::xdr_wrong_union("ManageContractResult: response accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_CONTRACT_H_INCLUDED__
