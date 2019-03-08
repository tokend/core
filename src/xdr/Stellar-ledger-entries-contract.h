// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-contract.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_CONTRACT_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_CONTRACT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct ContractEntry {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ContractEntry::_ext_t;
  using case_type = ::stellar::ContractEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ContractEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ContractEntry>
  : xdr_struct_base<field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::contractID),
                              &::stellar::ContractEntry::contractID>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::contractor),
                              &::stellar::ContractEntry::contractor>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::customer),
                              &::stellar::ContractEntry::customer>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::escrow),
                              &::stellar::ContractEntry::escrow>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::startTime),
                              &::stellar::ContractEntry::startTime>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::endTime),
                              &::stellar::ContractEntry::endTime>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::invoiceRequestsIDs),
                              &::stellar::ContractEntry::invoiceRequestsIDs>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::initialDetails),
                              &::stellar::ContractEntry::initialDetails>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::state),
                              &::stellar::ContractEntry::state>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::customerDetails),
                              &::stellar::ContractEntry::customerDetails>,
                    field_ptr<::stellar::ContractEntry,
                              decltype(::stellar::ContractEntry::ext),
                              &::stellar::ContractEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractEntry &obj) {
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.contractor, "contractor");
    archive(ar, obj.customer, "customer");
    archive(ar, obj.escrow, "escrow");
    archive(ar, obj.startTime, "startTime");
    archive(ar, obj.endTime, "endTime");
    archive(ar, obj.invoiceRequestsIDs, "invoiceRequestsIDs");
    archive(ar, obj.initialDetails, "initialDetails");
    archive(ar, obj.state, "state");
    archive(ar, obj.customerDetails, "customerDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractEntry &obj) {
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.contractor, "contractor");
    archive(ar, obj.customer, "customer");
    archive(ar, obj.escrow, "escrow");
    archive(ar, obj.startTime, "startTime");
    archive(ar, obj.endTime, "endTime");
    archive(ar, obj.invoiceRequestsIDs, "invoiceRequestsIDs");
    archive(ar, obj.initialDetails, "initialDetails");
    archive(ar, obj.state, "state");
    archive(ar, obj.customerDetails, "customerDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_CONTRACT_H_INCLUDED__
