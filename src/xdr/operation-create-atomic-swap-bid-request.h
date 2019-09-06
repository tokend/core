// -*- C++ -*-
// Automatically generated from operation-create-atomic-swap-bid-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_ATOMIC_SWAP_BID_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_ATOMIC_SWAP_BID_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/reviewable-request-atomic-swap-bid.h"

namespace stellar {

struct CreateAtomicSwapBidRequestOp  : xdr::xdr_abstract {
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

  CreateAtomicSwapBidRequest request{};
  _ext_t ext{};

  CreateAtomicSwapBidRequestOp() = default;
  template<typename _request_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<CreateAtomicSwapBidRequest, _request_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAtomicSwapBidRequestOp(_request_T &&_request,
                                        _ext_T &&_ext)
    : request(std::forward<_request_T>(_request)),
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

enum class CreateAtomicSwapBidRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_BASE_AMOUNT = -1,
  INVALID_QUOTE_ASSET = -2,
  ASK_NOT_FOUND = -3,
  QUOTE_ASSET_NOT_FOUND = -4,
  ASK_UNDERFUNDED = -5,
  ATOMIC_SWAP_BID_TASKS_NOT_FOUND = -6,
  INCORRECT_PRECISION = -7,
  ASK_IS_CANCELLED = -8,
  SOURCE_ACCOUNT_EQUALS_ASK_OWNER = -9,
  ATOMIC_SWAP_BID_ZERO_TASKS_NOT_ALLOWED = -10,
  QUOTE_AMOUNT_OVERFLOWS = -11,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAtomicSwapBidRequestResultCode>
  : xdr_integral_base<::stellar::CreateAtomicSwapBidRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateAtomicSwapBidRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateAtomicSwapBidRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::INVALID_BASE_AMOUNT:
      return "INVALID_BASE_AMOUNT";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::INVALID_QUOTE_ASSET:
      return "INVALID_QUOTE_ASSET";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::ASK_NOT_FOUND:
      return "ASK_NOT_FOUND";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::QUOTE_ASSET_NOT_FOUND:
      return "QUOTE_ASSET_NOT_FOUND";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::ASK_UNDERFUNDED:
      return "ASK_UNDERFUNDED";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::ATOMIC_SWAP_BID_TASKS_NOT_FOUND:
      return "ATOMIC_SWAP_BID_TASKS_NOT_FOUND";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::ASK_IS_CANCELLED:
      return "ASK_IS_CANCELLED";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::SOURCE_ACCOUNT_EQUALS_ASK_OWNER:
      return "SOURCE_ACCOUNT_EQUALS_ASK_OWNER";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::ATOMIC_SWAP_BID_ZERO_TASKS_NOT_ALLOWED:
      return "ATOMIC_SWAP_BID_ZERO_TASKS_NOT_ALLOWED";
    case ::stellar::CreateAtomicSwapBidRequestResultCode::QUOTE_AMOUNT_OVERFLOWS:
      return "QUOTE_AMOUNT_OVERFLOWS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::INVALID_BASE_AMOUNT,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::INVALID_QUOTE_ASSET,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::ASK_NOT_FOUND,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::QUOTE_ASSET_NOT_FOUND,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::ASK_UNDERFUNDED,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::ATOMIC_SWAP_BID_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::INCORRECT_PRECISION,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::ASK_IS_CANCELLED,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::SOURCE_ACCOUNT_EQUALS_ASK_OWNER,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::ATOMIC_SWAP_BID_ZERO_TASKS_NOT_ALLOWED,
      (int32_t)::stellar::CreateAtomicSwapBidRequestResultCode::QUOTE_AMOUNT_OVERFLOWS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAtomicSwapBidRequestSuccess  : xdr::xdr_abstract {
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
  AccountID askOwnerID{};
  uint64 quoteAmount{};
  _ext_t ext{};

  CreateAtomicSwapBidRequestSuccess() = default;
  template<typename _requestID_T,
           typename _askOwnerID_T,
           typename _quoteAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<AccountID, _askOwnerID_T>::value
                          && std::is_constructible<uint64, _quoteAmount_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAtomicSwapBidRequestSuccess(_requestID_T &&_requestID,
                                             _askOwnerID_T &&_askOwnerID,
                                             _quoteAmount_T &&_quoteAmount,
                                             _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      askOwnerID(std::forward<_askOwnerID_T>(_askOwnerID)),
      quoteAmount(std::forward<_quoteAmount_T>(_quoteAmount)),
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

struct CreateAtomicSwapBidRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateAtomicSwapBidRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateAtomicSwapBidRequestSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateAtomicSwapBidRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateAtomicSwapBidRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
      _f(&CreateAtomicSwapBidRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateAtomicSwapBidRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateAtomicSwapBidRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapBidRequestSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateAtomicSwapBidRequestResult(CreateAtomicSwapBidRequestResultCode which = CreateAtomicSwapBidRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapBidRequestSuccess{};
break;
    default:
      break;
}

  }
  CreateAtomicSwapBidRequestResult(const CreateAtomicSwapBidRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapBidRequestSuccess(source.success_);
break;
    default:
      break;
}

  }
  CreateAtomicSwapBidRequestResult(CreateAtomicSwapBidRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapBidRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateAtomicSwapBidRequestResult() {
switch (code_)
{
  case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
success_.~CreateAtomicSwapBidRequestSuccess();
break;
  default:
    break;
}
}

  CreateAtomicSwapBidRequestResult &operator=(const CreateAtomicSwapBidRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateAtomicSwapBidRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapBidRequestSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateAtomicSwapBidRequestResult &operator=(CreateAtomicSwapBidRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateAtomicSwapBidRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateAtomicSwapBidRequestResultCode::SUCCESS:
new(&success_) CreateAtomicSwapBidRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateAtomicSwapBidRequestResultCode code() const { return CreateAtomicSwapBidRequestResultCode(code_); }
  CreateAtomicSwapBidRequestResult &code(CreateAtomicSwapBidRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateAtomicSwapBidRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAtomicSwapBidRequestResult: success accessed when not selected");
  }
  const CreateAtomicSwapBidRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAtomicSwapBidRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_ATOMIC_SWAP_BID_REQUEST_H_INCLUDED__
