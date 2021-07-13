// -*- C++ -*-
// Automatically generated from operation-manage-sale.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_SALE_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_SALE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/ledger-entries-sale.h"
#include "reviewable-request-sale.h"

namespace stellar {

enum class ManageSaleAction : std::int32_t {
  CREATE_UPDATE_DETAILS_REQUEST = 1,
  CANCEL = 2,
  UPDATE_TIME = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSaleAction>
  : xdr_integral_base<::stellar::ManageSaleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageSaleAction val) {
    switch (val) {
    case ::stellar::ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
      return "CREATE_UPDATE_DETAILS_REQUEST";
    case ::stellar::ManageSaleAction::CANCEL:
      return "CANCEL";
    case ::stellar::ManageSaleAction::UPDATE_TIME:
      return "UPDATE_TIME";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST,
      (int32_t)::stellar::ManageSaleAction::CANCEL,
      (int32_t)::stellar::ManageSaleAction::UPDATE_TIME
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct UpdateSaleDetailsData  : xdr::xdr_abstract {
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
  longstring creatorDetails{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  UpdateSaleDetailsData() = default;
  template<typename _requestID_T,
           typename _creatorDetails_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit UpdateSaleDetailsData(_requestID_T &&_requestID,
                                 _creatorDetails_T &&_creatorDetails,
                                 _allTasks_T &&_allTasks,
                                 _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
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

struct UpdateTimeData  : xdr::xdr_abstract {
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

  uint64 newStartTime{};
  uint64 newEndTime{};
  _ext_t ext{};

  UpdateTimeData() = default;
  template<typename _newStartTime_T,
           typename _newEndTime_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _newStartTime_T>::value
                          && std::is_constructible<uint64, _newEndTime_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit UpdateTimeData(_newStartTime_T &&_newStartTime,
                          _newEndTime_T &&_newEndTime,
                          _ext_T &&_ext)
    : newStartTime(std::forward<_newStartTime_T>(_newStartTime)),
      newEndTime(std::forward<_newEndTime_T>(_newEndTime)),
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

struct ManageSaleOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageSaleAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      UpdateSaleDetailsData updateSaleDetailsData_;
      UpdateTimeData updateTime_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageSaleAction> &_xdr_case_values() {
      static const std::vector<ManageSaleAction> _xdr_disc_vec {
        ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST,
        ManageSaleAction::CANCEL,
        ManageSaleAction::UPDATE_TIME
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST ? 1
        : which == (int32_t)ManageSaleAction::CANCEL ? 0
        : which == (int32_t)ManageSaleAction::UPDATE_TIME ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
        _f(&_data_t::updateSaleDetailsData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageSaleAction::CANCEL:
        return true;
      case (int32_t)ManageSaleAction::UPDATE_TIME:
        _f(&_data_t::updateTime_, std::forward<_A>(_a)...);
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
        case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&updateSaleDetailsData_) UpdateSaleDetailsData{};
break;
        case (int32_t)ManageSaleAction::CANCEL:
          break;
        case (int32_t)ManageSaleAction::UPDATE_TIME:
new(&updateTime_) UpdateTimeData{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageSaleAction which = ManageSaleAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&updateSaleDetailsData_) UpdateSaleDetailsData{};
break;
      case (int32_t)ManageSaleAction::CANCEL:
        break;
      case (int32_t)ManageSaleAction::UPDATE_TIME:
new(&updateTime_) UpdateTimeData{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&updateSaleDetailsData_) UpdateSaleDetailsData(source.updateSaleDetailsData_);
break;
      case (int32_t)ManageSaleAction::CANCEL:
        break;
      case (int32_t)ManageSaleAction::UPDATE_TIME:
new(&updateTime_) UpdateTimeData(source.updateTime_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&updateSaleDetailsData_) UpdateSaleDetailsData(std::move(source.updateSaleDetailsData_));
break;
      case (int32_t)ManageSaleAction::CANCEL:
        break;
      case (int32_t)ManageSaleAction::UPDATE_TIME:
new(&updateTime_) UpdateTimeData(std::move(source.updateTime_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
updateSaleDetailsData_.~UpdateSaleDetailsData();
break;
    case (int32_t)ManageSaleAction::CANCEL:
      break;
    case (int32_t)ManageSaleAction::UPDATE_TIME:
updateTime_.~UpdateTimeData();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
updateSaleDetailsData_ = source.updateSaleDetailsData_;
break;
      case (int32_t)ManageSaleAction::CANCEL:
        break;
      case (int32_t)ManageSaleAction::UPDATE_TIME:
updateTime_ = source.updateTime_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&updateSaleDetailsData_) UpdateSaleDetailsData(source.updateSaleDetailsData_);
break;
      case (int32_t)ManageSaleAction::CANCEL:
        break;
      case (int32_t)ManageSaleAction::UPDATE_TIME:
new(&updateTime_) UpdateTimeData(source.updateTime_);
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
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
updateSaleDetailsData_ = std::move(source.updateSaleDetailsData_);
break;
      case (int32_t)ManageSaleAction::CANCEL:
        break;
      case (int32_t)ManageSaleAction::UPDATE_TIME:
updateTime_ = std::move(source.updateTime_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&updateSaleDetailsData_) UpdateSaleDetailsData(std::move(source.updateSaleDetailsData_));
break;
      case (int32_t)ManageSaleAction::CANCEL:
        break;
      case (int32_t)ManageSaleAction::UPDATE_TIME:
new(&updateTime_) UpdateTimeData(std::move(source.updateTime_));
break;
}
}
      return *this;
    }

    ManageSaleAction action() const { return ManageSaleAction(action_); }
    _data_t &action(ManageSaleAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    UpdateSaleDetailsData &updateSaleDetailsData() {
      if (_xdr_field_number(action_) == 1)
        return updateSaleDetailsData_;
      throw xdr::xdr_wrong_union("_data_t: updateSaleDetailsData accessed when not selected");
    }
    const UpdateSaleDetailsData &updateSaleDetailsData() const {
      if (_xdr_field_number(action_) == 1)
        return updateSaleDetailsData_;
      throw xdr::xdr_wrong_union("_data_t: updateSaleDetailsData accessed when not selected");
    }
    UpdateTimeData &updateTime() {
      if (_xdr_field_number(action_) == 2)
        return updateTime_;
      throw xdr::xdr_wrong_union("_data_t: updateTime accessed when not selected");
    }
    const UpdateTimeData &updateTime() const {
      if (_xdr_field_number(action_) == 2)
        return updateTime_;
      throw xdr::xdr_wrong_union("_data_t: updateTime accessed when not selected");
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

  uint64 saleID{};
  _data_t data{};
  _ext_t ext{};

  ManageSaleOp() = default;
  template<typename _saleID_T,
           typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _saleID_T>::value
                          && std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageSaleOp(_saleID_T &&_saleID,
                        _data_T &&_data,
                        _ext_T &&_ext)
    : saleID(std::forward<_saleID_T>(_saleID)),
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

enum class ManageSaleResultCode : std::int32_t {
  SUCCESS = 0,
  SALE_NOT_FOUND = -1,
  INVALID_CREATOR_DETAILS = -2,
  UPDATE_DETAILS_REQUEST_ALREADY_EXISTS = -3,
  UPDATE_DETAILS_REQUEST_NOT_FOUND = -4,
  NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE = -5,
  SALE_UPDATE_DETAILS_TASKS_NOT_FOUND = -6,
  INVALID_UPDATE_TIME_DATA = -7,
  INVALID_START_TIME = -8,
  INVALID_END_TIME = -9,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSaleResultCode>
  : xdr_integral_base<::stellar::ManageSaleResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageSaleResultCode val) {
    switch (val) {
    case ::stellar::ManageSaleResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageSaleResultCode::SALE_NOT_FOUND:
      return "SALE_NOT_FOUND";
    case ::stellar::ManageSaleResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::ManageSaleResultCode::UPDATE_DETAILS_REQUEST_ALREADY_EXISTS:
      return "UPDATE_DETAILS_REQUEST_ALREADY_EXISTS";
    case ::stellar::ManageSaleResultCode::UPDATE_DETAILS_REQUEST_NOT_FOUND:
      return "UPDATE_DETAILS_REQUEST_NOT_FOUND";
    case ::stellar::ManageSaleResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE:
      return "NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE";
    case ::stellar::ManageSaleResultCode::SALE_UPDATE_DETAILS_TASKS_NOT_FOUND:
      return "SALE_UPDATE_DETAILS_TASKS_NOT_FOUND";
    case ::stellar::ManageSaleResultCode::INVALID_UPDATE_TIME_DATA:
      return "INVALID_UPDATE_TIME_DATA";
    case ::stellar::ManageSaleResultCode::INVALID_START_TIME:
      return "INVALID_START_TIME";
    case ::stellar::ManageSaleResultCode::INVALID_END_TIME:
      return "INVALID_END_TIME";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageSaleResultCode::SUCCESS,
      (int32_t)::stellar::ManageSaleResultCode::SALE_NOT_FOUND,
      (int32_t)::stellar::ManageSaleResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::ManageSaleResultCode::UPDATE_DETAILS_REQUEST_ALREADY_EXISTS,
      (int32_t)::stellar::ManageSaleResultCode::UPDATE_DETAILS_REQUEST_NOT_FOUND,
      (int32_t)::stellar::ManageSaleResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE,
      (int32_t)::stellar::ManageSaleResultCode::SALE_UPDATE_DETAILS_TASKS_NOT_FOUND,
      (int32_t)::stellar::ManageSaleResultCode::INVALID_UPDATE_TIME_DATA,
      (int32_t)::stellar::ManageSaleResultCode::INVALID_START_TIME,
      (int32_t)::stellar::ManageSaleResultCode::INVALID_END_TIME
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageSaleResultSuccess  : xdr::xdr_abstract {
  struct _response_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageSaleAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      uint64 requestID_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageSaleAction> &_xdr_case_values() {
      static const std::vector<ManageSaleAction> _xdr_disc_vec {
        ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST,
        ManageSaleAction::CANCEL,
        ManageSaleAction::UPDATE_TIME
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST ? 1
        : which == (int32_t)ManageSaleAction::CANCEL || which == (int32_t)ManageSaleAction::UPDATE_TIME ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
        _f(&_response_t::requestID_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageSaleAction::CANCEL:
      case (int32_t)ManageSaleAction::UPDATE_TIME:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _response_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_response_t();
        action_ = which;switch (action_)
{
        case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&requestID_) uint64{};
break;
        case (int32_t)ManageSaleAction::CANCEL:
        case (int32_t)ManageSaleAction::UPDATE_TIME:
          break;
}

      }
      else
        action_ = which;
    }
    explicit _response_t(ManageSaleAction which = ManageSaleAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&requestID_) uint64{};
break;
      case (int32_t)ManageSaleAction::CANCEL:
      case (int32_t)ManageSaleAction::UPDATE_TIME:
        break;
}

    }
    _response_t(const _response_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&requestID_) uint64(source.requestID_);
break;
      case (int32_t)ManageSaleAction::CANCEL:
      case (int32_t)ManageSaleAction::UPDATE_TIME:
        break;
}

    }
    _response_t(_response_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&requestID_) uint64(std::move(source.requestID_));
break;
      case (int32_t)ManageSaleAction::CANCEL:
      case (int32_t)ManageSaleAction::UPDATE_TIME:
        break;
}

    }
    ~_response_t() {
switch (action_)
{
    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
requestID_.~uint64();
break;
    case (int32_t)ManageSaleAction::CANCEL:
    case (int32_t)ManageSaleAction::UPDATE_TIME:
      break;
}
}

    _response_t &operator=(const _response_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
requestID_ = source.requestID_;
break;
      case (int32_t)ManageSaleAction::CANCEL:
      case (int32_t)ManageSaleAction::UPDATE_TIME:
        break;
}
}
else {this->~_response_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&requestID_) uint64(source.requestID_);
break;
      case (int32_t)ManageSaleAction::CANCEL:
      case (int32_t)ManageSaleAction::UPDATE_TIME:
        break;
}
}
      return *this;
    }
    _response_t &operator=(_response_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
requestID_ = std::move(source.requestID_);
break;
      case (int32_t)ManageSaleAction::CANCEL:
      case (int32_t)ManageSaleAction::UPDATE_TIME:
        break;
}
}
else {this->~_response_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
new(&requestID_) uint64(std::move(source.requestID_));
break;
      case (int32_t)ManageSaleAction::CANCEL:
      case (int32_t)ManageSaleAction::UPDATE_TIME:
        break;
}
}
      return *this;
    }

    ManageSaleAction action() const { return ManageSaleAction(action_); }
    _response_t &action(ManageSaleAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    uint64 &requestID() {
      if (_xdr_field_number(action_) == 1)
        return requestID_;
      throw xdr::xdr_wrong_union("_response_t: requestID accessed when not selected");
    }
    const uint64 &requestID() const {
      if (_xdr_field_number(action_) == 1)
        return requestID_;
      throw xdr::xdr_wrong_union("_response_t: requestID accessed when not selected");
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

  bool fulfilled{};
  _response_t response{};
  _ext_t ext{};

  ManageSaleResultSuccess() = default;
  template<typename _fulfilled_T,
           typename _response_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_response_t, _response_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageSaleResultSuccess(_fulfilled_T &&_fulfilled,
                                   _response_T &&_response,
                                   _ext_T &&_ext)
    : fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      response(std::forward<_response_T>(_response)),
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

struct ManageSaleResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ManageSaleResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageSaleResultSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageSaleResultCode> &_xdr_case_values() {
    static const std::vector<ManageSaleResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageSaleResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageSaleResultCode::SUCCESS:
      _f(&ManageSaleResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageSaleResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageSaleResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageSaleResultCode::SUCCESS:
new(&success_) ManageSaleResultSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageSaleResult(ManageSaleResultCode which = ManageSaleResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageSaleResultCode::SUCCESS:
new(&success_) ManageSaleResultSuccess{};
break;
    default:
      break;
}

  }
  ManageSaleResult(const ManageSaleResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageSaleResultCode::SUCCESS:
new(&success_) ManageSaleResultSuccess(source.success_);
break;
    default:
      break;
}

  }
  ManageSaleResult(ManageSaleResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageSaleResultCode::SUCCESS:
new(&success_) ManageSaleResultSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageSaleResult() {
switch (code_)
{
  case (int32_t)ManageSaleResultCode::SUCCESS:
success_.~ManageSaleResultSuccess();
break;
  default:
    break;
}
}

  ManageSaleResult &operator=(const ManageSaleResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageSaleResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageSaleResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageSaleResultCode::SUCCESS:
new(&success_) ManageSaleResultSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageSaleResult &operator=(ManageSaleResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageSaleResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageSaleResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageSaleResultCode::SUCCESS:
new(&success_) ManageSaleResultSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageSaleResultCode code() const { return ManageSaleResultCode(code_); }
  ManageSaleResult &code(ManageSaleResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageSaleResultSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageSaleResult: success accessed when not selected");
  }
  const ManageSaleResultSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageSaleResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_SALE_H_INCLUDED__
