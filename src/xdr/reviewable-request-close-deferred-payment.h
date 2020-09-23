// -*- C++ -*-
// Automatically generated from reviewable-request-close-deferred-payment.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_REVIEWABLE_REQUEST_CLOSE_DEFERRED_PAYMENT_H_INCLUDED__
#define __XDR_REVIEWABLE_REQUEST_CLOSE_DEFERRED_PAYMENT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"

namespace stellar {

enum class CloseDeferredPaymentDestinationType : std::int32_t {
  ACCOUNT = 0,
  BALANCE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CloseDeferredPaymentDestinationType>
  : xdr_integral_base<::stellar::CloseDeferredPaymentDestinationType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CloseDeferredPaymentDestinationType val) {
    switch (val) {
    case ::stellar::CloseDeferredPaymentDestinationType::ACCOUNT:
      return "ACCOUNT";
    case ::stellar::CloseDeferredPaymentDestinationType::BALANCE:
      return "BALANCE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CloseDeferredPaymentDestinationType::ACCOUNT,
      (int32_t)::stellar::CloseDeferredPaymentDestinationType::BALANCE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CloseDeferredPaymentRequest  : xdr::xdr_abstract {
  struct _destination_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<CloseDeferredPaymentDestinationType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      AccountID accountID_;
      BalanceID balanceID_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<CloseDeferredPaymentDestinationType> &_xdr_case_values() {
      static const std::vector<CloseDeferredPaymentDestinationType> _xdr_disc_vec {
        CloseDeferredPaymentDestinationType::ACCOUNT,
        CloseDeferredPaymentDestinationType::BALANCE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT ? 1
        : which == (int32_t)CloseDeferredPaymentDestinationType::BALANCE ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
        _f(&_destination_t::accountID_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
        _f(&_destination_t::balanceID_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _destination_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_destination_t();
        type_ = which;switch (type_)
{
        case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID{};
break;
        case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID{};
break;
}

      }
      else
        type_ = which;
    }
    explicit _destination_t(CloseDeferredPaymentDestinationType which = CloseDeferredPaymentDestinationType{}) : type_((int32_t)which) {
      switch (type_)
{
      case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID{};
break;
      case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID{};
break;
}

    }
    _destination_t(const _destination_t &source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID(source.accountID_);
break;
      case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID(source.balanceID_);
break;
}

    }
    _destination_t(_destination_t &&source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID(std::move(source.accountID_));
break;
      case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID(std::move(source.balanceID_));
break;
}

    }
    ~_destination_t() {
switch (type_)
{
    case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
accountID_.~AccountID();
break;
    case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
balanceID_.~BalanceID();
break;
}
}

    _destination_t &operator=(const _destination_t &source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
accountID_ = source.accountID_;
break;
      case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
balanceID_ = source.balanceID_;
break;
}
}
else {this->~_destination_t();
      type_ = source.type_;
switch (type_)
{
      case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID(source.accountID_);
break;
      case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID(source.balanceID_);
break;
}
}
      return *this;
    }
    _destination_t &operator=(_destination_t &&source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
accountID_ = std::move(source.accountID_);
break;
      case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
balanceID_ = std::move(source.balanceID_);
break;
}
}
else {this->~_destination_t();
      type_ = std::move(source.type_);
switch (type_)
{
      case (int32_t)CloseDeferredPaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID(std::move(source.accountID_));
break;
      case (int32_t)CloseDeferredPaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID(std::move(source.balanceID_));
break;
}
}
      return *this;
    }

    CloseDeferredPaymentDestinationType type() const { return CloseDeferredPaymentDestinationType(type_); }
    _destination_t &type(CloseDeferredPaymentDestinationType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    AccountID &accountID() {
      if (_xdr_field_number(type_) == 1)
        return accountID_;
      throw xdr::xdr_wrong_union("_destination_t: accountID accessed when not selected");
    }
    const AccountID &accountID() const {
      if (_xdr_field_number(type_) == 1)
        return accountID_;
      throw xdr::xdr_wrong_union("_destination_t: accountID accessed when not selected");
    }
    BalanceID &balanceID() {
      if (_xdr_field_number(type_) == 2)
        return balanceID_;
      throw xdr::xdr_wrong_union("_destination_t: balanceID accessed when not selected");
    }
    const BalanceID &balanceID() const {
      if (_xdr_field_number(type_) == 2)
        return balanceID_;
      throw xdr::xdr_wrong_union("_destination_t: balanceID accessed when not selected");
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

  uint64 deferredPaymentID{};
  _destination_t destination{};
  longstring creatorDetails{};
  uint64 amount{};
  uint32 sequenceNumber{};
  EmptyExt ext{};

  CloseDeferredPaymentRequest() = default;
  template<typename _deferredPaymentID_T,
           typename _destination_T,
           typename _creatorDetails_T,
           typename _amount_T,
           typename _sequenceNumber_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _deferredPaymentID_T>::value
                          && std::is_constructible<_destination_t, _destination_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<uint32, _sequenceNumber_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CloseDeferredPaymentRequest(_deferredPaymentID_T &&_deferredPaymentID,
                                       _destination_T &&_destination,
                                       _creatorDetails_T &&_creatorDetails,
                                       _amount_T &&_amount,
                                       _sequenceNumber_T &&_sequenceNumber,
                                       _ext_T &&_ext)
    : deferredPaymentID(std::forward<_deferredPaymentID_T>(_deferredPaymentID)),
      destination(std::forward<_destination_T>(_destination)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
      amount(std::forward<_amount_T>(_amount)),
      sequenceNumber(std::forward<_sequenceNumber_T>(_sequenceNumber)),
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

#endif // !__XDR_REVIEWABLE_REQUEST_CLOSE_DEFERRED_PAYMENT_H_INCLUDED__
