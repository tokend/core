// -*- C++ -*-
// Automatically generated from Stellar-ledger.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-transaction.h"
#include "xdr/Stellar-types.h"

namespace stellar {

using UpgradeType = xdr::opaque_vec<128>;

struct StellarValue {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::StellarValue::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::StellarValue::_ext_t;
  using case_type = ::stellar::StellarValue::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::StellarValue::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::StellarValue::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::StellarValue::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::StellarValue>
  : xdr_struct_base<field_ptr<::stellar::StellarValue,
                              decltype(::stellar::StellarValue::txSetHash),
                              &::stellar::StellarValue::txSetHash>,
                    field_ptr<::stellar::StellarValue,
                              decltype(::stellar::StellarValue::closeTime),
                              &::stellar::StellarValue::closeTime>,
                    field_ptr<::stellar::StellarValue,
                              decltype(::stellar::StellarValue::upgrades),
                              &::stellar::StellarValue::upgrades>,
                    field_ptr<::stellar::StellarValue,
                              decltype(::stellar::StellarValue::ext),
                              &::stellar::StellarValue::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::StellarValue &obj) {
    archive(ar, obj.txSetHash, "txSetHash");
    archive(ar, obj.closeTime, "closeTime");
    archive(ar, obj.upgrades, "upgrades");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::StellarValue &obj) {
    archive(ar, obj.txSetHash, "txSetHash");
    archive(ar, obj.closeTime, "closeTime");
    archive(ar, obj.upgrades, "upgrades");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct IdGenerator {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::IdGenerator>
  : xdr_struct_base<field_ptr<::stellar::IdGenerator,
                              decltype(::stellar::IdGenerator::entryType),
                              &::stellar::IdGenerator::entryType>,
                    field_ptr<::stellar::IdGenerator,
                              decltype(::stellar::IdGenerator::idPool),
                              &::stellar::IdGenerator::idPool>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::IdGenerator &obj) {
    archive(ar, obj.entryType, "entryType");
    archive(ar, obj.idPool, "idPool");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::IdGenerator &obj) {
    archive(ar, obj.entryType, "entryType");
    archive(ar, obj.idPool, "idPool");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerHeader {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerHeader::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerHeader::_ext_t;
  using case_type = ::stellar::LedgerHeader::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerHeader::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeader::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeader::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerHeader>
  : xdr_struct_base<field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::ledgerVersion),
                              &::stellar::LedgerHeader::ledgerVersion>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::previousLedgerHash),
                              &::stellar::LedgerHeader::previousLedgerHash>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::scpValue),
                              &::stellar::LedgerHeader::scpValue>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::txSetResultHash),
                              &::stellar::LedgerHeader::txSetResultHash>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::bucketListHash),
                              &::stellar::LedgerHeader::bucketListHash>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::ledgerSeq),
                              &::stellar::LedgerHeader::ledgerSeq>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::idGenerators),
                              &::stellar::LedgerHeader::idGenerators>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::baseFee),
                              &::stellar::LedgerHeader::baseFee>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::baseReserve),
                              &::stellar::LedgerHeader::baseReserve>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::maxTxSetSize),
                              &::stellar::LedgerHeader::maxTxSetSize>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::txExpirationPeriod),
                              &::stellar::LedgerHeader::txExpirationPeriod>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::skipList),
                              &::stellar::LedgerHeader::skipList>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::ext),
                              &::stellar::LedgerHeader::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeader &obj) {
    archive(ar, obj.ledgerVersion, "ledgerVersion");
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.scpValue, "scpValue");
    archive(ar, obj.txSetResultHash, "txSetResultHash");
    archive(ar, obj.bucketListHash, "bucketListHash");
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.idGenerators, "idGenerators");
    archive(ar, obj.baseFee, "baseFee");
    archive(ar, obj.baseReserve, "baseReserve");
    archive(ar, obj.maxTxSetSize, "maxTxSetSize");
    archive(ar, obj.txExpirationPeriod, "txExpirationPeriod");
    archive(ar, obj.skipList, "skipList");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeader &obj) {
    archive(ar, obj.ledgerVersion, "ledgerVersion");
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.scpValue, "scpValue");
    archive(ar, obj.txSetResultHash, "txSetResultHash");
    archive(ar, obj.bucketListHash, "bucketListHash");
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.idGenerators, "idGenerators");
    archive(ar, obj.baseFee, "baseFee");
    archive(ar, obj.baseReserve, "baseReserve");
    archive(ar, obj.maxTxSetSize, "maxTxSetSize");
    archive(ar, obj.txExpirationPeriod, "txExpirationPeriod");
    archive(ar, obj.skipList, "skipList");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class LedgerUpgradeType : std::int32_t {
  VERSION = 1,
  MAX_TX_SET_SIZE = 2,
  TX_EXPIRATION_PERIOD = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerUpgradeType>
  : xdr_integral_base<::stellar::LedgerUpgradeType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct LedgerUpgrade {
  using _xdr_case_type = xdr::xdr_traits<LedgerUpgradeType>::case_type;
private:
  _xdr_case_type type_;
  union {
    uint32 newLedgerVersion_;
    uint32 newMaxTxSetSize_;
    int64 newTxExpirationPeriod_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerUpgradeType> &_xdr_case_values() {
    static const std::vector<LedgerUpgradeType> _xdr_disc_vec {
      LedgerUpgradeType::VERSION,
      LedgerUpgradeType::MAX_TX_SET_SIZE,
      LedgerUpgradeType::TX_EXPIRATION_PERIOD
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit LedgerUpgrade(LedgerUpgradeType which = LedgerUpgradeType{}) : type_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  LedgerUpgrade(const LedgerUpgrade &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  LedgerUpgrade(LedgerUpgrade &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~LedgerUpgrade() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  LedgerUpgrade &operator=(const LedgerUpgrade &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~LedgerUpgrade();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  LedgerUpgrade &operator=(LedgerUpgrade &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~LedgerUpgrade();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerUpgrade> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerUpgrade;
  using case_type = ::stellar::LedgerUpgrade::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "newLedgerVersion";
    case 2:
      return "newMaxTxSetSize";
    case 3:
      return "newTxExpirationPeriod";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerUpgrade &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in LedgerUpgrade");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerUpgrade &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in LedgerUpgrade");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerUpgrade &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerKey {
  struct _account_t {
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

    AccountID accountID{};
    _ext_t ext{};

    _account_t() = default;
    template<typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _account_t(_accountID_T &&_accountID,
                        _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _signer_t {
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

    PublicKey pubKey{};
    AccountID accountID{};
    _ext_t ext{};

    _signer_t() = default;
    template<typename _pubKey_T,
             typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<PublicKey, _pubKey_T>::value
                            && std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _signer_t(_pubKey_T &&_pubKey,
                       _accountID_T &&_accountID,
                       _ext_T &&_ext)
      : pubKey(std::forward<_pubKey_T>(_pubKey)),
        accountID(std::forward<_accountID_T>(_accountID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _feeState_t {
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

    Hash hash{};
    int64 lowerBound{};
    int64 upperBound{};
    _ext_t ext{};

    _feeState_t() = default;
    template<typename _hash_T,
             typename _lowerBound_T,
             typename _upperBound_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<Hash, _hash_T>::value
                            && std::is_constructible<int64, _lowerBound_T>::value
                            && std::is_constructible<int64, _upperBound_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _feeState_t(_hash_T &&_hash,
                         _lowerBound_T &&_lowerBound,
                         _upperBound_T &&_upperBound,
                         _ext_T &&_ext)
      : hash(std::forward<_hash_T>(_hash)),
        lowerBound(std::forward<_lowerBound_T>(_lowerBound)),
        upperBound(std::forward<_upperBound_T>(_upperBound)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _balance_t {
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

    BalanceID balanceID{};
    _ext_t ext{};

    _balance_t() = default;
    template<typename _balanceID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<BalanceID, _balanceID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _balance_t(_balanceID_T &&_balanceID,
                        _ext_T &&_ext)
      : balanceID(std::forward<_balanceID_T>(_balanceID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _asset_t {
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

    AssetCode code{};
    _ext_t ext{};

    _asset_t() = default;
    template<typename _code_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AssetCode, _code_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _asset_t(_code_T &&_code,
                      _ext_T &&_ext)
      : code(std::forward<_code_T>(_code)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _reference_t {
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

    AccountID sender{};
    string64 reference{};
    _ext_t ext{};

    _reference_t() = default;
    template<typename _sender_T,
             typename _reference_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _sender_T>::value
                            && std::is_constructible<string64, _reference_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _reference_t(_sender_T &&_sender,
                          _reference_T &&_reference,
                          _ext_T &&_ext)
      : sender(std::forward<_sender_T>(_sender)),
        reference(std::forward<_reference_T>(_reference)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _stats_t {
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

    AccountID accountID{};
    _ext_t ext{};

    _stats_t() = default;
    template<typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _stats_t(_accountID_T &&_accountID,
                      _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _accountLimits_t {
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

    AccountID accountID{};
    _ext_t ext{};

    _accountLimits_t() = default;
    template<typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _accountLimits_t(_accountID_T &&_accountID,
                              _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _assetPair_t {
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

    AssetCode base{};
    AssetCode quote{};
    _ext_t ext{};

    _assetPair_t() = default;
    template<typename _base_T,
             typename _quote_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AssetCode, _base_T>::value
                            && std::is_constructible<AssetCode, _quote_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _assetPair_t(_base_T &&_base,
                          _quote_T &&_quote,
                          _ext_T &&_ext)
      : base(std::forward<_base_T>(_base)),
        quote(std::forward<_quote_T>(_quote)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _offer_t {
    uint64 offerID{};
    AccountID ownerID{};

    _offer_t() = default;
    template<typename _offerID_T,
             typename _ownerID_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _offerID_T>::value
                            && std::is_constructible<AccountID, _ownerID_T>::value
                           >::type>
    explicit _offer_t(_offerID_T &&_offerID,
                      _ownerID_T &&_ownerID)
      : offerID(std::forward<_offerID_T>(_offerID)),
        ownerID(std::forward<_ownerID_T>(_ownerID)) {}
  };
  struct _reviewableRequest_t {
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

    uint64 requestID{};
    _ext_t ext{};

    _reviewableRequest_t() = default;
    template<typename _requestID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _reviewableRequest_t(_requestID_T &&_requestID,
                                  _ext_T &&_ext)
      : requestID(std::forward<_requestID_T>(_requestID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _externalSystemAccountID_t {
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

    AccountID accountID{};
    int32 externalSystemType{};
    _ext_t ext{};

    _externalSystemAccountID_t() = default;
    template<typename _accountID_T,
             typename _externalSystemType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<int32, _externalSystemType_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _externalSystemAccountID_t(_accountID_T &&_accountID,
                                        _externalSystemType_T &&_externalSystemType,
                                        _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
        externalSystemType(std::forward<_externalSystemType_T>(_externalSystemType)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _sale_t {
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

    uint64 saleID{};
    _ext_t ext{};

    _sale_t() = default;
    template<typename _saleID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _saleID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _sale_t(_saleID_T &&_saleID,
                     _ext_T &&_ext)
      : saleID(std::forward<_saleID_T>(_saleID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _keyValue_t {
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

    longstring key{};
    _ext_t ext{};

    _keyValue_t() = default;
    template<typename _key_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<longstring, _key_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _keyValue_t(_key_T &&_key,
                         _ext_T &&_ext)
      : key(std::forward<_key_T>(_key)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _accountKYC_t {
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

    AccountID accountID{};
    _ext_t ext{};

    _accountKYC_t() = default;
    template<typename _accountID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _accountKYC_t(_accountID_T &&_accountID,
                           _ext_T &&_ext)
      : accountID(std::forward<_accountID_T>(_accountID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _externalSystemAccountIDPoolEntry_t {
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

    uint64 poolEntryID{};
    _ext_t ext{};

    _externalSystemAccountIDPoolEntry_t() = default;
    template<typename _poolEntryID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _poolEntryID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _externalSystemAccountIDPoolEntry_t(_poolEntryID_T &&_poolEntryID,
                                                 _ext_T &&_ext)
      : poolEntryID(std::forward<_poolEntryID_T>(_poolEntryID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _limitsV2_t {
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
    _ext_t ext{};

    _limitsV2_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _limitsV2_t(_id_T &&_id,
                         _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _statisticsV2_t {
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
    _ext_t ext{};

    _statisticsV2_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _statisticsV2_t(_id_T &&_id,
                             _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _pendingStatistics_t {
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

    uint64 statisticsID{};
    uint64 requestID{};
    _ext_t ext{};

    _pendingStatistics_t() = default;
    template<typename _statisticsID_T,
             typename _requestID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _statisticsID_T>::value
                            && std::is_constructible<uint64, _requestID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _pendingStatistics_t(_statisticsID_T &&_statisticsID,
                                  _requestID_T &&_requestID,
                                  _ext_T &&_ext)
      : statisticsID(std::forward<_statisticsID_T>(_statisticsID)),
        requestID(std::forward<_requestID_T>(_requestID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _contract_t {
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
    _ext_t ext{};

    _contract_t() = default;
    template<typename _contractID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _contractID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _contract_t(_contractID_T &&_contractID,
                         _ext_T &&_ext)
      : contractID(std::forward<_contractID_T>(_contractID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _atomicSwapBid_t {
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

    uint64 bidID{};
    _ext_t ext{};

    _atomicSwapBid_t() = default;
    template<typename _bidID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _bidID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _atomicSwapBid_t(_bidID_T &&_bidID,
                              _ext_T &&_ext)
      : bidID(std::forward<_bidID_T>(_bidID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _accountRole_t {
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
    _ext_t ext{};

    _accountRole_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _accountRole_t(_id_T &&_id,
                            _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _accountRule_t {
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
    _ext_t ext{};

    _accountRule_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _accountRule_t(_id_T &&_id,
                            _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _signerRole_t {
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
    _ext_t ext{};

    _signerRole_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _signerRole_t(_id_T &&_id,
                           _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _signerRule_t {
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
    _ext_t ext{};

    _signerRule_t() = default;
    template<typename _id_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _signerRule_t(_id_T &&_id,
                           _ext_T &&_ext)
      : id(std::forward<_id_T>(_id)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _stamp_t {
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

    Hash ledgerHash{};
    Hash licenseHash{};
    _ext_t ext{};

    _stamp_t() = default;
    template<typename _ledgerHash_T,
             typename _licenseHash_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<Hash, _ledgerHash_T>::value
                            && std::is_constructible<Hash, _licenseHash_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _stamp_t(_ledgerHash_T &&_ledgerHash,
                      _licenseHash_T &&_licenseHash,
                      _ext_T &&_ext)
      : ledgerHash(std::forward<_ledgerHash_T>(_ledgerHash)),
        licenseHash(std::forward<_licenseHash_T>(_licenseHash)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _license_t {
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

    Hash licenseHash{};
    _ext_t ext{};

    _license_t() = default;
    template<typename _licenseHash_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<Hash, _licenseHash_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _license_t(_licenseHash_T &&_licenseHash,
                        _ext_T &&_ext)
      : licenseHash(std::forward<_licenseHash_T>(_licenseHash)),
        ext(std::forward<_ext_T>(_ext)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<LedgerEntryType>::case_type;
private:
  _xdr_case_type type_;
  union {
    _account_t account_;
    _signer_t signer_;
    _feeState_t feeState_;
    _balance_t balance_;
    _asset_t asset_;
    _reference_t reference_;
    _stats_t stats_;
    _accountLimits_t accountLimits_;
    _assetPair_t assetPair_;
    _offer_t offer_;
    _reviewableRequest_t reviewableRequest_;
    _externalSystemAccountID_t externalSystemAccountID_;
    _sale_t sale_;
    _keyValue_t keyValue_;
    _accountKYC_t accountKYC_;
    _externalSystemAccountIDPoolEntry_t externalSystemAccountIDPoolEntry_;
    _limitsV2_t limitsV2_;
    _statisticsV2_t statisticsV2_;
    _pendingStatistics_t pendingStatistics_;
    _contract_t contract_;
    _atomicSwapBid_t atomicSwapBid_;
    _accountRole_t accountRole_;
    _accountRule_t accountRule_;
    _signerRole_t signerRole_;
    _signerRule_t signerRule_;
    _stamp_t stamp_;
    _license_t license_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerEntryType> &_xdr_case_values() {
    static const std::vector<LedgerEntryType> _xdr_disc_vec {
      LedgerEntryType::ACCOUNT,
      LedgerEntryType::SIGNER,
      LedgerEntryType::FEE,
      LedgerEntryType::BALANCE,
      LedgerEntryType::ASSET,
      LedgerEntryType::REFERENCE_ENTRY,
      LedgerEntryType::STATISTICS,
      LedgerEntryType::ACCOUNT_LIMITS,
      LedgerEntryType::ASSET_PAIR,
      LedgerEntryType::OFFER_ENTRY,
      LedgerEntryType::REVIEWABLE_REQUEST,
      LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID,
      LedgerEntryType::SALE,
      LedgerEntryType::KEY_VALUE,
      LedgerEntryType::ACCOUNT_KYC,
      LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY,
      LedgerEntryType::LIMITS_V2,
      LedgerEntryType::STATISTICS_V2,
      LedgerEntryType::PENDING_STATISTICS,
      LedgerEntryType::CONTRACT,
      LedgerEntryType::ATOMIC_SWAP_BID,
      LedgerEntryType::ACCOUNT_ROLE,
      LedgerEntryType::ACCOUNT_RULE,
      LedgerEntryType::SIGNER_ROLE,
      LedgerEntryType::SIGNER_RULE,
      LedgerEntryType::STAMP,
      LedgerEntryType::LICENSE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LedgerEntryType::ACCOUNT ? 1
      : which == (int32_t)LedgerEntryType::SIGNER ? 2
      : which == (int32_t)LedgerEntryType::FEE ? 3
      : which == (int32_t)LedgerEntryType::BALANCE ? 4
      : which == (int32_t)LedgerEntryType::ASSET ? 5
      : which == (int32_t)LedgerEntryType::REFERENCE_ENTRY ? 6
      : which == (int32_t)LedgerEntryType::STATISTICS ? 7
      : which == (int32_t)LedgerEntryType::ACCOUNT_LIMITS ? 8
      : which == (int32_t)LedgerEntryType::ASSET_PAIR ? 9
      : which == (int32_t)LedgerEntryType::OFFER_ENTRY ? 10
      : which == (int32_t)LedgerEntryType::REVIEWABLE_REQUEST ? 11
      : which == (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID ? 12
      : which == (int32_t)LedgerEntryType::SALE ? 13
      : which == (int32_t)LedgerEntryType::KEY_VALUE ? 14
      : which == (int32_t)LedgerEntryType::ACCOUNT_KYC ? 15
      : which == (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY ? 16
      : which == (int32_t)LedgerEntryType::LIMITS_V2 ? 17
      : which == (int32_t)LedgerEntryType::STATISTICS_V2 ? 18
      : which == (int32_t)LedgerEntryType::PENDING_STATISTICS ? 19
      : which == (int32_t)LedgerEntryType::CONTRACT ? 20
      : which == (int32_t)LedgerEntryType::ATOMIC_SWAP_BID ? 21
      : which == (int32_t)LedgerEntryType::ACCOUNT_ROLE ? 22
      : which == (int32_t)LedgerEntryType::ACCOUNT_RULE ? 23
      : which == (int32_t)LedgerEntryType::SIGNER_ROLE ? 24
      : which == (int32_t)LedgerEntryType::SIGNER_RULE ? 25
      : which == (int32_t)LedgerEntryType::STAMP ? 26
      : which == (int32_t)LedgerEntryType::LICENSE ? 27
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LedgerEntryType::ACCOUNT:
      _f(&LedgerKey::account_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SIGNER:
      _f(&LedgerKey::signer_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::FEE:
      _f(&LedgerKey::feeState_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::BALANCE:
      _f(&LedgerKey::balance_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ASSET:
      _f(&LedgerKey::asset_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
      _f(&LedgerKey::reference_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::STATISTICS:
      _f(&LedgerKey::stats_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
      _f(&LedgerKey::accountLimits_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
      _f(&LedgerKey::assetPair_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
      _f(&LedgerKey::offer_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
      _f(&LedgerKey::reviewableRequest_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
      _f(&LedgerKey::externalSystemAccountID_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SALE:
      _f(&LedgerKey::sale_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::KEY_VALUE:
      _f(&LedgerKey::keyValue_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
      _f(&LedgerKey::accountKYC_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
      _f(&LedgerKey::externalSystemAccountIDPoolEntry_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::LIMITS_V2:
      _f(&LedgerKey::limitsV2_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
      _f(&LedgerKey::statisticsV2_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
      _f(&LedgerKey::pendingStatistics_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::CONTRACT:
      _f(&LedgerKey::contract_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_BID:
      _f(&LedgerKey::atomicSwapBid_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
      _f(&LedgerKey::accountRole_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
      _f(&LedgerKey::accountRule_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
      _f(&LedgerKey::signerRole_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
      _f(&LedgerKey::signerRule_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::STAMP:
      _f(&LedgerKey::stamp_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::LICENSE:
      _f(&LedgerKey::license_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in LedgerKey");
    if (fnum != _xdr_field_number(type_)) {
      this->~LedgerKey();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit LedgerKey(LedgerEntryType which = LedgerEntryType{}) : type_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  LedgerKey(const LedgerKey &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  LedgerKey(LedgerKey &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~LedgerKey() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  LedgerKey &operator=(const LedgerKey &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~LedgerKey();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  LedgerKey &operator=(LedgerKey &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~LedgerKey();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  LedgerEntryType type() const { return LedgerEntryType(type_); }
  LedgerKey &type(LedgerEntryType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _account_t &account() {
    if (_xdr_field_number(type_) == 1)
      return account_;
    throw xdr::xdr_wrong_union("LedgerKey: account accessed when not selected");
  }
  const _account_t &account() const {
    if (_xdr_field_number(type_) == 1)
      return account_;
    throw xdr::xdr_wrong_union("LedgerKey: account accessed when not selected");
  }
  _signer_t &signer() {
    if (_xdr_field_number(type_) == 2)
      return signer_;
    throw xdr::xdr_wrong_union("LedgerKey: signer accessed when not selected");
  }
  const _signer_t &signer() const {
    if (_xdr_field_number(type_) == 2)
      return signer_;
    throw xdr::xdr_wrong_union("LedgerKey: signer accessed when not selected");
  }
  _feeState_t &feeState() {
    if (_xdr_field_number(type_) == 3)
      return feeState_;
    throw xdr::xdr_wrong_union("LedgerKey: feeState accessed when not selected");
  }
  const _feeState_t &feeState() const {
    if (_xdr_field_number(type_) == 3)
      return feeState_;
    throw xdr::xdr_wrong_union("LedgerKey: feeState accessed when not selected");
  }
  _balance_t &balance() {
    if (_xdr_field_number(type_) == 4)
      return balance_;
    throw xdr::xdr_wrong_union("LedgerKey: balance accessed when not selected");
  }
  const _balance_t &balance() const {
    if (_xdr_field_number(type_) == 4)
      return balance_;
    throw xdr::xdr_wrong_union("LedgerKey: balance accessed when not selected");
  }
  _asset_t &asset() {
    if (_xdr_field_number(type_) == 5)
      return asset_;
    throw xdr::xdr_wrong_union("LedgerKey: asset accessed when not selected");
  }
  const _asset_t &asset() const {
    if (_xdr_field_number(type_) == 5)
      return asset_;
    throw xdr::xdr_wrong_union("LedgerKey: asset accessed when not selected");
  }
  _reference_t &reference() {
    if (_xdr_field_number(type_) == 6)
      return reference_;
    throw xdr::xdr_wrong_union("LedgerKey: reference accessed when not selected");
  }
  const _reference_t &reference() const {
    if (_xdr_field_number(type_) == 6)
      return reference_;
    throw xdr::xdr_wrong_union("LedgerKey: reference accessed when not selected");
  }
  _stats_t &stats() {
    if (_xdr_field_number(type_) == 7)
      return stats_;
    throw xdr::xdr_wrong_union("LedgerKey: stats accessed when not selected");
  }
  const _stats_t &stats() const {
    if (_xdr_field_number(type_) == 7)
      return stats_;
    throw xdr::xdr_wrong_union("LedgerKey: stats accessed when not selected");
  }
  _accountLimits_t &accountLimits() {
    if (_xdr_field_number(type_) == 8)
      return accountLimits_;
    throw xdr::xdr_wrong_union("LedgerKey: accountLimits accessed when not selected");
  }
  const _accountLimits_t &accountLimits() const {
    if (_xdr_field_number(type_) == 8)
      return accountLimits_;
    throw xdr::xdr_wrong_union("LedgerKey: accountLimits accessed when not selected");
  }
  _assetPair_t &assetPair() {
    if (_xdr_field_number(type_) == 9)
      return assetPair_;
    throw xdr::xdr_wrong_union("LedgerKey: assetPair accessed when not selected");
  }
  const _assetPair_t &assetPair() const {
    if (_xdr_field_number(type_) == 9)
      return assetPair_;
    throw xdr::xdr_wrong_union("LedgerKey: assetPair accessed when not selected");
  }
  _offer_t &offer() {
    if (_xdr_field_number(type_) == 10)
      return offer_;
    throw xdr::xdr_wrong_union("LedgerKey: offer accessed when not selected");
  }
  const _offer_t &offer() const {
    if (_xdr_field_number(type_) == 10)
      return offer_;
    throw xdr::xdr_wrong_union("LedgerKey: offer accessed when not selected");
  }
  _reviewableRequest_t &reviewableRequest() {
    if (_xdr_field_number(type_) == 11)
      return reviewableRequest_;
    throw xdr::xdr_wrong_union("LedgerKey: reviewableRequest accessed when not selected");
  }
  const _reviewableRequest_t &reviewableRequest() const {
    if (_xdr_field_number(type_) == 11)
      return reviewableRequest_;
    throw xdr::xdr_wrong_union("LedgerKey: reviewableRequest accessed when not selected");
  }
  _externalSystemAccountID_t &externalSystemAccountID() {
    if (_xdr_field_number(type_) == 12)
      return externalSystemAccountID_;
    throw xdr::xdr_wrong_union("LedgerKey: externalSystemAccountID accessed when not selected");
  }
  const _externalSystemAccountID_t &externalSystemAccountID() const {
    if (_xdr_field_number(type_) == 12)
      return externalSystemAccountID_;
    throw xdr::xdr_wrong_union("LedgerKey: externalSystemAccountID accessed when not selected");
  }
  _sale_t &sale() {
    if (_xdr_field_number(type_) == 13)
      return sale_;
    throw xdr::xdr_wrong_union("LedgerKey: sale accessed when not selected");
  }
  const _sale_t &sale() const {
    if (_xdr_field_number(type_) == 13)
      return sale_;
    throw xdr::xdr_wrong_union("LedgerKey: sale accessed when not selected");
  }
  _keyValue_t &keyValue() {
    if (_xdr_field_number(type_) == 14)
      return keyValue_;
    throw xdr::xdr_wrong_union("LedgerKey: keyValue accessed when not selected");
  }
  const _keyValue_t &keyValue() const {
    if (_xdr_field_number(type_) == 14)
      return keyValue_;
    throw xdr::xdr_wrong_union("LedgerKey: keyValue accessed when not selected");
  }
  _accountKYC_t &accountKYC() {
    if (_xdr_field_number(type_) == 15)
      return accountKYC_;
    throw xdr::xdr_wrong_union("LedgerKey: accountKYC accessed when not selected");
  }
  const _accountKYC_t &accountKYC() const {
    if (_xdr_field_number(type_) == 15)
      return accountKYC_;
    throw xdr::xdr_wrong_union("LedgerKey: accountKYC accessed when not selected");
  }
  _externalSystemAccountIDPoolEntry_t &externalSystemAccountIDPoolEntry() {
    if (_xdr_field_number(type_) == 16)
      return externalSystemAccountIDPoolEntry_;
    throw xdr::xdr_wrong_union("LedgerKey: externalSystemAccountIDPoolEntry accessed when not selected");
  }
  const _externalSystemAccountIDPoolEntry_t &externalSystemAccountIDPoolEntry() const {
    if (_xdr_field_number(type_) == 16)
      return externalSystemAccountIDPoolEntry_;
    throw xdr::xdr_wrong_union("LedgerKey: externalSystemAccountIDPoolEntry accessed when not selected");
  }
  _limitsV2_t &limitsV2() {
    if (_xdr_field_number(type_) == 17)
      return limitsV2_;
    throw xdr::xdr_wrong_union("LedgerKey: limitsV2 accessed when not selected");
  }
  const _limitsV2_t &limitsV2() const {
    if (_xdr_field_number(type_) == 17)
      return limitsV2_;
    throw xdr::xdr_wrong_union("LedgerKey: limitsV2 accessed when not selected");
  }
  _statisticsV2_t &statisticsV2() {
    if (_xdr_field_number(type_) == 18)
      return statisticsV2_;
    throw xdr::xdr_wrong_union("LedgerKey: statisticsV2 accessed when not selected");
  }
  const _statisticsV2_t &statisticsV2() const {
    if (_xdr_field_number(type_) == 18)
      return statisticsV2_;
    throw xdr::xdr_wrong_union("LedgerKey: statisticsV2 accessed when not selected");
  }
  _pendingStatistics_t &pendingStatistics() {
    if (_xdr_field_number(type_) == 19)
      return pendingStatistics_;
    throw xdr::xdr_wrong_union("LedgerKey: pendingStatistics accessed when not selected");
  }
  const _pendingStatistics_t &pendingStatistics() const {
    if (_xdr_field_number(type_) == 19)
      return pendingStatistics_;
    throw xdr::xdr_wrong_union("LedgerKey: pendingStatistics accessed when not selected");
  }
  _contract_t &contract() {
    if (_xdr_field_number(type_) == 20)
      return contract_;
    throw xdr::xdr_wrong_union("LedgerKey: contract accessed when not selected");
  }
  const _contract_t &contract() const {
    if (_xdr_field_number(type_) == 20)
      return contract_;
    throw xdr::xdr_wrong_union("LedgerKey: contract accessed when not selected");
  }
  _atomicSwapBid_t &atomicSwapBid() {
    if (_xdr_field_number(type_) == 21)
      return atomicSwapBid_;
    throw xdr::xdr_wrong_union("LedgerKey: atomicSwapBid accessed when not selected");
  }
  const _atomicSwapBid_t &atomicSwapBid() const {
    if (_xdr_field_number(type_) == 21)
      return atomicSwapBid_;
    throw xdr::xdr_wrong_union("LedgerKey: atomicSwapBid accessed when not selected");
  }
  _accountRole_t &accountRole() {
    if (_xdr_field_number(type_) == 22)
      return accountRole_;
    throw xdr::xdr_wrong_union("LedgerKey: accountRole accessed when not selected");
  }
  const _accountRole_t &accountRole() const {
    if (_xdr_field_number(type_) == 22)
      return accountRole_;
    throw xdr::xdr_wrong_union("LedgerKey: accountRole accessed when not selected");
  }
  _accountRule_t &accountRule() {
    if (_xdr_field_number(type_) == 23)
      return accountRule_;
    throw xdr::xdr_wrong_union("LedgerKey: accountRule accessed when not selected");
  }
  const _accountRule_t &accountRule() const {
    if (_xdr_field_number(type_) == 23)
      return accountRule_;
    throw xdr::xdr_wrong_union("LedgerKey: accountRule accessed when not selected");
  }
  _signerRole_t &signerRole() {
    if (_xdr_field_number(type_) == 24)
      return signerRole_;
    throw xdr::xdr_wrong_union("LedgerKey: signerRole accessed when not selected");
  }
  const _signerRole_t &signerRole() const {
    if (_xdr_field_number(type_) == 24)
      return signerRole_;
    throw xdr::xdr_wrong_union("LedgerKey: signerRole accessed when not selected");
  }
  _signerRule_t &signerRule() {
    if (_xdr_field_number(type_) == 25)
      return signerRule_;
    throw xdr::xdr_wrong_union("LedgerKey: signerRule accessed when not selected");
  }
  const _signerRule_t &signerRule() const {
    if (_xdr_field_number(type_) == 25)
      return signerRule_;
    throw xdr::xdr_wrong_union("LedgerKey: signerRule accessed when not selected");
  }
  _stamp_t &stamp() {
    if (_xdr_field_number(type_) == 26)
      return stamp_;
    throw xdr::xdr_wrong_union("LedgerKey: stamp accessed when not selected");
  }
  const _stamp_t &stamp() const {
    if (_xdr_field_number(type_) == 26)
      return stamp_;
    throw xdr::xdr_wrong_union("LedgerKey: stamp accessed when not selected");
  }
  _license_t &license() {
    if (_xdr_field_number(type_) == 27)
      return license_;
    throw xdr::xdr_wrong_union("LedgerKey: license accessed when not selected");
  }
  const _license_t &license() const {
    if (_xdr_field_number(type_) == 27)
      return license_;
    throw xdr::xdr_wrong_union("LedgerKey: license accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerKey::_account_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_account_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_account_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_account_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_account_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_account_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_account_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_account_t,
                              decltype(::stellar::LedgerKey::_account_t::accountID),
                              &::stellar::LedgerKey::_account_t::accountID>,
                    field_ptr<::stellar::LedgerKey::_account_t,
                              decltype(::stellar::LedgerKey::_account_t::ext),
                              &::stellar::LedgerKey::_account_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_account_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_account_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_signer_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_signer_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_signer_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_signer_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_signer_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_signer_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_signer_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_signer_t,
                              decltype(::stellar::LedgerKey::_signer_t::pubKey),
                              &::stellar::LedgerKey::_signer_t::pubKey>,
                    field_ptr<::stellar::LedgerKey::_signer_t,
                              decltype(::stellar::LedgerKey::_signer_t::accountID),
                              &::stellar::LedgerKey::_signer_t::accountID>,
                    field_ptr<::stellar::LedgerKey::_signer_t,
                              decltype(::stellar::LedgerKey::_signer_t::ext),
                              &::stellar::LedgerKey::_signer_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_signer_t &obj) {
    archive(ar, obj.pubKey, "pubKey");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_signer_t &obj) {
    archive(ar, obj.pubKey, "pubKey");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_feeState_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_feeState_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_feeState_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_feeState_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_feeState_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_feeState_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_feeState_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_feeState_t,
                              decltype(::stellar::LedgerKey::_feeState_t::hash),
                              &::stellar::LedgerKey::_feeState_t::hash>,
                    field_ptr<::stellar::LedgerKey::_feeState_t,
                              decltype(::stellar::LedgerKey::_feeState_t::lowerBound),
                              &::stellar::LedgerKey::_feeState_t::lowerBound>,
                    field_ptr<::stellar::LedgerKey::_feeState_t,
                              decltype(::stellar::LedgerKey::_feeState_t::upperBound),
                              &::stellar::LedgerKey::_feeState_t::upperBound>,
                    field_ptr<::stellar::LedgerKey::_feeState_t,
                              decltype(::stellar::LedgerKey::_feeState_t::ext),
                              &::stellar::LedgerKey::_feeState_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_feeState_t &obj) {
    archive(ar, obj.hash, "hash");
    archive(ar, obj.lowerBound, "lowerBound");
    archive(ar, obj.upperBound, "upperBound");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_feeState_t &obj) {
    archive(ar, obj.hash, "hash");
    archive(ar, obj.lowerBound, "lowerBound");
    archive(ar, obj.upperBound, "upperBound");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_balance_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_balance_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_balance_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_balance_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_balance_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_balance_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_balance_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_balance_t,
                              decltype(::stellar::LedgerKey::_balance_t::balanceID),
                              &::stellar::LedgerKey::_balance_t::balanceID>,
                    field_ptr<::stellar::LedgerKey::_balance_t,
                              decltype(::stellar::LedgerKey::_balance_t::ext),
                              &::stellar::LedgerKey::_balance_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_balance_t &obj) {
    archive(ar, obj.balanceID, "balanceID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_balance_t &obj) {
    archive(ar, obj.balanceID, "balanceID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_asset_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_asset_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_asset_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_asset_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_asset_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_asset_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_asset_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_asset_t,
                              decltype(::stellar::LedgerKey::_asset_t::code),
                              &::stellar::LedgerKey::_asset_t::code>,
                    field_ptr<::stellar::LedgerKey::_asset_t,
                              decltype(::stellar::LedgerKey::_asset_t::ext),
                              &::stellar::LedgerKey::_asset_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_asset_t &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_asset_t &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_reference_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_reference_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_reference_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_reference_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_reference_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_reference_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_reference_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_reference_t,
                              decltype(::stellar::LedgerKey::_reference_t::sender),
                              &::stellar::LedgerKey::_reference_t::sender>,
                    field_ptr<::stellar::LedgerKey::_reference_t,
                              decltype(::stellar::LedgerKey::_reference_t::reference),
                              &::stellar::LedgerKey::_reference_t::reference>,
                    field_ptr<::stellar::LedgerKey::_reference_t,
                              decltype(::stellar::LedgerKey::_reference_t::ext),
                              &::stellar::LedgerKey::_reference_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_reference_t &obj) {
    archive(ar, obj.sender, "sender");
    archive(ar, obj.reference, "reference");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_reference_t &obj) {
    archive(ar, obj.sender, "sender");
    archive(ar, obj.reference, "reference");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_stats_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_stats_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_stats_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_stats_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_stats_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_stats_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_stats_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_stats_t,
                              decltype(::stellar::LedgerKey::_stats_t::accountID),
                              &::stellar::LedgerKey::_stats_t::accountID>,
                    field_ptr<::stellar::LedgerKey::_stats_t,
                              decltype(::stellar::LedgerKey::_stats_t::ext),
                              &::stellar::LedgerKey::_stats_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_stats_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_stats_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_accountLimits_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_accountLimits_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_accountLimits_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_accountLimits_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_accountLimits_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_accountLimits_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_accountLimits_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_accountLimits_t,
                              decltype(::stellar::LedgerKey::_accountLimits_t::accountID),
                              &::stellar::LedgerKey::_accountLimits_t::accountID>,
                    field_ptr<::stellar::LedgerKey::_accountLimits_t,
                              decltype(::stellar::LedgerKey::_accountLimits_t::ext),
                              &::stellar::LedgerKey::_accountLimits_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_accountLimits_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_accountLimits_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_assetPair_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_assetPair_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_assetPair_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_assetPair_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_assetPair_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_assetPair_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_assetPair_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_assetPair_t,
                              decltype(::stellar::LedgerKey::_assetPair_t::base),
                              &::stellar::LedgerKey::_assetPair_t::base>,
                    field_ptr<::stellar::LedgerKey::_assetPair_t,
                              decltype(::stellar::LedgerKey::_assetPair_t::quote),
                              &::stellar::LedgerKey::_assetPair_t::quote>,
                    field_ptr<::stellar::LedgerKey::_assetPair_t,
                              decltype(::stellar::LedgerKey::_assetPair_t::ext),
                              &::stellar::LedgerKey::_assetPair_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_assetPair_t &obj) {
    archive(ar, obj.base, "base");
    archive(ar, obj.quote, "quote");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_assetPair_t &obj) {
    archive(ar, obj.base, "base");
    archive(ar, obj.quote, "quote");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_offer_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_offer_t,
                              decltype(::stellar::LedgerKey::_offer_t::offerID),
                              &::stellar::LedgerKey::_offer_t::offerID>,
                    field_ptr<::stellar::LedgerKey::_offer_t,
                              decltype(::stellar::LedgerKey::_offer_t::ownerID),
                              &::stellar::LedgerKey::_offer_t::ownerID>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_offer_t &obj) {
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.ownerID, "ownerID");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_offer_t &obj) {
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.ownerID, "ownerID");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_reviewableRequest_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_reviewableRequest_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_reviewableRequest_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_reviewableRequest_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_reviewableRequest_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_reviewableRequest_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_reviewableRequest_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_reviewableRequest_t,
                              decltype(::stellar::LedgerKey::_reviewableRequest_t::requestID),
                              &::stellar::LedgerKey::_reviewableRequest_t::requestID>,
                    field_ptr<::stellar::LedgerKey::_reviewableRequest_t,
                              decltype(::stellar::LedgerKey::_reviewableRequest_t::ext),
                              &::stellar::LedgerKey::_reviewableRequest_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_reviewableRequest_t &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_reviewableRequest_t &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_externalSystemAccountID_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_externalSystemAccountID_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_externalSystemAccountID_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_externalSystemAccountID_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_externalSystemAccountID_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_externalSystemAccountID_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_externalSystemAccountID_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_externalSystemAccountID_t,
                              decltype(::stellar::LedgerKey::_externalSystemAccountID_t::accountID),
                              &::stellar::LedgerKey::_externalSystemAccountID_t::accountID>,
                    field_ptr<::stellar::LedgerKey::_externalSystemAccountID_t,
                              decltype(::stellar::LedgerKey::_externalSystemAccountID_t::externalSystemType),
                              &::stellar::LedgerKey::_externalSystemAccountID_t::externalSystemType>,
                    field_ptr<::stellar::LedgerKey::_externalSystemAccountID_t,
                              decltype(::stellar::LedgerKey::_externalSystemAccountID_t::ext),
                              &::stellar::LedgerKey::_externalSystemAccountID_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_externalSystemAccountID_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.externalSystemType, "externalSystemType");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_externalSystemAccountID_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.externalSystemType, "externalSystemType");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_sale_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_sale_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_sale_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_sale_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_sale_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_sale_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_sale_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_sale_t,
                              decltype(::stellar::LedgerKey::_sale_t::saleID),
                              &::stellar::LedgerKey::_sale_t::saleID>,
                    field_ptr<::stellar::LedgerKey::_sale_t,
                              decltype(::stellar::LedgerKey::_sale_t::ext),
                              &::stellar::LedgerKey::_sale_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_sale_t &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_sale_t &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_keyValue_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_keyValue_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_keyValue_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_keyValue_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_keyValue_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_keyValue_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_keyValue_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_keyValue_t,
                              decltype(::stellar::LedgerKey::_keyValue_t::key),
                              &::stellar::LedgerKey::_keyValue_t::key>,
                    field_ptr<::stellar::LedgerKey::_keyValue_t,
                              decltype(::stellar::LedgerKey::_keyValue_t::ext),
                              &::stellar::LedgerKey::_keyValue_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_keyValue_t &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_keyValue_t &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_accountKYC_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_accountKYC_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_accountKYC_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_accountKYC_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_accountKYC_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_accountKYC_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_accountKYC_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_accountKYC_t,
                              decltype(::stellar::LedgerKey::_accountKYC_t::accountID),
                              &::stellar::LedgerKey::_accountKYC_t::accountID>,
                    field_ptr<::stellar::LedgerKey::_accountKYC_t,
                              decltype(::stellar::LedgerKey::_accountKYC_t::ext),
                              &::stellar::LedgerKey::_accountKYC_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_accountKYC_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_accountKYC_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t,
                              decltype(::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::poolEntryID),
                              &::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::poolEntryID>,
                    field_ptr<::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t,
                              decltype(::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::ext),
                              &::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t &obj) {
    archive(ar, obj.poolEntryID, "poolEntryID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_externalSystemAccountIDPoolEntry_t &obj) {
    archive(ar, obj.poolEntryID, "poolEntryID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_limitsV2_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_limitsV2_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_limitsV2_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_limitsV2_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_limitsV2_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_limitsV2_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_limitsV2_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_limitsV2_t,
                              decltype(::stellar::LedgerKey::_limitsV2_t::id),
                              &::stellar::LedgerKey::_limitsV2_t::id>,
                    field_ptr<::stellar::LedgerKey::_limitsV2_t,
                              decltype(::stellar::LedgerKey::_limitsV2_t::ext),
                              &::stellar::LedgerKey::_limitsV2_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_limitsV2_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_limitsV2_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_statisticsV2_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_statisticsV2_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_statisticsV2_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_statisticsV2_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_statisticsV2_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_statisticsV2_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_statisticsV2_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_statisticsV2_t,
                              decltype(::stellar::LedgerKey::_statisticsV2_t::id),
                              &::stellar::LedgerKey::_statisticsV2_t::id>,
                    field_ptr<::stellar::LedgerKey::_statisticsV2_t,
                              decltype(::stellar::LedgerKey::_statisticsV2_t::ext),
                              &::stellar::LedgerKey::_statisticsV2_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_statisticsV2_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_statisticsV2_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_pendingStatistics_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_pendingStatistics_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_pendingStatistics_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_pendingStatistics_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_pendingStatistics_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_pendingStatistics_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_pendingStatistics_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_pendingStatistics_t,
                              decltype(::stellar::LedgerKey::_pendingStatistics_t::statisticsID),
                              &::stellar::LedgerKey::_pendingStatistics_t::statisticsID>,
                    field_ptr<::stellar::LedgerKey::_pendingStatistics_t,
                              decltype(::stellar::LedgerKey::_pendingStatistics_t::requestID),
                              &::stellar::LedgerKey::_pendingStatistics_t::requestID>,
                    field_ptr<::stellar::LedgerKey::_pendingStatistics_t,
                              decltype(::stellar::LedgerKey::_pendingStatistics_t::ext),
                              &::stellar::LedgerKey::_pendingStatistics_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_pendingStatistics_t &obj) {
    archive(ar, obj.statisticsID, "statisticsID");
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_pendingStatistics_t &obj) {
    archive(ar, obj.statisticsID, "statisticsID");
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_contract_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_contract_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_contract_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_contract_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_contract_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_contract_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_contract_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_contract_t,
                              decltype(::stellar::LedgerKey::_contract_t::contractID),
                              &::stellar::LedgerKey::_contract_t::contractID>,
                    field_ptr<::stellar::LedgerKey::_contract_t,
                              decltype(::stellar::LedgerKey::_contract_t::ext),
                              &::stellar::LedgerKey::_contract_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_contract_t &obj) {
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_contract_t &obj) {
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_atomicSwapBid_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_atomicSwapBid_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_atomicSwapBid_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_atomicSwapBid_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_atomicSwapBid_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_atomicSwapBid_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_atomicSwapBid_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_atomicSwapBid_t,
                              decltype(::stellar::LedgerKey::_atomicSwapBid_t::bidID),
                              &::stellar::LedgerKey::_atomicSwapBid_t::bidID>,
                    field_ptr<::stellar::LedgerKey::_atomicSwapBid_t,
                              decltype(::stellar::LedgerKey::_atomicSwapBid_t::ext),
                              &::stellar::LedgerKey::_atomicSwapBid_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_atomicSwapBid_t &obj) {
    archive(ar, obj.bidID, "bidID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_atomicSwapBid_t &obj) {
    archive(ar, obj.bidID, "bidID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_accountRole_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_accountRole_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_accountRole_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_accountRole_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_accountRole_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_accountRole_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_accountRole_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_accountRole_t,
                              decltype(::stellar::LedgerKey::_accountRole_t::id),
                              &::stellar::LedgerKey::_accountRole_t::id>,
                    field_ptr<::stellar::LedgerKey::_accountRole_t,
                              decltype(::stellar::LedgerKey::_accountRole_t::ext),
                              &::stellar::LedgerKey::_accountRole_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_accountRole_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_accountRole_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_accountRule_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_accountRule_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_accountRule_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_accountRule_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_accountRule_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_accountRule_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_accountRule_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_accountRule_t,
                              decltype(::stellar::LedgerKey::_accountRule_t::id),
                              &::stellar::LedgerKey::_accountRule_t::id>,
                    field_ptr<::stellar::LedgerKey::_accountRule_t,
                              decltype(::stellar::LedgerKey::_accountRule_t::ext),
                              &::stellar::LedgerKey::_accountRule_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_accountRule_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_accountRule_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_signerRole_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_signerRole_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_signerRole_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_signerRole_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_signerRole_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_signerRole_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_signerRole_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_signerRole_t,
                              decltype(::stellar::LedgerKey::_signerRole_t::id),
                              &::stellar::LedgerKey::_signerRole_t::id>,
                    field_ptr<::stellar::LedgerKey::_signerRole_t,
                              decltype(::stellar::LedgerKey::_signerRole_t::ext),
                              &::stellar::LedgerKey::_signerRole_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_signerRole_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_signerRole_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_signerRule_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_signerRule_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_signerRule_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_signerRule_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_signerRule_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_signerRule_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_signerRule_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_signerRule_t,
                              decltype(::stellar::LedgerKey::_signerRule_t::id),
                              &::stellar::LedgerKey::_signerRule_t::id>,
                    field_ptr<::stellar::LedgerKey::_signerRule_t,
                              decltype(::stellar::LedgerKey::_signerRule_t::ext),
                              &::stellar::LedgerKey::_signerRule_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_signerRule_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_signerRule_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_stamp_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_stamp_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_stamp_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_stamp_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_stamp_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_stamp_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_stamp_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_stamp_t,
                              decltype(::stellar::LedgerKey::_stamp_t::ledgerHash),
                              &::stellar::LedgerKey::_stamp_t::ledgerHash>,
                    field_ptr<::stellar::LedgerKey::_stamp_t,
                              decltype(::stellar::LedgerKey::_stamp_t::licenseHash),
                              &::stellar::LedgerKey::_stamp_t::licenseHash>,
                    field_ptr<::stellar::LedgerKey::_stamp_t,
                              decltype(::stellar::LedgerKey::_stamp_t::ext),
                              &::stellar::LedgerKey::_stamp_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_stamp_t &obj) {
    archive(ar, obj.ledgerHash, "ledgerHash");
    archive(ar, obj.licenseHash, "licenseHash");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_stamp_t &obj) {
    archive(ar, obj.ledgerHash, "ledgerHash");
    archive(ar, obj.licenseHash, "licenseHash");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_license_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey::_license_t::_ext_t;
  using case_type = ::stellar::LedgerKey::_license_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey::_license_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_license_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_license_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey::_license_t>
  : xdr_struct_base<field_ptr<::stellar::LedgerKey::_license_t,
                              decltype(::stellar::LedgerKey::_license_t::licenseHash),
                              &::stellar::LedgerKey::_license_t::licenseHash>,
                    field_ptr<::stellar::LedgerKey::_license_t,
                              decltype(::stellar::LedgerKey::_license_t::ext),
                              &::stellar::LedgerKey::_license_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey::_license_t &obj) {
    archive(ar, obj.licenseHash, "licenseHash");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey::_license_t &obj) {
    archive(ar, obj.licenseHash, "licenseHash");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerKey> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerKey;
  using case_type = ::stellar::LedgerKey::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "account";
    case 2:
      return "signer";
    case 3:
      return "feeState";
    case 4:
      return "balance";
    case 5:
      return "asset";
    case 6:
      return "reference";
    case 7:
      return "stats";
    case 8:
      return "accountLimits";
    case 9:
      return "assetPair";
    case 10:
      return "offer";
    case 11:
      return "reviewableRequest";
    case 12:
      return "externalSystemAccountID";
    case 13:
      return "sale";
    case 14:
      return "keyValue";
    case 15:
      return "accountKYC";
    case 16:
      return "externalSystemAccountIDPoolEntry";
    case 17:
      return "limitsV2";
    case 18:
      return "statisticsV2";
    case 19:
      return "pendingStatistics";
    case 20:
      return "contract";
    case 21:
      return "atomicSwapBid";
    case 22:
      return "accountRole";
    case 23:
      return "accountRule";
    case 24:
      return "signerRole";
    case 25:
      return "signerRule";
    case 26:
      return "stamp";
    case 27:
      return "license";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerKey &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in LedgerKey");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerKey &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in LedgerKey");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerKey &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class BucketEntryType : std::int32_t {
  LIVEENTRY = 0,
  DEADENTRY = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BucketEntryType>
  : xdr_integral_base<::stellar::BucketEntryType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct BucketEntry {
  using _xdr_case_type = xdr::xdr_traits<BucketEntryType>::case_type;
private:
  _xdr_case_type type_;
  union {
    LedgerEntry liveEntry_;
    LedgerKey deadEntry_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<BucketEntryType> &_xdr_case_values() {
    static const std::vector<BucketEntryType> _xdr_disc_vec {
      BucketEntryType::LIVEENTRY,
      BucketEntryType::DEADENTRY
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit BucketEntry(BucketEntryType which = BucketEntryType{}) : type_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  BucketEntry(const BucketEntry &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  BucketEntry(BucketEntry &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~BucketEntry() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  BucketEntry &operator=(const BucketEntry &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~BucketEntry();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  BucketEntry &operator=(BucketEntry &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~BucketEntry();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BucketEntry> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::BucketEntry;
  using case_type = ::stellar::BucketEntry::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "liveEntry";
    case 2:
      return "deadEntry";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::BucketEntry &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in BucketEntry");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::BucketEntry &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in BucketEntry");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::BucketEntry &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionSet {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionSet>
  : xdr_struct_base<field_ptr<::stellar::TransactionSet,
                              decltype(::stellar::TransactionSet::previousLedgerHash),
                              &::stellar::TransactionSet::previousLedgerHash>,
                    field_ptr<::stellar::TransactionSet,
                              decltype(::stellar::TransactionSet::txs),
                              &::stellar::TransactionSet::txs>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionSet &obj) {
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.txs, "txs");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionSet &obj) {
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.txs, "txs");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionResultPair {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResultPair>
  : xdr_struct_base<field_ptr<::stellar::TransactionResultPair,
                              decltype(::stellar::TransactionResultPair::transactionHash),
                              &::stellar::TransactionResultPair::transactionHash>,
                    field_ptr<::stellar::TransactionResultPair,
                              decltype(::stellar::TransactionResultPair::result),
                              &::stellar::TransactionResultPair::result>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResultPair &obj) {
    archive(ar, obj.transactionHash, "transactionHash");
    archive(ar, obj.result, "result");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResultPair &obj) {
    archive(ar, obj.transactionHash, "transactionHash");
    archive(ar, obj.result, "result");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionResultSet {
  xdr::xvector<TransactionResultPair> results{};

  TransactionResultSet() = default;
  template<typename _results_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<TransactionResultPair>, _results_T>::value
                         >::type>
  explicit TransactionResultSet(_results_T &&_results)
    : results(std::forward<_results_T>(_results)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResultSet>
  : xdr_struct_base<field_ptr<::stellar::TransactionResultSet,
                              decltype(::stellar::TransactionResultSet::results),
                              &::stellar::TransactionResultSet::results>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResultSet &obj) {
    archive(ar, obj.results, "results");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResultSet &obj) {
    archive(ar, obj.results, "results");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionHistoryEntry {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionHistoryEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionHistoryEntry::_ext_t;
  using case_type = ::stellar::TransactionHistoryEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionHistoryEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionHistoryEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionHistoryEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionHistoryEntry>
  : xdr_struct_base<field_ptr<::stellar::TransactionHistoryEntry,
                              decltype(::stellar::TransactionHistoryEntry::ledgerSeq),
                              &::stellar::TransactionHistoryEntry::ledgerSeq>,
                    field_ptr<::stellar::TransactionHistoryEntry,
                              decltype(::stellar::TransactionHistoryEntry::txSet),
                              &::stellar::TransactionHistoryEntry::txSet>,
                    field_ptr<::stellar::TransactionHistoryEntry,
                              decltype(::stellar::TransactionHistoryEntry::ext),
                              &::stellar::TransactionHistoryEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionHistoryEntry &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionHistoryEntry &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionHistoryResultEntry {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionHistoryResultEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionHistoryResultEntry::_ext_t;
  using case_type = ::stellar::TransactionHistoryResultEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionHistoryResultEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionHistoryResultEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionHistoryResultEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionHistoryResultEntry>
  : xdr_struct_base<field_ptr<::stellar::TransactionHistoryResultEntry,
                              decltype(::stellar::TransactionHistoryResultEntry::ledgerSeq),
                              &::stellar::TransactionHistoryResultEntry::ledgerSeq>,
                    field_ptr<::stellar::TransactionHistoryResultEntry,
                              decltype(::stellar::TransactionHistoryResultEntry::txResultSet),
                              &::stellar::TransactionHistoryResultEntry::txResultSet>,
                    field_ptr<::stellar::TransactionHistoryResultEntry,
                              decltype(::stellar::TransactionHistoryResultEntry::ext),
                              &::stellar::TransactionHistoryResultEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionHistoryResultEntry &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.txResultSet, "txResultSet");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionHistoryResultEntry &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.txResultSet, "txResultSet");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerHeaderHistoryEntry {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerHeaderHistoryEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerHeaderHistoryEntry::_ext_t;
  using case_type = ::stellar::LedgerHeaderHistoryEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerHeaderHistoryEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeaderHistoryEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeaderHistoryEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerHeaderHistoryEntry>
  : xdr_struct_base<field_ptr<::stellar::LedgerHeaderHistoryEntry,
                              decltype(::stellar::LedgerHeaderHistoryEntry::hash),
                              &::stellar::LedgerHeaderHistoryEntry::hash>,
                    field_ptr<::stellar::LedgerHeaderHistoryEntry,
                              decltype(::stellar::LedgerHeaderHistoryEntry::header),
                              &::stellar::LedgerHeaderHistoryEntry::header>,
                    field_ptr<::stellar::LedgerHeaderHistoryEntry,
                              decltype(::stellar::LedgerHeaderHistoryEntry::ext),
                              &::stellar::LedgerHeaderHistoryEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeaderHistoryEntry &obj) {
    archive(ar, obj.hash, "hash");
    archive(ar, obj.header, "header");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeaderHistoryEntry &obj) {
    archive(ar, obj.hash, "hash");
    archive(ar, obj.header, "header");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerSCPMessages {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerSCPMessages>
  : xdr_struct_base<field_ptr<::stellar::LedgerSCPMessages,
                              decltype(::stellar::LedgerSCPMessages::ledgerSeq),
                              &::stellar::LedgerSCPMessages::ledgerSeq>,
                    field_ptr<::stellar::LedgerSCPMessages,
                              decltype(::stellar::LedgerSCPMessages::messages),
                              &::stellar::LedgerSCPMessages::messages>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerSCPMessages &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.messages, "messages");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerSCPMessages &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.messages, "messages");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCPHistoryEntryV0 {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCPHistoryEntryV0>
  : xdr_struct_base<field_ptr<::stellar::SCPHistoryEntryV0,
                              decltype(::stellar::SCPHistoryEntryV0::quorumSets),
                              &::stellar::SCPHistoryEntryV0::quorumSets>,
                    field_ptr<::stellar::SCPHistoryEntryV0,
                              decltype(::stellar::SCPHistoryEntryV0::ledgerMessages),
                              &::stellar::SCPHistoryEntryV0::ledgerMessages>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCPHistoryEntryV0 &obj) {
    archive(ar, obj.quorumSets, "quorumSets");
    archive(ar, obj.ledgerMessages, "ledgerMessages");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCPHistoryEntryV0 &obj) {
    archive(ar, obj.quorumSets, "quorumSets");
    archive(ar, obj.ledgerMessages, "ledgerMessages");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCPHistoryEntry {
  using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
private:
  _xdr_case_type v_;
  union {
    SCPHistoryEntryV0 v0_;
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
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit SCPHistoryEntry(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  SCPHistoryEntry(const SCPHistoryEntry &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  SCPHistoryEntry(SCPHistoryEntry &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~SCPHistoryEntry() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  SCPHistoryEntry &operator=(const SCPHistoryEntry &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~SCPHistoryEntry();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  SCPHistoryEntry &operator=(SCPHistoryEntry &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~SCPHistoryEntry();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCPHistoryEntry> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCPHistoryEntry;
  using case_type = ::stellar::SCPHistoryEntry::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "v0";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SCPHistoryEntry &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in SCPHistoryEntry");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCPHistoryEntry &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in SCPHistoryEntry");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCPHistoryEntry &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct LedgerEntryChange {
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
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerEntryChangeType> &_xdr_case_values() {
    static const std::vector<LedgerEntryChangeType> _xdr_disc_vec {
      LedgerEntryChangeType::CREATED,
      LedgerEntryChangeType::UPDATED,
      LedgerEntryChangeType::REMOVED,
      LedgerEntryChangeType::STATE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit LedgerEntryChange(LedgerEntryChangeType which = LedgerEntryChangeType{}) : type_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  LedgerEntryChange(const LedgerEntryChange &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  LedgerEntryChange(LedgerEntryChange &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~LedgerEntryChange() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  LedgerEntryChange &operator=(const LedgerEntryChange &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~LedgerEntryChange();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  LedgerEntryChange &operator=(LedgerEntryChange &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~LedgerEntryChange();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerEntryChange> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerEntryChange;
  using case_type = ::stellar::LedgerEntryChange::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "created";
    case 2:
      return "updated";
    case 3:
      return "removed";
    case 4:
      return "state";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerEntryChange &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in LedgerEntryChange");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerEntryChange &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in LedgerEntryChange");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerEntryChange &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

using LedgerEntryChanges = xdr::xvector<LedgerEntryChange>;

struct OperationMeta {
  LedgerEntryChanges changes{};

  OperationMeta() = default;
  template<typename _changes_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerEntryChanges, _changes_T>::value
                         >::type>
  explicit OperationMeta(_changes_T &&_changes)
    : changes(std::forward<_changes_T>(_changes)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationMeta>
  : xdr_struct_base<field_ptr<::stellar::OperationMeta,
                              decltype(::stellar::OperationMeta::changes),
                              &::stellar::OperationMeta::changes>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::OperationMeta &obj) {
    archive(ar, obj.changes, "changes");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::OperationMeta &obj) {
    archive(ar, obj.changes, "changes");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionMeta {
  using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
private:
  _xdr_case_type v_;
  union {
    xdr::xvector<OperationMeta> operations_;
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
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit TransactionMeta(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  TransactionMeta(const TransactionMeta &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  TransactionMeta(TransactionMeta &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~TransactionMeta() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  TransactionMeta &operator=(const TransactionMeta &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~TransactionMeta();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  TransactionMeta &operator=(TransactionMeta &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~TransactionMeta();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionMeta> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionMeta;
  using case_type = ::stellar::TransactionMeta::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "operations";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionMeta &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in TransactionMeta");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionMeta &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in TransactionMeta");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionMeta &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_H_INCLUDED__
