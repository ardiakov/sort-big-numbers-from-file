#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Максимальное Кол-во разрядов у чисел
#define RADIX_COUNT 2

// Размер сортируемого массива ( 8 байт в 1-ом лонг инт)
#define PARTITION_DATA_SIZE PARTITION_LIMIT * 8

// Метод сортировки данных
void sort(long int data[]);

// Метод записи отсортированных данных в файл
void writeToFile(char fileName[], char data[]);

// Метод инициализирует пустые списки для сортировки по разрядам
void initFiles();

int main() {
    FILE *file;
    file = fopen("./simple.txt", "r");

    if (file == NULL) {
        printf("Ошибка");

        return -1;
    }

    char number[RADIX_COUNT];
    int symbol;

    int radix = 1;
    int index = 0;

    initFiles();

    while ((symbol = fgetc(file)) != EOF) {
        if (symbol == '\n') {
            // Если количество знаков меньше чем максимальное количество разрядов, добавляем начальные нули
            if (index < RADIX_COUNT) {
                char temp[RADIX_COUNT];
                for (int i = 0; i < index; i++) {
                    temp[i] = number[i];
                }

                memset(number, 0, RADIX_COUNT);

                int j;
                for (j = 0; j < RADIX_COUNT - index; j++) {
                    number[j] = '0';
                }

                for (int k = 0; k < index; k++) {
                    number[j] = temp[k];
                    j++;
                }
            }

            int innerRadix = RADIX_COUNT - radix;

            // Запись числа в файл
            char fileName[12];
            sprintf(fileName, "./tmp/%c.txt", number[innerRadix]);

            writeToFile(fileName, number);

            memset(number, 0, RADIX_COUNT);
            index = 0;

            continue;
        }

        number[index] = symbol;
        index++;
    }

    fclose(file);

    return 0;
}

void initFiles() {
    FILE *fp;

    char filename[12];
    for (int i = 0; i <= 9; ++i) {
        sprintf(filename, "./tmp/%d.txt", i);
        fp = fopen(filename, "w+a+");
        fclose(fp);
    }
}

void writeToFile(char fileName[], char data[]) {
    FILE *fp;
    fp = fopen(fileName, "w+, ccs=UTF-8");

//    for (int l = 0; l < RADIX_COUNT; ++l) {
//        printf("%c", data[l]);
//    }
//    printf("\n");

    int i = 0;
    for (int j = 0; j < RADIX_COUNT; ++j) {
        fprintf(fp, "%c", data[i]);

        printf("%c", data[i]);
        ++i;
    }

    printf("\n");

    fclose(fp);
}
