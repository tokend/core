// -*- C++ -*-
// Automatically generated from ledger-entries-statistics-v2.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_STATISTICS_V2_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_STATISTICS_V2_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/ledger-entries-limits-v2.h"

namespace stellar {

struct StatisticsV2Entry  : xdr::xdr_abstract {
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
  AccountID accountID{};
  StatsOpType statsOpType{};
  AssetCode assetCode{};
  bool isConvertNeeded{};
  uint64 dailyOutcome{};
  uint64 weeklyOutcome{};
  uint64 monthlyOutcome{};
  uint64 annualOutcome{};
  int64 updatedAt{};
  _ext_t ext{};

  StatisticsV2Entry() = default;
  template<typename _id_T,
           typename _accountID_T,
           typename _statsOpType_T,
           typename _assetCode_T,
           typename _isConvertNeeded_T,
           typename _dailyOutcome_T,
           typename _weeklyOutcome_T,
           typename _monthlyOutcome_T,
           typename _annualOutcome_T,
           typename _updatedAt_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _id_T>::value
                          && std::is_constructible<AccountID, _accountID_T>::value
                          && std::is_constructible<StatsOpType, _statsOpType_T>::value
                          && std::is_constructible<AssetCode, _assetCode_T>::value
                          && std::is_constructible<bool, _isConvertNeeded_T>::value
                          && std::is_constructible<uint64, _dailyOutcome_T>::value
                          && std::is_constructible<uint64, _weeklyOutcome_T>::value
                          && std::is_constructible<uint64, _monthlyOutcome_T>::value
                          && std::is_constructible<uint64, _annualOutcome_T>::value
                          && std::is_constructible<int64, _updatedAt_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit StatisticsV2Entry(_id_T &&_id,
                             _accountID_T &&_accountID,
                             _statsOpType_T &&_statsOpType,
                             _assetCode_T &&_assetCode,
                             _isConvertNeeded_T &&_isConvertNeeded,
                             _dailyOutcome_T &&_dailyOutcome,
                             _weeklyOutcome_T &&_weeklyOutcome,
                             _monthlyOutcome_T &&_monthlyOutcome,
                             _annualOutcome_T &&_annualOutcome,
                             _updatedAt_T &&_updatedAt,
                             _ext_T &&_ext)
    : id(std::forward<_id_T>(_id)),
      accountID(std::forward<_accountID_T>(_accountID)),
      statsOpType(std::forward<_statsOpType_T>(_statsOpType)),
      assetCode(std::forward<_assetCode_T>(_assetCode)),
      isConvertNeeded(std::forward<_isConvertNeeded_T>(_isConvertNeeded)),
      dailyOutcome(std::forward<_dailyOutcome_T>(_dailyOutcome)),
      weeklyOutcome(std::forward<_weeklyOutcome_T>(_weeklyOutcome)),
      monthlyOutcome(std::forward<_monthlyOutcome_T>(_monthlyOutcome)),
      annualOutcome(std::forward<_annualOutcome_T>(_annualOutcome)),
      updatedAt(std::forward<_updatedAt_T>(_updatedAt)),
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

#endif // !__XDR_LEDGER_ENTRIES_STATISTICS_V2_H_INCLUDED__
