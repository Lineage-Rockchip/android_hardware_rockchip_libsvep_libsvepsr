
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendor_storage_v1.h"
#include "vendor_storage_v2.h"

#define SR_VENDOR_STORAGE_MAX_LEN 2048

int main(int argc, char **argv)
{
    if (argc != 4 && argc != 3)
    {
        printf("Usage : vendor_storage id len [code] \n");
        printf("\tConfig Code : vendor_storage 17 50 "
               "71581714-9736-4EEE-C029-B65E54280A91 \n");
        printf("\tRead Code   : vendor_storage 17 50 \n");
        return -1;
    }

    // svep_vendor_storage_init_v2 主要是由于Android 13/14 适配GKI版本添加
    // 目前仅支持UFS版本的初始化
    int ret = svep_vendor_storage_init_v2();
    if (ret == 0)
    {
        if (argc == 4)
        {
            uint32 id  = atoi(argv[1]);
            uint32 len = atoi(argv[2]);
            char *data = argv[3];

            if (len > SR_VENDOR_STORAGE_MAX_LEN)
            {
                fprintf(
                    stderr,
                    "Error writing to vendor storage with ID %d, input len=%d "
                    "support_max_len=%d\n",
                    id, len, SR_VENDOR_STORAGE_MAX_LEN);
                return -1;
            }

            char write_buffer[SR_VENDOR_STORAGE_MAX_LEN]; // Assume maximum data
                                                          // length for
                                                          // simplicity
            memset(write_buffer, 0x0, SR_VENDOR_STORAGE_MAX_LEN * sizeof(char));
            memcpy(write_buffer, data, strlen(data));

            // 写入数据到vendor存储
            if (vendor_storage_write(id, write_buffer, len) < 0)
            { // Include null-terminator
                fprintf(stderr, "Error writing to vendor storage with ID %d\n",
                        id);
                return -1;
            }
            printf("V2 Write Success:  id=%d len=%d code = %s\n", id, len,
                   data);
            char read_buffer[2048]; // Assume maximum data length for simplicity
            // 从vendor存储读取数据
            if (vendor_storage_read(id, read_buffer, len) < 0)
            {
                fprintf(stderr,
                        "Error reading from vendor storage with ID %d\n", id);
                return -1;
            }
            printf("V2 Read Success:  id=%d len=%d code = %s\n", id, len,
                   read_buffer);
        }

        if (argc == 3)
        {
            uint32 id  = atoi(argv[1]);
            uint32 len = atoi(argv[2]);

            char read_buffer[2048]; // Assume maximum data length for simplicity
            // 从vendor存储读取数据
            if (vendor_storage_read(id, read_buffer, len) < 0)
            {
                fprintf(stderr,
                        "Error reading from vendor storage with ID %d\n", id);
                return -1;
            }
            printf("V2 Read  Success:  id=%d len=%d code = %s\n", id, len,
                   read_buffer);
        }
        return 0;
    }
    else
    {
        // printf("svep_vendor_storage_init_v2 ufs init fail, try to call"
        //        "vendor_storage_init_v1 by emmc.\n");
        if (argc == 4)
        {
            u16 id     = atoi(argv[1]);
            u16 len    = atoi(argv[2]);
            char *data = argv[3];

            // 写入数据到vendor存储
            ret = vendor_storage_write_test(id, len, data);
            if (ret < 0)
            { // Include null-terminator
                fprintf(stderr,
                        "EMMC: Error writing to vendor storage with ID %d, "
                        "ret=%d\n",
                        id, ret);
                return -1;
            }
            printf("V1 Write Success:  id=%d len=%d code = %s\n", id, len,
                   data);

            char read_buffer[2048] = {0};
            ; // Assume maximum data length for simplicity
            // 从vendor存储读取数据
            ret = vendor_storage_read_test(id, len, read_buffer);
            if (ret < 0)
            {
                fprintf(stderr,
                        "EMMC: Error reading from vendor storage with ID %d, "
                        "ret=%d\n",
                        id, ret);
                return -1;
            }

            printf("V1 Read  Success:  id=%d len=%d code = %s\n", id, len,
                   read_buffer);
        }

        if (argc == 3)
        {
            u16 id                 = atoi(argv[1]);
            u16 len                = atoi(argv[2]);

            char read_buffer[2048] = {
                0}; // Assume maximum data length for simplicity
            // 从vendor存储读取数据
            ret = vendor_storage_read_test(id, len, read_buffer);
            if (ret < 0)
            {
                fprintf(stderr,
                        "V1 Error reading from vendor storage with ID %d, "
                        "ret=%d\n",
                        id, ret);
                return -1;
            }

            printf("V1 Read Success:  id=%d len=%d code = %s (EMMC)\n", id, len,
                   read_buffer);
            ;
        }
    }

    return 0;
}
