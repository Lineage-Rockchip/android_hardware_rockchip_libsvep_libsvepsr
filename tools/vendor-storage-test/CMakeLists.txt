# set minimum cmake version
cmake_minimum_required(VERSION 3.5)

# project name and language
project(vendor-storage-test)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O2")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(ENABLE_ASAN)
  message(STATUS "BUILD WITH ADDRESS SANTITIZE")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
  set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
else()
  if(CMAKE_C_COMPILER MATCHES "aarch64")
    set(LIB_ARCH aarch64)
  else()
    set(LIB_ARCH armhf)
  endif()
endif()

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(sr_SRCS
    src/main.cpp
    src/vendor_storage_v1.c
    src/vendor_storage_v2.c)

# demo
add_executable(vendor-storage-test ${sr_SRCS})

if(ANDROID)
  target_link_libraries(vendor-storage-test log z)
else()
  target_link_libraries(vendor-storage-test pthread)
endif()

# install target and libraries
if(CMAKE_SYSTEM_NAME STREQUAL "Android")
  INSTALL(TARGETS vendor-storage-test DESTINATION bin/${CMAKE_SYSTEM_NAME}/${TARGET_SOC}/${CMAKE_ANDROID_ARCH_ABI})
else()
  INSTALL(TARGETS vendor-storage-test DESTINATION bin/${CMAKE_SYSTEM_NAME}/${TARGET_SOC}/${LIB_ARCH})
endif()
