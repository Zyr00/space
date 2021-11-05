#ifndef __UTIL_H__
#define __UTIL_H__

// #include <sys/param.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int collision(int, int, int, int, int, int, int, int);
float randomNumber(const float, const float);

#endif
