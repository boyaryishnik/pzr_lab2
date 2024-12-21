#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "sed_operations.h"

void print_usage() {
    printf("Использование: ./sed_simplified <input_file> '<operation>'\n");
    printf("Примеры:\n");
    printf("  ./sed_simplified input.txt 's/old_text/new_text/'\n");
    printf("  ./sed_simplified input.txt '/regex/d'\n");
    printf("  ./sed_simplified input.txt 's/^/prefix/'\n");
    printf("  ./sed_simplified input.txt 's/$/suffix/'\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage();
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    char *operation = argv[2];

    if (strstr(operation, "s/") == operation) {
        // Замена текста
        char *old_text = operation + 2;
        char *new_text = strchr(old_text, '/');
        if (new_text) {
            *new_text = '\0';
            new_text++;
            if (*new_text == '\0') {
                fprintf(stderr, "Ошибка: не указано новое значение для замены.\n");
                return EXIT_FAILURE;
            }
            replace_text(filename, old_text, new_text);
        } else {
            fprintf(stderr, "Ошибка: некорректная операция замены.\n");
            return EXIT_FAILURE;
        }
    } else if (operation[0] == '/' && operation[strlen(operation) - 1] == 'd') {
        // Удаление строк
        char *regex_pattern = operation + 1;
        regex_pattern[strlen(regex_pattern) - 1] = '\0'; // Удаляем 'd'
        delete_lines(filename, regex_pattern);
    } else if (strstr(operation, "s/^/") == operation) {
        // Добавление префикса
        char *prefix = operation + 3;
        prefix[strlen(prefix) - 1] = '\0'; // Удаляем '/'
        add_prefix(filename, prefix);
    } else if (strstr(operation, "s/$/") == operation) {
        // Добавление суффикса
        char *suffix = operation + 3;
        suffix[strlen(suffix) - 1] = '\0'; // Удаляем '/'
        add_suffix(filename, suffix);
    } else {
        fprintf(stderr, "Ошибка: некорректная операция.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
