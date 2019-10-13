#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define        size       16*1024*1024

void swap(int &a,int &b)
{
//    std::cout << "A: " << a << " B: " << b << std::endl;
    int x = a;
    a = b;
    b = x;
//    std::cout << "A: " << a << " B: " << b << std::endl;
}
int partition(int array[], int start, int end)
{
    //starting pivot is always at last index
    int pivot = array[end];
    //index for index of earliest num found that is > pivot that should be swapped with
    int smaller = start - 1;
    for(int j = 0; j < end; j++)
    {
        if(array[j] <= pivot)
        {
            smaller++;
            swap(array[smaller],array[j);
        }
    }
}
void quickSort(int *array, int lo, int hi)
{
    // you quick sort function goes here
    if(lo < hi)
    {
        int pIndex = partition(array,lo,hi);
        
        //bottom half
        quickSort(array, lo, pIndex-1);
        //top half
        quickSort(array,pIndex+1,hi);
    }
    
}
int main(void)
  {

    int i, j, tmp;
    struct timespec start, stop;
    double exe_time;
    srand(time(NULL));
    int* m = new int[size];
    for(i=0; i<size; i++){
        m[i]=size-i;
    }
                                      
    quickSort(m,m[0],m[size -1]);
                                      
    if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
    ////////**********Your code goes here***************//
    
    
    
    ///////******************************////
    
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}
    exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
    
    for(i=0;i<16;i++) printf("%d ", m[i]);
    printf("\nExecution time = %f sec\n",  exe_time);
}
