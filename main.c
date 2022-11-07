/*        
             RANGE MINIMUM/MAXIMUM QUERY:
 C code to do range minimum/maximum query using sparse table ->
 *          Time complexity= O(1)  and
 *          Preprocessing time=O(n Log n)
 *          Extra space =O(n Log n)
 */

// including the required header files:
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define MAX 10000//maximum length of the array

// Structure to represent a query range
struct Node
{
    int data; // storing the data of the structure
    struct Node *next;
};

int lookup[MAX][MAX];     // it is going to store index of minimum value in arr[i..j].
int lookup_max[MAX][MAX]; // it is going to store index of maximum value in arr[i..j].


// declaring all the functions used:
void preprocess(int arr[], int size, int n);     // it will fill table lookup[MAX][MAX]
void preprocess_max(int arr[], int size, int n); // it will fill table lookup[MAX][MAX]

int query_min(int arr[], int L, int R, int size); // it will find the minimum of part from an index to the log of the size
int query_max(int arr[], int L, int R, int size); // it will find the maximum of part from an index to the log of the size

void range_minimum_query(int arr[], struct Node *q, int size, int n, int m); // it will compute sum of all queries
void range_maximum_query(int arr[], struct Node *q, int size, int n, int m); // it will compute sum of all queries

void print(int L, int R, int ans);  // it will print the required values
void printm(int L, int R, int ans); // it will print the required values


// Driver code
int main()
{

    int size; // it will store the size of the array
    printf("Enter the size of your array:\n   ");
    scanf("%d", &size);

    int a[size]; // declaring the array
    printf("Enter the data of your array:\n   ");

    // taking input from the user:
    for (int i = 0; i < size; i++)
    {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }

    // the number of times you want to find maximum and minimum of any range:
    int query;
    printf("Enter the number of queries you want to perform:\n   ");
    scanf("%d", &query);

    // making the structures which will store the first and the last index of the range
    struct Node *q;
    struct Node *p;

    // allocating memory:
    q = (struct Node *)malloc(sizeof(struct Node));
    p = (struct Node *)malloc(sizeof(struct Node));

    // taking input of first and last index of the range
    for (int i = 0; i < query; i++)
    {

        printf("\nEnter the first and last index of the range whose maximum and minimum element you want to find:\n   ");
        int l, r;
        scanf("%d %d", &l, &r);

        q->data = l;
        p->data = r;
        q->next = p;//linking the first node with a node
        //just like a linked list

        if(l==r) 
        {
            printf("Minimum of [%d,%d] is %d",l,r,a[l]);
            printf("\nMaximum of [%d,%d] is %d\n",l,r,a[l]);
        }

        else
        {
            // calling the functions:
            range_minimum_query(a, q, size, size, 1);
            range_maximum_query(a, q, size, size, 1);
        }

        printf("\n");
    }

    return 0;
}



//*    CALCULATING MINIMUM VALUE:   *

// filling the lookup[MAX][MAX] table
void preprocess(int arr[], int size, int n)
{

    // Initializing MAX for the intervals with length 1
    for (int i = 0; i < n; i++)
    {
        lookup[i][0] = i;
    }

    // Computing values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++)
    {

        // Computeing minimum values for all intervals with size 2^j
        for (int i = 0; 1 < 2; i++)
        {

            int x = (i + (1 << j) - 1);   // finding the range till which we have to find check
            int y = (i + (1 << (j - 1))); // calculating the index for comparision

            if (x < n)
            {

                // comparing the elements:
                if (arr[lookup[i][j - 1]] < arr[lookup[y][j - 1]])
                {
                    lookup[i][j] = lookup[i][j - 1];
                }

                else
                {
                    lookup[i][j] = lookup[y][j - 1];
                }
            }

            else
            {
                // we will go out of range so we have to break
                break;
            }
        }
    }
}


void range_minimum_query(int arr[], struct Node *q, int size, int n, int m)
{

    // calling the function which will fill the table
    preprocess(arr, size, n);

    // one by one computing sum of all queries
    for (int i = 0; i < m; i++)
    {

        // Left and right boundaries of current range:
        int first_index = q->data;
        int last_index = q->next->data;
        int min = query_min(arr, first_index, last_index, size);

        // Print sum of current query range
        print(first_index, last_index, min);
    }
}


// finding the minimum value:
// or finding the smallest element...
int query_min(int arr[], int L, int R, int size)
{

    int j = log2(R - L + 1); // it will be till log of base 2
    int x = arr[lookup[L][j]];
    int y = arr[lookup[R - (1 << j) + 1][j]];
    // For [2,10], we compare arr[lookup[0][3]] and arr[lookup[3][3]]

    if (x <= y)
    {
        return x; // returning the minimum value
    }

    else
    {
        return y; // returning the minimum value
    }
}


// printing the maximum value of the given range
void print(int L, int R, int ans)
{
    printf("Minimum of [%d,%d] is %d \n", L, R, ans);
}


//*    CALCULATING MAXIMUM VALUE:   *
void range_maximum_query(int arr[], struct Node *q, int size, int n, int m)
{

    // calling the function which will fill the table
    preprocess_max(arr, size, n);

    // one by one computing sum of all queries
    for (int i = 0; i < m; i++)
    {

        // Left and right boundaries of current range:
        int first_index = q->data;
        int last_index = q->next->data;
        int max = query_max(arr, first_index, last_index, size);

        // Print sum of current query range
        printm(first_index, last_index, max);
    }
}


// filling the lookup_max[MAX][MAX] table
void preprocess_max(int arr[], int size, int n)
{

    // Initialize M for the intervals with length 1
    for (int i = 0; i < n; i++)
    {
        lookup_max[i][0] = arr[i];
    }

    // Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++)
    {

        // Computing minimum value for all intervals with size 2^j
        for (int i = 0; 1 < 2; i++)
        {
            int x = (i + (1 << j) - 1);   // finding the range till which we have to find check
            int y = (i + (1 << (j - 1))); // calculating the index for comparision

            if (x < n)
            {

                // comparing the elements:
                if (arr[lookup_max[i][j - 1]] > arr[lookup_max[y][j - 1]])
                {
                    lookup_max[i][j] = lookup_max[i][j - 1];
                }

                else
                {
                    lookup_max[i][j] = lookup_max[y][j - 1];
                }
            }

            else
            {
                // we will go out of range so we have to break
                break;
            }
        }
    }
}


// finding the minimum value:
int query_max(int arr[], int L, int R, int size)
{

    int j = log2(R - L + 1); // it will be till log of base 2
    int x = lookup_max[L][j];
    int y = lookup_max[R - (1 << j) + 1][j];
    // For [2,10], we compare arr[lookup[0][3]] and arr[lookup[3][3]],

    if (x >= y)
    {
        return x; // returning the maximum value
    }

    else
    {
        return y; // returning the maximum value
    }
}


// printing the maximum value of the given range
void printm(int L, int R, int ans)
{
    printf("Maximum of [%d,%d] is %d \n", L, R, ans);
}

//end of the code