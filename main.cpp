#include <iostream>
#include <fstream>
#include <limits>
#include <ctime>

using namespace std;
int Partition(int numbers[], int lowIndex, int highIndex) {
// Set middle pivot.
    int midpoint = lowIndex + (highIndex - lowIndex) / 2;
    int pivot = numbers[midpoint];

    bool done = false;

    //Iterate through partition to sort each part.
    while (!done) {
        // Increment lowIndex while numbers[lowIndex] is less than pivot
        while (numbers[lowIndex] < pivot) {
            lowIndex += 1;
        }

        // Decrement highIndex while pivot is less than numbers[highIndex]
        while (pivot < numbers[highIndex]) {
            highIndex -= 1;
        }

        // If one or less than one element remain then the numbers are partitioned
        if (lowIndex >= highIndex) {
            done = true;
        } else {
            // Swap numbers[lowIndex] and numbers[highIndex]
            int temp = numbers[lowIndex];
            numbers[lowIndex] = numbers[highIndex];
            numbers[highIndex] = temp;
            // Update lowIndex and highIndex
            lowIndex += 1;
            highIndex -= 1;
        }
    }
    return highIndex;
}

void Quicksort(int numbers[], int lowIndex, int highIndex) {
    // Base case: If the partition size is 1 or zero elements, then the partition is already sorted
    if (lowIndex >= highIndex) {
        return;
    }

    // Partition the data
    int lowEndIndex = Partition(numbers, lowIndex, highIndex);

    // Recursively sort low partition
    Quicksort(numbers, lowIndex, lowEndIndex);
    // Recursively sort high partition
    Quicksort(numbers, lowEndIndex+ 1, highIndex);
}

//Switched to Reference for left and right pivots because I cant return multiple variables.
void Dual_Pivot_Partition(int numbers[], int &low_pivot_index, int &high_pivot_index, int low, int high) {
    if (numbers[low] > numbers[high]) {
        int temp = numbers[low];
        numbers[low] = numbers[high];
        numbers[high] = temp;
    }

    int pivot_low = numbers[low];
    int pivot_high = numbers[high];
    int left = low + 1;
    int right = high - 1;
    int index = left;

    while (index <= right) {
        //Checking if index is less than the low pivot, if so, I swap left with the index.
        if (numbers[index] < pivot_low) {
            int temp = numbers[left];
            numbers[left] = numbers[index];
            numbers[index] = temp;
            left++;
        //Checking if index is greater than or equal to high.
        } else if (numbers[index] >= pivot_high) {
            //Iterating through the index and right var. I was getting problems with duplicate variables.
            while (numbers[right] > pivot_high && index < right) {
                right--;
            }
            //Swapping once done. IF right is higher than pivot high.
            int temp = numbers[right];
            numbers[right] = numbers[index];
            numbers[index] = temp;
            right--;
            //Checking if index is less than pivot low.
            if (numbers[index] < pivot_low) {
                temp = numbers[left];
                numbers[left] = numbers[index];
                numbers[index] = temp;
                left++;
            }
        }
        //Incrementing index to check next variable.
        index++;
    }

    //Decremented left and increment right so I can update variables properly. Became an issue when duplicate variables.
    left--;
    right++;

    int temp = numbers[low];
    numbers[low] = numbers[left];
    numbers[left] = temp;

    temp = numbers[high];
    numbers[high] = numbers[right];
    numbers[right] = temp;

    low_pivot_index = left;
    high_pivot_index = right;
}

void Dual_Pivot_QuickSort(int numbers[], int lowIndex, int HighIndex) {
    //Check base case that lowindex is not greater than or equal to highindex, then continue with function.
    if(lowIndex >= HighIndex) {
        return;
    } else {
        int left_pivot_index, right_pivot_index;

        Dual_Pivot_Partition(numbers, left_pivot_index, right_pivot_index, lowIndex, HighIndex);

        //Recursively sort the three partitions made.
        Dual_Pivot_QuickSort(numbers, lowIndex, left_pivot_index-1);
        Dual_Pivot_QuickSort(numbers, left_pivot_index + 1, right_pivot_index - 1);
        Dual_Pivot_QuickSort(numbers, right_pivot_index + 1, HighIndex);
    }
}

//Print functions
void print_unsorted(int arr[], int size) {
    ofstream outfile("unsorted.txt");
    for(int i = 0; i < size; i++) {
        outfile << arr[i] << " ";
    }
}

void print_sorted(int arr[], int size) {
    ofstream outfile("sorted.txt");
    for(int i = 0; i < size; i++) {
        outfile << arr[i] << " ";
    }
}

int get_option() {
    cout << "Welcome to the Quicksort Menu! o7 \nPlease tell me which method of sorting you would like. \n" <<
         "1) Basic Quicksort\t 2) Dual Pivot Quicksort\n";
    string option;
    cin >> option;
    try {
        int choice = stoi(option);
        if(choice != 1 && choice != 2) {
            cout << "Option much be an integer of either 1, or 2" << endl;
            get_option();
        } else {
            if(choice == 1) {
                return 1;
            } else {
                return 2;
            }
        }
    } catch (exception e) {
        cout << "Option much be an integer of either 1, or 2" << endl;
        get_option();
    }
    return 0;
}
void call_menu() {
    bool continueSorting = true;

    while (continueSorting) {
        cout << "Welcome to the Quicksort Menu!\n";
        cout << "Please select a sorting method:\n";
        cout << "1) Basic QuickSort\n";
        cout << "2) Dual Pivot QuickSort\n";
        cout << "Enter your choice: ";

        int choice;
        while (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cout << "Invalid choice. Please enter 1 or 2: ";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        cout << "Enter the size of the array: ";
        int size;
        while (!(cin >> size) || size <= 0) {
            cout << "Invalid size. Please enter a positive integer: ";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        int* numbers = new int[size];
        cout << "Enter the elements of the array:\n";
        for (int i = 0; i < size; ++i) {
            while (!(cin >> numbers[i])) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
        }

        cout << "Unsorted array: ";
        for (int i = 0; i < size; ++i) {
            cout << numbers[i] << " ";
        }
        cout << endl;

        if (choice == 1) {
            Quicksort(numbers, 0, size - 1);
        } else {
            Dual_Pivot_QuickSort(numbers, 0, size - 1);
        }

        cout << "Sorted array: ";
        for (int i = 0; i < size; ++i) {
            cout << numbers[i] << " ";
        }
        cout << endl;

        cout << "Do you want to sort another array? (y/n): ";
        char repeat;
        cin >> repeat;

        while (repeat != 'y' && repeat != 'n') {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no: ";
            cin >> repeat;
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        if (repeat == 'n') {
            continueSorting = false;
        }

        delete[] numbers; // Clean up dynamically allocated array
    }
}

int main() {
    call_menu();
    return 0;
}
