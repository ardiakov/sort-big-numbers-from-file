#include <stdio.h>
#include <stdlib.h>

void print_array(char array[]);
void jumpOnNextLine(FILE *file, int index);

int main() {
    FILE *file;

    file = fopen("./simple.txt", "r");

    if (file == NULL) {
        printf("Ошибка");

        return -1;
    }

    int symbol;

    char number[255] = {};

    int bytePosition = 0;
    int counter = 0;
    while ((symbol = fgetc(file)) != EOF) {
        if (symbol != ' ') {
            number[counter] = (char) symbol;
            ++bytePosition;
            ++counter;
            printf("Отступ: %d \n", counter);

        } else {
            printf("Целое число: %lli \n", atoll(number));
            printf("Отступ: %d \n", bytePosition);

            counter = 0;

            jumpOnNextLine(file, bytePosition);

            printf("Новый символ: %c", fgetc(file));

            exit(1);
        }
    }


    return 0;
}

void jumpOnNextLine(FILE *file, int index) {
    if (fseek(file, index + 2,SEEK_SET) != 0) {
        printf("Ошибка");
    }
}

void print_array(char array[]) {
    for (int i = 0; i < 255; ++i) {
        printf("%c", array[i]);
    }
}