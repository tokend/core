# Quorums

Setting correct quorum is a very important part of TokenD configuration.

**Quorum set** is a list of validators and threshold.

**Threshold** is a percent of entities from quorum set, which must agree to close ledger.

The simplest Quorum set is:

```
[QUORUM_SET]
THRESHOLD_PERCENT=66
VALIDATORS=[
    "alice",
    "bob",
    "carol"
]
```
In human language this says, "Close ledger if at least two out of 'alice', 'bob' and 'carol' agree that it is correct".

Quorum sets can have groups and sub-groups participating. Each group has one vote in the enclosed quorum set. Each sub-group has one vote in enclosed group.

Given the following configuration:
```
[QUORUM_SET]
THRESHOLD_PERCENT=67
VALIDATORS=[
    "alice",
    "bob",
    "carol"
]

[QUORUM_SET.TIE_BREAKER]
THRESHOLD_PERCENT=50
VALIDATORS=[
    "dave",
    "eve"
]
```
Ledger will be closed if:
  - all three of 'alice', 'bob' and 'carol' agreed;
  - one of them disagreed, but at least one of 'dave' or 'eve' agreed.

However, even if both 'dave' and 'eve' agreed, but only one of 'alice', 'bob' and 'carol' agreed - ledger won't be closed, because top-level threshold won't be passed (there will be 2 votes out of 3 needed).

 
