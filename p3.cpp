#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <fstream>
#include <vector>

using namespace std;


#define h  800
#define w  800

#define input_file  "input.raw"
#define output_file "output.raw"


unsigned char meanFunc(char sum, int size,unsigned char currMean)
{
    if(size == 0)
    {
        return currMean;
    }
    else
    {
        char mean = sum/size;
        return mean;
    }
};

short minFunct(short value1, short value2)
{
    if(value1 > value2)
    {
        return value2;
    }
    else
    {
        return value1;
    }
};

short closestDistanceFunc(unsigned char element, vector<pair <unsigned char, vector<int> > > clusterVects)
{
    short diff1 = abs(element - clusterVects[0].first);
    short diff2 = abs(element - clusterVects[1].first);
    short diff3 = abs(element - clusterVects[2].first);
    short diff4 = abs(element - clusterVects[3].first);
    short diff5 = abs(element - clusterVects[4].first);
    short diff6 = abs(element - clusterVects[5].first);
    
    short min = minFunct(diff1,diff2);
    min = minFunct(min,diff3);
    min = minFunct(min,diff4);
    min = minFunct(min,diff5);
    min = minFunct(min,diff6);
    
    return (min);
    
};

int main(int argc, char** argv)
{
    //int numThreads = atoi(argv[1]);
    int numThreads = 3;
    struct timespec start, stop;
    double time;
    
    int i;
    FILE *fp;
    
    unsigned char *a = new unsigned char[h*w];
//    unsigned char *a = (unsigned char*) malloc (sizeof(unsigned char)*h*w);

    // the matrix is stored in a linear array in row major fashion
    if (!(fp=fopen(input_file, "rb"))) {
        printf("can not opern file\n");
        return 1;
    }
    fread(a, sizeof(unsigned char), w*h, fp);
    fclose(fp);
    
    //c:
//    ifstream input(input_file, ios::binary);
//    input.read((char*) &a[0], h*w);
//    input.close()
    
       printf("sup");
    unsigned char meanArray [6] = {0,60,100,125,190,255};
    //vectors of pairs for each cluster the index of each corresponds to according cluster:
    vector<pair <unsigned char, vector<int> > > clusterVects;
    for(int i = 0; i < 6; i++)
    {
        vector<int> vect;
        unsigned char mean = meanArray[i];
        pair<unsigned char,vector<int> > myPair;
        myPair.first = mean;
        myPair.second = vect;
        clusterVects.push_back(myPair);
    }
    

    // measure the start time here
    if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
//     omp_set_num_threads(numThreads);
    
    
    //repeat steps 2 and 3 50 times
    for(int n = 0; n < 1; n++)
    {
        //clear vector each time:
        for(int f = 0; f < clusterVects.size(); f++)
        {
            clusterVects[f].second.clear();
        }
        //step 2
        for(int i = 0; i < h*w; i++)
        {
            unsigned char currValue = a[i];
            short closestDistance = closestDistanceFunc(currValue,clusterVects);
            for(int l = 0; l < clusterVects.size(); l++)
            {
                short distPlusVal = closestDistance + currValue;
                short distMinusVal = closestDistance - currValue;
                if(distPlusVal == clusterVects[l].first || distMinusVal == clusterVects[l].first)
                {
                    //found closest mean: clusterVects[l].first
                    //now add the index of this value to corresponding cluserVector
                    clusterVects[l].second.push_back(i);
                }
//                if(closestDistance == clusterVects[l].first)
//                {
//                    //found closest mean: clusterVects[l].first
//                    //now add the index of this value to corresponding cluserVector
//                    clusterVects[l].second.push_back(i);
//                }
            }
        }
        
        //step3:
        //for each vector:
        for(int j = 0; j < clusterVects.size(); j++)
        {
            //clear sum after evry vector
            int sum = 0;
            //for each index in each vector
            for(int m = 0; m < clusterVects[j].second.size();m++ )
            {
                int index = clusterVects[j].second[m];
                sum += a[index];
            }
            //caluclating mean and changing mean of cluster only if size isnt 0
            if(clusterVects[j].second.size() != 0)
            {
                clusterVects[j].first = sum/clusterVects[j].second.size();
            }
            unsigned char check = clusterVects[j].first;
        }
        
    }
    
    //assigning cluster back to array a[]
    for(int b = 0; b < clusterVects.size(); b++)
    {
        for(int c = 0; c < clusterVects[b].second.size(); b++)
        {
            int index = clusterVects[b].second[c];
            a[index] = clusterVects[b].first;
        }
        
    }
    
    // measure the end time here
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}
    time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
    
    // print out the execution time here
    printf("Execution time = %f sec\n", time);
    
    
    if (!(fp=fopen(output_file,"wb"))) {
        printf("can not opern file\n");
        return 1;
    }
    
//    fwrite(a.data(), sizeof(unsigned char), WIDTH * HEIGHT, fp);
    fwrite(a, sizeof(unsigned char),w*h, fp);
    fclose(fp);
    
    return 0;

}

