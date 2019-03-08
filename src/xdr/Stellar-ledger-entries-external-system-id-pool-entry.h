// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-external-system-id-pool-entry.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_EXTERNAL_SYSTEM_ID_POOL_ENTRY_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_EXTERNAL_SYSTEM_ID_POOL_ENTRY_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct ExternalSystemAccountIDPoolEntry {
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
  int32 externalSystemType{};
  longstring data{};
  xdr::pointer<AccountID> accountID{};
  uint64 expiresAt{};
  uint64 bindedAt{};
  uint64 parent{};
  bool isDeleted{};
  _ext_t ext{};

  ExternalSystemAccountIDPoolEntry() = default;
  template<typename _poolEntryID_T,
           typename _externalSystemType_T,
           typename _data_T,
           typename _accountID_T,
           typename _expiresAt_T,
           typename _bindedAt_T,
           typename _parent_T,
           typename _isDeleted_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _poolEntryID_T>::value
                          && std::is_constructible<int32, _externalSystemType_T>::value
                          && std::is_constructible<longstring, _data_T>::value
                          && std::is_constructible<xdr::pointer<AccountID>, _accountID_T>::value
                          && std::is_constructible<uint64, _expiresAt_T>::value
                          && std::is_constructible<uint64, _bindedAt_T>::value
                          && std::is_constructible<uint64, _parent_T>::value
                          && std::is_constructible<bool, _isDeleted_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ExternalSystemAccountIDPoolEntry(_poolEntryID_T &&_poolEntryID,
                                            _externalSystemType_T &&_externalSystemType,
                                            _data_T &&_data,
                                            _accountID_T &&_accountID,
                                            _expiresAt_T &&_expiresAt,
                                            _bindedAt_T &&_bindedAt,
                                            _parent_T &&_parent,
                                            _isDeleted_T &&_isDeleted,
                                            _ext_T &&_ext)
    : poolEntryID(std::forward<_poolEntryID_T>(_poolEntryID)),
      externalSystemType(std::forward<_externalSystemType_T>(_externalSystemType)),
      data(std::forward<_data_T>(_data)),
      accountID(std::forward<_accountID_T>(_accountID)),
      expiresAt(std::forward<_expiresAt_T>(_expiresAt)),
      bindedAt(std::forward<_bindedAt_T>(_bindedAt)),
      parent(std::forward<_parent_T>(_parent)),
      isDeleted(std::forward<_isDeleted_T>(_isDeleted)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ExternalSystemAccountIDPoolEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ExternalSystemAccountIDPoolEntry::_ext_t;
  using case_type = ::stellar::ExternalSystemAccountIDPoolEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ExternalSystemAccountIDPoolEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ExternalSystemAccountIDPoolEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ExternalSystemAccountIDPoolEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ExternalSystemAccountIDPoolEntry>
  : xdr_struct_base<field_ptr<::stellar::ExternalSystemAccountIDPoolEntry,
                              decltype(::stellar::ExternalSystemAccountIDPoolEntry::poolEntryID),
                              &::stellar::ExternalSystemAccountIDPoolEntry::poolEntryID>,
                    field_ptr<::stellar::ExternalSystemAccountIDPoolEntry,
                              decltype(::stellar::ExternalSystemAccountIDPoolEntry::externalSystemType),
                              &::stellar::ExternalSystemAccountIDPoolEntry::externalSystemType>,
                    field_ptr<::stellar::ExternalSystemAccountIDPoolEntry,
                              decltype(::stellar::ExternalSystemAccountIDPoolEntry::data),
                              &::stellar::ExternalSystemAccountIDPoolEntry::data>,
                    field_ptr<::stellar::ExternalSystemAccountIDPoolEntry,
                              decltype(::stellar::ExternalSystemAccountIDPoolEntry::accountID),
                              &::stellar::ExternalSystemAccountIDPoolEntry::accountID>,
                    field_ptr<::stellar::ExternalSystemAccountIDPoolEntry,
                              decltype(::stellar::ExternalSystemAccountIDPoolEntry::expiresAt),
                              &::stellar::ExternalSystemAccountIDPoolEntry::expiresAt>,
                    field_ptr<::stellar::ExternalSystemAccountIDPoolEntry,
                              decltype(::stellar::ExternalSystemAccountIDPoolEntry::bindedAt),
                              &::stellar::ExternalSystemAccountIDPoolEntry::bindedAt>,
                    field_ptr<::stellar::ExternalSystemAccountIDPoolEntry,
                              decltype(::stellar::ExternalSystemAccountIDPoolEntry::parent),
                              &::stellar::ExternalSystemAccountIDPoolEntry::parent>,
                    field_ptr<::stellar::ExternalSystemAccountIDPoolEntry,
                              decltype(::stellar::ExternalSystemAccountIDPoolEntry::isDeleted),
                              &::stellar::ExternalSystemAccountIDPoolEntry::isDeleted>,
                    field_ptr<::stellar::ExternalSystemAccountIDPoolEntry,
                              decltype(::stellar::ExternalSystemAccountIDPoolEntry::ext),
                              &::stellar::ExternalSystemAccountIDPoolEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ExternalSystemAccountIDPoolEntry &obj) {
    archive(ar, obj.poolEntryID, "poolEntryID");
    archive(ar, obj.externalSystemType, "externalSystemType");
    archive(ar, obj.data, "data");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.expiresAt, "expiresAt");
    archive(ar, obj.bindedAt, "bindedAt");
    archive(ar, obj.parent, "parent");
    archive(ar, obj.isDeleted, "isDeleted");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ExternalSystemAccountIDPoolEntry &obj) {
    archive(ar, obj.poolEntryID, "poolEntryID");
    archive(ar, obj.externalSystemType, "externalSystemType");
    archive(ar, obj.data, "data");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.expiresAt, "expiresAt");
    archive(ar, obj.bindedAt, "bindedAt");
    archive(ar, obj.parent, "parent");
    archive(ar, obj.isDeleted, "isDeleted");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_EXTERNAL_SYSTEM_ID_POOL_ENTRY_H_INCLUDED__
