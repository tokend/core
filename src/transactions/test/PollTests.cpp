#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ReviewRequestTestHelper.h>
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/ReviewableRequestHelper.h"
#include "test/test.h"
#include "TxTests.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test/test_marshaler.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test_helper/ManagePollTestHelper.h"
#include "test_helper/ManageVoteTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

TEST_CASE("Poll", "[tx][voting][poll]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    Database& db = testManager->getDB();

    auto root = Account{getRoot(), Salt(0)};

    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManagePollTestHelper managePollTestHelper(testManager);
    ManageVoteTestHelper manageVoteTestHelper(testManager);
    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    ReviewRequestHelper reviewRequestTestHelper(testManager);

    uint32_t pollTasks = 1;
    longstring pollKey = ManageKeyValueOpFrame::makeCreatePollKey("*");
    manageKeyValueHelper.setKey(pollKey)->setUi32Value(pollTasks);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    uint32_t pollPermissionType(1);

    // create policy (just entry)
    // to create poll
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_POLL);
    resource.reviewableRequest().details.createPoll().permissionType = UINT32_MAX;
    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, resource, AccountRuleAction::CREATE, false);
    auto createPollRuleID = manageAccountRuleTestHelper.applyTx(
        root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;
    // to send tx
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, AccountRuleResource(LedgerEntryType::TRANSACTION), AccountRuleAction::SEND, false);
    auto txSendRuleID = manageAccountRuleTestHelper.applyTx(
        root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;
    //to  create poll
    resource.type(LedgerEntryType::VOTE);
    resource.vote().permissionType = UINT32_MAX;
    resource.vote().pollID = UINT64_MAX;
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, resource, AccountRuleAction::CREATE, false);
    auto createVoteRuleID = manageAccountRuleTestHelper.applyTx(
        root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, resource, AccountRuleAction::REMOVE, false);
    auto removeVoteRuleID = manageAccountRuleTestHelper.applyTx(
        root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;
    //to  close poll
    resource.type(LedgerEntryType::POLL);
    resource.poll().permissionType = UINT32_MAX;
    resource.poll().pollID = UINT64_MAX;
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, resource, AccountRuleAction::CLOSE, false);
    auto closePollRuleID = manageAccountRuleTestHelper.applyTx(
        root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    //to update poll end time
    resource.type(LedgerEntryType::POLL);
    resource.poll().permissionType = UINT32_MAX;
    resource.poll().pollID = UINT64_MAX;
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, resource, AccountRuleAction::UPDATE_END_TIME, false);
    auto managePollRuleID = manageAccountRuleTestHelper.applyTx(
        root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    //to cancel poll
    resource.type(LedgerEntryType::POLL);
    resource.poll().permissionType = UINT32_MAX;
    resource.poll().pollID = UINT64_MAX;
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, resource, AccountRuleAction::CANCEL, false);
    auto cancelPollRuleID = manageAccountRuleTestHelper.applyTx(
        root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;


    // voting role
    auto votingRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
        R"({"feature":"voting"})", {createPollRuleID, txSendRuleID, createVoteRuleID, removeVoteRuleID,
                                    closePollRuleID, managePollRuleID, cancelPollRuleID});
    auto votingRoleID = manageAccountRoleTestHelper.applyTx(
        root, votingRoleOp).success().roleID;

    // basic account builder
    auto createAccountBuilder = CreateAccountTestBuilder()
        .setSource(root).setRoleID(votingRoleID);

    auto poller = Account{SecretKey::random(), 0};
    auto pollerPubkey = poller.key.getPublicKey();
    createAccountTestHelper.applyTx(createAccountBuilder
                                        .setToPublicKey(pollerPubkey)
                                        .addBasicSigner());
    auto resultProvider = Account{SecretKey::random(), 0};
    auto resultProviderPubkey = resultProvider.key.getPublicKey();
    createAccountTestHelper.applyTx(createAccountBuilder
                                        .setToPublicKey(resultProviderPubkey)
                                        .addBasicSigner());
    auto voter = Account{SecretKey::random(), 0};
    auto voterPubkey = voter.key.getPublicKey();
    createAccountTestHelper.applyTx(createAccountBuilder
                                        .setToPublicKey(voterPubkey)
                                        .addBasicSigner());

    const auto currentTime = testManager->getLedgerManager().getCloseTime();
    const auto startTime = currentTime + 500;
    const auto endTime = currentTime + 1000;

    PollData pollData;
    pollData.type(PollType::SINGLE_CHOICE);
    CreatePollRequest req;
    req.permissionType = pollPermissionType;
    req.voteConfirmationRequired = false;
    req.resultProviderID = resultProviderPubkey;
    req.startTime = startTime;
    req.endTime = endTime;
    req.creatorDetails = "{}";
    req.data = pollData;
    req.numberOfChoices = 2;
    CreatePollRequestData createPollReq;
    createPollReq.request = req;
    auto managePollBuilder = ManagePollTestBuilder().setSource(poller);
    auto createPollBuilder = ManageCreatePollRequestTestBuilder().setSource(poller);

    SECTION("Invalid details")
    {
        createPollReq.request.creatorDetails = "invalid data";

        auto pollCreationResultCode = managePollTestHelper.applyTx(createPollBuilder.
            setAction(ManageCreatePollRequestAction::CREATE).
            setCreateRequestData(createPollReq).
            setResultCode(ManageCreatePollRequestResultCode::INVALID_CREATOR_DETAILS)
        );
    }

    SECTION("Invalid dates")
    {
        createPollReq.request.startTime = endTime;

        auto pollCreationResultCode = managePollTestHelper.applyTx(createPollBuilder.
            setAction(ManageCreatePollRequestAction::CREATE).
            setCreateRequestData(createPollReq).
            setResultCode(ManageCreatePollRequestResultCode::INVALID_DATES)
        );
    }

    SECTION("Invalid start time")
    {
        createPollReq.request.startTime = currentTime - 1;
        createPollReq.request.endTime = currentTime;

        auto pollCreationResultCode = managePollTestHelper.applyTx(createPollBuilder.
            setAction(ManageCreatePollRequestAction::CREATE).
            setCreateRequestData(createPollReq).
            setResultCode(ManageCreatePollRequestResultCode::INVALID_END_TIME)
        );
    }

    SECTION("Invalid result provider")
    {
        createPollReq.request.resultProviderID = PubKeyUtils::random();

        managePollTestHelper.applyTx(createPollBuilder.
            setAction(ManageCreatePollRequestAction::CREATE).
            setCreateRequestData(createPollReq).
            setResultCode(ManageCreatePollRequestResultCode::RESULT_PROVIDER_NOT_FOUND)
        );
    }

    SECTION("Tasks not found")
    {
        manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::REMOVE, true);
        managePollTestHelper.applyTx(createPollBuilder.
            setAction(ManageCreatePollRequestAction::CREATE).
            setCreateRequestData(createPollReq).
            setResultCode(ManageCreatePollRequestResultCode::CREATE_POLL_TASKS_NOT_FOUND)
        );
    }

    SECTION("Happy path")
    {
        auto pollCreationResult = managePollTestHelper.applyTx(createPollBuilder.
            setAction(ManageCreatePollRequestAction::CREATE).
            setCreateRequestData(createPollReq)
        );

        auto requestID = pollCreationResult.success().details.response().requestID;

        auto reviewResult = reviewRequestTestHelper.applyReviewRequestTxWithTasks(root,
                                                                                  requestID, ReviewRequestOpAction::APPROVE, "", ReviewRequestResultCode::SUCCESS,
                                                                                  nullptr, &pollTasks);
        auto pollID = reviewResult.success().typeExt.createPoll().pollID;

        VoteData voteData;
        voteData.pollType(PollType::SINGLE_CHOICE);
        voteData.single().choice = 1;
        CreateVoteData createVoteData;
        createVoteData.pollID = pollID;
        createVoteData.data = voteData;

        auto manageVoteBuilder = ManageVoteTestBuilder().setSource(voter);

        SECTION("Cancel poll")
        {
            managePollTestHelper.applyTx(managePollBuilder.
                setPollID(pollID).
                setAction(ManagePollAction::CANCEL));
        }

        SECTION("Update end time")
        {
            UpdatePollEndTimeData updateEndTimeData;
            updateEndTimeData.newEndTime = endTime + 1000;

            managePollTestHelper.applyTx(managePollBuilder.
                setPollID(pollID).
                setAction(ManagePollAction::UPDATE_END_TIME).
                setUpdateEndTimeData(updateEndTimeData));
        }

        SECTION("Admin updates end time")
        {

            UpdatePollEndTimeData updateEndTimeData;
            updateEndTimeData.newEndTime = endTime + 1000;

            managePollTestHelper.applyTx(managePollBuilder.
                setSource(root).
                setPollID(pollID).
                setAction(ManagePollAction::UPDATE_END_TIME).
                setUpdateEndTimeData(updateEndTimeData));
        }

        SECTION("Random account with rules updates end time")
        {
            auto sneaker = Account{SecretKey::random(), 0};
            auto sneakerPubkey = sneaker.key.getPublicKey();
            createAccountTestHelper.applyTx(createAccountBuilder
                                                .setToPublicKey(sneakerPubkey)
                                                .addBasicSigner());

            managePollBuilder;

            UpdatePollEndTimeData updateEndTimeData;
            updateEndTimeData.newEndTime = endTime + 1000;

            managePollTestHelper.applyTx(managePollBuilder.
                setSource(sneaker).
                setPollID(pollID).
                setAction(ManagePollAction::UPDATE_END_TIME).
                setUpdateEndTimeData(updateEndTimeData).
                setResultCode(ManagePollResultCode::NOT_AUTHORIZED));
        }


        SECTION("Too early")
        {
            auto voteCreationResultCode = manageVoteTestHelper.applyTx(manageVoteBuilder.
                setAction(ManageVoteAction::CREATE).
                setCreateVoteData(createVoteData).
                setResultCode(ManageVoteResultCode::POLL_NOT_STARTED)
            );
        }

        SECTION("Too late")
        {
            testManager->advanceToTime(endTime + 1);
            auto voteCreationResultCode = manageVoteTestHelper.applyTx(manageVoteBuilder.
                setAction(ManageVoteAction::CREATE).
                setCreateVoteData(createVoteData).
                setResultCode(ManageVoteResultCode::POLL_ENDED)
            );
        }

        SECTION("vote not found")
        {
            RemoveVoteData removeData;
            removeData.pollID = pollID;

            manageVoteTestHelper.applyTx(manageVoteBuilder.
                setAction(ManageVoteAction::REMOVE).
                setRemoveVoteData(removeData).
                setResultCode(ManageVoteResultCode::VOTE_NOT_FOUND)
            );
        }

        SECTION("Vote successfully")
        {
            testManager->advanceToTime(startTime);
            auto voteCreationResultCode = manageVoteTestHelper.applyTx(manageVoteBuilder.
                setAction(ManageVoteAction::CREATE).
                setCreateVoteData(createVoteData)
            );

            SECTION("Cancel poll with votes")
            {
                managePollTestHelper.applyTx(managePollBuilder.
                    setPollID(pollID).
                    setAction(ManagePollAction::CANCEL));
            }

            SECTION("Update end time with votes")
            {
                UpdatePollEndTimeData updateEndTimeData;
                updateEndTimeData.newEndTime = endTime + 1000;

                managePollTestHelper.applyTx(managePollBuilder.
                    setPollID(pollID).
                    setAction(ManagePollAction::UPDATE_END_TIME).
                    setUpdateEndTimeData(updateEndTimeData));
            }

            SECTION("Update end time with votes after end time")
            {
                testManager->advanceToTime(endTime);

                UpdatePollEndTimeData updateEndTimeData;
                updateEndTimeData.newEndTime = endTime + 1000;

                managePollTestHelper.applyTx(managePollBuilder.
                    setPollID(pollID).
                    setAction(ManagePollAction::UPDATE_END_TIME).
                    setUpdateEndTimeData(updateEndTimeData));
            }

            SECTION("Update end time with end time in the past")
            {
                testManager->advanceToTime(endTime);

                UpdatePollEndTimeData updateEndTimeData;
                updateEndTimeData.newEndTime = endTime - 1000;

                managePollTestHelper.applyTx(managePollBuilder.
                    setPollID(pollID).
                    setAction(ManagePollAction::UPDATE_END_TIME).
                    setUpdateEndTimeData(updateEndTimeData).
                    setResultCode(ManagePollResultCode::INVALID_END_TIME));
            }

            SECTION("Cancel poll with votes after end time")
            {
                testManager->advanceToTime(endTime);

                managePollTestHelper.applyTx(managePollBuilder.
                    setPollID(pollID).
                    setAction(ManagePollAction::CANCEL));
            }

            SECTION("Admin cancel poll with votes after end time")
            {
                testManager->advanceToTime(endTime);

                managePollTestHelper.applyTx(managePollBuilder.
                    setSource(root).
                    setPollID(pollID).
                    setAction(ManagePollAction::CANCEL));
            }

            SECTION("Sneaker cancel poll with votes after end time")
            {
                auto sneaker = Account{SecretKey::random(), 0};
                auto sneakerPubkey = sneaker.key.getPublicKey();
                createAccountTestHelper.applyTx(createAccountBuilder
                                                    .setToPublicKey(sneakerPubkey)
                                                    .addBasicSigner());

                testManager->advanceToTime(endTime);

                managePollTestHelper.applyTx(managePollBuilder.
                    setSource(sneaker).
                    setPollID(pollID).
                    setAction(ManagePollAction::CANCEL).
                    setResultCode(ManagePollResultCode::NOT_AUTHORIZED));
            }

            SECTION("Vote exists")
            {
                manageVoteTestHelper.applyTx(manageVoteBuilder.
                    setAction(ManageVoteAction::CREATE).
                    setCreateVoteData(createVoteData).
                    setResultCode(ManageVoteResultCode::VOTE_EXISTS)
                );
            }

            SECTION("Remove vote")
            {
                RemoveVoteData removeData;
                removeData.pollID = pollID;

                manageVoteTestHelper.applyTx(manageVoteBuilder.
                    setAction(ManageVoteAction::REMOVE).
                    setRemoveVoteData(removeData).
                    setResultCode(ManageVoteResultCode::SUCCESS).
                    setTxResultCode(TransactionResultCode::txSUCCESS)
                );

                SECTION("Update vote")
                {
                    manageVoteTestHelper.applyTx(manageVoteBuilder.
                        setAction(ManageVoteAction::CREATE).
                        setCreateVoteData(createVoteData)
                    );
                }
            }

            SECTION("Finish poll")
            {
                testManager->advanceToTime(endTime + 1);
                ClosePollData data;
                data.result = PollResult::PASSED;
                data.details = "{}";
                auto finishPollResult = managePollTestHelper.applyTx(
                    managePollBuilder.
                        setSource(resultProvider).
                        setAction(ManagePollAction::CLOSE).
                        setPollID(pollID).
                        setClosePollData(data)
                );
            }

            SECTION("Not poll result provider")
            {
                testManager->advanceToTime(endTime);
                ClosePollData data;
                data.result = PollResult::PASSED;
                data.details = "{}";
                auto finishPollResult = managePollTestHelper.applyTx(
                    managePollBuilder.
                        setSource(root).
                        setAction(ManagePollAction::CLOSE).
                        setPollID(pollID).
                        setClosePollData(data).
                        setResultCode(ManagePollResultCode::NOT_AUTHORIZED_TO_CLOSE_POLL)
                );
            }

            SECTION("Finish poll too early")
            {
                ClosePollData data;
                data.result = PollResult::PASSED;
                data.details = "{}";
                auto finishPollResult = managePollTestHelper.applyTx(managePollBuilder.
                    setSource(resultProvider).
                    setAction(ManagePollAction::CLOSE).
                    setPollID(pollID).
                    setClosePollData(data).
                    setResultCode(ManagePollResultCode::POLL_NOT_READY)
                );
            }
        }
    }

    SECTION("Vote approve required")
    {
        createPollReq.request.voteConfirmationRequired = true;

        auto pollCreationResult = managePollTestHelper.applyTx(createPollBuilder.
            setAction(ManageCreatePollRequestAction::CREATE).
            setCreateRequestData(createPollReq).
            setTxResultCode(TransactionResultCode::txSUCCESS)
        );

        auto requestID = pollCreationResult.success().details.response().requestID;

        SECTION("Cancel poll request")
        {
            CancelPollRequestData cancelData;
            cancelData.requestID = requestID;

            managePollTestHelper.applyTx(createPollBuilder.
                setAction(ManageCreatePollRequestAction::CANCEL).
                setCancelPollRequestData(cancelData)
            );

            managePollTestHelper.applyTx(createPollBuilder.
                setAction(ManageCreatePollRequestAction::CANCEL).
                setCancelPollRequestData(cancelData).
                setResultCode(ManageCreatePollRequestResultCode::NOT_FOUND).
                setOperationResultCode(OperationResultCode::opNO_ENTRY)
            );
        }

        SECTION("Approve")
        {
            auto reviewResult = reviewRequestTestHelper.applyReviewRequestTxWithTasks(root, requestID,
                                                                                      ReviewRequestOpAction::APPROVE, "", ReviewRequestResultCode::SUCCESS, nullptr, &pollTasks);
            auto pollID = reviewResult.success().typeExt.createPoll().pollID;

            SECTION("Cancel poll")
            {
                managePollTestHelper.applyTx(managePollBuilder.
                    setPollID(pollID).
                    setAction(ManagePollAction::CANCEL));
            }

            SECTION("Update end time")
            {
                UpdatePollEndTimeData updateEndTimeData;
                updateEndTimeData.newEndTime = endTime + 1000;

                managePollTestHelper.applyTx(managePollBuilder.
                    setPollID(pollID).
                    setAction(ManagePollAction::UPDATE_END_TIME).
                    setUpdateEndTimeData(updateEndTimeData));
            }

            SECTION("Vote successfully")
            {
                testManager->advanceToTime(startTime);
                VoteData voteData;
                voteData.pollType(PollType::SINGLE_CHOICE);
                voteData.single().choice = 1;
                CreateVoteData createVoteData;
                createVoteData.pollID = pollID;
                createVoteData.data = voteData;

                auto manageVoteBuilder = ManageVoteTestBuilder().setSource(voter);
                manageVoteTestHelper.applyTx(manageVoteBuilder.
                    setAction(ManageVoteAction::CREATE).
                    setCreateVoteData(createVoteData).
                    addSigner(&resultProvider).
                    addSigner(&voter)
                );

                SECTION("Cancel poll with votes")
                {
                    managePollTestHelper.applyTx(managePollBuilder.
                        setPollID(pollID).
                        setAction(ManagePollAction::CANCEL));
                }

                SECTION("Update end time with votes")
                {
                    UpdatePollEndTimeData updateEndTimeData;
                    updateEndTimeData.newEndTime = endTime + 1000;

                    managePollTestHelper.applyTx(managePollBuilder.
                        setPollID(pollID).
                        setAction(ManagePollAction::UPDATE_END_TIME).
                        setUpdateEndTimeData(updateEndTimeData));
                }

                SECTION("Update end time with votes after end time")
                {
                    testManager->advanceToTime(endTime);

                    UpdatePollEndTimeData updateEndTimeData;
                    updateEndTimeData.newEndTime = endTime + 1000;

                    managePollTestHelper.applyTx(managePollBuilder.
                        setPollID(pollID).
                        setAction(ManagePollAction::UPDATE_END_TIME).
                        setUpdateEndTimeData(updateEndTimeData));
                }

                SECTION("Cancel poll with votes after end time")
                {
                    testManager->advanceToTime(endTime);

                    managePollTestHelper.applyTx(managePollBuilder.
                        setPollID(pollID).
                        setAction(ManagePollAction::CANCEL));
                }
            }

            SECTION("Try vote with out signature of result Provider")
            {
                testManager->advanceToTime(startTime);
                VoteData voteData;
                voteData.pollType(PollType::SINGLE_CHOICE);
                voteData.single().choice = 1;
                CreateVoteData createVoteData;
                createVoteData.pollID = pollID;
                createVoteData.data = voteData;

                auto manageVoteBuilder = ManageVoteTestBuilder().setSource(voter);
                manageVoteTestHelper.applyTx(manageVoteBuilder.
                    setAction(ManageVoteAction::CREATE).
                    setCreateVoteData(createVoteData).
                    setOperationResultCode(OperationResultCode::opBAD_AUTH).
                    addSigner(&voter).
                    addSigner(&root)
                );
            }
        }
    }

}

