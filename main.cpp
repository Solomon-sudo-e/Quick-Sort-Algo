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

void print_runtime(double time) {
    ofstream outfile("runtime.txt");
    outfile << time;
}

void load_file(int *&numbers, int& size, const string &filename) {
    ifstream infile(filename);
    if(!infile) {
        cout << "Error opening file: " << filename << endl;
        size = 0;
        return;
    }

    //Check memory to avoid segementation fault.
    if(numbers != nullptr) {
        delete[] numbers;
    }

    numbers = new int[size];

    for(int i = 0; i < size; i++) {
        infile >> numbers[i];
    }

    infile.close();
}

void call_menu() {
    bool continueSorting = true;

    //Iterative while loop so that I can initialize variables as I go
    while (continueSorting) {
        cout << "Welcome to the Quicksort Menu!\n";
        cout << "Please select an option:\n";
        cout << "1) Input array manually\n";
        cout << "2) Load array from file\n";
        cout << "Enter your choice: ";

        //Getting choice
        int choice;
        while (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cout << "Invalid choice. Please enter 1 or 2: ";
            //Clearing cin flags then filtering out all inputs.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int size = 0;
        int *numbers = nullptr;

        if (choice == 1) {
            cout << "Enter the size of the array: ";
            while (!(cin >> size) || size <= 0) {
                cout << "Invalid size. Please enter a positive integer: ";
                //Clearing cin flags then filtering out all inputs.
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            numbers = new int[size];
            cout << "Enter the elements of the array:\n";
            for (int i = 0; i < size; ++i) {
                while (!(cin >> numbers[i])) {
                    cout << "Invalid input. Please enter an integer: ";
                    //Clearing cin flags then filtering out all inputs.
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        } else {
            cout << "Select file size:\n";
            cout << "1) 5,000 numbers\n";
            cout << "2) 10,000 numbers\n";
            cout << "3) 100,000 numbers\n";
            cout << "4) 1,000,000 numbers\n";
            cout << "5) 10,000,000 numbers\n";
            cout << "6) 100,000,000 numbers\n";
            cout << "Enter your choice: ";

            int fileChoice;
            while (!(cin >> fileChoice) || (fileChoice < 1 || fileChoice > 6)) {
                cout << "Invalid choice. Please enter a number from 1 to 6: ";
                //Clearing cin flags then filtering out all inputs.
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            string filenames[] = {
                    "5000file.txt", "10000file.txt", "100000file.txt",
                    "million.txt", "tenmillion.txt", "hundredmillion.txt"
            };

            switch(fileChoice) {
                case 1:
                    size=5000;
                    break;
                case 2:
                    size=10000;
                    break;
                case 3:
                    size=100000;
                    break;
                case 4:
                    size=1000000;
                    break;
                case 5:
                    size=10000000;
                    break;
                case 6:
                    size=100000000;
                    break;
                default:
                    cout << "invalid size needed..." << endl;
                    break;
            }

            load_file(numbers, size, filenames[fileChoice - 1]);
        }

        cout << "Please select a sorting method:\n";
        cout << "1) Basic QuickSort\n";
        cout << "2) Dual Pivot QuickSort\n";
        cout << "Enter your choice: ";

        int result;
        while (!(cin >> result) || (result != 1 && result != 2)) {
            cout << "Invalid choice. Please enter 1 or 2: ";
            //Clearing cin flags then filtering out all inputs.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        print_unsorted(numbers, size);
        double runtime;
        if (result == 1) {
            clock_t timeQuickSort = clock();
            Quicksort(numbers, 0, size - 1);
            clock_t timeQuickSort2 = clock();
            runtime = (timeQuickSort2 - timeQuickSort)/(double) CLOCKS_PER_SEC;
        } else {
            clock_t timeDualPivotQuickSort = clock();
            Dual_Pivot_QuickSort(numbers, 0, size - 1);
            clock_t timeDualPivotQuickSort2 = clock();
            runtime = (timeDualPivotQuickSort2 - timeDualPivotQuickSort)/(double) CLOCKS_PER_SEC;
        }
        print_sorted(numbers, size);
        print_runtime(runtime);

        //Checking array to see if they want to make another or not.
        cout << "Do you want to sort another array? (y/n): ";
        char repeat;
        cin >> repeat;

        while (repeat != 'y' && repeat != 'n') {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no: ";
            cin >> repeat;
            //Clearing cin flags then filtering out all inputs.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        //Stop while loop
        if (repeat == 'n') {
            continueSorting = false;
        }

        //Delete array
        delete[] numbers;
    }
}

int main() {

    call_menu();
    return 0;
}
