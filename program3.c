/* COP 3502C Programming Assignment3 This program is written by: Benjamin Osante */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct
{
    int x;
    int y;

}Coordinates;

Coordinates myLocation;


int main()
{

    FILE* fp = fopen("assignment3input.txt", "r");


    if(fp == NULL)
    {
        printf("Unable to open file\n");
    }
    else
    {

        int n;
        int s;
        int t;
        int i;


        FILE* outFilepoint = fopen("out.txt", "w");

        Coordinates points[20];
        Coordinates key;


        fscanf(fp, "%d %d %d %d %d",&myLocation.x, &myLocation.y, &n, &s, &t);

        ReadData(fp, points, n);
        sort(points, n, t);

        // print the sorted Coordinates to output.txt
        for(i=0;i<n;i++)
        {
            fprintf(outFilepoint, "%d %d\n",points[i].x, points[i].y);
        }

        //  search for points and print the result to output.txt
        for(i=0;i<s;i++)
        {
            fscanf(fp, "%d %d",&key.x, &key.y);

            int rank = binarySearch(points, n, key);

            if(rank == -1)
                fprintf(outFilepoint,"%d %d not found\n",key.x,key.y);
            else
                fprintf(outFilepoint,"%d %d found at rank %d\n",key.x,key.y, rank+1);

        }


        fclose(fp);
        fclose(outFilepoint);
    }

    return 0;
}

// reads n Coordinates from input file into the array
void ReadData(FILE* file, Coordinates points[], int n)
{
    int i=0;

    while(i < n)
    {
    fscanf(file, "%d %d",&points[i].x, &points[i].y);
    i++;
    }
}

//Compare Coordinates ptrP1 and ptrP2

int compareTo(Coordinates *ptrP1, Coordinates *ptrP2)
{
    // Distance of ptrP1 and ptrP2 from myLocation
    float distanceP1 = sqrt((float)pow(myLocation.x-ptrP1->x,2) +
                            (float)pow(myLocation.y-ptrP1->y, 2));

    float distanceP2 = sqrt((float)pow(myLocation.x-ptrP2->x,2) +
                            (float)pow(myLocation.y-ptrP2->y, 2));


    if(distanceP1 < distanceP2)
        return -1;

    else if(distanceP1 > distanceP2)
        return 1;

    else
    {
     if(ptrP1->x < ptrP2->x)
        return -1;

    else if(ptrP1->x > ptrP2->x)
        return 1;

    else
    {
        if(ptrP1->y < ptrP2->y)
            return -1;

        else if(ptrP1->y > ptrP2->y)
            return 1;

        else
            return 0;
        }
    }
}

// sort the array of Coordinates
void sort(Coordinates points[], int n, int t)
{
    // insertionSort or MergeSort
    if(n <= t)
    {
        insertionSort(points, 0, n-1);
    }
    else
        mergeSort(points, 0, n-1, t);
}


//  insertion sort Function
void insertionSort(Coordinates points[], int low, int high)
{
    int i;
    int j;
    Coordinates key;

    for(i=low+1;i<=high;i++)
    {
        j = i-1;
        key = points[i];

        while(j>=low && compareTo(&key, &points[j]) < 0)
        {
        points[j+1] = points[j];
        j--;
        }

        points[j+1] = key;
    }
}

// Sort the array using merge sort
void mergeSort(Coordinates points[], int start, int ending, int t)
{
    int n = (ending-start)+1;

    if(n <= t)
    {
    insertionSort(points, start, ending);
    }
    else
    {

    int mid = (start+ending)/2;

    mergeSort(points, start, mid, t);
    mergeSort(points, mid+1, ending, t);
    merge(points, start, mid, ending);
    }
}

//merge the sorted sub arrays
void merge(Coordinates points[], int start, int mid, int ending)
{

    Coordinates temp[ending-start+1];


    int i = start;
    int j = mid+1;
    int k=0;

    // loop through subarray
    while(i <= mid && j <= ending)
    {
        if(compareTo(&points[i], &points[j]) <= 0)
        {
        temp[k] = points[i];
        i++;
        }
        else
        {
        temp[k] = points[j];
        j++;
        }

        k++;
    }


    while(i <= mid)
    {
    temp[k] = points[i];
    k++;
    i++;
    }


    while(j <= ending)
    {
    temp[k] = points[j];
    k++;
    j++;
    }


    for(i=start, k=0;i<=ending;i++, k++)
    {
    points[i] = temp[k];
    }
}


// Binary Search function
int binarySearch(Coordinates points[], int n, Coordinates key)
{

    int low = 0;
    int high = n-1;


    while(low <= high)
    {

    int mid = (low+high)/2;

    float distance;
    distance = compareTo(&key, &points[mid]);

    if(distance == 0)
        return mid;

    else if(distance < 0)
        high = mid-1;

    else
        low = mid+1;
    }

    return -1;
}


