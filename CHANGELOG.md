# Changelog

## 3.8.0 

### Added

Liquidity pools support, based on Uniswap v2:
* `LpAddLiquidityOp`, `LpRemoveLiquidityOp`, and `LpSwapOp` operations
* Account and signer rules for liquidity pools operations
* Ledger entry `LiquidityPool` to store information about a liquidity pool

## 3.7.3

### Added

* Added new poll type `CUSTOM_CHOICE` for custom polls
* Update data owner operation for transferring data ownership
* Ability to set custom rule and action in permissions
* Reviewable requests for create, update and remove data operations

## 3.7.1

### Added

* Action `ManageSaleAction::UPDATE_TIME` for sale start time update
* Ledger version `FIX_UNORDERED_FEE_DESTINATION`

### Fixed

* Fixed balances order

## 3.7.0

### Added

Deferred payments:
* Create/close deferred payment requests 
* Review create/close deferred payment requests
* Ledger entry `DEFERRED_PAYMENT`
* Account and signer rule resources for deferred payments

### Fixed

* Change role request requester

## 3.6.5

### Added 

* Creator details handling & validation for manage offer and payment reviewable requests 

### Fixed

* Crash core with payment transaction
* Exception during invest to immediate sale
* Wildcard value does not work for the 'payment_tasks:*'

## 3.6.4

### Fixed

* multiple time reviewing of movement request
* autoreview in create asset/update asset operations
* entry duplicates in ledger changes

## 3.6.3

### Added

* Redemption reviewable request

## 3.6.2

### Changed

* `RemoveAssetOp` now changes asset status to deleted but not delete it

### Fixed

* internal error on set fee op application

## 3.6.1

### Fixed

* Checking initiate kyc recovery account rule

## 3.6.0

### Added 

* `CreatePaymentRequestOpFrame`
* `CreateManageOfferRequestOpFrame`
* Account rule resources for `ManageOffer` and `CreatePayment` reviewable requests
* Signer rule resources for `ManageOffer` and `CreatePayment` reviewable requests
* `RemoveAssetOp` operation to remove asset
* BalanceManager
* `OpenSwapOpFrame`
* `CloseSwapOpFrame`
* `SwapEntry`
* Account rule resources for `Swap`
* Signer rule resources for `Swap` 

### Changed
* Partially migrated to new helpers
* Refactored all OpFrames to use StorageHelper

### Removed
* AccountManager

### Fixed

* long serialization on OS X 64-bit
* Reviewer for issuance requests

## 3.5.2

### Changed

* XDR marshaling/unmarshaling

## 3.5.1

### Removed

* xdr submodule

### Added

* script for xdr generation

### Fixed

* Ledger changes after removing signer and signer role
* Statistics calculation for deposit stats op type
* Create KYC recovery request permissions
* Panic on horizon (not found reviewable request in ledger changes)

## 3.5.0

### Added

* Rules for `AccountSpecificRule`
* `RemoveAssetPairOp` operation to remove asset pair
* `InitiateKYCRecoveryOpFrame`
* `CreateKYCRecoveryRequestOpFrame`
* `ReviewKYCRecoveryOpFrame`
* `atomic_swap_bid_tasks` and `atomic_swap_ask_tasks` reserved keys

### Fixed

* unsuccessful test passing by (--test)
* exception on drop and ban peer command
* Tasks handling on `ChangeRoleRequest` reject
* Ability to set fixed fee for `INVEST_FEE` type
* Ability to create asset pair for the same asset, i.e. `A/A`
* atomic swaps, enable them

## 3.4.1

### Fixed

* exception on ledger version upgrade

## 3.4.0

### Added

* Unlimited (`UINT_64MAX`) signers amount in free license
* New CreateAMLAlert error codes

### Fixed

* Added checking permission for setting `allTasks` in operations: `CreateAMLAlertRequestOp`, `CreateManageLimitsRequestOp`, `CreateIssuanceRequestOp`, `CreatePreIssuanceRequestOp`, `UpdateAssetOp`, `ManageSaleOp`
* Exception on check sale state op because of wrong removing sale specific rules

## 3.3.1

### Fixed

* curl now added in containers

## 3.3.0

### Added

* Manage account specific rule op frame
* Cancel change role reviewable request

### Fixed

* Create and approve change role request for role that does  not exist
* Removed ability to create sale for reversed pair

## 3.2.1

### Fixed 
* Fail of histexists command if db has not been initialized


### Fixed 
* Manage asset tests

###Fixed

* Delete vote after poll ended

## 3.2.0

### Added

* Close poll op frame
* Update poll end time op frame
* Invest fee
* Voting tests

### Changed

* Merge internal and non-functionality (non business logic) improvements from stellar
* Updated Cereal serialization library version 

### Fixed

* exception on poll migration
* Current and physical price restrictions

## 3.1.3

### Fixed

* Calculating statistics for payment

## 3.1.2

### Fixed

* Writing poll permission type to db which more then int32_max

## 3.1.1

### Fixed

* Rule checking for voting (by permissionType equaled UINT32)

## 3.1.0

### Added

* Manage create poll request op frame
* Manage poll op frame
* Manage vote op frame
* Docker healthcheck
* Logging to Sentry besides of the regular logging with configurable DSN and minimal level of messages to send

## 3.0.2-x.0

### Fixed

* Managing fee for not existing account (horizon panics)
* get exists Entry from cache

## 3.0.1

### Fixed

* tx internal error on update signer operation

### Changed

* Rotation of license keys

## 3.0.0

### Fixed

* Fixed unexpected error (`Unexpected state: tring to unlock more then we have in current cap in base asset`) on cancel of sale participation for fixed price sale
* unexpected sale participation exceeds hard cap for fixed price sales
* adding signer to admin results in failure of other admins operations due to license violation
* Do not add to cache if load entry without delta (add delta to putCacheEntry method)
* Implement getLedgerDelta method for all new helpers
* Issue with update of not rejected reviewable request
* Removing key values by key which is determined in mValueTypes map in manageKyValueOpFrame
* Check amount precision fitting on set fee operation level, remove checks for upper and lower bounds
* Manage account and signer role operations
* EntryHelperProvider work with new entries
* Fixed problem with adding to reference table
* Populate base and quote assets on offer removal

### Added

* Return error code if value of withdraw tasks is zero in manage key value op
* Field with payload for txNO_ROLE_PERMISSION and opNO_ROLE_PERMISSION
* Licensing
* License, Stamp operations
* Add change role tasks keys with `*`
* EntryHelperLegacyImpl
* RuleVerifier
* AccountRuleVerifier

### Changed

* Key value resource comparing in rule verifying
* Rename paymentV2 to payment
* Rename isForbid to forbids, in db too
* SignerRequirements for create and review withdraw
* Create asset request operation conditions
* Use error code invalid creator details
* ManageAccountRule and ManageAccountRole op frames
* AccountRole and AccountRule helpers and frames
* Account frame
* Rename KYC request to change role
* Create account op frame
* Squashed ledger version;

### Deprecated

* atomic swap
* Account type
* Payout

### Removed

* source account details, counterparty details
* getSourceAccountDetails and getCounterpartyDetails for all op frames
* manage account op frame
* trust frame
* account type limits frame
* Payment and Direct Debit Operations
