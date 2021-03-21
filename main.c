#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Максимальное Кол-во разрядов у чисел
#define RADIX_COUNT 2
#define FULL_PATH_TO_SOURCE_FILE "/Users/ardiakov/CLionProjects/sort-big-numbers-from-file/simple.txt"
#define FULL_PATH_TO_TMP_FILES "/Users/ardiakov/CLionProjects/sort-big-numbers-from-file/%s%c%s"
#define FULL_PATH_TO_INIT_FILES "/Users/ardiakov/CLionProjects/sort-big-numbers-from-file/%s%d%s"

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
    FILE *file;

    file = fopen(FULL_PATH_TO_SOURCE_FILE, "r+");

    if (file == NULL) {
        printf("Ошибка");

        return -1;
    }

    char number[RADIX_COUNT + 1];
    char tempNumber[RADIX_COUNT + 1];

    memset(number, '\0', RADIX_COUNT + 1);
    memset(tempNumber, '\0', RADIX_COUNT + 1);

    int currentRadix = 0;
    int countSymbolsInNumber = 0;

    initFiles();

    char symbol;

    // Чтение чисел из файла и разбиение их на отдельные файлы по разрядам
    while ((symbol = fgetc(file)) != EOF) {
        if (symbol == '\n') {
            // Если количество знаков меньше чем максимальное количество разрядов, добавляем начальные нули
            if (countSymbolsInNumber < RADIX_COUNT) {
                number[countSymbolsInNumber] = '\0';
                addLeadingZeroes(number, tempNumber, countSymbolsInNumber);
            }

            // Запись числа в файл в соответствии с их разрядом
            char fileName[100];
            sprintf(fileName, FULL_PATH_TO_TMP_FILES, "tmp/", number[currentRadix], ".txt");
            writeToFile(fileName, number);

            // Обнуляем
            memset(number, 0, RADIX_COUNT);
            countSymbolsInNumber = 0;
        } else {
            number[countSymbolsInNumber] = symbol;
            countSymbolsInNumber++;
        }
    }

    fclose(file);
    remove(FULL_PATH_TO_SOURCE_FILE);

    // Сборка чисел из поразрадных файлов в один
    for (int i = 0; i <= 9; ++i) {
        FILE *fp;
        char filename[100];
        sprintf(filename, FULL_PATH_TO_INIT_FILES, "tmp/", i, ".txt");
        fp = fopen(filename, "r");

        while ((symbol = fgetc(fp)) != EOF) {
            if (symbol == '\n') {
                writeToFile(FULL_PATH_TO_SOURCE_FILE, number);

                // Обнуляем
                memset(number, 0, RADIX_COUNT);
                countSymbolsInNumber = 0;
            } else {
                number[countSymbolsInNumber] = symbol;
                countSymbolsInNumber++;
            }
        }
        fclose(fp);
    }

    return 0;
}

void addLeadingZeroes(char *number, char *tempNumber, int length) {
    if (length == RADIX_COUNT) {
        return;
    }

    int index = 0;
    while (index <= RADIX_COUNT) {
        tempNumber[index] = number[index];
        index++;
    }

    int i;
    int diff = RADIX_COUNT - length;
    for (i = 0; i < diff; i++) {
        number[i] = '0';
    }

    for (int j = 0; i < RADIX_COUNT; j++) {
        number[i] = tempNumber[j];
        i++;
    }

    number[i] = '\0';

//    printf("R %s \n", number);
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

    char filename[100];
    for (int i = 0; i <= 9; ++i) {
        sprintf(filename, FULL_PATH_TO_INIT_FILES, "tmp/", i, ".txt");
        fp = fopen(filename, "wb+");
        fclose(fp);
    }
}

void writeToFile(char *fileName, char data[]) {
    FILE *fp;
    fp = fopen(fileName, "ab, ccs=UTF-8");
    if (fp == NULL) {
        printf("Ошибка");
    }

    for (int i = 0; i < RADIX_COUNT; i++) {
        fprintf(fp, "%c", data[i]);
    }

    fprintf(fp, "\n");

    fclose(fp);
}
