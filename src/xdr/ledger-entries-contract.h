// -*- C++ -*-
// Automatically generated from ledger-entries-contract.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_CONTRACT_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_CONTRACT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

enum class ContractState : std::int32_t {
  NO_CONFIRMATIONS = 0,
  CUSTOMER_CONFIRMED = 1,
  CONTRACTOR_CONFIRMED = 2,
  DISPUTING = 4,
  REVERTING_RESOLVE = 8,
  NOT_REVERTING_RESOLVE = 16,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractState>
  : xdr_integral_base<::stellar::ContractState, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ContractState val) {
    switch (val) {
    case ::stellar::ContractState::NO_CONFIRMATIONS:
      return "NO_CONFIRMATIONS";
    case ::stellar::ContractState::CUSTOMER_CONFIRMED:
      return "CUSTOMER_CONFIRMED";
    case ::stellar::ContractState::CONTRACTOR_CONFIRMED:
      return "CONTRACTOR_CONFIRMED";
    case ::stellar::ContractState::DISPUTING:
      return "DISPUTING";
    case ::stellar::ContractState::REVERTING_RESOLVE:
      return "REVERTING_RESOLVE";
    case ::stellar::ContractState::NOT_REVERTING_RESOLVE:
      return "NOT_REVERTING_RESOLVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ContractState::NO_CONFIRMATIONS,
      (int32_t)::stellar::ContractState::CUSTOMER_CONFIRMED,
      (int32_t)::stellar::ContractState::CONTRACTOR_CONFIRMED,
      (int32_t)::stellar::ContractState::DISPUTING,
      (int32_t)::stellar::ContractState::REVERTING_RESOLVE,
      (int32_t)::stellar::ContractState::NOT_REVERTING_RESOLVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ContractEntry  : xdr::xdr_abstract {
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
  AccountID contractor{};
  AccountID customer{};
  AccountID escrow{};
  uint64 startTime{};
  uint64 endTime{};
  xdr::xvector<uint64> invoiceRequestsIDs{};
  longstring initialDetails{};
  uint32 state{};
  longstring customerDetails{};
  _ext_t ext{};

  ContractEntry() = default;
  template<typename _contractID_T,
           typename _contractor_T,
           typename _customer_T,
           typename _escrow_T,
           typename _startTime_T,
           typename _endTime_T,
           typename _invoiceRequestsIDs_T,
           typename _initialDetails_T,
           typename _state_T,
           typename _customerDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _contractID_T>::value
                          && std::is_constructible<AccountID, _contractor_T>::value
                          && std::is_constructible<AccountID, _customer_T>::value
                          && std::is_constructible<AccountID, _escrow_T>::value
                          && std::is_constructible<uint64, _startTime_T>::value
                          && std::is_constructible<uint64, _endTime_T>::value
                          && std::is_constructible<xdr::xvector<uint64>, _invoiceRequestsIDs_T>::value
                          && std::is_constructible<longstring, _initialDetails_T>::value
                          && std::is_constructible<uint32, _state_T>::value
                          && std::is_constructible<longstring, _customerDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ContractEntry(_contractID_T &&_contractID,
                         _contractor_T &&_contractor,
                         _customer_T &&_customer,
                         _escrow_T &&_escrow,
                         _startTime_T &&_startTime,
                         _endTime_T &&_endTime,
                         _invoiceRequestsIDs_T &&_invoiceRequestsIDs,
                         _initialDetails_T &&_initialDetails,
                         _state_T &&_state,
                         _customerDetails_T &&_customerDetails,
                         _ext_T &&_ext)
    : contractID(std::forward<_contractID_T>(_contractID)),
      contractor(std::forward<_contractor_T>(_contractor)),
      customer(std::forward<_customer_T>(_customer)),
      escrow(std::forward<_escrow_T>(_escrow)),
      startTime(std::forward<_startTime_T>(_startTime)),
      endTime(std::forward<_endTime_T>(_endTime)),
      invoiceRequestsIDs(std::forward<_invoiceRequestsIDs_T>(_invoiceRequestsIDs)),
      initialDetails(std::forward<_initialDetails_T>(_initialDetails)),
      state(std::forward<_state_T>(_state)),
      customerDetails(std::forward<_customerDetails_T>(_customerDetails)),
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

}

#endif // !__XDR_LEDGER_ENTRIES_CONTRACT_H_INCLUDED__
