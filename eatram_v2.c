#include<stdio.h>
#include<stdlib.h>
#include<sys/sysinfo.h>

typedef struct memoryNode {
    struct memoryNode *next;
    int *pdata;
} mnode;

#define MB_BLOCK        (1024 * 1024)
#define KB_BLOCK        (1024)

#define MEMTHRESHOLD    300 * MB_BLOCK

int main( int argc, char *argv[])
{
    int i;
    int total_alloc = 0;
    mnode *head = malloc(sizeof(mnode));
    mnode *temp = NULL;
    struct sysinfo msys;
    int threshold;

    if( argc == 2 )
        {
        threshold = atoi(*(argv + 1)) * MB_BLOCK;
        }
    else
        {
        threshold = MEMTHRESHOLD;
        }
    sysinfo(&msys);

    head->next=NULL;
    head->pdata=NULL;

    while( msys.freeram > threshold ) {
        temp = malloc(sizeof(mnode));
        temp->pdata = malloc( 1 * MB_BLOCK * sizeof(int));
        for( i = 0; i < 1* MB_BLOCK; i++ ) {
            *(temp->pdata+i) = i;
        }
        total_alloc += 1 * MB_BLOCK;
        temp->next = head;
        head = temp;
        sysinfo(&msys);
        printf("Remain freemem = %dMB\n", msys.freeram / MB_BLOCK );
    }

    printf("Finish allocate %d MB, halt\n", total_alloc /MB_BLOCK);

    while(1)
    {
        sleep(100);
    }

    return 0;
}
