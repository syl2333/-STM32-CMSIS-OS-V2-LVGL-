#ifndef __MEM_H__
#define __MEM_H__

#include "stdint.h"

void* mpu_memset(void* dst,int val, uint32_t count);
int mpu_memcmp(const void *s1, const void *s2, int len);
void *mpu_memcpy_byte(void *dst, const void *src, int n);

#define memset mpu_memset
#define memcmp mpu_memcmp
#define memcpy mpu_memcpy_byte
#endif
