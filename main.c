#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Кол-вл элементов для сортировки
#define PARTITION_LIMIT 4

// Размер сортируемого массива
#define PARTITION_DATA_SIZE PARTITION_LIMIT * 8

// Метод сортировки данных
void sort(long int data[]);

// Метод записи отсортированных данных в файл
void writeToFile(char name[]);

int main() {
    FILE *file;

    file = fopen("./simple.txt", "r");

    if (file == NULL) {
        printf("Ошибка");

        return -1;
    }

    int symbol;
    char number[255] = {0};

    // Массив для сортровки 625000 значений (5мб)
    long int data[PARTITION_DATA_SIZE] = {0};

    int dataIndex = 0;
    int numberIndex = 0;

    while ((symbol = fgetc(file)) != EOF && dataIndex <= PARTITION_LIMIT) {
        if (symbol != ' ' && symbol != '\n') {
            number[numberIndex] = (char) symbol;
            ++numberIndex;
        } else {
            data[dataIndex] = atoll(number);

            memset(number, 0, numberIndex);
            numberIndex = 0;
            ++dataIndex;
        }
    }

    for (int i = 0; i < PARTITION_LIMIT; ++i) {
        printf("%d \n", data[i]);
    }

    return 0;
}