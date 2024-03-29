#common definitions. #not valid for clang in MAC

add_definitions(
        -DASIO_STANDALONE
        -DHAVE_CONFIG_H
        -DELPP_FEATURE_PERFORMANCE_TRACKING
        -DASIO_SEPARATE_COMPILATION=1
        -DSQLITE_OMIT_LOAD_EXTENSION=1
        -DUSE_POSTGRES=1
        -DBUILD_TESTS=1
    )

set(DISABLE_CONSESUS ${DISABLE_CONSESUS})
if(DEFINED DISABLE_CONSESUS)
    message("consensus is disabled")
    add_definitions(-DDISABLE_CONSESUS=1) 
endif(DEFINED DISABLE_CONSESUS)

set(DEVELOPER_EDITION ${DEVELOPER_EDITION})
if(DEFINED DEVELOPER_EDITION)
    add_definitions(-DDEVELOPER_EDITION=1)
endif(DEFINED DEVELOPER_EDITION)

# version
#execute_process(COMMAND bash -c "git describe --always --dirty --tags" OUTPUT_VARIABLE VERSION)
#string(STRIP ${VERSION})
configure_file(main/StellarCoreVersion.cpp.in ${CMAKE_CURRENT_SOURCE_DIR}/main/StellarCoreVersion.cpp)

# add revision of xdr submodule, use in core info
#execute_process(COMMAND bash -c "(cd ${CMAKE_CURRENT_SOURCE_DIR}/xdr && git rev-parse HEAD)" OUTPUT_VARIABLE XDR_REVISION)
#string(STRIP ${XDR_REVISION} XDR_REVISION)
add_definitions(-DXDR_REVISION="${XDR_REVISION}")

# add revision of core itself, using it in /info EP
set (CORE_REVISION $ENV{CORE_REVISION})
if(NOT DEFINED CORE_REVISION)
    execute_process(COMMAND bash -c "(cd ${CMAKE_CURRENT_SOURCE_DIR}/ && git rev-parse HEAD)" OUTPUT_VARIABLE CORE_REVISION)
endif(NOT DEFINED CORE_REVISION)
string(STRIP ${CORE_REVISION} CORE_REVISION)
add_definitions(-DCORE_REVISION="${CORE_REVISION}")

#For Windows
if(${CMAKE_HOST_WIN32})
    add_definitions(
            -D_WINSOCK_DEPRECATED_NO_WARNINGS
            -D_CRT_NONSTDC_NO_DEPRECATE
            -D_CRT_SECURE_NO_WARNINGS
            -D_WIN32_WINNT=0x0501
            -DNOMINMAX
            -DWIN32
            -D_MBCS
    )
endif()

# Definition for compiles.
#if it's gnu compiler
if(${CMAKE_COMPILER_IS_GNUCXX})
    set(COMMON_FLAGS_WARNINGS "-Wall -Wno-unused-command-line-argument -Wno-unused-local-typedef -Wno-unknown-warning-option -Werror=unused-result")

endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(COMMON_FLAGS_WARNINGS "-Wall -Wno-unused-command-line-argument -Qunused-arguments -Wno-unused-local-typedef -Wno-unknown-warning-option -Werror=unused-result")
endif()

if((${CMAKE_COMPILER_IS_GNUCXX}) OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    set(CMAKE_C_FLAGS_DEBUG "-g -O0 ${COMMON_FLAGS_WARNINGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -pthread ${COMMON_FLAGS_CXX_CONF}")
    #For Release
    set(CMAKE_C_FLAGS_RELEASE "-g -O2 ${COMMON_FLAGS_WARNINGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "-g -O2 -pthread ${COMMON_FLAGS_CXX_CONF}")
    #For MaxOptz
    set(CMAKE_C_FLAGS_MAXOPTZ "-g -O3 ${COMMON_FLAGS_WARNINGS}")
    set(CMAKE_CXX_FLAGS_MAXOPTZ "-g -O3 -pthread ${COMMON_FLAGS_CXX_CONF}")
endif()

#MCVS compiler
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP /GS /W4 /Gy /Zc:wchar_t")
    add_definitions(
            /wd4060 /wd4127 /wd4324 /wd4408 /wd4510 /wd4512
            /wd4582 /wd4583 /wd4592 /wd4018 /wd4244 /wd4715
            /wd4267 /wd4005 /wd4100 /wd4307 /Gd
    )
endif()
