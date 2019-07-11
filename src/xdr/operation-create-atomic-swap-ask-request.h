// -*- C++ -*-
// Automatically generated from operation-create-atomic-swap-ask-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_ATOMIC_SWAP_ASK_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_ATOMIC_SWAP_ASK_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/reviewable-request-atomic-swap-ask.h"

namespace stellar {

struct CreateAtomicSwapAskRequestOp  : xdr::xdr_abstract {
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

  CreateAtomicSwapAskRequest request{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateAtomicSwapAskRequestOp() = default;
  template<typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<CreateAtomicSwapAskRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAtomicSwapAskRequestOp(_request_T &&_request,
                                        _allTasks_T &&_allTasks,
                                        _ext_T &&_ext)
    : request(std::forward<_request_T>(_request)),
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

enum class CreateAtomicSwapAskRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_AMOUNT = -1,
  INVALID_PRICE = -2,
  INVALID_DETAILS = -3,
  INCORRECT_PRECISION = -4,
  BASE_ASSET_NOT_FOUND = -5,
  BASE_ASSET_CANNOT_BE_SWAPPED = -6,
  QUOTE_ASSET_NOT_FOUND = -7,
  QUOTE_ASSET_CANNOT_BE_SWAPPED = -8,
  BASE_BALANCE_NOT_FOUND = -9,
  ASSETS_ARE_EQUAL = -10,
  BASE_BALANCE_UNDERFUNDED = -11,
  INVALID_QUOTE_ASSET = -12,
  ATOMIC_SWAP_ASK_TASKS_NOT_FOUND = -13,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAtomicSwapAskRequestResultCode>
  : xdr_integral_base<::stellar::CreateAtomicSwapAskRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateAtomicSwapAskRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateAtomicSwapAskRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::INVALID_PRICE:
      return "INVALID_PRICE";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::INVALID_DETAILS:
      return "INVALID_DETAILS";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::BASE_ASSET_NOT_FOUND:
      return "BASE_ASSET_NOT_FOUND";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED:
      return "BASE_ASSET_CANNOT_BE_SWAPPED";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_NOT_FOUND:
      return "QUOTE_ASSET_NOT_FOUND";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED:
      return "QUOTE_ASSET_CANNOT_BE_SWAPPED";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::BASE_BALANCE_NOT_FOUND:
      return "BASE_BALANCE_NOT_FOUND";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::ASSETS_ARE_EQUAL:
      return "ASSETS_ARE_EQUAL";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::BASE_BALANCE_UNDERFUNDED:
      return "BASE_BALANCE_UNDERFUNDED";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::INVALID_QUOTE_ASSET:
      return "INVALID_QUOTE_ASSET";
    case ::stellar::CreateAtomicSwapAskRequestResultCode::ATOMIC_SWAP_ASK_TASKS_NOT_FOUND:
      return "ATOMIC_SWAP_ASK_TASKS_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::INVALID_PRICE,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::INVALID_DETAILS,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::INCORRECT_PRECISION,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::BASE_ASSET_NOT_FOUND,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_NOT_FOUND,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::BASE_BALANCE_NOT_FOUND,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::ASSETS_ARE_EQUAL,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::BASE_BALANCE_UNDERFUNDED,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::INVALID_QUOTE_ASSET,
      (int32_t)::stellar::CreateAtomicSwapAskRequestResultCode::ATOMIC_SWAP_ASK_TASKS_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAtomicSwapAskRequestSuccess  : xdr::xdr_abstract {
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
  uint64 askID{};
  _ext_t ext{};

  CreateAtomicSwapAskRequestSuccess() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _askID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<uint64, _askID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAtomicSwapAskRequestSuccess(_requestID_T &&_requestID,
                                             _fulfilled_T &&_fulfilled,
                                             _askID_T &&_askID,
                                             _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      askID(std::forward<_askID_T>(_askID)),
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

struct CreateAtomicSwapAskRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateAtomicSwapAskRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateAtomicSwapAskRequestSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateAtomicSwapAskRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateAtomicSwapAskRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
      _f(&CreateAtomicSwapAskRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateAtomicSwapAskRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateAtomicSwapAskRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapAskRequestSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateAtomicSwapAskRequestResult(CreateAtomicSwapAskRequestResultCode which = CreateAtomicSwapAskRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapAskRequestSuccess{};
break;
    default:
      break;
}

  }
  CreateAtomicSwapAskRequestResult(const CreateAtomicSwapAskRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapAskRequestSuccess(source.success_);
break;
    default:
      break;
}

  }
  CreateAtomicSwapAskRequestResult(CreateAtomicSwapAskRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapAskRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateAtomicSwapAskRequestResult() {
switch (code_)
{
  case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
success_.~CreateAtomicSwapAskRequestSuccess();
break;
  default:
    break;
}
}

  CreateAtomicSwapAskRequestResult &operator=(const CreateAtomicSwapAskRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateAtomicSwapAskRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapAskRequestSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateAtomicSwapAskRequestResult &operator=(CreateAtomicSwapAskRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateAtomicSwapAskRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateAtomicSwapAskRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapAskRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateAtomicSwapAskRequestResultCode code() const { return CreateAtomicSwapAskRequestResultCode(code_); }
  CreateAtomicSwapAskRequestResult &code(CreateAtomicSwapAskRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateAtomicSwapAskRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAtomicSwapAskRequestResult: success accessed when not selected");
  }
  const CreateAtomicSwapAskRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAtomicSwapAskRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_ATOMIC_SWAP_ASK_REQUEST_H_INCLUDED__
