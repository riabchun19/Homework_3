// 1. Попробовать оптимизировать пузырьковую сортировку. Сравнить количество операций сравнения
// оптимизированной и не оптимизированной программы. Напишите функции сортировки, которые возвращают
// количество операций.
// 2. * Реализовать шейкерную сортировку.
// 3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив.
// Функция возвращает индекс найденного элемента или - 1, если элемент не найден.
// 4. * Подсчитать количество операций для каждой из сортировок и сравнить его с асимптотической сложностью алгоритма.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 40

int countBubble = 0;
int countOptBubble = 0;
int countShaker = 0;

void fillArray(int* arr, int len) // Заполнение массива
{
    int i;
    for (i = 0; i < len; i++)
        arr[i] = rand() % 100;
}

void printArray(int* arr, int len) // Вывод массива
{
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    puts("");
}

void swap(int* a, int* b) // Функция обмена значениями двух переменных
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void bubbleSort(int* arr, int len) // Пузырьковая сортировка
{
    int i;
    int j;
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < len - 1; j++)
        {
            countBubble++;
            if (arr[j] > arr[j + 1])
            {
                countBubble++;
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    printf("Number of operations bubble sort: %d\n", countBubble);
}

void bubbleSort_2(int* arr, int len) // 1. Оптимизированная пузырьковая сортировка
{
    int i;
    int j;
    int right = len - 1;
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < right; j++)
        {
            countOptBubble++;
            if (arr[j] > arr[j + 1])
            {
                countOptBubble++;
                swap(&arr[j], &arr[j + 1]);
            }
        }
        right--; // Убираем проверку отсортированых елементов
    }
    printf("Number of operations optimized bubble sort: %d\n", countOptBubble);
}

void shakerSorting(int* arr, int len) // 2. Шейкерная сортировка
{
    int left = 0;
    int right = len - 1;
    while (left < len)
    {
        for (int i = left; i < right; i++) // Сортировка в правую стоону
        {
            countShaker++;
            if (arr[i] > arr[i + 1])
            {
                countShaker++;
                swap(&arr[i], &arr[i + 1]);
            }
        }
        right--; // Убираем проверку отсортированых елементов

        for (int i = right; i > left; i--) // Сортировка в левую сторону
        {
            countShaker++;
            if (arr[i - 1] > arr[i])
            {
                countShaker++;
                swap(&arr[i - 1], &arr[i]);
            }
        }
        left++; // Убираем проверку отсортированых елементов
    }
    printf("Number of operations shaker sorting: %d\n", countShaker);
}

int binarySearch(int* arr, int len, int value) // 3. Поиск половинным делением(бинарный)
{
    int left = 0;
    int right = len - 1;
    int middle = left + (right - left) / 2;
    while (left <= right && arr[middle] != value)
    {
        if (arr[middle] < value)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
        middle = left + (right - left) / 2;
    }
    return (arr[middle] == value) ? middle : -1;
}

int main()
{
    const int SIZE = N;
    int arr1[N];
    int arr2[N];
    int arr3[N];

    fillArray(arr1, SIZE);
    memcpy(arr2, arr1, 160); // Копирование массива
    memcpy(arr3, arr1, 160); // Копирование массива

    puts("Array - 1");
    printArray(arr1, SIZE);
    puts("\t\t\t\t after sorting");
    bubbleSort(arr1, SIZE);
    printArray(arr1, SIZE);
    puts("");

    puts("Array - 2");
    printArray(arr2, SIZE);
    puts("\t\t\t\t after sorting");
    bubbleSort_2(arr2, SIZE);
    printArray(arr2, SIZE);
    puts("");

    puts("Array - 3");
    printArray(arr3, SIZE);
    puts("\t\t\t\t after sorting");
    shakerSorting(arr3, SIZE);
    printArray(arr3, SIZE);
    puts("");

    printf("(binarySearch) The index of the element(45) found = %d\n", binarySearch(arr1, SIZE, 45));
    puts("");

    printf("Bubble sort - %d op., asymptotic complexity of the algorithm - O(N * K)\n", countBubble);
    printf("Optimized sort - %d op., asymptotic complexity of the algorithm - O(N * K)\n", countOptBubble);
    printf("Shaker sorting - %d op., asymptotic complexity of the algorithm - O(N + K)\n", countShaker);
    puts("");
}