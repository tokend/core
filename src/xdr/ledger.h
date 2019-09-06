// -*- C++ -*-
// Automatically generated from ledger.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_H_INCLUDED__
#define __XDR_LEDGER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/transaction.h"
#include "xdr/SCP.h"
#include "xdr/ledger-keys.h"

namespace stellar {

using UpgradeType = xdr::opaque_vec<128>;

struct StellarValue  : xdr::xdr_abstract {
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

  Hash txSetHash{};
  uint64 closeTime{};
  xdr::xvector<UpgradeType,6> upgrades{};
  _ext_t ext{};

  StellarValue() = default;
  template<typename _txSetHash_T,
           typename _closeTime_T,
           typename _upgrades_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _txSetHash_T>::value
                          && std::is_constructible<uint64, _closeTime_T>::value
                          && std::is_constructible<xdr::xvector<UpgradeType,6>, _upgrades_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit StellarValue(_txSetHash_T &&_txSetHash,
                        _closeTime_T &&_closeTime,
                        _upgrades_T &&_upgrades,
                        _ext_T &&_ext)
    : txSetHash(std::forward<_txSetHash_T>(_txSetHash)),
      closeTime(std::forward<_closeTime_T>(_closeTime)),
      upgrades(std::forward<_upgrades_T>(_upgrades)),
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

struct IdGenerator  : xdr::xdr_abstract {
  LedgerEntryType entryType{};
  uint64 idPool{};

  IdGenerator() = default;
  template<typename _entryType_T,
           typename _idPool_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerEntryType, _entryType_T>::value
                          && std::is_constructible<uint64, _idPool_T>::value
                         >::type>
  explicit IdGenerator(_entryType_T &&_entryType,
                       _idPool_T &&_idPool)
    : entryType(std::forward<_entryType_T>(_entryType)),
      idPool(std::forward<_idPool_T>(_idPool)) {}
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

struct LedgerHeader  : xdr::xdr_abstract {
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

  uint32 ledgerVersion{};
  Hash previousLedgerHash{};
  StellarValue scpValue{};
  Hash txSetResultHash{};
  Hash bucketListHash{};
  uint32 ledgerSeq{};
  xdr::xvector<IdGenerator> idGenerators{};
  uint32 baseFee{};
  uint32 baseReserve{};
  uint32 maxTxSetSize{};
  int64 txExpirationPeriod{};
  xdr::xarray<Hash,4> skipList{};
  _ext_t ext{};

  LedgerHeader() = default;
  template<typename _ledgerVersion_T,
           typename _previousLedgerHash_T,
           typename _scpValue_T,
           typename _txSetResultHash_T,
           typename _bucketListHash_T,
           typename _ledgerSeq_T,
           typename _idGenerators_T,
           typename _baseFee_T,
           typename _baseReserve_T,
           typename _maxTxSetSize_T,
           typename _txExpirationPeriod_T,
           typename _skipList_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerVersion_T>::value
                          && std::is_constructible<Hash, _previousLedgerHash_T>::value
                          && std::is_constructible<StellarValue, _scpValue_T>::value
                          && std::is_constructible<Hash, _txSetResultHash_T>::value
                          && std::is_constructible<Hash, _bucketListHash_T>::value
                          && std::is_constructible<uint32, _ledgerSeq_T>::value
                          && std::is_constructible<xdr::xvector<IdGenerator>, _idGenerators_T>::value
                          && std::is_constructible<uint32, _baseFee_T>::value
                          && std::is_constructible<uint32, _baseReserve_T>::value
                          && std::is_constructible<uint32, _maxTxSetSize_T>::value
                          && std::is_constructible<int64, _txExpirationPeriod_T>::value
                          && std::is_constructible<xdr::xarray<Hash,4>, _skipList_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LedgerHeader(_ledgerVersion_T &&_ledgerVersion,
                        _previousLedgerHash_T &&_previousLedgerHash,
                        _scpValue_T &&_scpValue,
                        _txSetResultHash_T &&_txSetResultHash,
                        _bucketListHash_T &&_bucketListHash,
                        _ledgerSeq_T &&_ledgerSeq,
                        _idGenerators_T &&_idGenerators,
                        _baseFee_T &&_baseFee,
                        _baseReserve_T &&_baseReserve,
                        _maxTxSetSize_T &&_maxTxSetSize,
                        _txExpirationPeriod_T &&_txExpirationPeriod,
                        _skipList_T &&_skipList,
                        _ext_T &&_ext)
    : ledgerVersion(std::forward<_ledgerVersion_T>(_ledgerVersion)),
      previousLedgerHash(std::forward<_previousLedgerHash_T>(_previousLedgerHash)),
      scpValue(std::forward<_scpValue_T>(_scpValue)),
      txSetResultHash(std::forward<_txSetResultHash_T>(_txSetResultHash)),
      bucketListHash(std::forward<_bucketListHash_T>(_bucketListHash)),
      ledgerSeq(std::forward<_ledgerSeq_T>(_ledgerSeq)),
      idGenerators(std::forward<_idGenerators_T>(_idGenerators)),
      baseFee(std::forward<_baseFee_T>(_baseFee)),
      baseReserve(std::forward<_baseReserve_T>(_baseReserve)),
      maxTxSetSize(std::forward<_maxTxSetSize_T>(_maxTxSetSize)),
      txExpirationPeriod(std::forward<_txExpirationPeriod_T>(_txExpirationPeriod)),
      skipList(std::forward<_skipList_T>(_skipList)),
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

enum class LedgerUpgradeType : std::int32_t {
  VERSION = 1,
  MAX_TX_SET_SIZE = 2,
  TX_EXPIRATION_PERIOD = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerUpgradeType>
  : xdr_integral_base<::stellar::LedgerUpgradeType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LedgerUpgradeType val) {
    switch (val) {
    case ::stellar::LedgerUpgradeType::VERSION:
      return "VERSION";
    case ::stellar::LedgerUpgradeType::MAX_TX_SET_SIZE:
      return "MAX_TX_SET_SIZE";
    case ::stellar::LedgerUpgradeType::TX_EXPIRATION_PERIOD:
      return "TX_EXPIRATION_PERIOD";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LedgerUpgradeType::VERSION,
      (int32_t)::stellar::LedgerUpgradeType::MAX_TX_SET_SIZE,
      (int32_t)::stellar::LedgerUpgradeType::TX_EXPIRATION_PERIOD
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LedgerUpgrade : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<LedgerUpgradeType>::case_type;
private:
  _xdr_case_type type_;
  union {
    uint32 newLedgerVersion_;
    uint32 newMaxTxSetSize_;
    int64 newTxExpirationPeriod_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerUpgradeType> &_xdr_case_values() {
    static const std::vector<LedgerUpgradeType> _xdr_disc_vec {
      LedgerUpgradeType::VERSION,
      LedgerUpgradeType::MAX_TX_SET_SIZE,
      LedgerUpgradeType::TX_EXPIRATION_PERIOD
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LedgerUpgradeType::VERSION ? 1
      : which == (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE ? 2
      : which == (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD ? 3
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LedgerUpgradeType::VERSION:
      _f(&LedgerUpgrade::newLedgerVersion_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
      _f(&LedgerUpgrade::newMaxTxSetSize_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
      _f(&LedgerUpgrade::newTxExpirationPeriod_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in LedgerUpgrade");
    if (fnum != _xdr_field_number(type_)) {
      this->~LedgerUpgrade();
      type_ = which;switch (type_)
{
      case (int32_t)LedgerUpgradeType::VERSION:
new(&newLedgerVersion_) uint32{};
break;
      case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
new(&newMaxTxSetSize_) uint32{};
break;
      case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
new(&newTxExpirationPeriod_) int64{};
break;
}

    }
    else
      type_ = which;
  }
  explicit LedgerUpgrade(LedgerUpgradeType which = LedgerUpgradeType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)LedgerUpgradeType::VERSION:
new(&newLedgerVersion_) uint32{};
break;
    case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
new(&newMaxTxSetSize_) uint32{};
break;
    case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
new(&newTxExpirationPeriod_) int64{};
break;
}

  }
  LedgerUpgrade(const LedgerUpgrade &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerUpgradeType::VERSION:
new(&newLedgerVersion_) uint32(source.newLedgerVersion_);
break;
    case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
new(&newMaxTxSetSize_) uint32(source.newMaxTxSetSize_);
break;
    case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
new(&newTxExpirationPeriod_) int64(source.newTxExpirationPeriod_);
break;
}

  }
  LedgerUpgrade(LedgerUpgrade &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerUpgradeType::VERSION:
new(&newLedgerVersion_) uint32(std::move(source.newLedgerVersion_));
break;
    case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
new(&newMaxTxSetSize_) uint32(std::move(source.newMaxTxSetSize_));
break;
    case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
new(&newTxExpirationPeriod_) int64(std::move(source.newTxExpirationPeriod_));
break;
}

  }
  ~LedgerUpgrade() {
switch (type_)
{
  case (int32_t)LedgerUpgradeType::VERSION:
newLedgerVersion_.~uint32();
break;
  case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
newMaxTxSetSize_.~uint32();
break;
  case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
newTxExpirationPeriod_.~int64();
break;
}
}

  LedgerUpgrade &operator=(const LedgerUpgrade &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerUpgradeType::VERSION:
newLedgerVersion_ = source.newLedgerVersion_;
break;
    case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
newMaxTxSetSize_ = source.newMaxTxSetSize_;
break;
    case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
newTxExpirationPeriod_ = source.newTxExpirationPeriod_;
break;
}
}
else {this->~LedgerUpgrade();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)LedgerUpgradeType::VERSION:
new(&newLedgerVersion_) uint32(source.newLedgerVersion_);
break;
    case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
new(&newMaxTxSetSize_) uint32(source.newMaxTxSetSize_);
break;
    case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
new(&newTxExpirationPeriod_) int64(source.newTxExpirationPeriod_);
break;
}
}
    return *this;
  }
  LedgerUpgrade &operator=(LedgerUpgrade &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerUpgradeType::VERSION:
newLedgerVersion_ = std::move(source.newLedgerVersion_);
break;
    case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
newMaxTxSetSize_ = std::move(source.newMaxTxSetSize_);
break;
    case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
newTxExpirationPeriod_ = std::move(source.newTxExpirationPeriod_);
break;
}
}
else {this->~LedgerUpgrade();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)LedgerUpgradeType::VERSION:
new(&newLedgerVersion_) uint32(std::move(source.newLedgerVersion_));
break;
    case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
new(&newMaxTxSetSize_) uint32(std::move(source.newMaxTxSetSize_));
break;
    case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
new(&newTxExpirationPeriod_) int64(std::move(source.newTxExpirationPeriod_));
break;
}
}
    return *this;
  }

  LedgerUpgradeType type() const { return LedgerUpgradeType(type_); }
  LedgerUpgrade &type(LedgerUpgradeType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  uint32 &newLedgerVersion() {
    if (_xdr_field_number(type_) == 1)
      return newLedgerVersion_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newLedgerVersion accessed when not selected");
  }
  const uint32 &newLedgerVersion() const {
    if (_xdr_field_number(type_) == 1)
      return newLedgerVersion_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newLedgerVersion accessed when not selected");
  }
  uint32 &newMaxTxSetSize() {
    if (_xdr_field_number(type_) == 2)
      return newMaxTxSetSize_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newMaxTxSetSize accessed when not selected");
  }
  const uint32 &newMaxTxSetSize() const {
    if (_xdr_field_number(type_) == 2)
      return newMaxTxSetSize_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newMaxTxSetSize accessed when not selected");
  }
  int64 &newTxExpirationPeriod() {
    if (_xdr_field_number(type_) == 3)
      return newTxExpirationPeriod_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newTxExpirationPeriod accessed when not selected");
  }
  const int64 &newTxExpirationPeriod() const {
    if (_xdr_field_number(type_) == 3)
      return newTxExpirationPeriod_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newTxExpirationPeriod accessed when not selected");
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

enum class BucketEntryType : std::int32_t {
  LIVEENTRY = 0,
  DEADENTRY = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BucketEntryType>
  : xdr_integral_base<::stellar::BucketEntryType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::BucketEntryType val) {
    switch (val) {
    case ::stellar::BucketEntryType::LIVEENTRY:
      return "LIVEENTRY";
    case ::stellar::BucketEntryType::DEADENTRY:
      return "DEADENTRY";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::BucketEntryType::LIVEENTRY,
      (int32_t)::stellar::BucketEntryType::DEADENTRY
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct BucketEntry : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<BucketEntryType>::case_type;
private:
  _xdr_case_type type_;
  union {
    LedgerEntry liveEntry_;
    LedgerKey deadEntry_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<BucketEntryType> &_xdr_case_values() {
    static const std::vector<BucketEntryType> _xdr_disc_vec {
      BucketEntryType::LIVEENTRY,
      BucketEntryType::DEADENTRY
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)BucketEntryType::LIVEENTRY ? 1
      : which == (int32_t)BucketEntryType::DEADENTRY ? 2
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)BucketEntryType::LIVEENTRY:
      _f(&BucketEntry::liveEntry_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)BucketEntryType::DEADENTRY:
      _f(&BucketEntry::deadEntry_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in BucketEntry");
    if (fnum != _xdr_field_number(type_)) {
      this->~BucketEntry();
      type_ = which;switch (type_)
{
      case (int32_t)BucketEntryType::LIVEENTRY:
new(&liveEntry_) LedgerEntry{};
break;
      case (int32_t)BucketEntryType::DEADENTRY:
new(&deadEntry_) LedgerKey{};
break;
}

    }
    else
      type_ = which;
  }
  explicit BucketEntry(BucketEntryType which = BucketEntryType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)BucketEntryType::LIVEENTRY:
new(&liveEntry_) LedgerEntry{};
break;
    case (int32_t)BucketEntryType::DEADENTRY:
new(&deadEntry_) LedgerKey{};
break;
}

  }
  BucketEntry(const BucketEntry &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)BucketEntryType::LIVEENTRY:
new(&liveEntry_) LedgerEntry(source.liveEntry_);
break;
    case (int32_t)BucketEntryType::DEADENTRY:
new(&deadEntry_) LedgerKey(source.deadEntry_);
break;
}

  }
  BucketEntry(BucketEntry &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)BucketEntryType::LIVEENTRY:
new(&liveEntry_) LedgerEntry(std::move(source.liveEntry_));
break;
    case (int32_t)BucketEntryType::DEADENTRY:
new(&deadEntry_) LedgerKey(std::move(source.deadEntry_));
break;
}

  }
  ~BucketEntry() {
switch (type_)
{
  case (int32_t)BucketEntryType::LIVEENTRY:
liveEntry_.~LedgerEntry();
break;
  case (int32_t)BucketEntryType::DEADENTRY:
deadEntry_.~LedgerKey();
break;
}
}

  BucketEntry &operator=(const BucketEntry &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)BucketEntryType::LIVEENTRY:
liveEntry_ = source.liveEntry_;
break;
    case (int32_t)BucketEntryType::DEADENTRY:
deadEntry_ = source.deadEntry_;
break;
}
}
else {this->~BucketEntry();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)BucketEntryType::LIVEENTRY:
new(&liveEntry_) LedgerEntry(source.liveEntry_);
break;
    case (int32_t)BucketEntryType::DEADENTRY:
new(&deadEntry_) LedgerKey(source.deadEntry_);
break;
}
}
    return *this;
  }
  BucketEntry &operator=(BucketEntry &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)BucketEntryType::LIVEENTRY:
liveEntry_ = std::move(source.liveEntry_);
break;
    case (int32_t)BucketEntryType::DEADENTRY:
deadEntry_ = std::move(source.deadEntry_);
break;
}
}
else {this->~BucketEntry();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)BucketEntryType::LIVEENTRY:
new(&liveEntry_) LedgerEntry(std::move(source.liveEntry_));
break;
    case (int32_t)BucketEntryType::DEADENTRY:
new(&deadEntry_) LedgerKey(std::move(source.deadEntry_));
break;
}
}
    return *this;
  }

  BucketEntryType type() const { return BucketEntryType(type_); }
  BucketEntry &type(BucketEntryType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  LedgerEntry &liveEntry() {
    if (_xdr_field_number(type_) == 1)
      return liveEntry_;
    throw xdr::xdr_wrong_union("BucketEntry: liveEntry accessed when not selected");
  }
  const LedgerEntry &liveEntry() const {
    if (_xdr_field_number(type_) == 1)
      return liveEntry_;
    throw xdr::xdr_wrong_union("BucketEntry: liveEntry accessed when not selected");
  }
  LedgerKey &deadEntry() {
    if (_xdr_field_number(type_) == 2)
      return deadEntry_;
    throw xdr::xdr_wrong_union("BucketEntry: deadEntry accessed when not selected");
  }
  const LedgerKey &deadEntry() const {
    if (_xdr_field_number(type_) == 2)
      return deadEntry_;
    throw xdr::xdr_wrong_union("BucketEntry: deadEntry accessed when not selected");
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

struct TransactionSet  : xdr::xdr_abstract {
  Hash previousLedgerHash{};
  xdr::xvector<TransactionEnvelope> txs{};

  TransactionSet() = default;
  template<typename _previousLedgerHash_T,
           typename _txs_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _previousLedgerHash_T>::value
                          && std::is_constructible<xdr::xvector<TransactionEnvelope>, _txs_T>::value
                         >::type>
  explicit TransactionSet(_previousLedgerHash_T &&_previousLedgerHash,
                          _txs_T &&_txs)
    : previousLedgerHash(std::forward<_previousLedgerHash_T>(_previousLedgerHash)),
      txs(std::forward<_txs_T>(_txs)) {}
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

struct TransactionResultPair  : xdr::xdr_abstract {
  Hash transactionHash{};
  TransactionResult result{};

  TransactionResultPair() = default;
  template<typename _transactionHash_T,
           typename _result_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _transactionHash_T>::value
                          && std::is_constructible<TransactionResult, _result_T>::value
                         >::type>
  explicit TransactionResultPair(_transactionHash_T &&_transactionHash,
                                 _result_T &&_result)
    : transactionHash(std::forward<_transactionHash_T>(_transactionHash)),
      result(std::forward<_result_T>(_result)) {}
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

struct TransactionResultSet  : xdr::xdr_abstract {
  xdr::xvector<TransactionResultPair> results{};

  TransactionResultSet() = default;
  template<typename _results_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<TransactionResultPair>, _results_T>::value
                         >::type>
  explicit TransactionResultSet(_results_T &&_results)
    : results(std::forward<_results_T>(_results)) {}
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

struct TransactionHistoryEntry  : xdr::xdr_abstract {
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

  uint32 ledgerSeq{};
  TransactionSet txSet{};
  _ext_t ext{};

  TransactionHistoryEntry() = default;
  template<typename _ledgerSeq_T,
           typename _txSet_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerSeq_T>::value
                          && std::is_constructible<TransactionSet, _txSet_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit TransactionHistoryEntry(_ledgerSeq_T &&_ledgerSeq,
                                   _txSet_T &&_txSet,
                                   _ext_T &&_ext)
    : ledgerSeq(std::forward<_ledgerSeq_T>(_ledgerSeq)),
      txSet(std::forward<_txSet_T>(_txSet)),
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

struct TransactionHistoryResultEntry  : xdr::xdr_abstract {
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

  uint32 ledgerSeq{};
  TransactionResultSet txResultSet{};
  _ext_t ext{};

  TransactionHistoryResultEntry() = default;
  template<typename _ledgerSeq_T,
           typename _txResultSet_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerSeq_T>::value
                          && std::is_constructible<TransactionResultSet, _txResultSet_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit TransactionHistoryResultEntry(_ledgerSeq_T &&_ledgerSeq,
                                         _txResultSet_T &&_txResultSet,
                                         _ext_T &&_ext)
    : ledgerSeq(std::forward<_ledgerSeq_T>(_ledgerSeq)),
      txResultSet(std::forward<_txResultSet_T>(_txResultSet)),
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

struct LedgerHeaderHistoryEntry  : xdr::xdr_abstract {
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

  Hash hash{};
  LedgerHeader header{};
  _ext_t ext{};

  LedgerHeaderHistoryEntry() = default;
  template<typename _hash_T,
           typename _header_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _hash_T>::value
                          && std::is_constructible<LedgerHeader, _header_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LedgerHeaderHistoryEntry(_hash_T &&_hash,
                                    _header_T &&_header,
                                    _ext_T &&_ext)
    : hash(std::forward<_hash_T>(_hash)),
      header(std::forward<_header_T>(_header)),
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

struct LedgerSCPMessages  : xdr::xdr_abstract {
  uint32 ledgerSeq{};
  xdr::xvector<SCPEnvelope> messages{};

  LedgerSCPMessages() = default;
  template<typename _ledgerSeq_T,
           typename _messages_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerSeq_T>::value
                          && std::is_constructible<xdr::xvector<SCPEnvelope>, _messages_T>::value
                         >::type>
  explicit LedgerSCPMessages(_ledgerSeq_T &&_ledgerSeq,
                             _messages_T &&_messages)
    : ledgerSeq(std::forward<_ledgerSeq_T>(_ledgerSeq)),
      messages(std::forward<_messages_T>(_messages)) {}
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

struct SCPHistoryEntryV0  : xdr::xdr_abstract {
  xdr::xvector<SCPQuorumSet> quorumSets{};
  LedgerSCPMessages ledgerMessages{};

  SCPHistoryEntryV0() = default;
  template<typename _quorumSets_T,
           typename _ledgerMessages_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<SCPQuorumSet>, _quorumSets_T>::value
                          && std::is_constructible<LedgerSCPMessages, _ledgerMessages_T>::value
                         >::type>
  explicit SCPHistoryEntryV0(_quorumSets_T &&_quorumSets,
                             _ledgerMessages_T &&_ledgerMessages)
    : quorumSets(std::forward<_quorumSets_T>(_quorumSets)),
      ledgerMessages(std::forward<_ledgerMessages_T>(_ledgerMessages)) {}
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

struct SCPHistoryEntry : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
private:
  _xdr_case_type v_;
  union {
    SCPHistoryEntryV0 v0_;
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
    return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      _f(&SCPHistoryEntry::v0_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in SCPHistoryEntry");
    if (fnum != _xdr_field_number(v_)) {
      this->~SCPHistoryEntry();
      v_ = which;switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) SCPHistoryEntryV0{};
break;
}

    }
    else
      v_ = which;
  }
  explicit SCPHistoryEntry(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) SCPHistoryEntryV0{};
break;
}

  }
  SCPHistoryEntry(const SCPHistoryEntry &source) : v_(source.v_) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) SCPHistoryEntryV0(source.v0_);
break;
}

  }
  SCPHistoryEntry(SCPHistoryEntry &&source) : v_(source.v_) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) SCPHistoryEntryV0(std::move(source.v0_));
break;
}

  }
  ~SCPHistoryEntry() {
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
v0_.~SCPHistoryEntryV0();
break;
}
}

  SCPHistoryEntry &operator=(const SCPHistoryEntry &source) {
    if (v_ == source.v_)
{
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
v0_ = source.v0_;
break;
}
}
else {this->~SCPHistoryEntry();
    v_ = source.v_;
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) SCPHistoryEntryV0(source.v0_);
break;
}
}
    return *this;
  }
  SCPHistoryEntry &operator=(SCPHistoryEntry &&source) {
    if (v_ == source.v_)
{
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
v0_ = std::move(source.v0_);
break;
}
}
else {this->~SCPHistoryEntry();
    v_ = std::move(source.v_);
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&v0_) SCPHistoryEntryV0(std::move(source.v0_));
break;
}
}
    return *this;
  }

  LedgerVersion v() const { return LedgerVersion(v_); }
  SCPHistoryEntry &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  SCPHistoryEntryV0 &v0() {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("SCPHistoryEntry: v0 accessed when not selected");
  }
  const SCPHistoryEntryV0 &v0() const {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("SCPHistoryEntry: v0 accessed when not selected");
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

enum class LedgerEntryChangeType : std::int32_t {
  CREATED = 0,
  UPDATED = 1,
  REMOVED = 2,
  STATE = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerEntryChangeType>
  : xdr_integral_base<::stellar::LedgerEntryChangeType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LedgerEntryChangeType val) {
    switch (val) {
    case ::stellar::LedgerEntryChangeType::CREATED:
      return "CREATED";
    case ::stellar::LedgerEntryChangeType::UPDATED:
      return "UPDATED";
    case ::stellar::LedgerEntryChangeType::REMOVED:
      return "REMOVED";
    case ::stellar::LedgerEntryChangeType::STATE:
      return "STATE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LedgerEntryChangeType::CREATED,
      (int32_t)::stellar::LedgerEntryChangeType::UPDATED,
      (int32_t)::stellar::LedgerEntryChangeType::REMOVED,
      (int32_t)::stellar::LedgerEntryChangeType::STATE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LedgerEntryChange : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<LedgerEntryChangeType>::case_type;
private:
  _xdr_case_type type_;
  union {
    LedgerEntry created_;
    LedgerEntry updated_;
    LedgerKey removed_;
    LedgerEntry state_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerEntryChangeType> &_xdr_case_values() {
    static const std::vector<LedgerEntryChangeType> _xdr_disc_vec {
      LedgerEntryChangeType::CREATED,
      LedgerEntryChangeType::UPDATED,
      LedgerEntryChangeType::REMOVED,
      LedgerEntryChangeType::STATE
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LedgerEntryChangeType::CREATED ? 1
      : which == (int32_t)LedgerEntryChangeType::UPDATED ? 2
      : which == (int32_t)LedgerEntryChangeType::REMOVED ? 3
      : which == (int32_t)LedgerEntryChangeType::STATE ? 4
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LedgerEntryChangeType::CREATED:
      _f(&LedgerEntryChange::created_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryChangeType::UPDATED:
      _f(&LedgerEntryChange::updated_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryChangeType::REMOVED:
      _f(&LedgerEntryChange::removed_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryChangeType::STATE:
      _f(&LedgerEntryChange::state_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in LedgerEntryChange");
    if (fnum != _xdr_field_number(type_)) {
      this->~LedgerEntryChange();
      type_ = which;switch (type_)
{
      case (int32_t)LedgerEntryChangeType::CREATED:
new(&created_) LedgerEntry{};
break;
      case (int32_t)LedgerEntryChangeType::UPDATED:
new(&updated_) LedgerEntry{};
break;
      case (int32_t)LedgerEntryChangeType::REMOVED:
new(&removed_) LedgerKey{};
break;
      case (int32_t)LedgerEntryChangeType::STATE:
new(&state_) LedgerEntry{};
break;
}

    }
    else
      type_ = which;
  }
  explicit LedgerEntryChange(LedgerEntryChangeType which = LedgerEntryChangeType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)LedgerEntryChangeType::CREATED:
new(&created_) LedgerEntry{};
break;
    case (int32_t)LedgerEntryChangeType::UPDATED:
new(&updated_) LedgerEntry{};
break;
    case (int32_t)LedgerEntryChangeType::REMOVED:
new(&removed_) LedgerKey{};
break;
    case (int32_t)LedgerEntryChangeType::STATE:
new(&state_) LedgerEntry{};
break;
}

  }
  LedgerEntryChange(const LedgerEntryChange &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerEntryChangeType::CREATED:
new(&created_) LedgerEntry(source.created_);
break;
    case (int32_t)LedgerEntryChangeType::UPDATED:
new(&updated_) LedgerEntry(source.updated_);
break;
    case (int32_t)LedgerEntryChangeType::REMOVED:
new(&removed_) LedgerKey(source.removed_);
break;
    case (int32_t)LedgerEntryChangeType::STATE:
new(&state_) LedgerEntry(source.state_);
break;
}

  }
  LedgerEntryChange(LedgerEntryChange &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerEntryChangeType::CREATED:
new(&created_) LedgerEntry(std::move(source.created_));
break;
    case (int32_t)LedgerEntryChangeType::UPDATED:
new(&updated_) LedgerEntry(std::move(source.updated_));
break;
    case (int32_t)LedgerEntryChangeType::REMOVED:
new(&removed_) LedgerKey(std::move(source.removed_));
break;
    case (int32_t)LedgerEntryChangeType::STATE:
new(&state_) LedgerEntry(std::move(source.state_));
break;
}

  }
  ~LedgerEntryChange() {
switch (type_)
{
  case (int32_t)LedgerEntryChangeType::CREATED:
created_.~LedgerEntry();
break;
  case (int32_t)LedgerEntryChangeType::UPDATED:
updated_.~LedgerEntry();
break;
  case (int32_t)LedgerEntryChangeType::REMOVED:
removed_.~LedgerKey();
break;
  case (int32_t)LedgerEntryChangeType::STATE:
state_.~LedgerEntry();
break;
}
}

  LedgerEntryChange &operator=(const LedgerEntryChange &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerEntryChangeType::CREATED:
created_ = source.created_;
break;
    case (int32_t)LedgerEntryChangeType::UPDATED:
updated_ = source.updated_;
break;
    case (int32_t)LedgerEntryChangeType::REMOVED:
removed_ = source.removed_;
break;
    case (int32_t)LedgerEntryChangeType::STATE:
state_ = source.state_;
break;
}
}
else {this->~LedgerEntryChange();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)LedgerEntryChangeType::CREATED:
new(&created_) LedgerEntry(source.created_);
break;
    case (int32_t)LedgerEntryChangeType::UPDATED:
new(&updated_) LedgerEntry(source.updated_);
break;
    case (int32_t)LedgerEntryChangeType::REMOVED:
new(&removed_) LedgerKey(source.removed_);
break;
    case (int32_t)LedgerEntryChangeType::STATE:
new(&state_) LedgerEntry(source.state_);
break;
}
}
    return *this;
  }
  LedgerEntryChange &operator=(LedgerEntryChange &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerEntryChangeType::CREATED:
created_ = std::move(source.created_);
break;
    case (int32_t)LedgerEntryChangeType::UPDATED:
updated_ = std::move(source.updated_);
break;
    case (int32_t)LedgerEntryChangeType::REMOVED:
removed_ = std::move(source.removed_);
break;
    case (int32_t)LedgerEntryChangeType::STATE:
state_ = std::move(source.state_);
break;
}
}
else {this->~LedgerEntryChange();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)LedgerEntryChangeType::CREATED:
new(&created_) LedgerEntry(std::move(source.created_));
break;
    case (int32_t)LedgerEntryChangeType::UPDATED:
new(&updated_) LedgerEntry(std::move(source.updated_));
break;
    case (int32_t)LedgerEntryChangeType::REMOVED:
new(&removed_) LedgerKey(std::move(source.removed_));
break;
    case (int32_t)LedgerEntryChangeType::STATE:
new(&state_) LedgerEntry(std::move(source.state_));
break;
}
}
    return *this;
  }

  LedgerEntryChangeType type() const { return LedgerEntryChangeType(type_); }
  LedgerEntryChange &type(LedgerEntryChangeType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  LedgerEntry &created() {
    if (_xdr_field_number(type_) == 1)
      return created_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: created accessed when not selected");
  }
  const LedgerEntry &created() const {
    if (_xdr_field_number(type_) == 1)
      return created_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: created accessed when not selected");
  }
  LedgerEntry &updated() {
    if (_xdr_field_number(type_) == 2)
      return updated_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: updated accessed when not selected");
  }
  const LedgerEntry &updated() const {
    if (_xdr_field_number(type_) == 2)
      return updated_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: updated accessed when not selected");
  }
  LedgerKey &removed() {
    if (_xdr_field_number(type_) == 3)
      return removed_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: removed accessed when not selected");
  }
  const LedgerKey &removed() const {
    if (_xdr_field_number(type_) == 3)
      return removed_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: removed accessed when not selected");
  }
  LedgerEntry &state() {
    if (_xdr_field_number(type_) == 4)
      return state_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: state accessed when not selected");
  }
  const LedgerEntry &state() const {
    if (_xdr_field_number(type_) == 4)
      return state_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: state accessed when not selected");
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

using LedgerEntryChanges = xdr::xvector<LedgerEntryChange>;

struct OperationMeta  : xdr::xdr_abstract {
  LedgerEntryChanges changes{};

  OperationMeta() = default;
  template<typename _changes_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerEntryChanges, _changes_T>::value
                         >::type>
  explicit OperationMeta(_changes_T &&_changes)
    : changes(std::forward<_changes_T>(_changes)) {}
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

struct TransactionMeta : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
private:
  _xdr_case_type v_;
  union {
    xdr::xvector<OperationMeta> operations_;
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
    return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      _f(&TransactionMeta::operations_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in TransactionMeta");
    if (fnum != _xdr_field_number(v_)) {
      this->~TransactionMeta();
      v_ = which;switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&operations_) xdr::xvector<OperationMeta>{};
break;
}

    }
    else
      v_ = which;
  }
  explicit TransactionMeta(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&operations_) xdr::xvector<OperationMeta>{};
break;
}

  }
  TransactionMeta(const TransactionMeta &source) : v_(source.v_) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&operations_) xdr::xvector<OperationMeta>(source.operations_);
break;
}

  }
  TransactionMeta(TransactionMeta &&source) : v_(source.v_) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&operations_) xdr::xvector<OperationMeta>(std::move(source.operations_));
break;
}

  }
  ~TransactionMeta() {
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
operations_.~xvector<OperationMeta>();
break;
}
}

  TransactionMeta &operator=(const TransactionMeta &source) {
    if (v_ == source.v_)
{
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
operations_ = source.operations_;
break;
}
}
else {this->~TransactionMeta();
    v_ = source.v_;
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&operations_) xdr::xvector<OperationMeta>(source.operations_);
break;
}
}
    return *this;
  }
  TransactionMeta &operator=(TransactionMeta &&source) {
    if (v_ == source.v_)
{
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
operations_ = std::move(source.operations_);
break;
}
}
else {this->~TransactionMeta();
    v_ = std::move(source.v_);
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
new(&operations_) xdr::xvector<OperationMeta>(std::move(source.operations_));
break;
}
}
    return *this;
  }

  LedgerVersion v() const { return LedgerVersion(v_); }
  TransactionMeta &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  xdr::xvector<OperationMeta> &operations() {
    if (_xdr_field_number(v_) == 1)
      return operations_;
    throw xdr::xdr_wrong_union("TransactionMeta: operations accessed when not selected");
  }
  const xdr::xvector<OperationMeta> &operations() const {
    if (_xdr_field_number(v_) == 1)
      return operations_;
    throw xdr::xdr_wrong_union("TransactionMeta: operations accessed when not selected");
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

#endif // !__XDR_LEDGER_H_INCLUDED__
