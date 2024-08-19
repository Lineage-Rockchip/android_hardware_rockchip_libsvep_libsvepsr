/*
 * Copyright (c) 2021 by Rockchip Electronics Co., Ltd. All Rights Reserved.
 *
 *
 * @Author: Randall Zhuo
 * @Date: 2022-05-09 20:26:55
 * @LastEditors: Randall
 * @LastEditTime: 2022-05-09 20:30:26
 * @Description: TODO
 */

#pragma once

#include "SrGitVersion.h"

#define STR_HELPER(x)           #x
#define STR(x)                  STR_HELPER(x)

#define SVEPSR_VERSION_MAJOR    2
#define SVEPSR_VERSION_MINOR    2
#define SVEPSR_VERSION_REVISION 0
#define SVEPSR_VERSION_SUFFIX   ""

#define SVEPSR_CORE_VERSION                                    \
    "libsvepsr version: " STR(SVEPSR_VERSION_MAJOR) "." STR(   \
        SVEPSR_VERSION_MINOR) "." STR(SVEPSR_VERSION_REVISION) \
        SVEPSR_VERSION_SUFFIX " (" SR_GIT_REVISION "@" SR_BUILD_TIMESTAMP ")"

#define SR_VERSION                                                         \
    "SR-" STR(SVEPSR_VERSION_MAJOR) "." STR(SVEPSR_VERSION_MINOR) "." STR( \
        SVEPSR_VERSION_REVISION)
