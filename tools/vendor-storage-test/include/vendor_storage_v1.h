/*
 *
 * Copyright 2023 Rockchip Electronics S.LSI Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VENDOR_STORAGE_V1_H_
#define VENDOR_STORAGE_V1_H_
// 21 – 31 RK reserved for future use
#ifdef __cplusplus
extern "C"
{
#endif

    typedef unsigned char u8;
    typedef unsigned short u16;
    typedef unsigned int u32;
    typedef signed char s8;
    typedef signed short s16;
    typedef signed int s32;
    int vendor_storage_write_test(u16 id, u16 len, const char *str);
    int vendor_storage_read_test(u16 id, u16 len, void *read_buffer);

#ifdef __cplusplus
}
#endif
#endif
