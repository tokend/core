## Config options
### Connection options
#### HTTP_PORT
  - Type: Integer
  - Possible values: 1024 < HTTP_PORT < 65535
  - Default: 11626

At this port tokend core will listen for commands.

> Connections to this port are unauthenticated, so consider setting PUBLIC_HTTP_PORT to false, or protect connection by other means.

#### PUBLIC_HTTP_PORT
  - Type: Boolean

Tells tokend core to listen to the commands from the source other than localhost. Set it to true only if you know what you are doing.

#### PEER_PORT
  - Type: Integer
  - Possible values: 1024 < HTTP_PORT < 65535
  - Default: 11625

At this port tokend core will listen for connections from other tokend nodes.

#### NETWORK_PASSPHRASE
  - Type: String

Tokend network identificator. Sets in which network node will work (connect to other nodes, receive transactions, etc.)

Example:
```
NETWORK_PASSPHRASE="TokenD Developer Network"
```

#### DATABASE
  - Type: String
  - Possible value: Postgres connection string

Gives node access to the database.

> If running in docker container, you should put core's and DB's containers into the same network and set host to be the name of DB's container.

Example:
```
DATABASE="postgresql://dbname=core user=core password=core host=127.0.0.1 port=5432"

```

#### RUN_STANDALONE
  - Type: Boolean
  - Default: false

Prevents node from connecting to other nodes. For testing purposes.

#### KNOWN_PEERS
  - Type: Array
  - Possible values: list of {IP|domain}[:port] entries

List of peers this node will try to connect if there are less than TARGET_PEER_CONECTIONS connections.

Example:
```
KNOWN_PEERS=[
    "172.17.0.2:9081",
    "172.17.0.4:8090",
]
```

### Miscellaneous

#### CATCHUP_COMPLETE
  - Type: Boolean

If set to true tells core to catchup from the beggining, replaying all history.

#### MASTER_ACCOUNT_ID
  - Type: String
  - Possible values: Tokend account id

Sets public account id of the master account for this platform. Ensure that you own secret seed from this account id.

Example:
```
MASTER_ACCOUNT_ID="GBA4EX43M25UPV4WIE6RRMQOFTWXZZRIPFAI5VPY6Z2ZVVXVWZ6NEOOB"
```

#### NODE_SEED
  - Type: String
  - Possible values: Tokend secret seed [+ " " + "alias"]

Sets seed that will be used to authenticate node in network. You may set alias to the node seed, to use it later in configs

Example:
```
# With alias
NODE_SEED="SCWZDAKCXTQIKJHLHUVIBUTOOPJ4E5HW5ILVL42MMQWJRY2A2ARBB7H3 self"

# Without alias
NODE_SEED="SCWZDAKCXTQIKJHLHUVIBUTOOPJ4E5HW5ILVL42MMQWJRY2A2ARBB7H3"
```

#### NODE_IS_VALIDATOR
  - Type: Boolean
  - Default: false

Tells node to participate in consensus.

#### NODE_NAMES
  - Type: Array of strings
  - Possible values: Public keys + aliases

You may set aliases to different nodes for further use and easier distinction between nodes in logs and info requests.

Example:
```
NODE_NAMES=[
        "GCMG52W47XY5WCMGINWDTY73BFLBJTKTYL4M66YVPOVMQNAZSFMRCYET alice",
        "GARYGOHMMIFXYJO462SL52YY4JNBOWW25I54JDWZXAXN7W2A3PR3WUAP bob",
        "GBY55MMAFM56S375YWVMSY3FDA65UOKOH3AB7SULNCZNTVRIVVWAP7D2 carol",
]
```

#### BUTCKET_DIR_PATH
  - Type: String

Gives node the path where buckets should be stored. This will be written to a lot and will grow in size as ledger growth.

### Quorum configs

#### FAILURE_SAFETY
  - Type: Integer
  - Default: -1

Sets the amount of faulty validators you want to tolerate.
You'll need at least 3 * FAILURE_SAFETY + 1 entities in the top level of QUORUM_SET to be able to tolerate FAILURE_SAFETY nodes. If you have less nodes, core won't start.

The value of -1 tells to set FAILURE_SAFETY to (n-1)/3, where n is the amount of entities in the top level of QUORUM_SET.

The value of 0 is allowed only if UNSAFE_QUORUM is set to true. Do not use this unless you are absolutely sure what you are doing.

Example:
```
# Good
FAILURE_SAFETY=1
[QUORUM_SET]
THRESHOLD_PERCENT=66
VALIDATORS=[
    "alice",
    "bob",
    "carol",
    "dave"
]

# Bad: Not enough entities in validators list
FAILURE_SAFETY=2
[QUORUM_SET]
THRESHOLD_PERCENT=66
VALIDATORS=[
    "alice",
    "bob",
    "carol",
    "dave",
    "eve",
    "franklin"
]
```

#### UNSAFE_QUORUM
  - Type: Boolean
  - Default value: false

Will skip errors due to potentially unsafe quorum_set (for example too low THRESHOLD_PERCENT or FAILURE_SAFETY above the value which may be handled by the quorum).
You may set it to true only if you are running your own network and you are not concerned with byzantine failures or if you fully understand how the quorum sets of other node relate to your node.

#### QUORUM_SET
Quorum set is a separate section. Each Quorum set section contains 2 configs: THRESHOLD_PERCENT and VALIDATORS. The latter lists everybody whose voice counts. The former sets the amount of voices needed to close ledger. Set quorum set wisely not to have splits and/or conflicts. To introduce groups and subgroups, name section in the following way: `[QUORUM_SET.group_name.subgroup_name]`.

Example:
```
[QUORUM_SET]
THRESHOLD_PERCENT=67
VALIDATORS=[
  "$alice",
  "$bob",
  "$carol"
]

[QUORUM_SET.1]
THRESHOLD_PERCENT=50
VALIDATORS=[
  "$dave",
  "$eve"
]

[QUORUM_SET.1.1]
THRESHOLD_PERCENT=100
VALIDATORS=[
  "$franklin",
  "$grace",
  "$henry"
]

[QUORUM_SET.1.2]
THRESHOLD_PERCENT=66
VALIDATORS=[
  "$ivy",
  "$jacob",
  "$kelly"
]

[QUORUM_SET.2]
THRESHOLD_PERCENT=66
VALIDATORS=[
  "$liam",
  "$mia",
  "$nataly"
]
```

## Quorums

Setting correct quorum is a very important part of tokend configuration.

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
In human language this says, "Close ledger if at lest two out of 'alice', 'bob' and 'carol' agree that it is correct".

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

 
