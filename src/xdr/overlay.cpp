#include "overlay.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
Error::from_bytes(xdr::unmarshaler& u) 
{
bool okcode = u.from_bytes(code);
if (!okcode)
{
return false;
}
bool okmsg = u.from_bytes(msg);
if (!okmsg)
{
return false;
}
return true;
}
bool
Error::to_bytes(xdr::marshaler& m) const 
{
bool okcode = m.to_bytes(code);
if (!okcode)
{
return false;
}
bool okmsg = m.to_bytes(msg);
if (!okmsg)
{
return false;
}
return true;
}
void
Error::count_size(xdr::measurer& m) const 
{
m.count_size(code);
m.count_size(msg);
}
bool
Error::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<Error const&>(other_abstract);return true
&& (code== other.code)
&& (msg== other.msg)
;}
bool
Error::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Error const&>(other_abstract);
if (code < other.code) return true;
if (other.code < code) return false;
if (msg < other.msg) return true;
if (other.msg < msg) return false;
return false;
}bool
AuthCert::from_bytes(xdr::unmarshaler& u) 
{
bool okpubkey = u.from_bytes(pubkey);
if (!okpubkey)
{
return false;
}
bool okexpiration = u.from_bytes(expiration);
if (!okexpiration)
{
return false;
}
bool oksig = u.from_bytes(sig);
if (!oksig)
{
return false;
}
return true;
}
bool
AuthCert::to_bytes(xdr::marshaler& m) const 
{
bool okpubkey = m.to_bytes(pubkey);
if (!okpubkey)
{
return false;
}
bool okexpiration = m.to_bytes(expiration);
if (!okexpiration)
{
return false;
}
bool oksig = m.to_bytes(sig);
if (!oksig)
{
return false;
}
return true;
}
void
AuthCert::count_size(xdr::measurer& m) const 
{
m.count_size(pubkey);
m.count_size(expiration);
m.count_size(sig);
}
bool
AuthCert::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AuthCert const&>(other_abstract);return true
&& (pubkey== other.pubkey)
&& (expiration== other.expiration)
&& (sig== other.sig)
;}
bool
AuthCert::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AuthCert const&>(other_abstract);
if (pubkey < other.pubkey) return true;
if (other.pubkey < pubkey) return false;
if (expiration < other.expiration) return true;
if (other.expiration < expiration) return false;
if (sig < other.sig) return true;
if (other.sig < sig) return false;
return false;
}bool
Hello::from_bytes(xdr::unmarshaler& u) 
{
bool okledgerVersion = u.from_bytes(ledgerVersion);
if (!okledgerVersion)
{
return false;
}
bool okoverlayVersion = u.from_bytes(overlayVersion);
if (!okoverlayVersion)
{
return false;
}
bool okoverlayMinVersion = u.from_bytes(overlayMinVersion);
if (!okoverlayMinVersion)
{
return false;
}
bool oknetworkID = u.from_bytes(networkID);
if (!oknetworkID)
{
return false;
}
bool okversionStr = u.from_bytes(versionStr);
if (!okversionStr)
{
return false;
}
bool oklisteningPort = u.from_bytes(listeningPort);
if (!oklisteningPort)
{
return false;
}
bool okpeerID = u.from_bytes(peerID);
if (!okpeerID)
{
return false;
}
bool okcert = u.from_bytes(cert);
if (!okcert)
{
return false;
}
bool oknonce = u.from_bytes(nonce);
if (!oknonce)
{
return false;
}
return true;
}
bool
Hello::to_bytes(xdr::marshaler& m) const 
{
bool okledgerVersion = m.to_bytes(ledgerVersion);
if (!okledgerVersion)
{
return false;
}
bool okoverlayVersion = m.to_bytes(overlayVersion);
if (!okoverlayVersion)
{
return false;
}
bool okoverlayMinVersion = m.to_bytes(overlayMinVersion);
if (!okoverlayMinVersion)
{
return false;
}
bool oknetworkID = m.to_bytes(networkID);
if (!oknetworkID)
{
return false;
}
bool okversionStr = m.to_bytes(versionStr);
if (!okversionStr)
{
return false;
}
bool oklisteningPort = m.to_bytes(listeningPort);
if (!oklisteningPort)
{
return false;
}
bool okpeerID = m.to_bytes(peerID);
if (!okpeerID)
{
return false;
}
bool okcert = m.to_bytes(cert);
if (!okcert)
{
return false;
}
bool oknonce = m.to_bytes(nonce);
if (!oknonce)
{
return false;
}
return true;
}
void
Hello::count_size(xdr::measurer& m) const 
{
m.count_size(ledgerVersion);
m.count_size(overlayVersion);
m.count_size(overlayMinVersion);
m.count_size(networkID);
m.count_size(versionStr);
m.count_size(listeningPort);
m.count_size(peerID);
m.count_size(cert);
m.count_size(nonce);
}
bool
Hello::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<Hello const&>(other_abstract);return true
&& (ledgerVersion== other.ledgerVersion)
&& (overlayVersion== other.overlayVersion)
&& (overlayMinVersion== other.overlayMinVersion)
&& (networkID== other.networkID)
&& (versionStr== other.versionStr)
&& (listeningPort== other.listeningPort)
&& (peerID== other.peerID)
&& (cert== other.cert)
&& (nonce== other.nonce)
;}
bool
Hello::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Hello const&>(other_abstract);
if (ledgerVersion < other.ledgerVersion) return true;
if (other.ledgerVersion < ledgerVersion) return false;
if (overlayVersion < other.overlayVersion) return true;
if (other.overlayVersion < overlayVersion) return false;
if (overlayMinVersion < other.overlayMinVersion) return true;
if (other.overlayMinVersion < overlayMinVersion) return false;
if (networkID < other.networkID) return true;
if (other.networkID < networkID) return false;
if (versionStr < other.versionStr) return true;
if (other.versionStr < versionStr) return false;
if (listeningPort < other.listeningPort) return true;
if (other.listeningPort < listeningPort) return false;
if (peerID < other.peerID) return true;
if (other.peerID < peerID) return false;
if (cert < other.cert) return true;
if (other.cert < cert) return false;
if (nonce < other.nonce) return true;
if (other.nonce < nonce) return false;
return false;
}bool
Auth::from_bytes(xdr::unmarshaler& u) 
{
bool okunused = u.from_bytes(unused);
if (!okunused)
{
return false;
}
return true;
}
bool
Auth::to_bytes(xdr::marshaler& m) const 
{
bool okunused = m.to_bytes(unused);
if (!okunused)
{
return false;
}
return true;
}
void
Auth::count_size(xdr::measurer& m) const 
{
m.count_size(unused);
}
bool
Auth::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<Auth const&>(other_abstract);return true
&& (unused== other.unused)
;}
bool
Auth::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Auth const&>(other_abstract);
if (unused < other.unused) return true;
if (other.unused < unused) return false;
return false;
}bool
PeerAddress::_ip_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

    case (int32_t)IPAddrType::IPv4:
return u.from_bytes(ipv4_);
    case (int32_t)IPAddrType::IPv6:
return u.from_bytes(ipv6_);
}
return false;
}
bool
PeerAddress::_ip_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

    case (int32_t)IPAddrType::IPv4:
return m.to_bytes(ipv4_);
    case (int32_t)IPAddrType::IPv6:
return m.to_bytes(ipv6_);
}
return false;
}
void
PeerAddress::_ip_t::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

    case (int32_t)IPAddrType::IPv4:
return m.count_size(ipv4_);
    case (int32_t)IPAddrType::IPv6:
return m.count_size(ipv6_);
}
}
bool
PeerAddress::_ip_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ip_t const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
    case (int32_t)IPAddrType::IPv4:
return ipv4_ == other.ipv4_;
    case (int32_t)IPAddrType::IPv6:
return ipv6_ == other.ipv6_;
}
return false;
}
bool
PeerAddress::_ip_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ip_t const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
    case (int32_t)IPAddrType::IPv4:
return ipv4_ < other.ipv4_;
    case (int32_t)IPAddrType::IPv6:
return ipv6_ < other.ipv6_;
}
return false;
}
bool
PeerAddress::from_bytes(xdr::unmarshaler& u) 
{
bool okip = u.from_bytes(ip);
if (!okip)
{
return false;
}
bool okport = u.from_bytes(port);
if (!okport)
{
return false;
}
bool oknumFailures = u.from_bytes(numFailures);
if (!oknumFailures)
{
return false;
}
return true;
}
bool
PeerAddress::to_bytes(xdr::marshaler& m) const 
{
bool okip = m.to_bytes(ip);
if (!okip)
{
return false;
}
bool okport = m.to_bytes(port);
if (!okport)
{
return false;
}
bool oknumFailures = m.to_bytes(numFailures);
if (!oknumFailures)
{
return false;
}
return true;
}
void
PeerAddress::count_size(xdr::measurer& m) const 
{
m.count_size(ip);
m.count_size(port);
m.count_size(numFailures);
}
bool
PeerAddress::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PeerAddress const&>(other_abstract);return true
&& (ip== other.ip)
&& (port== other.port)
&& (numFailures== other.numFailures)
;}
bool
PeerAddress::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PeerAddress const&>(other_abstract);
if (ip < other.ip) return true;
if (other.ip < ip) return false;
if (port < other.port) return true;
if (other.port < port) return false;
if (numFailures < other.numFailures) return true;
if (other.numFailures < numFailures) return false;
return false;
}bool
DontHave::from_bytes(xdr::unmarshaler& u) 
{
bool oktype = u.from_bytes(type);
if (!oktype)
{
return false;
}
bool okreqHash = u.from_bytes(reqHash);
if (!okreqHash)
{
return false;
}
return true;
}
bool
DontHave::to_bytes(xdr::marshaler& m) const 
{
bool oktype = m.to_bytes(type);
if (!oktype)
{
return false;
}
bool okreqHash = m.to_bytes(reqHash);
if (!okreqHash)
{
return false;
}
return true;
}
void
DontHave::count_size(xdr::measurer& m) const 
{
m.count_size(type);
m.count_size(reqHash);
}
bool
DontHave::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<DontHave const&>(other_abstract);return true
&& (type== other.type)
&& (reqHash== other.reqHash)
;}
bool
DontHave::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<DontHave const&>(other_abstract);
if (type < other.type) return true;
if (other.type < type) return false;
if (reqHash < other.reqHash) return true;
if (other.reqHash < reqHash) return false;
return false;
}bool
StellarMessage::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)MessageType::ERROR_MSG:
return u.from_bytes(error_);
  case (int32_t)MessageType::HELLO:
return u.from_bytes(hello_);
  case (int32_t)MessageType::AUTH:
return u.from_bytes(auth_);
  case (int32_t)MessageType::DONT_HAVE:
return u.from_bytes(dontHave_);
  case (int32_t)MessageType::GET_PEERS:
    return true;
  case (int32_t)MessageType::PEERS:
return u.from_bytes(peers_);
  case (int32_t)MessageType::GET_TX_SET:
return u.from_bytes(txSetHash_);
  case (int32_t)MessageType::TX_SET:
return u.from_bytes(txSet_);
  case (int32_t)MessageType::TRANSACTION:
return u.from_bytes(transaction_);
  case (int32_t)MessageType::GET_SCP_QUORUMSET:
return u.from_bytes(qSetHash_);
  case (int32_t)MessageType::SCP_QUORUMSET:
return u.from_bytes(qSet_);
  case (int32_t)MessageType::SCP_MESSAGE:
return u.from_bytes(envelope_);
  case (int32_t)MessageType::GET_SCP_STATE:
return u.from_bytes(getSCPLedgerSeq_);
}
return false;
}
bool
StellarMessage::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)MessageType::ERROR_MSG:
return m.to_bytes(error_);
  case (int32_t)MessageType::HELLO:
return m.to_bytes(hello_);
  case (int32_t)MessageType::AUTH:
return m.to_bytes(auth_);
  case (int32_t)MessageType::DONT_HAVE:
return m.to_bytes(dontHave_);
  case (int32_t)MessageType::GET_PEERS:
    return true;
  case (int32_t)MessageType::PEERS:
return m.to_bytes(peers_);
  case (int32_t)MessageType::GET_TX_SET:
return m.to_bytes(txSetHash_);
  case (int32_t)MessageType::TX_SET:
return m.to_bytes(txSet_);
  case (int32_t)MessageType::TRANSACTION:
return m.to_bytes(transaction_);
  case (int32_t)MessageType::GET_SCP_QUORUMSET:
return m.to_bytes(qSetHash_);
  case (int32_t)MessageType::SCP_QUORUMSET:
return m.to_bytes(qSet_);
  case (int32_t)MessageType::SCP_MESSAGE:
return m.to_bytes(envelope_);
  case (int32_t)MessageType::GET_SCP_STATE:
return m.to_bytes(getSCPLedgerSeq_);
}
return false;
}
void
StellarMessage::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)MessageType::ERROR_MSG:
return m.count_size(error_);
  case (int32_t)MessageType::HELLO:
return m.count_size(hello_);
  case (int32_t)MessageType::AUTH:
return m.count_size(auth_);
  case (int32_t)MessageType::DONT_HAVE:
return m.count_size(dontHave_);
  case (int32_t)MessageType::GET_PEERS:
  
  return;
  case (int32_t)MessageType::PEERS:
return m.count_size(peers_);
  case (int32_t)MessageType::GET_TX_SET:
return m.count_size(txSetHash_);
  case (int32_t)MessageType::TX_SET:
return m.count_size(txSet_);
  case (int32_t)MessageType::TRANSACTION:
return m.count_size(transaction_);
  case (int32_t)MessageType::GET_SCP_QUORUMSET:
return m.count_size(qSetHash_);
  case (int32_t)MessageType::SCP_QUORUMSET:
return m.count_size(qSet_);
  case (int32_t)MessageType::SCP_MESSAGE:
return m.count_size(envelope_);
  case (int32_t)MessageType::GET_SCP_STATE:
return m.count_size(getSCPLedgerSeq_);
}
}
bool
StellarMessage::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<StellarMessage const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)MessageType::ERROR_MSG:
return error_ == other.error_;
  case (int32_t)MessageType::HELLO:
return hello_ == other.hello_;
  case (int32_t)MessageType::AUTH:
return auth_ == other.auth_;
  case (int32_t)MessageType::DONT_HAVE:
return dontHave_ == other.dontHave_;
  case (int32_t)MessageType::GET_PEERS:
  
  return true;
  case (int32_t)MessageType::PEERS:
return peers_ == other.peers_;
  case (int32_t)MessageType::GET_TX_SET:
return txSetHash_ == other.txSetHash_;
  case (int32_t)MessageType::TX_SET:
return txSet_ == other.txSet_;
  case (int32_t)MessageType::TRANSACTION:
return transaction_ == other.transaction_;
  case (int32_t)MessageType::GET_SCP_QUORUMSET:
return qSetHash_ == other.qSetHash_;
  case (int32_t)MessageType::SCP_QUORUMSET:
return qSet_ == other.qSet_;
  case (int32_t)MessageType::SCP_MESSAGE:
return envelope_ == other.envelope_;
  case (int32_t)MessageType::GET_SCP_STATE:
return getSCPLedgerSeq_ == other.getSCPLedgerSeq_;
}
return false;
}
bool
StellarMessage::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<StellarMessage const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)MessageType::ERROR_MSG:
return error_ < other.error_;
  case (int32_t)MessageType::HELLO:
return hello_ < other.hello_;
  case (int32_t)MessageType::AUTH:
return auth_ < other.auth_;
  case (int32_t)MessageType::DONT_HAVE:
return dontHave_ < other.dontHave_;
  case (int32_t)MessageType::GET_PEERS:
    return false;
  case (int32_t)MessageType::PEERS:
return peers_ < other.peers_;
  case (int32_t)MessageType::GET_TX_SET:
return txSetHash_ < other.txSetHash_;
  case (int32_t)MessageType::TX_SET:
return txSet_ < other.txSet_;
  case (int32_t)MessageType::TRANSACTION:
return transaction_ < other.transaction_;
  case (int32_t)MessageType::GET_SCP_QUORUMSET:
return qSetHash_ < other.qSetHash_;
  case (int32_t)MessageType::SCP_QUORUMSET:
return qSet_ < other.qSet_;
  case (int32_t)MessageType::SCP_MESSAGE:
return envelope_ < other.envelope_;
  case (int32_t)MessageType::GET_SCP_STATE:
return getSCPLedgerSeq_ < other.getSCPLedgerSeq_;
}
return false;
}
bool
AuthenticatedMessage::_v0_t::from_bytes(xdr::unmarshaler& u) 
{
bool oksequence = u.from_bytes(sequence);
if (!oksequence)
{
return false;
}
bool okmessage = u.from_bytes(message);
if (!okmessage)
{
return false;
}
bool okmac = u.from_bytes(mac);
if (!okmac)
{
return false;
}
return true;
}
bool
AuthenticatedMessage::_v0_t::to_bytes(xdr::marshaler& m) const 
{
bool oksequence = m.to_bytes(sequence);
if (!oksequence)
{
return false;
}
bool okmessage = m.to_bytes(message);
if (!okmessage)
{
return false;
}
bool okmac = m.to_bytes(mac);
if (!okmac)
{
return false;
}
return true;
}
void
AuthenticatedMessage::_v0_t::count_size(xdr::measurer& m) const 
{
m.count_size(sequence);
m.count_size(message);
m.count_size(mac);
}
bool
AuthenticatedMessage::_v0_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_v0_t const&>(other_abstract);return true
&& (sequence== other.sequence)
&& (message== other.message)
&& (mac== other.mac)
;}
bool
AuthenticatedMessage::_v0_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_v0_t const&>(other_abstract);
if (sequence < other.sequence) return true;
if (other.sequence < sequence) return false;
if (message < other.message) return true;
if (other.message < message) return false;
if (mac < other.mac) return true;
if (other.mac < mac) return false;
return false;
}bool
AuthenticatedMessage::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
return u.from_bytes(v0_);
}
return false;
}
bool
AuthenticatedMessage::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
return m.to_bytes(v0_);
}
return false;
}
void
AuthenticatedMessage::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
return m.count_size(v0_);
}
}
bool
AuthenticatedMessage::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<AuthenticatedMessage const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
return v0_ == other.v0_;
}
return false;
}
bool
AuthenticatedMessage::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AuthenticatedMessage const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
return v0_ < other.v0_;
}
return false;
}
}