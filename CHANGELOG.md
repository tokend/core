# Changelog

## Unreleased

### Fixed

* Check for exceeding of maxIssuanceAmount on pre issuance (add pendingIssuance of asset to sum in canAddAvailableForIssuance method)
* Check for exceeding of maxIssuanceAmount on create `CREATE_SALE` request
* Remove checking for not empty signers on signature validation
* Return error code on review pre issuance if max issuance amount exceeded

## 3.0.0-x.8

### Fixed

* Exception after sending Stamp or LicenseOp: LedgerCmp cannot compare structures

## 3.0.0-x.7

### Fixed

* Sale request changes are not saved on update

## 3.0.0-x.6

### Added

* Return error code if value of withdraw tasks is zero in manage key value op
* Field with payload for txNO_ROLE_PERMISSION and opNO_ROLE_PERMISSION
* Licensing
* License, Stamp operations

### Fixed

* Do not add to cache if load entry without delta (add delta to putCacheEntry method)
* Implement getLedgerDelta method for all new helpers
* Issue with update of not rejected reviewable request
* Removing key values by key which is determined in mValueTypes map in manageKyValueOpFrame
* Check amount precision fitting on set fee operation level, remove checks for upper and lower bounds

### Changed

* Key value resource comparing in rule verifying

## 3.0.0-x.5

### Added

* Add change role tasks keys with `*`
* EntryHelperLegacyImpl

### Fixed

* Manage account and signer role operations
* EntryHelperProvider work with new entries

### Changed

* Rename paymentV2 to payment
* Rename isForbid to forbids, in db too
* SignerRequirements for create and review withdraw
* Create asset request operation conditions
* Use error code invalid creator details

### Deprecated

* atomic swap

## 3.0.0-x.4

### Added

* RuleVerifier
* AccountRuleVerifier

### Changed

* ManageAccountRule and ManageAccountRole op frames
* AccountRole and AccountRule helpers and frames
* Account frame
* Rename KYC request to change role
* Create account op frame

### Deprecated

* Account type
* Payout

### Removed

* source account details, counterparty details
* getSourceAccountDetails and getCounterpartyDetails for all op frames
* manage account op frame
* trust frame
* account type limits frame

## 3.0.0-x.3

### Fixed

* Fixed problem with adding to reference table

## 3.0.0-x.2

### Changed

* Squashed ledger version;

### Removed

* Payment and Direct Debit Operations

### Fixed

* Populate base and quote assets on offer removal
