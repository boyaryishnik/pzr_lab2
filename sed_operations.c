#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "sed_operations.h"

void replace_text(const char *filename, const char *old_text, const char *new_text) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    char *buffer = NULL;
    size_t size = 0;
    long file_size;
    file_size = ftell(file);
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char *)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    char *pos = strstr(buffer, old_text);
    while (pos) {
        char *temp = (char *)malloc(strlen(buffer) + strlen(new_text) - strlen(old_text) + 1);
        strncpy(temp, buffer, pos - buffer);
        temp[pos - buffer] = '\0';
        strcat(temp, new_text);
        strcat(temp, pos + strlen(old_text));
        free(buffer);
        buffer = temp;
        pos = strstr(buffer, old_text);
    }

    fseek(file, 0, SEEK_SET);
    ftruncate(fileno(file), 0);
    fwrite(buffer, 1, strlen(buffer), file);
    fclose(file);
    free(buffer);
}

void delete_lines(const char *filename, const char *regex_pattern) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    char *buffer = NULL;
    size_t size = 0;
    long file_size;
    file_size = ftell(file);
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char *)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    regex_t regex;
    regcomp(&regex, regex_pattern, 0);

    char *line = strtok(buffer, "\n");
    char *new_buffer = (char *)malloc(file_size + 1);
    new_buffer[0] = '\0';

    while (line) {
        if (regexec(&regex, line, 0, NULL, 0) != 0) {
            strcat(new_buffer, line);
            strcat(new_buffer, "\n");
        }
        line = strtok(NULL, "\n");
    }

    fseek(file, 0, SEEK_SET);
    ftruncate(fileno(file), 0);
    fwrite(new_buffer, 1, strlen(new_buffer), file);
    fclose(file);
    free(buffer);
    free(new_buffer);
    regfree(&regex);
}

void add_prefix(const char *filename, const char *prefix) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    char *buffer = NULL;
    size_t size = 0;
    long file_size;
    file_size = ftell(file);
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char *)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    char *line = strtok(buffer, "\n");
    char *new_buffer = (char *)malloc(file_size + 1);
    new_buffer[0] = '\0';

    while (line) {
        strcat(new_buffer, prefix);
        strcat(new_buffer, line);
        strcat(new_buffer, "\n");
        line = strtok(NULL, "\n");
    }

    fseek(file, 0, SEEK_SET);
    ftruncate(fileno(file), 0);
    fwrite(new_buffer, 1, strlen(new_buffer), file);
    fclose(file);
    free(buffer);
    free(new_buffer);
}

void add_suffix(const char *filename, const char *suffix) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    char *buffer = NULL;
    size_t size = 0;
    long file_size;
    file_size = ftell(file);
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char *)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    char *line = strtok(buffer, "\n");
    char *new_buffer = (char *)malloc(file_size + 1);
    new_buffer[0] = '\0';

    while (line) {
        strcat(new_buffer, line);
        strcat(new_buffer, suffix);
        strcat(new_buffer, "\n");
        line = strtok(NULL, "\n");
    }

    fseek(file, 0, SEEK_SET);
    ftruncate(fileno(file), 0);
    fwrite(new_buffer, 1, strlen(new_buffer), file);
    fclose(file);
    free(buffer);
    free(new_buffer);
}
