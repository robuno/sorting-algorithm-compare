#include <iostream>
#include <vector>
#include<ctime>

using namespace std;
/**
* Sorting Algorithms Implementation
* Unat Teksen
* 20181701048
* Computer Engineering
* 23.05.2021
*
* This is the sorting algorithms comparison application that creates
* two same vectors in length 1000, and two same vectors in length 1000.
* Then, it sorts these arrays and calculates the number of comparisons for
* both each algorithm. Finally, prints the number of comparisons to the console.
*
* There is main function in this file and all commands will be executed in there.
*/



/** Insertion Sort Algorithm Function
 * This is the insertion sort algorithm to sort the vector in
 * ascending order (lowest element is the first element of vector).
 *
 * @tparam Comparable is the type of the vector.
 * @param a is the name of the vector.
 * @param count_insert1 the number of comparisons.
 */
template <typename Comparable>
void insertionSort( vector<Comparable> & a , int&count_insert1 ) {

    for (int p = 1; p < a.size(); ++p) { // check unsorted part of the vector
        Comparable tmp = std::move(a[p]); // move and assign unsorted first element to temporary value

        if (p != 0) {
            count_insert1 += 1; // increase counter
        }

        int j; // assign new index to iterate on sorted part
        for (j = p; j > 0 && tmp < a[j - 1]; --j) { // check sorted part of the vector
            if (j > 1) { // ensure that checking in vector
                count_insert1 += 1; // increase counter
            }
            a[j] = std::move(a[j - 1]); // move smaller element to the front
        }

        a[j] = std::move(tmp); // swap largest element with smaller element

    }
}

/**Merge Function
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * @tparam Comparable is the type of the vector.
 * @param a is an array of Comparable items.
 * @param tmpArray is an array to place the merged result.
 * @param leftPos is the left-most index of the subarray.
 * @param rightPos is the index of the start of the second half.
 * @param rightEnd is the right-most index of the subarray.
 * @param count_merge1 is the number of comparisons.
 */
template <typename Comparable>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
            int leftPos, int rightPos, int rightEnd,int& count_merge1)
{

    int leftEnd = rightPos - 1; // assigning the end of the first half
    int tmpPos = leftPos; // assign left most index to temporary value
    int numElements = rightEnd - leftPos + 1; // number of elements in vector

// Main loop
    while( leftPos <= leftEnd && rightPos <= rightEnd ) // divide all array until
    {
        if( a[ leftPos ] <= a[ rightPos ] ) //
            tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] ); // swap the largest element with smallest one
        else
            tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] ); // swap the largest element with smallest one
        count_merge1+=1; // increase counter
    }

    while( leftPos <= leftEnd ) // Copy rest of first half
        tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] ); // swap the largest element with smallest one
    while( rightPos <= rightEnd ) // Copy rest of right half
        tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] ); // swap the largest element with smallest one

    for( int i = 0; i < numElements; ++i, --rightEnd ) // Copy tmpArray back
        a[ rightEnd ] = std::move( tmpArray[ rightEnd ] ); // swap the largest element with smallest one

}

/** MergeSort Function
 * Internal method that makes recursive calls.
 * a is an array of Comparable items
 * @tparam Comparable is the type of the vector.
 * @param a is an array of Comparable items.
 * @param tmpArray is an array to place the merged result.
 * @param left is the left-most index of the subarray.
 * @param right is the right-most index of the subarray.
 * @param count_merge1 is the number of comparisons.
 */
template<typename Comparable>
void mergeSort(vector<Comparable> & a, vector<Comparable> &
tmpArray, int left, int right,int& count_merge1) {
    if (left < right) {
        int center = (left + right) / 2; // assign the center index of vector

        mergeSort(a, tmpArray, left, center, count_merge1); // recursive call for first half of the vector
        mergeSort(a, tmpArray, center + 1, right, count_merge1); // recursive call for second half of the vector
        merge(a, tmpArray, left, center + 1, right, count_merge1); // merge parts of vector
    }
}

/** Merge Sort Function
 * Merge sort driver function for first call.
 *
 * @tparam Comparable is the type of the vector.
 * @param a is an array of Comparable items.
 * @param count_merge1 is the number of comparisons.
 */
template <typename Comparable>
void mergeSort( vector<Comparable> & a,int& count_merge1)
{
    vector<Comparable> tmpArray( a.size( ) ); // create temporary vector to be assigned by exist vector
    mergeSort( a, tmpArray, 0, a.size( ) - 1,count_merge1); // call mergesort function for whole vector
}

/** Main function
 * This is the main function that creates 4 vectors with 1000 and 10000 random values.
 * Then, it calls sort algorithms for these vectors and prints out the number of
 * comparisons to the console.
 * @return nothing
 */
int main() {
    int count_merge = 0; // number of comparisons for merge sort
    int count_insert = 0; // number of comparisons for insertion sort
    vector<int> v1; // declaration of vector for merge sort


    srand(time(nullptr)); // create random values
    for(int i=0; i <1000; i++) // iterate 1000 random values
    {
        v1.push_back(rand()); // place random values to the vector
    }

    vector<int> v1_copy = v1; // copy existing vector

    mergeSort(v1,count_merge); // sort vector v1 with merge algorithm
    cout << "Number of comparisons in MERGE SORT for 1000 elements vector: " << count_merge << endl; // prompt
    insertionSort(v1_copy, count_insert); // sort vector v1_copy with insertion algorithm
    cout << "Number of comparisons in INSERTION SORT for 1000 elements vector: " << count_insert << endl; // prompt

    int count_merge2 = 0; // number of comparisons for merge sort
    int count_insert2 = 0; // number of comparisons for insertion sort
    vector<int> v2; // declaration of vector for merge sort
    srand(time(nullptr)); // create random values
    for(int i=0; i <10000; i++) // iterate 1000 random values
    {
        v2.push_back(rand()); // place random values to the vector
    }

    vector<int> v2_copy = v2; // copy existing vector

    mergeSort(v2,count_merge2); // sort vector v2 with merge algorithm
    cout << "\nNumber of comparisons in MERGE SORT for 10000 elements vector: " << count_merge2 << endl; // prompt
    insertionSort(v2_copy, count_insert2); // sort vector v2_copy with insertion algorithm
    cout << "Number of comparisons in INSERTION SORT for 10000 elements vector: " << count_insert2 << endl; // prompt

    return 0;
}




