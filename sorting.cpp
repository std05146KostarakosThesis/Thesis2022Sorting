/**
 * Performance test for sorting algorithms
 * with profiler to record computing time
**/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define BASE 10

using namespace std;
 
long arraySize = 1000;
const long max_arraySize = 300001;
const int bSize = 200000;
int data[max_arraySize];
int temp[max_arraySize];


void load_data()
{
	srand(time(NULL));
	for(long k = 0; k < arraySize; k++)
	{
		long randNumber = rand();
		randNumber *= RAND_MAX;
		randNumber += rand();
		randNumber %= 200000;
		data[k] = randNumber;
	}

}


void mod_bubble_sort()
{
    int temp, flag = 0;
    for(long i = 0; i < arraySize; i++)
    {
        for(long j = 0; j < arraySize-i-1; j++)
        {
            if (data[j] > data[j+1])
            {
                temp        = data[j];
                data[j]     = data[j+1];
                data[j+1]   = temp;
				flag = 1;
            }
        }
		if(flag == 0)
		{
			break;
		}
    }
}
 
void insertion_sort()
{
    int temp;
    for(long i = 1; i < arraySize; i++)
    {
        temp = data[i];
        long j;
        for(j = i-1; j >= 0 && data[j] > temp; j--)
        {
            data[j+1] = data[j];
        }
        data[j+1] = temp;
    }
}

void selection_sort()
{
	for(long i=0; i<arraySize-1; i++)
	{
		int iMin = i;
		for(int j=i+1; j<arraySize; j++)
		{
			if(data[j] < data[iMin])
			{
				iMin=j;
			}
		}
		int temp = data[i];
		data[i] = data[iMin];
		data[iMin] = temp;
	}
}

int partition (int start, int end)
{
	int pivot = data[end];
	int partitionIndex = start;
	for(int i = start; i < end; i++)
	{
		if(data[i] <= pivot)
		{
			swap(data[i], data[partitionIndex]);
			partitionIndex++;
		}
	}
	swap(data[partitionIndex], data[end]);
	return partitionIndex;
}

void quick_sort (int start, int end)
{
	if(start < end)
	{
		int partitionIndex = partition(start,end);
		quick_sort(start, partitionIndex-1);
		quick_sort(partitionIndex+1, end);
	}
}


void merge(int low, int pivot, int high)
{
    int h,i,j,k;
    h = low;
    i = low;
    j = pivot+1;

    while((h <= pivot)&&(j <= high))
    {
        if(data[h] <= data[j])
        {
            temp[i] = data[h];
            h++;
        }
        else
        {
            temp[i] = data[j];
            j++;
        }
        i++;
    }
    if(h > pivot)
    {
        for(k = j; k <= high; k++)
        {
            temp[i] = data[k];
            i++;
        }
    }
    else
    {
        for(k = h; k <= pivot; k++)
        {
            temp[i] = data[k];
            i++;
        }
    }
    for(k = low; k<=high; k++)
	{
		data[k] = temp[k];
	}
}

void merge_sort(int low, int high)
{
    int pivot;
    if(low < high)
    {
        pivot = (low+high)/2;
        merge_sort(low,pivot);
        merge_sort(pivot+1,high);
        merge(low,pivot,high);
    }
}

void shift_down(int low, int high)
{
    int root = low;
    while ((root*2)+1 <= high)
    {
        int leftChild = (root * 2) + 1;
        int rightChild = leftChild + 1;
        int swapIndex = root;
        if (data[swapIndex] < data[leftChild])
        {
            swapIndex = leftChild;
        }
        if ((rightChild <= high) && (data[swapIndex] < data[rightChild]))
        {
            swapIndex = rightChild;
        }
        if (swapIndex != root)
        {
            int temp = data[root];
            data[root] = data[swapIndex];
            data[swapIndex] = temp;
            root = swapIndex;
        }
        else
        {
            break;
        }
    }
    return;
}

void heapify(int low, int high)
{
    int midIndex = (high - low -1)/2;
    while (midIndex >= 0)
    {
        shift_down(midIndex, high);
        --midIndex;
    }
    return;
}

void heap_sort(int size)
{
	heapify(0, size-1);
    int high = size - 1;
    while (high > 0)
    {
        int temp = data[high];
        data[high] = data[0];
        data[0] = temp;
        --high;
        shift_down(0, high);
    }
    return;
}


int main()
{
    double startTime, endTime;
	ofstream outputFile;
	outputFile.open("timeBasedDataInteger.txt");
	outputFile << "Profiling Execution time for different Sorting Algorithms using Integers" << '\n';
	outputFile << "=======================================================================" << '\n';
 
    for (arraySize = 1000; arraySize < max_arraySize; )
    {
        outputFile << "\nArray Size\t: " << arraySize << '\n';
		cout << "\nArray Size\t: " << arraySize << '\n';
 
		load_data();
        startTime = clock();
        mod_bubble_sort();
        endTime = clock();
        outputFile << "Mod Bubble Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Mod Bubble Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";

		load_data();
        startTime = clock();
        selection_sort();
        endTime = clock();
        outputFile << "Selection Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Selection Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";

        load_data();
        startTime = clock();
        insertion_sort();
        endTime = clock();
        outputFile << "Insertion Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Insertion Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		
		load_data();
		startTime = clock();
		quick_sort(0, arraySize-1);
		endTime = clock();
		outputFile << "Quick Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Quick Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";

		
		load_data();
		startTime = clock();
        merge_sort(0, arraySize-1);
        endTime = clock();
        outputFile << "Merge Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Merge Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";

		load_data();
		startTime = clock();
        heap_sort(arraySize);
        endTime = clock();
        outputFile << "Heap Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Heap Sort\t: " << (endTime - startTime)/CLK_TCK << " sec\n";

		
		switch (arraySize)
        {
        case 1000 :
            arraySize = 2000;
            break;
		case 2000 :
            arraySize = 3000;
			break;
		case 3000 :
            arraySize = 5000;
			break;
        case 5000 :
            arraySize = 10000;
            break;
        case 10000 :
            arraySize = 20000;
            break;
		case 20000 :
            arraySize = 30000;
			break;
		case 30000 :
			arraySize = 50000;
			break;
        case 50000 :
            arraySize = 100000;
            break;
        case 100000 :
            arraySize = 200000;
            break;
        case 200000 :
            arraySize = 300000;
            break;
        case 300000 :
            arraySize = 400000;
            break;
        }
    }
	outputFile.close();
    return 0;
}

	
