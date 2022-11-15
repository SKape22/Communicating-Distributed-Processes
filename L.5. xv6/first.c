#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char const *argv[])
{
    printf(1,"My First User Program on Xv-6.\n");
    int size=getprocessmemory();
    printf(1,"Process memory is %d\n", size);

    int totalsize=getTotalMemoryConsumed();
    printf(1,"Total memory consumed %d\n",totalsize);
    // exit();

    int val=34;
    val--;
    int *a=(int *)malloc(sizeof(int)*2);
    a[0]=1;
    a[1]=0;
    size=getprocessmemory();
    printf(1,"Process memory after malloc is %d\n", size);

    free(a);

    size=getprocessmemory();
    printf(1,"Process memory after free is %d\n", size);    
    exit();
}
