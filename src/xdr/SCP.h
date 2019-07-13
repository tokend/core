// -*- C++ -*-
// Automatically generated from SCP.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_SCP_H_INCLUDED__
#define __XDR_SCP_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

using Value = xdr::opaque_vec<>;

struct SCPBallot  : xdr::xdr_abstract {
  uint32 counter{};
  Value value{};

  SCPBallot() = default;
  template<typename _counter_T,
           typename _value_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _counter_T>::value
                          && std::is_constructible<Value, _value_T>::value
                         >::type>
  explicit SCPBallot(_counter_T &&_counter,
                     _value_T &&_value)
    : counter(std::forward<_counter_T>(_counter)),
      value(std::forward<_value_T>(_value)) {}
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

enum class SCPStatementType : std::int32_t {
  PREPARE = 0,
  CONFIRM = 1,
  EXTERNALIZE = 2,
  NOMINATE = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCPStatementType>
  : xdr_integral_base<::stellar::SCPStatementType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCPStatementType val) {
    switch (val) {
    case ::stellar::SCPStatementType::PREPARE:
      return "PREPARE";
    case ::stellar::SCPStatementType::CONFIRM:
      return "CONFIRM";
    case ::stellar::SCPStatementType::EXTERNALIZE:
      return "EXTERNALIZE";
    case ::stellar::SCPStatementType::NOMINATE:
      return "NOMINATE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::SCPStatementType::PREPARE,
      (int32_t)::stellar::SCPStatementType::CONFIRM,
      (int32_t)::stellar::SCPStatementType::EXTERNALIZE,
      (int32_t)::stellar::SCPStatementType::NOMINATE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SCPNomination  : xdr::xdr_abstract {
  Hash quorumSetHash{};
  xdr::xvector<Value> votes{};
  xdr::xvector<Value> accepted{};

  SCPNomination() = default;
  template<typename _quorumSetHash_T,
           typename _votes_T,
           typename _accepted_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _quorumSetHash_T>::value
                          && std::is_constructible<xdr::xvector<Value>, _votes_T>::value
                          && std::is_constructible<xdr::xvector<Value>, _accepted_T>::value
                         >::type>
  explicit SCPNomination(_quorumSetHash_T &&_quorumSetHash,
                         _votes_T &&_votes,
                         _accepted_T &&_accepted)
    : quorumSetHash(std::forward<_quorumSetHash_T>(_quorumSetHash)),
      votes(std::forward<_votes_T>(_votes)),
      accepted(std::forward<_accepted_T>(_accepted)) {}
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

struct SCPStatement  : xdr::xdr_abstract {
  struct _pledges_t : xdr::xdr_abstract {
    struct _prepare_t  : xdr::xdr_abstract {
      Hash quorumSetHash{};
      SCPBallot ballot{};
      xdr::pointer<SCPBallot> prepared{};
      xdr::pointer<SCPBallot> preparedPrime{};
      uint32 nC{};
      uint32 nH{};

      _prepare_t() = default;
      template<typename _quorumSetHash_T,
               typename _ballot_T,
               typename _prepared_T,
               typename _preparedPrime_T,
               typename _nC_T,
               typename _nH_T,
               typename = typename
               std::enable_if<std::is_constructible<Hash, _quorumSetHash_T>::value
                              && std::is_constructible<SCPBallot, _ballot_T>::value
                              && std::is_constructible<xdr::pointer<SCPBallot>, _prepared_T>::value
                              && std::is_constructible<xdr::pointer<SCPBallot>, _preparedPrime_T>::value
                              && std::is_constructible<uint32, _nC_T>::value
                              && std::is_constructible<uint32, _nH_T>::value
                             >::type>
      explicit _prepare_t(_quorumSetHash_T &&_quorumSetHash,
                          _ballot_T &&_ballot,
                          _prepared_T &&_prepared,
                          _preparedPrime_T &&_preparedPrime,
                          _nC_T &&_nC,
                          _nH_T &&_nH)
        : quorumSetHash(std::forward<_quorumSetHash_T>(_quorumSetHash)),
          ballot(std::forward<_ballot_T>(_ballot)),
          prepared(std::forward<_prepared_T>(_prepared)),
          preparedPrime(std::forward<_preparedPrime_T>(_preparedPrime)),
          nC(std::forward<_nC_T>(_nC)),
          nH(std::forward<_nH_T>(_nH)) {}
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
    struct _confirm_t  : xdr::xdr_abstract {
      SCPBallot ballot{};
      uint32 nPrepared{};
      uint32 nCommit{};
      uint32 nH{};
      Hash quorumSetHash{};

      _confirm_t() = default;
      template<typename _ballot_T,
               typename _nPrepared_T,
               typename _nCommit_T,
               typename _nH_T,
               typename _quorumSetHash_T,
               typename = typename
               std::enable_if<std::is_constructible<SCPBallot, _ballot_T>::value
                              && std::is_constructible<uint32, _nPrepared_T>::value
                              && std::is_constructible<uint32, _nCommit_T>::value
                              && std::is_constructible<uint32, _nH_T>::value
                              && std::is_constructible<Hash, _quorumSetHash_T>::value
                             >::type>
      explicit _confirm_t(_ballot_T &&_ballot,
                          _nPrepared_T &&_nPrepared,
                          _nCommit_T &&_nCommit,
                          _nH_T &&_nH,
                          _quorumSetHash_T &&_quorumSetHash)
        : ballot(std::forward<_ballot_T>(_ballot)),
          nPrepared(std::forward<_nPrepared_T>(_nPrepared)),
          nCommit(std::forward<_nCommit_T>(_nCommit)),
          nH(std::forward<_nH_T>(_nH)),
          quorumSetHash(std::forward<_quorumSetHash_T>(_quorumSetHash)) {}
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
    struct _externalize_t  : xdr::xdr_abstract {
      SCPBallot commit{};
      uint32 nH{};
      Hash commitQuorumSetHash{};

      _externalize_t() = default;
      template<typename _commit_T,
               typename _nH_T,
               typename _commitQuorumSetHash_T,
               typename = typename
               std::enable_if<std::is_constructible<SCPBallot, _commit_T>::value
                              && std::is_constructible<uint32, _nH_T>::value
                              && std::is_constructible<Hash, _commitQuorumSetHash_T>::value
                             >::type>
      explicit _externalize_t(_commit_T &&_commit,
                              _nH_T &&_nH,
                              _commitQuorumSetHash_T &&_commitQuorumSetHash)
        : commit(std::forward<_commit_T>(_commit)),
          nH(std::forward<_nH_T>(_nH)),
          commitQuorumSetHash(std::forward<_commitQuorumSetHash_T>(_commitQuorumSetHash)) {}
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

    using _xdr_case_type = xdr::xdr_traits<SCPStatementType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      _prepare_t prepare_;
      _confirm_t confirm_;
      _externalize_t externalize_;
      SCPNomination nominate_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<SCPStatementType> &_xdr_case_values() {
      static const std::vector<SCPStatementType> _xdr_disc_vec {
        SCPStatementType::PREPARE,
        SCPStatementType::CONFIRM,
        SCPStatementType::EXTERNALIZE,
        SCPStatementType::NOMINATE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)SCPStatementType::PREPARE ? 1
        : which == (int32_t)SCPStatementType::CONFIRM ? 2
        : which == (int32_t)SCPStatementType::EXTERNALIZE ? 3
        : which == (int32_t)SCPStatementType::NOMINATE ? 4
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)SCPStatementType::PREPARE:
        _f(&_pledges_t::prepare_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)SCPStatementType::CONFIRM:
        _f(&_pledges_t::confirm_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)SCPStatementType::EXTERNALIZE:
        _f(&_pledges_t::externalize_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)SCPStatementType::NOMINATE:
        _f(&_pledges_t::nominate_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _pledges_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_pledges_t();
        type_ = which;switch (type_)
{
        case (int32_t)SCPStatementType::PREPARE:
new(&prepare_) _prepare_t{};
break;
        case (int32_t)SCPStatementType::CONFIRM:
new(&confirm_) _confirm_t{};
break;
        case (int32_t)SCPStatementType::EXTERNALIZE:
new(&externalize_) _externalize_t{};
break;
        case (int32_t)SCPStatementType::NOMINATE:
new(&nominate_) SCPNomination{};
break;
}

      }
      else
        type_ = which;
    }
    explicit _pledges_t(SCPStatementType which = SCPStatementType{}) : type_((int32_t)which) {
      switch (type_)
{
      case (int32_t)SCPStatementType::PREPARE:
new(&prepare_) _prepare_t{};
break;
      case (int32_t)SCPStatementType::CONFIRM:
new(&confirm_) _confirm_t{};
break;
      case (int32_t)SCPStatementType::EXTERNALIZE:
new(&externalize_) _externalize_t{};
break;
      case (int32_t)SCPStatementType::NOMINATE:
new(&nominate_) SCPNomination{};
break;
}

    }
    _pledges_t(const _pledges_t &source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)SCPStatementType::PREPARE:
new(&prepare_) _prepare_t(source.prepare_);
break;
      case (int32_t)SCPStatementType::CONFIRM:
new(&confirm_) _confirm_t(source.confirm_);
break;
      case (int32_t)SCPStatementType::EXTERNALIZE:
new(&externalize_) _externalize_t(source.externalize_);
break;
      case (int32_t)SCPStatementType::NOMINATE:
new(&nominate_) SCPNomination(source.nominate_);
break;
}

    }
    _pledges_t(_pledges_t &&source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)SCPStatementType::PREPARE:
new(&prepare_) _prepare_t(std::move(source.prepare_));
break;
      case (int32_t)SCPStatementType::CONFIRM:
new(&confirm_) _confirm_t(std::move(source.confirm_));
break;
      case (int32_t)SCPStatementType::EXTERNALIZE:
new(&externalize_) _externalize_t(std::move(source.externalize_));
break;
      case (int32_t)SCPStatementType::NOMINATE:
new(&nominate_) SCPNomination(std::move(source.nominate_));
break;
}

    }
    ~_pledges_t() {
switch (type_)
{
    case (int32_t)SCPStatementType::PREPARE:
prepare_.~_prepare_t();
break;
    case (int32_t)SCPStatementType::CONFIRM:
confirm_.~_confirm_t();
break;
    case (int32_t)SCPStatementType::EXTERNALIZE:
externalize_.~_externalize_t();
break;
    case (int32_t)SCPStatementType::NOMINATE:
nominate_.~SCPNomination();
break;
}
}

    _pledges_t &operator=(const _pledges_t &source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)SCPStatementType::PREPARE:
prepare_ = source.prepare_;
break;
      case (int32_t)SCPStatementType::CONFIRM:
confirm_ = source.confirm_;
break;
      case (int32_t)SCPStatementType::EXTERNALIZE:
externalize_ = source.externalize_;
break;
      case (int32_t)SCPStatementType::NOMINATE:
nominate_ = source.nominate_;
break;
}
}
else {this->~_pledges_t();
      type_ = source.type_;
switch (type_)
{
      case (int32_t)SCPStatementType::PREPARE:
new(&prepare_) _prepare_t(source.prepare_);
break;
      case (int32_t)SCPStatementType::CONFIRM:
new(&confirm_) _confirm_t(source.confirm_);
break;
      case (int32_t)SCPStatementType::EXTERNALIZE:
new(&externalize_) _externalize_t(source.externalize_);
break;
      case (int32_t)SCPStatementType::NOMINATE:
new(&nominate_) SCPNomination(source.nominate_);
break;
}
}
      return *this;
    }
    _pledges_t &operator=(_pledges_t &&source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)SCPStatementType::PREPARE:
prepare_ = std::move(source.prepare_);
break;
      case (int32_t)SCPStatementType::CONFIRM:
confirm_ = std::move(source.confirm_);
break;
      case (int32_t)SCPStatementType::EXTERNALIZE:
externalize_ = std::move(source.externalize_);
break;
      case (int32_t)SCPStatementType::NOMINATE:
nominate_ = std::move(source.nominate_);
break;
}
}
else {this->~_pledges_t();
      type_ = std::move(source.type_);
switch (type_)
{
      case (int32_t)SCPStatementType::PREPARE:
new(&prepare_) _prepare_t(std::move(source.prepare_));
break;
      case (int32_t)SCPStatementType::CONFIRM:
new(&confirm_) _confirm_t(std::move(source.confirm_));
break;
      case (int32_t)SCPStatementType::EXTERNALIZE:
new(&externalize_) _externalize_t(std::move(source.externalize_));
break;
      case (int32_t)SCPStatementType::NOMINATE:
new(&nominate_) SCPNomination(std::move(source.nominate_));
break;
}
}
      return *this;
    }

    SCPStatementType type() const { return SCPStatementType(type_); }
    _pledges_t &type(SCPStatementType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    _prepare_t &prepare() {
      if (_xdr_field_number(type_) == 1)
        return prepare_;
      throw xdr::xdr_wrong_union("_pledges_t: prepare accessed when not selected");
    }
    const _prepare_t &prepare() const {
      if (_xdr_field_number(type_) == 1)
        return prepare_;
      throw xdr::xdr_wrong_union("_pledges_t: prepare accessed when not selected");
    }
    _confirm_t &confirm() {
      if (_xdr_field_number(type_) == 2)
        return confirm_;
      throw xdr::xdr_wrong_union("_pledges_t: confirm accessed when not selected");
    }
    const _confirm_t &confirm() const {
      if (_xdr_field_number(type_) == 2)
        return confirm_;
      throw xdr::xdr_wrong_union("_pledges_t: confirm accessed when not selected");
    }
    _externalize_t &externalize() {
      if (_xdr_field_number(type_) == 3)
        return externalize_;
      throw xdr::xdr_wrong_union("_pledges_t: externalize accessed when not selected");
    }
    const _externalize_t &externalize() const {
      if (_xdr_field_number(type_) == 3)
        return externalize_;
      throw xdr::xdr_wrong_union("_pledges_t: externalize accessed when not selected");
    }
    SCPNomination &nominate() {
      if (_xdr_field_number(type_) == 4)
        return nominate_;
      throw xdr::xdr_wrong_union("_pledges_t: nominate accessed when not selected");
    }
    const SCPNomination &nominate() const {
      if (_xdr_field_number(type_) == 4)
        return nominate_;
      throw xdr::xdr_wrong_union("_pledges_t: nominate accessed when not selected");
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

  NodeID nodeID{};
  uint64 slotIndex{};
  _pledges_t pledges{};

  SCPStatement() = default;
  template<typename _nodeID_T,
           typename _slotIndex_T,
           typename _pledges_T,
           typename = typename
           std::enable_if<std::is_constructible<NodeID, _nodeID_T>::value
                          && std::is_constructible<uint64, _slotIndex_T>::value
                          && std::is_constructible<_pledges_t, _pledges_T>::value
                         >::type>
  explicit SCPStatement(_nodeID_T &&_nodeID,
                        _slotIndex_T &&_slotIndex,
                        _pledges_T &&_pledges)
    : nodeID(std::forward<_nodeID_T>(_nodeID)),
      slotIndex(std::forward<_slotIndex_T>(_slotIndex)),
      pledges(std::forward<_pledges_T>(_pledges)) {}
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

struct SCPEnvelope  : xdr::xdr_abstract {
  SCPStatement statement{};
  Signature signature{};

  SCPEnvelope() = default;
  template<typename _statement_T,
           typename _signature_T,
           typename = typename
           std::enable_if<std::is_constructible<SCPStatement, _statement_T>::value
                          && std::is_constructible<Signature, _signature_T>::value
                         >::type>
  explicit SCPEnvelope(_statement_T &&_statement,
                       _signature_T &&_signature)
    : statement(std::forward<_statement_T>(_statement)),
      signature(std::forward<_signature_T>(_signature)) {}
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

struct SCPQuorumSet  : xdr::xdr_abstract {
  uint32 threshold{};
  xdr::xvector<PublicKey> validators{};
  xdr::xvector<SCPQuorumSet> innerSets{};

  SCPQuorumSet() = default;
  template<typename _threshold_T,
           typename _validators_T,
           typename _innerSets_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _threshold_T>::value
                          && std::is_constructible<xdr::xvector<PublicKey>, _validators_T>::value
                          && std::is_constructible<xdr::xvector<SCPQuorumSet>, _innerSets_T>::value
                         >::type>
  explicit SCPQuorumSet(_threshold_T &&_threshold,
                        _validators_T &&_validators,
                        _innerSets_T &&_innerSets)
    : threshold(std::forward<_threshold_T>(_threshold)),
      validators(std::forward<_validators_T>(_validators)),
      innerSets(std::forward<_innerSets_T>(_innerSets)) {}
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

#endif // !__XDR_SCP_H_INCLUDED__
