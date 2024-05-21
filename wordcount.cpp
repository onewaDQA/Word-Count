#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype> 

int countCharacters(const char *filePath);
int countWords(const char *filePath);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c|-w] input_file_name\n", argv[0]);
        return 1;
    }

    char *parameter = argv[1];
    char *fileName = argv[2];

    if (strcmp(parameter, "-c") == 0) {
        int count = countCharacters(fileName);
        printf("�ַ�����%d\n", count);
    } else if (strcmp(parameter, "-w") == 0) {
        int count = countWords(fileName);
        printf("��������%d\n", count);
    } else {
        printf("Error: Invalid parameter. Use -c for character count or -w for word count.\n");
        return 1;
    }

    return 0;
}

int countCharacters(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        ++count;
    }
    fclose(file);
    return count;
}

int countWords(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    int inWord = 0; // 0: not in word, 1: in word
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',') {
            if (inWord) {
                ++count;
                inWord = 0;
            }
        } else {
            inWord = 1;
        }
    }
    // Count last word if exists
    if (inWord) ++count;
    fclose(file);
    return count;
}
