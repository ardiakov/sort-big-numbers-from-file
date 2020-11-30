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
void writeToFile(char *fileName, char data[]);

// Метод инициализирует пустые списки для сортировки по разрядам
void initFiles();

// Метод для добавления начальных нулей
void addLeadingZeroes(char *number, char *tempNumber, int length);

// Метод для удаления начальных нулей
void removeLeadingZeroes();

// Метод для
void join();

int main() {
    // есть char[]
    // передать в функцию
    // заполнить данными
    // вернуть

//    char number[6] = "456";
//
//    for (int i = 0; i < sizeof(number); ++i) {
//        printf("%c", number[i]);
//    }
//
//    printf("\n");
//
//    char *pt;
//    pt = addLeadingZeros(number, 3);
//    printf("%s \n", pt);
//
//    char *removeZerosPt = removeLeadingZeros(pt);
//
//    printf("%s", removeZerosPt);

    FILE *file;
    file = fopen("/Users/ardiakov/CLionProjects/sort-big-numbers-from-file/simple.txt", "r+");

    if (file == NULL) {
        printf("Ошибка");

        return -1;
    }

    char number[RADIX_COUNT];

    printf("%pt \n", number);
    char tempNumber[RADIX_COUNT];

    int radix = 1;
    int countSymbolsInNumber = 0;

    initFiles();

    char symbol;
    while ((symbol = fgetc(file)) != EOF) {
        if (symbol == '\n') {
            // Если количество знаков меньше чем максимальное количество разрядов, добавляем начальные нули
            if (countSymbolsInNumber < RADIX_COUNT) {
                addLeadingZeroes(number, tempNumber, countSymbolsInNumber);
            }

            printf("%s \n", number);

//
//            int innerRadix = RADIX_COUNT - radix;
//
//            // Запись числа в файл
//            char fileName[12];
//            sprintf(fileName, "./tmp/%c.txt", number[innerRadix]);
//            writeToFile(fileName, number);
//            memset(number, 0, RADIX_COUNT);
//            countSymbolsInNumber = 0;
//
//            continue;
        }

        number[countSymbolsInNumber] = symbol;
        countSymbolsInNumber++;
    }

    fclose(file);

    return 0;
}

void addLeadingZeroes(char *number, char *tempNumber, int length) {
    printf("%pt \n", number);
    if (length == RADIX_COUNT) {
        return;
    }

    int index = 0;
    while (*number != '\0') {
        tempNumber[index] = *number;

        number++;
        index++;
    }

    memset(&number, 0, RADIX_COUNT);

    int i;
    int diff = RADIX_COUNT - length;
    for (i = 0; i < diff; i++) {
        number[i] = '6';
    }

    for (int j = 0; i < RADIX_COUNT; j++) {
        number[i] = tempNumber[j];
        i++;
    }

    memset(&tempNumber, 0, RADIX_COUNT);

    printf("%s \n", number);
}

char *removeLeadingZeros(char *number) {
    char temp[6];

    int i = 0;
    int j = 0;
    int startNumber = 0;
    while (*number != '\0') {
        i++;
        if (startNumber == 0 && number[i] == '0') {
            continue;
        }

        startNumber = 1;

        temp[j] = number[i];
        j++;
    }

    memset(number, 0, 6);

    for (int k = 0; k < 6; ++k) {
        number[k] = temp[k];
    }

    return number;
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

void writeToFile(char *fileName, char data[]) {
    FILE *fp;
    fp = fopen(fileName, "w+, ccs=UTF-8");
    if (fp == NULL) {
        printf("Ошибка");
    }

    for (int i = 0; i < RADIX_COUNT; i++) {
        fprintf(fp, "%c", data[i]);
    }

    printf("1");
    fclose(fp);

    printf("%s rrr", data);
}
