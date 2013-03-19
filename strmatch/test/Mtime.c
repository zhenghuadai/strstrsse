#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include"util.h"
#include "rdtsc.h"
void Mtime(_U64* u)
{
    int* res = (int*) u;
    //rdtsc(u->low, u->high);
    rdtsc(res[0],res[1]);
}

double Mdifftime(_U64 start, _U64 end)
{
    return (double) (end._u64 - start._u64);
}
