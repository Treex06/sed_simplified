#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "sed_operations.h"

void replace_text(const char *filename, const char *old_text, const char *new_text) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Считываем файл в память
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    // Подсчитываем количество вхождений
    char *pos = buffer;
    while ((pos = strstr(pos, old_text)) != NULL) {
        pos += strlen(new_text);
    }

    // Создаем новый буфер для сохранения изменений
    char *new_buffer = malloc(file_size + (strlen(new_text) - strlen(old_text)) * (pos - buffer));
    char *current_pos = new_buffer;
    
    pos = buffer;
    while (*pos) {
        if (strstr(pos, old_text) == pos) {
            strcpy(current_pos, new_text);
            current_pos += strlen(new_text);
            pos += strlen(old_text);
        } else {
            *current_pos++ = *pos++;
        }
    }
    *current_pos = '\0';

    // Сбрасываем файл и записываем новый содержимое
    freopen(filename, "w+", file);
    fputs(new_buffer, file);

    // Освобождаем память
    free(buffer);
    free(new_buffer);
    fclose(file);
}

void delete_lines(const char *filename, const char *regex_pattern) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    regex_t regex;
    regcomp(&regex, regex_pattern, 0);

    // Файл временного хранения отфильтрованных строк
    FILE *temp_file =tmpfile();
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        if (regexec(&regex, line, 0, NULL, 0) != 0) {
            fputs(line, temp_file);
        }
    }

    // Сбросим указатель на начало временного файла
    rewind(temp_file);
    freopen(filename, "w+", file);
    
    while (fgets(line, sizeof(line), temp_file)) {
        fputs(line, file);
    }

    // Освобождаем память и закрываем файлы
    regfree(&regex);
    fclose(file);
    fclose(temp_file);
}

void insert_text(const char *filename, const char *insert_text, int at_beginning) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    FILE *temp_file = tmpfile();
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        if (at_beginning) {
            fprintf(temp_file, "%s%s", insert_text, line);
        } else {
            fprintf(temp_file, "%s%s", line, insert_text);
        }
    }

    // Сбросим указатель на начало временного файла
    rewind(temp_file);
    freopen(filename, "w+", file);
    
    while (fgets(line, sizeof(line), temp_file)) {
        fputs(line, file);
    }

    // Закрываем файлы
    fclose(temp_file);
    fclose(file);
}

