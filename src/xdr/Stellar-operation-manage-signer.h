// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-signer.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_SIGNER_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_SIGNER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

enum class ManageSignerAction : std::int32_t {
  CREATE = 0,
  UPDATE = 1,
  REMOVE = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerAction>
  : xdr_integral_base<::stellar::ManageSignerAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageSignerAction val) {
    switch (val) {
    case ::stellar::ManageSignerAction::CREATE:
      return "CREATE";
    case ::stellar::ManageSignerAction::UPDATE:
      return "UPDATE";
    case ::stellar::ManageSignerAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageSignerAction::CREATE,
      (int32_t)::stellar::ManageSignerAction::UPDATE,
      (int32_t)::stellar::ManageSignerAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct UpdateSignerData {
  PublicKey publicKey{};
  uint64 roleID{};
  uint32 weight{};
  uint32 identity{};
  longstring details{};
  EmptyExt ext{};

  UpdateSignerData() = default;
  template<typename _publicKey_T,
           typename _roleID_T,
           typename _weight_T,
           typename _identity_T,
           typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<PublicKey, _publicKey_T>::value
                          && std::is_constructible<uint64, _roleID_T>::value
                          && std::is_constructible<uint32, _weight_T>::value
                          && std::is_constructible<uint32, _identity_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit UpdateSignerData(_publicKey_T &&_publicKey,
                            _roleID_T &&_roleID,
                            _weight_T &&_weight,
                            _identity_T &&_identity,
                            _details_T &&_details,
                            _ext_T &&_ext)
    : publicKey(std::forward<_publicKey_T>(_publicKey)),
      roleID(std::forward<_roleID_T>(_roleID)),
      weight(std::forward<_weight_T>(_weight)),
      identity(std::forward<_identity_T>(_identity)),
      details(std::forward<_details_T>(_details)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UpdateSignerData>
  : xdr_struct_base<field_ptr<::stellar::UpdateSignerData,
                              decltype(::stellar::UpdateSignerData::publicKey),
                              &::stellar::UpdateSignerData::publicKey>,
                    field_ptr<::stellar::UpdateSignerData,
                              decltype(::stellar::UpdateSignerData::roleID),
                              &::stellar::UpdateSignerData::roleID>,
                    field_ptr<::stellar::UpdateSignerData,
                              decltype(::stellar::UpdateSignerData::weight),
                              &::stellar::UpdateSignerData::weight>,
                    field_ptr<::stellar::UpdateSignerData,
                              decltype(::stellar::UpdateSignerData::identity),
                              &::stellar::UpdateSignerData::identity>,
                    field_ptr<::stellar::UpdateSignerData,
                              decltype(::stellar::UpdateSignerData::details),
                              &::stellar::UpdateSignerData::details>,
                    field_ptr<::stellar::UpdateSignerData,
                              decltype(::stellar::UpdateSignerData::ext),
                              &::stellar::UpdateSignerData::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UpdateSignerData &obj) {
    archive(ar, obj.publicKey, "publicKey");
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.weight, "weight");
    archive(ar, obj.identity, "identity");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UpdateSignerData &obj) {
    archive(ar, obj.publicKey, "publicKey");
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.weight, "weight");
    archive(ar, obj.identity, "identity");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct RemoveSignerData {
  PublicKey publicKey{};
  EmptyExt ext{};

  RemoveSignerData() = default;
  template<typename _publicKey_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<PublicKey, _publicKey_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit RemoveSignerData(_publicKey_T &&_publicKey,
                            _ext_T &&_ext)
    : publicKey(std::forward<_publicKey_T>(_publicKey)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RemoveSignerData>
  : xdr_struct_base<field_ptr<::stellar::RemoveSignerData,
                              decltype(::stellar::RemoveSignerData::publicKey),
                              &::stellar::RemoveSignerData::publicKey>,
                    field_ptr<::stellar::RemoveSignerData,
                              decltype(::stellar::RemoveSignerData::ext),
                              &::stellar::RemoveSignerData::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RemoveSignerData &obj) {
    archive(ar, obj.publicKey, "publicKey");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RemoveSignerData &obj) {
    archive(ar, obj.publicKey, "publicKey");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageSignerOp {
  struct _data_t {
    using _xdr_case_type = xdr::xdr_traits<ManageSignerAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      UpdateSignerData createData_;
      UpdateSignerData updateData_;
      RemoveSignerData removeData_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageSignerAction> &_xdr_case_values() {
      static const std::vector<ManageSignerAction> _xdr_disc_vec {
        ManageSignerAction::CREATE,
        ManageSignerAction::UPDATE,
        ManageSignerAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageSignerAction::CREATE ? 1
        : which == (int32_t)ManageSignerAction::UPDATE ? 2
        : which == (int32_t)ManageSignerAction::REMOVE ? 3
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageSignerAction::CREATE:
        _f(&_data_t::createData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageSignerAction::UPDATE:
        _f(&_data_t::updateData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageSignerAction::REMOVE:
        _f(&_data_t::removeData_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _data_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_data_t();
        action_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      else
        action_ = which;
    }
    explicit _data_t(ManageSignerAction which = ManageSignerAction{}) : action_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
    }
    _data_t(const _data_t &source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
    }
    _data_t(_data_t &&source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                        std::move(source));
    }
    ~_data_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
    _data_t &operator=(const _data_t &source) {
      if (_xdr_field_number(action_)
          == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
      else {
        this->~_data_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
      }
      action_ = source.action_;
      return *this;
    }
    _data_t &operator=(_data_t &&source) {
      if (_xdr_field_number(action_)
           == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                          std::move(source));
      else {
        this->~_data_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                          std::move(source));
      }
      action_ = source.action_;
      return *this;
    }

    ManageSignerAction action() const { return ManageSignerAction(action_); }
    _data_t &action(ManageSignerAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    UpdateSignerData &createData() {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    const UpdateSignerData &createData() const {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    UpdateSignerData &updateData() {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    const UpdateSignerData &updateData() const {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    RemoveSignerData &removeData() {
      if (_xdr_field_number(action_) == 3)
        return removeData_;
      throw xdr::xdr_wrong_union("_data_t: removeData accessed when not selected");
    }
    const RemoveSignerData &removeData() const {
      if (_xdr_field_number(action_) == 3)
        return removeData_;
      throw xdr::xdr_wrong_union("_data_t: removeData accessed when not selected");
    }
  };

  _data_t data{};
  EmptyExt ext{};

  ManageSignerOp() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit ManageSignerOp(_data_T &&_data,
                          _ext_T &&_ext)
    : data(std::forward<_data_T>(_data)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerOp::_data_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerOp::_data_t;
  using case_type = ::stellar::ManageSignerOp::_data_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createData";
    case 2:
      return "updateData";
    case 3:
      return "removeData";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSignerOp::_data_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _data_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerOp::_data_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _data_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerOp::_data_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageSignerOp>
  : xdr_struct_base<field_ptr<::stellar::ManageSignerOp,
                              decltype(::stellar::ManageSignerOp::data),
                              &::stellar::ManageSignerOp::data>,
                    field_ptr<::stellar::ManageSignerOp,
                              decltype(::stellar::ManageSignerOp::ext),
                              &::stellar::ManageSignerOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerOp &obj) {
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerOp &obj) {
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class ManageSignerResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_DETAILS = -1,
  ALREADY_EXISTS = -2,
  NO_SUCH_ROLE = -3,
  INVALID_WEIGHT = -4,
  NOT_FOUND = -5,
  NUMBER_OF_ADMINS_EXCEEDS_LICENSE = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerResultCode>
  : xdr_integral_base<::stellar::ManageSignerResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageSignerResultCode val) {
    switch (val) {
    case ::stellar::ManageSignerResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageSignerResultCode::INVALID_DETAILS:
      return "INVALID_DETAILS";
    case ::stellar::ManageSignerResultCode::ALREADY_EXISTS:
      return "ALREADY_EXISTS";
    case ::stellar::ManageSignerResultCode::NO_SUCH_ROLE:
      return "NO_SUCH_ROLE";
    case ::stellar::ManageSignerResultCode::INVALID_WEIGHT:
      return "INVALID_WEIGHT";
    case ::stellar::ManageSignerResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageSignerResultCode::NUMBER_OF_ADMINS_EXCEEDS_LICENSE:
      return "NUMBER_OF_ADMINS_EXCEEDS_LICENSE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageSignerResultCode::SUCCESS,
      (int32_t)::stellar::ManageSignerResultCode::INVALID_DETAILS,
      (int32_t)::stellar::ManageSignerResultCode::ALREADY_EXISTS,
      (int32_t)::stellar::ManageSignerResultCode::NO_SUCH_ROLE,
      (int32_t)::stellar::ManageSignerResultCode::INVALID_WEIGHT,
      (int32_t)::stellar::ManageSignerResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageSignerResultCode::NUMBER_OF_ADMINS_EXCEEDS_LICENSE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageSignerResult {
  using _xdr_case_type = xdr::xdr_traits<ManageSignerResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    EmptyExt ext_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageSignerResultCode> &_xdr_case_values() {
    static const std::vector<ManageSignerResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageSignerResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageSignerResultCode::SUCCESS:
      _f(&ManageSignerResult::ext_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageSignerResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageSignerResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageSignerResult(ManageSignerResultCode which = ManageSignerResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageSignerResult(const ManageSignerResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageSignerResult(ManageSignerResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageSignerResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageSignerResult &operator=(const ManageSignerResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageSignerResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageSignerResult &operator=(ManageSignerResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageSignerResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageSignerResultCode code() const { return ManageSignerResultCode(code_); }
  ManageSignerResult &code(ManageSignerResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  EmptyExt &ext() {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("ManageSignerResult: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("ManageSignerResult: ext accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerResult;
  using case_type = ::stellar::ManageSignerResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "ext";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSignerResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageSignerResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageSignerResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_OPERATION_MANAGE_SIGNER_H_INCLUDED__
