#include "mem.h"

void* mpu_memset(void* dst,int val, uint32_t count)
{
    void* ret = dst;
    while(count--)
    {
        *(char*)dst = (char)val;
        dst = (char*)dst + 1; //移动一个字节
    }
    return ret;
}

int mpu_memcmp(const void *s1, const void *s2, int len)
{
    unsigned char *p = (unsigned char *)s1;
    unsigned char *q = (unsigned char *)s2;
    int charCompareStatus = 0;
    //If both pointer pointing same memory block
    if (s1 == s2)
    {
        return charCompareStatus;
    }
    while (len > 0)
    {
        if (*p != *q)
        {  //compare the mismatching character
            charCompareStatus = (*p >*q)?1:-1;
            break;
        }
        len--;
        p++;
        q++;
    }
    return charCompareStatus;
}
void *mpu_memcpy_byte(void *dst, const void *src, int n)
{
    if (dst == 0 || src == 0 || n <= 0)
        return 0;
    char * pdst = (char *)dst;
    char * psrc = (char *)src;

    if (pdst > psrc && pdst < psrc + n)
    {
        pdst = pdst + n - 1;
        psrc = psrc + n - 1;
        while (n--)
            *pdst-- = *psrc--;
    }
    else
    {
        while (n--)
            *pdst++ = *psrc++;
    }
    return dst;
}