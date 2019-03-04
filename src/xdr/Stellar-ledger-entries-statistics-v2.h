// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-statistics-v2.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_STATISTICS_V2_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_STATISTICS_V2_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"
#include "xdr/Stellar-ledger-entries-limits-v2.h"

namespace stellar {

struct StatisticsV2Entry {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::StatisticsV2Entry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::StatisticsV2Entry::_ext_t;
  using case_type = ::stellar::StatisticsV2Entry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::StatisticsV2Entry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::StatisticsV2Entry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::StatisticsV2Entry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::StatisticsV2Entry>
  : xdr_struct_base<field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::id),
                              &::stellar::StatisticsV2Entry::id>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::accountID),
                              &::stellar::StatisticsV2Entry::accountID>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::statsOpType),
                              &::stellar::StatisticsV2Entry::statsOpType>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::assetCode),
                              &::stellar::StatisticsV2Entry::assetCode>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::isConvertNeeded),
                              &::stellar::StatisticsV2Entry::isConvertNeeded>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::dailyOutcome),
                              &::stellar::StatisticsV2Entry::dailyOutcome>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::weeklyOutcome),
                              &::stellar::StatisticsV2Entry::weeklyOutcome>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::monthlyOutcome),
                              &::stellar::StatisticsV2Entry::monthlyOutcome>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::annualOutcome),
                              &::stellar::StatisticsV2Entry::annualOutcome>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::updatedAt),
                              &::stellar::StatisticsV2Entry::updatedAt>,
                    field_ptr<::stellar::StatisticsV2Entry,
                              decltype(::stellar::StatisticsV2Entry::ext),
                              &::stellar::StatisticsV2Entry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::StatisticsV2Entry &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.statsOpType, "statsOpType");
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.isConvertNeeded, "isConvertNeeded");
    archive(ar, obj.dailyOutcome, "dailyOutcome");
    archive(ar, obj.weeklyOutcome, "weeklyOutcome");
    archive(ar, obj.monthlyOutcome, "monthlyOutcome");
    archive(ar, obj.annualOutcome, "annualOutcome");
    archive(ar, obj.updatedAt, "updatedAt");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::StatisticsV2Entry &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.statsOpType, "statsOpType");
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.isConvertNeeded, "isConvertNeeded");
    archive(ar, obj.dailyOutcome, "dailyOutcome");
    archive(ar, obj.weeklyOutcome, "weeklyOutcome");
    archive(ar, obj.monthlyOutcome, "monthlyOutcome");
    archive(ar, obj.annualOutcome, "annualOutcome");
    archive(ar, obj.updatedAt, "updatedAt");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_STATISTICS_V2_H_INCLUDED__
