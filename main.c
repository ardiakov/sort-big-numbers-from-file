#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Кол-вл элементов для сортировки
#define PARTITION_LIMIT 4

// Размер сортируемого массива ( 8 байт в 1-ом лонг инт)
#define PARTITION_DATA_SIZE PARTITION_LIMIT * 8

// Метод сортировки данных
void sort(long int data[]);

// Метод записи отсортированных данных в файл
void writeToFile(char name[], long int data[]);

int main() {
    FILE *file;
    file = fopen("./simple.txt", "r");

    if (file == NULL) {
        printf("Ошибка");

        return -1;
    }

    int symbol;
    char number[255] = {0};

    // Массив для сортировки
    long int data[PARTITION_DATA_SIZE] = {0};

    int dataIndex = 0;
    int numberIndex = 0;
    int part = 0;

    while ((symbol = fgetc(file)) != EOF) {
        if (dataIndex < PARTITION_LIMIT) {
            if (symbol != ' ' && symbol != '\n') {
                number[numberIndex] = (char) symbol;
                ++numberIndex;
            } else {
                data[dataIndex] = atoll(number);

                memset(number, 0, numberIndex);
                numberIndex = 0;

                ++dataIndex;
            }

            if (dataIndex == PARTITION_LIMIT) {
                // Сортировка порции данных
                printf("Сортировка \n");
                sort(data);

                // Запись отсортированных данных в файл
                char fileNameWithPath[50];
                sprintf(fileNameWithPath, "./tmp/%d.txt", part);

                // for (int i = 0; i < 30; ++i) {
                //     printf("%c", fileNameWithPath[i]);
                // }

                writeToFile(fileNameWithPath, data);
                
                memset(data, 0, dataIndex * 8);

                dataIndex = 0;
                ++part;
            }
        }
    }

    fclose(file);

    return 0;
}

void sort(long int data[]) {
    for (int i = 1; i < PARTITION_LIMIT; ++i) {
        int j = i;

        while (j > 0 && data[j - 1] > data[j]) {
            long int temp = data[j - 1];
            data[j - 1] = data[j];
            data[j] = temp;

            j--;
        }
    }

    for (int i = 0; i < PARTITION_LIMIT; ++i) {
        printf("%li \n", data[i]);
    }
}

void writeToFile(char name[], long int data[]) {
    FILE *fp;

    fp = fopen(name, "w+, ccs=UTF-8");

    int i = 0;
    while (i < PARTITION_LIMIT) {
        fprintf(fp, "%li\n", data[i]);

        ++i;
    }

    fclose(fp);
}
