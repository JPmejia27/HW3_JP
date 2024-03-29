#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define        size       16 * 1024 * 1024

void swap(int *a,int *b)
{
    int x = *a;
    *a = *b;
    *b = x;
}
int partition(int array[], int start, int end)
{
    //starting pivot is always at last index
    int pivot = array[end];
    //index for index of earliest num found that is > pivot that should be swapped with
    int smaller = start;
    for(int j = start; j < end; j++)
    {
        if(array[j] < pivot)
        {
            swap(&array[smaller],&array[j]);
            smaller++;
        }
    }
    swap(&array[smaller], &array[end]);
    return(smaller);
}
int partition_Random(int array[], int start, int end)
{
    int randPivot = start + rand()%(end - start + 1);
    swap(&array[randPivot],&array[end]);
    
    return (partition(array, start, end));
}
int quickSort(int array[], int lo, int hi)
{
    // you quick sort function goes here
    
    //    printf("Low is %d and high is %d",lo,hi);
    if(lo < hi)
    {
        int pIndex = partition_Random(array,lo,hi);
        
        //bottom half
        quickSort(array, lo, pIndex-1);
        //top half
        quickSort(array,pIndex+1,hi);
    }
    
    return(0);
}
int main(void)
{
    
    int i, j, tmp;
    struct timespec start, stop;
    double exe_time;
    srand(time(NULL));
    int * m = new int[size];
    for(i=0; i<size; i++){
        m[i]=size-i;
    }
    
    
    
    if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
    
    ////////**********Your code goes here***************//
    //first pivot
    int pivotIndex = partition_Random(m,0,size -1);
    //creting threads:
    omp_set_num_threads(2);
    #pragma omp parallel shared(m)
    {
        #pragma omp sections nowait
        {
            #pragma omp section
            {
                quickSort(m,0,pivotIndex-1);
            
            }
            #pragma omp section
            {
                quickSort(m,pivotIndex+1,size -1);
            }
            
        }
    }
    
    
    
    ///////******************************////
    
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}
    exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
    
    for(i=0;i<16;i++) printf("%d ", m[i]);
    //    for(i=0;i<10;i++) printf("%d ", m[i]);
    printf("\nExecution time = %f sec\n",  exe_time);
}
