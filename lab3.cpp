//5. Имеется массив целых чисел.Отсортировать его  на  месте
//методом шейкер - сортировки.Удалить повторное вхождение  чисел,
//не используя дополнительной памяти(8).

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

int maxSize = 10;

int binarySearch(int arr[], int n, int x) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == x) {
            return mid;
        }
        else if (arr[mid] > x) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return -1;
}

int removeDuplicates(int arr[], int n) {
    int newLength = 1;

    for (int i = 1; i < n; i++) {
        int index = binarySearch(arr, newLength, arr[i]);
        if (index == -1) {
            arr[newLength] = arr[i];
            newLength++;
        }
    }

    return newLength;
}

int shakerSort(int arr[], int& n, int x = 0, bool insert = false, bool del = false) {
    int left = 0;
    int right = n - 1;
    int k = 0;
    int newLength = n;

    while (left < right) {
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                k = i;
            }
        }
        right = k;

        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                k = i;
            }
        }
        left = k;
    }

    if (insert) {
        // find the position to insert the new element
        int pos = binarySearch(arr, n, x);
        if (pos < 0) {
            pos = -(pos + 1);
        }

        int* newArr = new int[maxSize + 1];
        if (newLength == maxSize) {
            int* newArr = new int[maxSize * 2];
            for (int i = 0; i < maxSize; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            maxSize *= 2;
        }

        // shift the elements to the right of the insertion position
        for (int i = n - 1; i >= pos; i--) {
            arr[i + 1] = arr[i];
        }

        // insert the new element
        arr[pos] = x;
        newLength++;
    }

    if (del) {
        // find the position of the element to be deleted
        int pos = binarySearch(arr, n, x);
        if (pos >= 0) {
            // shift the elements to the left of the deletion position
            for (int i = pos; i < n; i++) {
                arr[i] = arr[i + 1];
            }
            newLength--;
        }
    }

    newLength = removeDuplicates(arr, n);
    n = newLength;
    return newLength;
}

int main() {

    int arr[] = { 7, 3, 2, 8, 2, 4, 9, 1, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    while (true) {
        shakerSort(arr, n);
        cout << "Array sorted" << endl;
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        cout << "Enter an option: " << endl;
        cout << "1. Search for an element" << endl;
        cout << "2. Insert an element" << endl;
        cout << "3. Delete an element" << endl;
        cout << "4. Exit" << endl;

        int option;
        cin >> option;

        if (option == 1) {
            int x;
            cout << "Enter the element to search: ";
            cin >> x;
            int index = binarySearch(arr, n, x);
            if (index != -1) {
                cout << "Element found at index " << index << endl;
            }
            else {
                cout << "Element not found" << endl;
            }
        }
        else if (option == 2) {
            int x;
            cout << "Enter the element to insert: ";
            cin >> x;
            int newLength = shakerSort(arr, n, x, true, false);
            n = newLength;
        }
        else if (option == 3) {
            int x;
            cout << "Enter the element to delete: ";
            cin >> x;
            int newLength = shakerSort(arr, n, x, false, true);
            n = newLength;
        }
        else if (option == 4) {
            break;
        }
        else {
            cout << "Invalid option. Try again." << endl;
        }

        cout << endl;
    }

    return 0;
}