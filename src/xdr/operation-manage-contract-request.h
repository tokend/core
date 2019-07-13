// -*- C++ -*-
// Automatically generated from operation-manage-contract-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_CONTRACT_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_CONTRACT_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

enum class ManageContractRequestAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractRequestAction>
  : xdr_integral_base<::stellar::ManageContractRequestAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageContractRequestAction val) {
    switch (val) {
    case ::stellar::ManageContractRequestAction::CREATE:
      return "CREATE";
    case ::stellar::ManageContractRequestAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageContractRequestAction::CREATE,
      (int32_t)::stellar::ManageContractRequestAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateContractRequest  : xdr::xdr_abstract {
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

  ContractRequest contractRequest{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateContractRequest() = default;
  template<typename _contractRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ContractRequest, _contractRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateContractRequest(_contractRequest_T &&_contractRequest,
                                 _allTasks_T &&_allTasks,
                                 _ext_T &&_ext)
    : contractRequest(std::forward<_contractRequest_T>(_contractRequest)),
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

struct ManageContractRequestOp  : xdr::xdr_abstract {
  struct _details_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageContractRequestAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateContractRequest createContractRequest_;
      uint64 requestID_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageContractRequestAction> &_xdr_case_values() {
      static const std::vector<ManageContractRequestAction> _xdr_disc_vec {
        ManageContractRequestAction::CREATE,
        ManageContractRequestAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageContractRequestAction::CREATE ? 1
        : which == (int32_t)ManageContractRequestAction::REMOVE ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageContractRequestAction::CREATE:
        _f(&_details_t::createContractRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageContractRequestAction::REMOVE:
        _f(&_details_t::requestID_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _details_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_details_t();
        action_ = which;switch (action_)
{
        case (int32_t)ManageContractRequestAction::CREATE:
new(&createContractRequest_) CreateContractRequest{};
break;
        case (int32_t)ManageContractRequestAction::REMOVE:
new(&requestID_) uint64{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _details_t(ManageContractRequestAction which = ManageContractRequestAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageContractRequestAction::CREATE:
new(&createContractRequest_) CreateContractRequest{};
break;
      case (int32_t)ManageContractRequestAction::REMOVE:
new(&requestID_) uint64{};
break;
}

    }
    _details_t(const _details_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageContractRequestAction::CREATE:
new(&createContractRequest_) CreateContractRequest(source.createContractRequest_);
break;
      case (int32_t)ManageContractRequestAction::REMOVE:
new(&requestID_) uint64(source.requestID_);
break;
}

    }
    _details_t(_details_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageContractRequestAction::CREATE:
new(&createContractRequest_) CreateContractRequest(std::move(source.createContractRequest_));
break;
      case (int32_t)ManageContractRequestAction::REMOVE:
new(&requestID_) uint64(std::move(source.requestID_));
break;
}

    }
    ~_details_t() {
switch (action_)
{
    case (int32_t)ManageContractRequestAction::CREATE:
createContractRequest_.~CreateContractRequest();
break;
    case (int32_t)ManageContractRequestAction::REMOVE:
requestID_.~uint64();
break;
}
}

    _details_t &operator=(const _details_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageContractRequestAction::CREATE:
createContractRequest_ = source.createContractRequest_;
break;
      case (int32_t)ManageContractRequestAction::REMOVE:
requestID_ = source.requestID_;
break;
}
}
else {this->~_details_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageContractRequestAction::CREATE:
new(&createContractRequest_) CreateContractRequest(source.createContractRequest_);
break;
      case (int32_t)ManageContractRequestAction::REMOVE:
new(&requestID_) uint64(source.requestID_);
break;
}
}
      return *this;
    }
    _details_t &operator=(_details_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageContractRequestAction::CREATE:
createContractRequest_ = std::move(source.createContractRequest_);
break;
      case (int32_t)ManageContractRequestAction::REMOVE:
requestID_ = std::move(source.requestID_);
break;
}
}
else {this->~_details_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageContractRequestAction::CREATE:
new(&createContractRequest_) CreateContractRequest(std::move(source.createContractRequest_));
break;
      case (int32_t)ManageContractRequestAction::REMOVE:
new(&requestID_) uint64(std::move(source.requestID_));
break;
}
}
      return *this;
    }

    ManageContractRequestAction action() const { return ManageContractRequestAction(action_); }
    _details_t &action(ManageContractRequestAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateContractRequest &createContractRequest() {
      if (_xdr_field_number(action_) == 1)
        return createContractRequest_;
      throw xdr::xdr_wrong_union("_details_t: createContractRequest accessed when not selected");
    }
    const CreateContractRequest &createContractRequest() const {
      if (_xdr_field_number(action_) == 1)
        return createContractRequest_;
      throw xdr::xdr_wrong_union("_details_t: createContractRequest accessed when not selected");
    }
    uint64 &requestID() {
      if (_xdr_field_number(action_) == 2)
        return requestID_;
      throw xdr::xdr_wrong_union("_details_t: requestID accessed when not selected");
    }
    const uint64 &requestID() const {
      if (_xdr_field_number(action_) == 2)
        return requestID_;
      throw xdr::xdr_wrong_union("_details_t: requestID accessed when not selected");
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

  _details_t details{};
  _ext_t ext{};

  ManageContractRequestOp() = default;
  template<typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_details_t, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageContractRequestOp(_details_T &&_details,
                                   _ext_T &&_ext)
    : details(std::forward<_details_T>(_details)),
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

enum class ManageContractRequestResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  NOT_FOUND = -2,
  TOO_MANY_CONTRACTS = -3,
  NOT_ALLOWED_TO_REMOVE = -4,
  DETAILS_TOO_LONG = -5,
  CONTRACT_CREATE_TASKS_NOT_FOUND = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractRequestResultCode>
  : xdr_integral_base<::stellar::ManageContractRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageContractRequestResultCode val) {
    switch (val) {
    case ::stellar::ManageContractRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageContractRequestResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageContractRequestResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageContractRequestResultCode::TOO_MANY_CONTRACTS:
      return "TOO_MANY_CONTRACTS";
    case ::stellar::ManageContractRequestResultCode::NOT_ALLOWED_TO_REMOVE:
      return "NOT_ALLOWED_TO_REMOVE";
    case ::stellar::ManageContractRequestResultCode::DETAILS_TOO_LONG:
      return "DETAILS_TOO_LONG";
    case ::stellar::ManageContractRequestResultCode::CONTRACT_CREATE_TASKS_NOT_FOUND:
      return "CONTRACT_CREATE_TASKS_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageContractRequestResultCode::SUCCESS,
      (int32_t)::stellar::ManageContractRequestResultCode::MALFORMED,
      (int32_t)::stellar::ManageContractRequestResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageContractRequestResultCode::TOO_MANY_CONTRACTS,
      (int32_t)::stellar::ManageContractRequestResultCode::NOT_ALLOWED_TO_REMOVE,
      (int32_t)::stellar::ManageContractRequestResultCode::DETAILS_TOO_LONG,
      (int32_t)::stellar::ManageContractRequestResultCode::CONTRACT_CREATE_TASKS_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateContractRequestResponse  : xdr::xdr_abstract {
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

  CreateContractRequestResponse() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateContractRequestResponse(_requestID_T &&_requestID,
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

struct ManageContractRequestResult : xdr::xdr_abstract {
  struct _success_t  : xdr::xdr_abstract {
    struct _details_t : xdr::xdr_abstract {
      using _xdr_case_type = xdr::xdr_traits<ManageContractRequestAction>::case_type;
    private:
      _xdr_case_type action_;
      union {
        CreateContractRequestResponse response_;
      };

    public:
      static constexpr const bool _xdr_has_default_case = false;
      static const std::vector<ManageContractRequestAction> &_xdr_case_values() {
        static const std::vector<ManageContractRequestAction> _xdr_disc_vec {
          ManageContractRequestAction::CREATE,
          ManageContractRequestAction::REMOVE
        };
        return _xdr_disc_vec;
      }
      static constexpr int _xdr_field_number(_xdr_case_type which) {
        return which == (int32_t)ManageContractRequestAction::CREATE ? 1
          : which == (int32_t)ManageContractRequestAction::REMOVE ? 0
          : -1;
      }
      template<typename _F, typename..._A> static bool
      _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
        switch (_which) {
        case (int32_t)ManageContractRequestAction::CREATE:
          _f(&_details_t::response_, std::forward<_A>(_a)...);
          return true;
        case (int32_t)ManageContractRequestAction::REMOVE:
          return true;
        }
        return false;
      }

      _xdr_case_type _xdr_discriminant() const { return action_; }
      void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
        int fnum = _xdr_field_number(which);
        if (fnum < 0 && validate)
          throw xdr::xdr_bad_discriminant("bad value of action in _details_t");
        if (fnum != _xdr_field_number(action_)) {
          this->~_details_t();
          action_ = which;switch (action_)
{
          case (int32_t)ManageContractRequestAction::CREATE:
new(&response_) CreateContractRequestResponse{};
break;
          case (int32_t)ManageContractRequestAction::REMOVE:
            break;
}

        }
        else
          action_ = which;
      }
      explicit _details_t(ManageContractRequestAction which = ManageContractRequestAction{}) : action_((int32_t)which) {
        switch (action_)
{
        case (int32_t)ManageContractRequestAction::CREATE:
new(&response_) CreateContractRequestResponse{};
break;
        case (int32_t)ManageContractRequestAction::REMOVE:
          break;
}

      }
      _details_t(const _details_t &source) : action_(source.action_) {
        switch (action_)
{
        case (int32_t)ManageContractRequestAction::CREATE:
new(&response_) CreateContractRequestResponse(source.response_);
break;
        case (int32_t)ManageContractRequestAction::REMOVE:
          break;
}

      }
      _details_t(_details_t &&source) : action_(source.action_) {
        switch (action_)
{
        case (int32_t)ManageContractRequestAction::CREATE:
new(&response_) CreateContractRequestResponse(std::move(source.response_));
break;
        case (int32_t)ManageContractRequestAction::REMOVE:
          break;
}

      }
      ~_details_t() {
switch (action_)
{
      case (int32_t)ManageContractRequestAction::CREATE:
response_.~CreateContractRequestResponse();
break;
      case (int32_t)ManageContractRequestAction::REMOVE:
        break;
}
}

      _details_t &operator=(const _details_t &source) {
        if (action_ == source.action_)
{
switch (action_)
{
        case (int32_t)ManageContractRequestAction::CREATE:
response_ = source.response_;
break;
        case (int32_t)ManageContractRequestAction::REMOVE:
          break;
}
}
else {this->~_details_t();
        action_ = source.action_;
switch (action_)
{
        case (int32_t)ManageContractRequestAction::CREATE:
new(&response_) CreateContractRequestResponse(source.response_);
break;
        case (int32_t)ManageContractRequestAction::REMOVE:
          break;
}
}
        return *this;
      }
      _details_t &operator=(_details_t &&source) {
        if (action_ == source.action_)
{
switch (action_)
{
        case (int32_t)ManageContractRequestAction::CREATE:
response_ = std::move(source.response_);
break;
        case (int32_t)ManageContractRequestAction::REMOVE:
          break;
}
}
else {this->~_details_t();
        action_ = std::move(source.action_);
switch (action_)
{
        case (int32_t)ManageContractRequestAction::CREATE:
new(&response_) CreateContractRequestResponse(std::move(source.response_));
break;
        case (int32_t)ManageContractRequestAction::REMOVE:
          break;
}
}
        return *this;
      }

      ManageContractRequestAction action() const { return ManageContractRequestAction(action_); }
      _details_t &action(ManageContractRequestAction _xdr_d, bool _xdr_validate = true) {
        _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
        return *this;
      }

      CreateContractRequestResponse &response() {
        if (_xdr_field_number(action_) == 1)
          return response_;
        throw xdr::xdr_wrong_union("_details_t: response accessed when not selected");
      }
      const CreateContractRequestResponse &response() const {
        if (_xdr_field_number(action_) == 1)
          return response_;
        throw xdr::xdr_wrong_union("_details_t: response accessed when not selected");
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

    _details_t details{};
    _ext_t ext{};

    _success_t() = default;
    template<typename _details_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<_details_t, _details_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_details_T &&_details,
                        _ext_T &&_ext)
      : details(std::forward<_details_T>(_details)),
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

  using _xdr_case_type = xdr::xdr_traits<ManageContractRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageContractRequestResultCode> &_xdr_case_values() {
    static const std::vector<ManageContractRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageContractRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageContractRequestResultCode::SUCCESS:
      _f(&ManageContractRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageContractRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageContractRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageContractRequestResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageContractRequestResult(ManageContractRequestResultCode which = ManageContractRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageContractRequestResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    default:
      break;
}

  }
  ManageContractRequestResult(const ManageContractRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageContractRequestResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}

  }
  ManageContractRequestResult(ManageContractRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageContractRequestResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageContractRequestResult() {
switch (code_)
{
  case (int32_t)ManageContractRequestResultCode::SUCCESS:
success_.~_success_t();
break;
  default:
    break;
}
}

  ManageContractRequestResult &operator=(const ManageContractRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageContractRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageContractRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageContractRequestResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageContractRequestResult &operator=(ManageContractRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageContractRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageContractRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageContractRequestResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageContractRequestResultCode code() const { return ManageContractRequestResultCode(code_); }
  ManageContractRequestResult &code(ManageContractRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageContractRequestResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageContractRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_CONTRACT_REQUEST_H_INCLUDED__
