#include <iostream>
#include <array>
using namespace std;

void swap(int * a, int * b)
{
    int tempt = *a;
    *a = *b;
    *b = tempt;
}

int main()
{
    int arr[5] = {300, 350, 200, 400, 250};
    int array_length = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < array_length / 2; i++) {
        swap(&arr[i], &arr[array_length - i - 1]);
    }

    for (int i = 0; i < array_length; i++)
        cout << arr[i] << endl;

    return 0;
}

/* int main()
{
    int arr[5] = {300, 350, 200, 400, 250};
    int array_length = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < array_length / 2; i++)
    {
        int tempt = arr[i];
        arr[i] = arr[array_length - i - 1];
        arr[array_length - i - 1] = tempt;
    }

    for (int i = 0; i < array_length; i++)
        cout << arr[i] << endl;

    return 0;
} */
