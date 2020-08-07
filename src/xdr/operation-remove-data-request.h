// -*- C++ -*-
// Automatically generated from operation-remove-data-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_REMOVE_DATA_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_REMOVE_DATA_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-remove-data.h"

namespace stellar {

struct RemoveDataRequestOp  : xdr::xdr_abstract {
  RemoveDataRequest removeDataRequest{};
  xdr::pointer<uint32> allTasks{};
  EmptyExt ext{};

  RemoveDataRequestOp() = default;
  template<typename _removeDataRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<RemoveDataRequest, _removeDataRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit RemoveDataRequestOp(_removeDataRequest_T &&_removeDataRequest,
                               _allTasks_T &&_allTasks,
                               _ext_T &&_ext)
    : removeDataRequest(std::forward<_removeDataRequest_T>(_removeDataRequest)),
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

enum class RemoveDataRequestResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RemoveDataRequestResultCode>
  : xdr_integral_base<::stellar::RemoveDataRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::RemoveDataRequestResultCode val) {
    switch (val) {
    case ::stellar::RemoveDataRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::RemoveDataRequestResultCode::NOT_FOUND:
      return "NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::RemoveDataRequestResultCode::SUCCESS,
      (int32_t)::stellar::RemoveDataRequestResultCode::NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct RemoveDataRequestResponse  : xdr::xdr_abstract {
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

  RemoveDataRequestResponse() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit RemoveDataRequestResponse(_requestID_T &&_requestID,
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

struct RemoveDataRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<RemoveDataRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    RemoveDataRequestResponse removeDataRequestResponse_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<RemoveDataRequestResultCode> &_xdr_case_values() {
    static const std::vector<RemoveDataRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)RemoveDataRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)RemoveDataRequestResultCode::SUCCESS:
      _f(&RemoveDataRequestResult::removeDataRequestResponse_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in RemoveDataRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~RemoveDataRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)RemoveDataRequestResultCode::SUCCESS:
new(&removeDataRequestResponse_) RemoveDataRequestResponse{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit RemoveDataRequestResult(RemoveDataRequestResultCode which = RemoveDataRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)RemoveDataRequestResultCode::SUCCESS:
new(&removeDataRequestResponse_) RemoveDataRequestResponse{};
break;
    default:
      break;
}

  }
  RemoveDataRequestResult(const RemoveDataRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)RemoveDataRequestResultCode::SUCCESS:
new(&removeDataRequestResponse_) RemoveDataRequestResponse(source.removeDataRequestResponse_);
break;
    default:
      break;
}

  }
  RemoveDataRequestResult(RemoveDataRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)RemoveDataRequestResultCode::SUCCESS:
new(&removeDataRequestResponse_) RemoveDataRequestResponse(std::move(source.removeDataRequestResponse_));
break;
    default:
      break;
}

  }
  ~RemoveDataRequestResult() {
switch (code_)
{
  case (int32_t)RemoveDataRequestResultCode::SUCCESS:
removeDataRequestResponse_.~RemoveDataRequestResponse();
break;
  default:
    break;
}
}

  RemoveDataRequestResult &operator=(const RemoveDataRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)RemoveDataRequestResultCode::SUCCESS:
removeDataRequestResponse_ = source.removeDataRequestResponse_;
break;
    default:
      break;
}
}
else {this->~RemoveDataRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)RemoveDataRequestResultCode::SUCCESS:
new(&removeDataRequestResponse_) RemoveDataRequestResponse(source.removeDataRequestResponse_);
break;
    default:
      break;
}
}
    return *this;
  }
  RemoveDataRequestResult &operator=(RemoveDataRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)RemoveDataRequestResultCode::SUCCESS:
removeDataRequestResponse_ = std::move(source.removeDataRequestResponse_);
break;
    default:
      break;
}
}
else {this->~RemoveDataRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)RemoveDataRequestResultCode::SUCCESS:
new(&removeDataRequestResponse_) RemoveDataRequestResponse(std::move(source.removeDataRequestResponse_));
break;
    default:
      break;
}
}
    return *this;
  }

  RemoveDataRequestResultCode code() const { return RemoveDataRequestResultCode(code_); }
  RemoveDataRequestResult &code(RemoveDataRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  RemoveDataRequestResponse &removeDataRequestResponse() {
    if (_xdr_field_number(code_) == 1)
      return removeDataRequestResponse_;
    throw xdr::xdr_wrong_union("RemoveDataRequestResult: removeDataRequestResponse accessed when not selected");
  }
  const RemoveDataRequestResponse &removeDataRequestResponse() const {
    if (_xdr_field_number(code_) == 1)
      return removeDataRequestResponse_;
    throw xdr::xdr_wrong_union("RemoveDataRequestResult: removeDataRequestResponse accessed when not selected");
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

#endif // !__XDR_OPERATION_REMOVE_DATA_REQUEST_H_INCLUDED__
