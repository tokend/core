cmake_minimum_required(VERSION 3.8)

project(core)

#definitions for compilers
include(platform_definitions.cmake)

#include headers directory
include(platform_include.cmake)

#path to .x
set(XDRS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/xdr)

#include generated files .h from .x
include_directories(${XDRS_PATH})

#include headers files without .cpp
set(NOT_COMMON_SOURCE_FILES
        util/asio.h
        util/must_use.h
        util/NonCopyable.h
        util/optional.h
        util/XDRStream.h
        test/test_marshaler.h
        work/WorkManager.h
        crypto/ByteSlice.h
        bucket/LedgerCmp.h
        bucket/BucketManager.h
        ledger/LedgerManager.h
        ledger/StorageHelper.h
        ledger/BalanceHelper.h
        ledger/AccountHelper.h
        ledger/AccountRuleHelper.h
        ledger/AccountRoleHelper.h
        ledger/SignerHelper.h
        ledger/SignerRuleHelper.h
        ledger/SignerRoleHelper.h
        ledger/KeyValueHelper.h
        ledger/PollHelper.h
        ledger/AccountSpecificRuleHelper.h
        history/HistoryManager.h
        overlay/BanManager.h
        overlay/StellarXDR.h
        overlay/OverlayManager.h
        process/ProcessManager.h
        transactions/SignatureValidator.h
        transactions/test/test_helper/Account.h
        transactions/rule_verifing/AccountRuleVerifier.h
        transactions/rule_verifing/SignerRuleVerifier.h)

# mocks
set(MOCKS_FILES transactions/test/mocks/)


#find source files
file(GLOB STELLAR_CORE_SOURCE_FILES **/*.cpp **/**/*.cpp **/**/**/*.cpp)

#create executeble file "core"
add_executable(core ${STELLAR_CORE_SOURCE_FILES} ${XDRS_PATH} ${H_GENERATE_FILES} ${NOT_COMMON_SOURCE_FILES} ${MOCKS_FILES})

# just build xdr files before build core
file(GLOB xdrs_files
        "${CMAKE_CURRENT_SOURCE_DIR}/xdr/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/xdr/*.cpp"
        )
add_custom_target(xdrs ${xdrs_files})
add_dependencies(core xdrs)

#link libs
include(platform_libs.cmake)
