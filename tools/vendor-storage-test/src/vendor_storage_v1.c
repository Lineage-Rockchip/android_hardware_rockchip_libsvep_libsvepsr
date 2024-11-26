
#define LOG_TAG "SvepAuth"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "vendor_storage_v1.h"

#define VENDOR_REQ_TAG  0x56524551
#define VENDOR_READ_IO  _IOW('v', 0x01, unsigned int)

#define VENDOR_WRITE_IO _IOW('v', 0x02, unsigned int)

struct rk_vendor_req
{
    u32 tag;
    u16 id;
    u16 len;
    u8 data[1];
};

int vendor_storage_read_test(u16 id, u16 len, void *read_buffer)
{
    int ret, sys_fd;
    u8 p_buf[2048] = {0}; /* malloc req buffer or used extern buffer */
    struct rk_vendor_req *req;
    req    = (struct rk_vendor_req *)p_buf;
    sys_fd = open("/dev/vendor_storage", O_RDONLY, 0);
    if (sys_fd < 0)
    {
        printf("/dev/vendor_storage open fail, error=%s\n", strerror(errno));
        return -1;
    }
    req->tag = VENDOR_REQ_TAG;
    req->id  = id;
    req->len = len; /* max read length to read*/
    ret      = ioctl(sys_fd, VENDOR_READ_IO, req);
    /* return req->len is the real data length stored in the NV-storage */
    if (ret)
    {
        printf("vendor read fail, error=%s\n", strerror(errno));
        return -1;
    }
    memcpy(read_buffer, req->data, len);
    close(sys_fd);
    return 0;
}

int vendor_storage_write_test(u16 id, u16 len, const char *str)
{
    u32 i;
    int ret, sys_fd;
    u8 p_buf[2048] = {0}; /* malloc req buffer or used extern buffer */
    struct rk_vendor_req *req;
    req    = (struct rk_vendor_req *)p_buf;
    sys_fd = open("/dev/vendor_storage", O_RDWR, 0);
    if (sys_fd < 0)
    {
        printf("/dev/vendor_storage open fail, error=%s\n", strerror(errno));
        return -1;
    }
    req->tag = VENDOR_REQ_TAG;
    req->id  = id;
    req->len = len; /* data len */

    for (i = 0; i < strlen(str); i++) req->data[i] = str[i];

    ret = ioctl(sys_fd, VENDOR_WRITE_IO, req);
    if (ret)
    {
        printf("vendor write fail, error=%s\n", strerror(errno));
        return -1;
    }
    close(sys_fd);
    return 0;
}

#if 0
int main(int argc, char **argv)
{
    if (argc != 4 && argc != 3)
    {
        printf("Error argc=%d\n", argc);
        printf("Usage : vendor_storage id len [code] \n");
        printf("\tConfig Code : vendor_storage 17 50 "
               "71581714-9736-4EEE-C029-B65E54280A91 \n");
        printf("\tRead Code   : vendor_storage 17 50 \n");
        return -1;
    }

    if (argc == 4)
    {
        u16 id  = atoi(argv[1]);
        u16 len = atoi(argv[2]);

        vendor_storage_write_test(id, len, argv[3]);
        vendor_storage_read_test(id, len);
    }

    if (argc == 3)
    {
        u16 id  = atoi(argv[1]);
        u16 len = atoi(argv[2]);

        vendor_storage_read_test(id, len);
    }
    return 0;
}
#endif
