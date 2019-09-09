// -*- C++ -*-
// Automatically generated from ledger-entries-key-value.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_KEY_VALUE_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_KEY_VALUE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

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
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct KeyValueEntryValue : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<KeyValueEntryType>::case_type;
private:
  _xdr_case_type type_;
  union {
    uint32 ui32Value_;
    xdr::xstring<> stringValue_;
    uint64 ui64Value_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<KeyValueEntryType> &_xdr_case_values() {
    static const std::vector<KeyValueEntryType> _xdr_disc_vec {
      KeyValueEntryType::UINT32,
      KeyValueEntryType::STRING,
      KeyValueEntryType::UINT64
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
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
      type_ = which;switch (type_)
{
      case (int32_t)KeyValueEntryType::UINT32:
new(&ui32Value_) uint32{};
break;
      case (int32_t)KeyValueEntryType::STRING:
new(&stringValue_) xdr::xstring<>{};
break;
      case (int32_t)KeyValueEntryType::UINT64:
new(&ui64Value_) uint64{};
break;
}

    }
    else
      type_ = which;
  }
  explicit KeyValueEntryValue(KeyValueEntryType which = KeyValueEntryType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)KeyValueEntryType::UINT32:
new(&ui32Value_) uint32{};
break;
    case (int32_t)KeyValueEntryType::STRING:
new(&stringValue_) xdr::xstring<>{};
break;
    case (int32_t)KeyValueEntryType::UINT64:
new(&ui64Value_) uint64{};
break;
}

  }
  KeyValueEntryValue(const KeyValueEntryValue &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)KeyValueEntryType::UINT32:
new(&ui32Value_) uint32(source.ui32Value_);
break;
    case (int32_t)KeyValueEntryType::STRING:
new(&stringValue_) xdr::xstring<>(source.stringValue_);
break;
    case (int32_t)KeyValueEntryType::UINT64:
new(&ui64Value_) uint64(source.ui64Value_);
break;
}

  }
  KeyValueEntryValue(KeyValueEntryValue &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)KeyValueEntryType::UINT32:
new(&ui32Value_) uint32(std::move(source.ui32Value_));
break;
    case (int32_t)KeyValueEntryType::STRING:
new(&stringValue_) xdr::xstring<>(std::move(source.stringValue_));
break;
    case (int32_t)KeyValueEntryType::UINT64:
new(&ui64Value_) uint64(std::move(source.ui64Value_));
break;
}

  }
  ~KeyValueEntryValue() {
switch (type_)
{
  case (int32_t)KeyValueEntryType::UINT32:
ui32Value_.~uint32();
break;
  case (int32_t)KeyValueEntryType::STRING:
stringValue_.~xstring<>();
break;
  case (int32_t)KeyValueEntryType::UINT64:
ui64Value_.~uint64();
break;
}
}

  KeyValueEntryValue &operator=(const KeyValueEntryValue &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)KeyValueEntryType::UINT32:
ui32Value_ = source.ui32Value_;
break;
    case (int32_t)KeyValueEntryType::STRING:
stringValue_ = source.stringValue_;
break;
    case (int32_t)KeyValueEntryType::UINT64:
ui64Value_ = source.ui64Value_;
break;
}
}
else {this->~KeyValueEntryValue();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)KeyValueEntryType::UINT32:
new(&ui32Value_) uint32(source.ui32Value_);
break;
    case (int32_t)KeyValueEntryType::STRING:
new(&stringValue_) xdr::xstring<>(source.stringValue_);
break;
    case (int32_t)KeyValueEntryType::UINT64:
new(&ui64Value_) uint64(source.ui64Value_);
break;
}
}
    return *this;
  }
  KeyValueEntryValue &operator=(KeyValueEntryValue &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)KeyValueEntryType::UINT32:
ui32Value_ = std::move(source.ui32Value_);
break;
    case (int32_t)KeyValueEntryType::STRING:
stringValue_ = std::move(source.stringValue_);
break;
    case (int32_t)KeyValueEntryType::UINT64:
ui64Value_ = std::move(source.ui64Value_);
break;
}
}
else {this->~KeyValueEntryValue();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)KeyValueEntryType::UINT32:
new(&ui32Value_) uint32(std::move(source.ui32Value_));
break;
    case (int32_t)KeyValueEntryType::STRING:
new(&stringValue_) xdr::xstring<>(std::move(source.stringValue_));
break;
    case (int32_t)KeyValueEntryType::UINT64:
new(&ui64Value_) uint64(std::move(source.ui64Value_));
break;
}
}
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

struct KeyValueEntry  : xdr::xdr_abstract {
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

#endif // !__XDR_LEDGER_ENTRIES_KEY_VALUE_H_INCLUDED__
