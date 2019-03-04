// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-key-value.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_KEY_VALUE_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_KEY_VALUE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

enum class KeyValueEntryType : std::int32_t {
  UINT32 = 1,
  STRING = 2,
  UINT64 = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::KeyValueEntryType>
  : xdr_integral_base<::stellar::KeyValueEntryType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::KeyValueEntryType val) {
    switch (val) {
    case ::stellar::KeyValueEntryType::UINT32:
      return "UINT32";
    case ::stellar::KeyValueEntryType::STRING:
      return "STRING";
    case ::stellar::KeyValueEntryType::UINT64:
      return "UINT64";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::KeyValueEntryType::UINT32,
      (int32_t)::stellar::KeyValueEntryType::STRING,
      (int32_t)::stellar::KeyValueEntryType::UINT64
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct KeyValueEntryValue {
  using _xdr_case_type = xdr::xdr_traits<KeyValueEntryType>::case_type;
private:
  _xdr_case_type type_;
  union {
    uint32 ui32Value_;
    xdr::xstring<> stringValue_;
    uint64 ui64Value_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<KeyValueEntryType> &_xdr_case_values() {
    static const std::vector<KeyValueEntryType> _xdr_disc_vec {
      KeyValueEntryType::UINT32,
      KeyValueEntryType::STRING,
      KeyValueEntryType::UINT64
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)KeyValueEntryType::UINT32 ? 1
      : which == (int32_t)KeyValueEntryType::STRING ? 2
      : which == (int32_t)KeyValueEntryType::UINT64 ? 3
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)KeyValueEntryType::UINT32:
      _f(&KeyValueEntryValue::ui32Value_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)KeyValueEntryType::STRING:
      _f(&KeyValueEntryValue::stringValue_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)KeyValueEntryType::UINT64:
      _f(&KeyValueEntryValue::ui64Value_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in KeyValueEntryValue");
    if (fnum != _xdr_field_number(type_)) {
      this->~KeyValueEntryValue();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit KeyValueEntryValue(KeyValueEntryType which = KeyValueEntryType{}) : type_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  KeyValueEntryValue(const KeyValueEntryValue &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  KeyValueEntryValue(KeyValueEntryValue &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~KeyValueEntryValue() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  KeyValueEntryValue &operator=(const KeyValueEntryValue &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~KeyValueEntryValue();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  KeyValueEntryValue &operator=(KeyValueEntryValue &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~KeyValueEntryValue();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  KeyValueEntryType type() const { return KeyValueEntryType(type_); }
  KeyValueEntryValue &type(KeyValueEntryType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  uint32 &ui32Value() {
    if (_xdr_field_number(type_) == 1)
      return ui32Value_;
    throw xdr::xdr_wrong_union("KeyValueEntryValue: ui32Value accessed when not selected");
  }
  const uint32 &ui32Value() const {
    if (_xdr_field_number(type_) == 1)
      return ui32Value_;
    throw xdr::xdr_wrong_union("KeyValueEntryValue: ui32Value accessed when not selected");
  }
  xdr::xstring<> &stringValue() {
    if (_xdr_field_number(type_) == 2)
      return stringValue_;
    throw xdr::xdr_wrong_union("KeyValueEntryValue: stringValue accessed when not selected");
  }
  const xdr::xstring<> &stringValue() const {
    if (_xdr_field_number(type_) == 2)
      return stringValue_;
    throw xdr::xdr_wrong_union("KeyValueEntryValue: stringValue accessed when not selected");
  }
  uint64 &ui64Value() {
    if (_xdr_field_number(type_) == 3)
      return ui64Value_;
    throw xdr::xdr_wrong_union("KeyValueEntryValue: ui64Value accessed when not selected");
  }
  const uint64 &ui64Value() const {
    if (_xdr_field_number(type_) == 3)
      return ui64Value_;
    throw xdr::xdr_wrong_union("KeyValueEntryValue: ui64Value accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::KeyValueEntryValue> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::KeyValueEntryValue;
  using case_type = ::stellar::KeyValueEntryValue::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "ui32Value";
    case 2:
      return "stringValue";
    case 3:
      return "ui64Value";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::KeyValueEntryValue &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in KeyValueEntryValue");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::KeyValueEntryValue &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in KeyValueEntryValue");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::KeyValueEntryValue &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct KeyValueEntry {
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
  KeyValueEntryValue value{};
  _ext_t ext{};

  KeyValueEntry() = default;
  template<typename _key_T,
           typename _value_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<longstring, _key_T>::value
                          && std::is_constructible<KeyValueEntryValue, _value_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit KeyValueEntry(_key_T &&_key,
                         _value_T &&_value,
                         _ext_T &&_ext)
    : key(std::forward<_key_T>(_key)),
      value(std::forward<_value_T>(_value)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::KeyValueEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::KeyValueEntry::_ext_t;
  using case_type = ::stellar::KeyValueEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::KeyValueEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::KeyValueEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::KeyValueEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::KeyValueEntry>
  : xdr_struct_base<field_ptr<::stellar::KeyValueEntry,
                              decltype(::stellar::KeyValueEntry::key),
                              &::stellar::KeyValueEntry::key>,
                    field_ptr<::stellar::KeyValueEntry,
                              decltype(::stellar::KeyValueEntry::value),
                              &::stellar::KeyValueEntry::value>,
                    field_ptr<::stellar::KeyValueEntry,
                              decltype(::stellar::KeyValueEntry::ext),
                              &::stellar::KeyValueEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::KeyValueEntry &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.value, "value");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::KeyValueEntry &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.value, "value");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_KEY_VALUE_H_INCLUDED__
