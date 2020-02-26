// -*- C++ -*-
// Automatically generated from reviewable-request-manage-offer.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_REVIEWABLE_REQUEST_MANAGE_OFFER_H_INCLUDED__
#define __XDR_REVIEWABLE_REQUEST_MANAGE_OFFER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/operation-manage-offer.h"

namespace stellar {

struct ManageOfferRequest  : xdr::xdr_abstract {
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
      longstring creatorDetails_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION,
        LedgerVersion::MOVEMENT_REQUESTS_DETAILS
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : which == (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
        _f(&_ext_t::creatorDetails_, std::forward<_A>(_a)...);
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
        case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
new(&creatorDetails_) longstring{};
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
      case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
new(&creatorDetails_) longstring{};
break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
new(&creatorDetails_) longstring(source.creatorDetails_);
break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
new(&creatorDetails_) longstring(std::move(source.creatorDetails_));
break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
    case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
creatorDetails_.~longstring();
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
      case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
creatorDetails_ = source.creatorDetails_;
break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
new(&creatorDetails_) longstring(source.creatorDetails_);
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
      case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
creatorDetails_ = std::move(source.creatorDetails_);
break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
new(&creatorDetails_) longstring(std::move(source.creatorDetails_));
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

    longstring &creatorDetails() {
      if (_xdr_field_number(v_) == 1)
        return creatorDetails_;
      throw xdr::xdr_wrong_union("_ext_t: creatorDetails accessed when not selected");
    }
    const longstring &creatorDetails() const {
      if (_xdr_field_number(v_) == 1)
        return creatorDetails_;
      throw xdr::xdr_wrong_union("_ext_t: creatorDetails accessed when not selected");
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

  ManageOfferOp op{};
  _ext_t ext{};

  ManageOfferRequest() = default;
  template<typename _op_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ManageOfferOp, _op_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageOfferRequest(_op_T &&_op,
                              _ext_T &&_ext)
    : op(std::forward<_op_T>(_op)),
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

#endif // !__XDR_REVIEWABLE_REQUEST_MANAGE_OFFER_H_INCLUDED__
