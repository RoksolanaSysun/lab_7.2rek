#include <iomanip>
#include <iostream>
#include <time.h>
using namespace std;

void CreateRecursive(int** a, int row, int col, const int k, const int n, const int Low, const int High);
void PrintRecursive(int** a, int row, int col, const int k, const int n);
int MinInColumnRecursive(int** a, int row, const int col, const int k);
int MaxOfMinInEvenColumnsRecursive(int** a, int col, const int k, const int n, int currentMax);

int main()
{
    srand((unsigned)time(NULL));
    int Low = 5;
    int High = 51;
    int k, n;

    cout << "k = "; cin >> k;
    cout << "n = "; cin >> n;

    int** a = new int* [k];
    for (int i = 0; i < k; i++)
        a[i] = new int[n];

    CreateRecursive(a, 0, 0, k, n, Low, High);
    PrintRecursive(a, 0, 0, k, n);

    int maxMinEvenCols = MaxOfMinInEvenColumnsRecursive(a, 0, k, n, INT_MIN);
    cout << "Greatest of the minimums in even columns: " << maxMinEvenCols << endl;

    for (int i = 0; i < k; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}

void CreateRecursive(int** a, int row, int col, const int k, const int n, const int Low, const int High)
{
    if (row >= k)
        return;

    if (col < n)
    {
        a[row][col] = Low + rand() % (High - Low + 1);
        CreateRecursive(a, row, col + 1, k, n, Low, High);
    }
    else
    {
        CreateRecursive(a, row + 1, 0, k, n, Low, High);
    }
}

void PrintRecursive(int** a, int row, int col, const int k, const int n)
{
    if (row >= k)
        return;

    if (col < n)
    {
        cout << setw(4) << a[row][col];
        PrintRecursive(a, row, col + 1, k, n);
    }
    else
    {
        cout << endl;
        PrintRecursive(a, row + 1, 0, k, n);
    }
}

int MinInColumnRecursive(int** a, int row, const int col, const int k)
{
    if (row == k - 1)
        return a[row][col];

    int minInRest = MinInColumnRecursive(a, row + 1, col, k);
    return (a[row][col] < minInRest) ? a[row][col] : minInRest;
}

int MaxOfMinInEvenColumnsRecursive(int** a, int col, const int k, const int n, int currentMax)
{
    if (col >= n)
        return currentMax;

    int minInCol = MinInColumnRecursive(a, 0, col, k);
    currentMax = (minInCol > currentMax) ? minInCol : currentMax;

    return MaxOfMinInEvenColumnsRecursive(a, col + 2, k, n, currentMax); // Перебираємо лише парні стовпці
}
