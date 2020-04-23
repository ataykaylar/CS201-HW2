#include <iostream>
#include <ctime>
#include <math.h>
#include <cstdlib>

#include<stdlib.h>

using namespace std;

static void swap( int& n1, int& n2 )
{

    int temp = n1;
    n1 = n2;
    n2 = temp;
}

void solution1( int input[], const int n, const int k, int output[] )
{

    int maxIndex, maxValue;
    for ( int i = 0; i < k; i++ )
    {
        maxIndex = i;
        maxValue = input[i];
        for ( int j = i+1; j < n; j++ )
        {
            if ( input[j] >= maxValue )
            {
                maxIndex = j;
                maxValue = input[ j ];
            }
        }
        swap( input[i], input[maxIndex] );
        output[i] = input[i];
    }
}
static int partition( int input[], int p, int r )
{

    int x = input[ r ], i = p - 1;
    for ( int j = p; j < r; j++ )
    {
        if ( input[ j ] >= x )
        {
            i = i + 1;
            swap( input[i], input[j] );
        }
    }
    swap( input[i+1], input[r] );
    return i + 1;
}

static void quickSort( int input[], int p, int r )
{

    int q;
    if ( p < r )
    {
        q = partition( input, p, r );
        quickSort( input, p, q - 1 );
        quickSort( input, q + 1, r );
    }
}

void solution2( int input[], const int n, const int k, int output[] )
{

    quickSort( input, 0, n - 1 );
    for ( int i = 0; i < k; i++ )
    {
        output[i] = input[i];
    }
}

static int partition( int input[], int a, int p, int r )
{

    int x = a, i = p - 1;
    for ( int j = p; j < r; j++ )
    {
        if ( input[ j ] == x )
        {
            swap( input[ j ], input[ r ] );
        }
        if ( input[ j ] >= x )
        {
            i = i + 1;
            swap( input[i], input[j] );
        }
    }
    swap( input[ i + 1 ], input[ r ] );
    return i + 1;
}

static int findMin( int n1, int n2 )
{

    if ( n1 <= n2 )
        return n1;
    else
        return n2;
}

static int select( int input[], int n, int k, int start, int end, int flag )
{
    if ( n <= 5 )
    {
        quickSort( input, start, end );
        return input[ start + k - 1 ];
    }
    int i = start, numGroups = (int) ceil( ( double ) n / 5 ), numElements, j = 0;
    int *medians = new int[numGroups];
    while ( i <= end )
    {
        numElements = findMin( 5, end - i + 1 );
        medians[( i - start ) / 5] = select( input, numElements, (int) ceil( ( double ) numElements / 2 ), i, i + numElements - 1, 1 );
        i = i + 5;
    }
    int M = select( medians, numGroups, (int) ceil( ( double ) numGroups / 2 ), 0, numGroups - 1, 1 );
    delete[] medians;
    if ( flag == 1 )
        return M;
    int q = partition( input, M, start, end );
    int m = q - start + 1;
    if ( k == m )
        return M;
    else if ( k < m )
        return select( input, m - 1, k, start, q - 1, 0 );
    else
        return select( input, end - q, k - m, q + 1, end, 0 );
}



void solution3( int input[], const int n, const int k, int output[] )
{

    select( input, n, k, 0, n - 1, 0 );
    for( int i = 0; i < k; i++ )
        output[i] = input[i];
}



int main()
{
    int arrSize[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000, 130000, 140000,
                     150000, 160000, 170000, 180000, 190000, 200000, 210000,220000, 230000, 240000, 250000, 260000,
                     270000, 280000, 290000, 300000, 310000, 320000, 330000, 340000, 350000,360000,370000,380000,390000,400000,
                     410000,420000,430000,440000, 450000,460000,470000,480000,490000,500000, 510000, 520000, 530000, 540000, 550000,
                     560000, 570000, 580000, 590000, 600000, 610000,620000, 630000, 640000, 650000, 660000,
                     670000, 680000, 690000, 700000, 710000, 720000, 730000, 740000, 750000,760000,770000,780000,790000,800000,
                     810000,820000,830000,840000, 850000,860000,870000,880000,890000,900000,
                     910000,920000,930000,940000, 950000,960000,970000,980000,990000,1000000
                    };

    int array1[] = {1,2,3,4,55,6};
    double duration;
    int* arrTest;
    int* arrSelection1 = new int[100];
    int* arrSelection2 = new int[100];
    int* arrSelection3 = new int[100];
    int* arrTestOut = new int[1000];

    for(int i = 0; i < 100; i++)
    {
        arrTest = new int[arrSize[i]];

        for(int j = 0; j < arrSize[i]; j++)
        {
            arrTest[j] = rand() % 100;
        }

        clock_t startTime = clock();
        solution1(arrTest, arrSize[i], 1000, arrTestOut);
        duration = (1000 * double( clock() - startTime ) / CLOCKS_PER_SEC);
        arrSelection1[i] = duration;
        startTime = clock();
        solution2(arrTest, arrSize[i], 1000, arrTestOut);
        duration = (1000 * double( clock() - startTime ) / CLOCKS_PER_SEC);
        arrSelection2[i] = duration;
        startTime = clock();
        solution3(arrTest, arrSize[i], 1000, arrTestOut);
        duration = (1000 * double( clock() - startTime ) / CLOCKS_PER_SEC);
        arrSelection3[i] = duration;
        cout <<i<<endl;
        delete []arrTest;

    }
    cout <<"Execution times for Solution 1"<<endl;
    for(int i = 0; i < 100; i++)
    {
        cout << arrSelection1[i]<< endl;
    }

    cout <<"Execution times for Solution 2"<<endl;
    for(int i = 0; i < 100; i++)
    {
        cout << arrSelection2[i]<< endl;
    }

    cout <<"Execution times for Solution 3"<<endl;
    for(int i = 0; i < 100; i++)
    {
        cout << arrSelection3[i]<< endl;
    }

    delete[]arrSelection1;
    delete[]arrSelection2;
    delete[]arrSelection3;
    delete[]arrTestOut;
    return 0;
}
