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

// Метод для добавления начальных нулей
char* addLeadingZeroes(int index, char number[]);

// Метод для удаления начальных нулей
void removeLeadingZeroes();

// Метод для
void join();

char *testFunc(char *number, int length) {
    if (length == 6) {
        return number;
    }

    char temp[6];
    int index = 0;
    while (*number != '\0') {
        temp[index] = *number;

        number++;
        index++;
    }

    int i;
    int diff = 6 - length;
    for (i = 0; i < diff; ++i) {
        number[i] = '0';
    }

    int j = 0;
    for (; i < 6; ++i, ++j) {
        number[i] = temp[j];
    }

    number[i] = '\0';

    return number;
}


int main() {
    // есть char[]
    // передать в функцию
    // заполнить данными
    // вернуть

    char number[6] = "456";

    for (int i = 0; i < sizeof(number); ++i) {
        printf("%c", number[i]);
    }

    printf("\n");

    char *pt;
    pt = testFunc(number, 3);

    printf("%s", pt);
//
//    while (*pt != '\0') {
//        printf("%c", pt);
//
//        pt++;
//    }




    /*FILE *file;
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
                number = addLeadingZeroes(index, number);
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

    fclose(file);*/

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
