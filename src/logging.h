#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <time.h>
#include <string.h>

// Макрос для логгирования начала функции
#define LOG_FUNCTION_START(func_name, ...) \
    do { \
        time_t now = time(0); \
        char* time_str = ctime(&now); \
        time_str[strlen(time_str) - 1] = '\0'; \
        fprintf(log_file, "[START] %s: %s", time_str, func_name); \
        if (sizeof(#__VA_ARGS__) > 1) { \
            fprintf(log_file, " - " __VA_ARGS__); \
        } \
        fprintf(log_file, "\n"); \
        fflush(log_file); \
    } while(0)

// Макрос для логгирования конца функции
#define LOG_FUNCTION_END(func_name, ...) \
    do { \
        time_t now = time(0); \
        char* time_str = ctime(&now); \
        time_str[strlen(time_str) - 1] = '\0'; \
        fprintf(log_file, "[END] %s: %s", time_str, func_name); \
        if (sizeof(#__VA_ARGS__) > 1) { \
            fprintf(log_file, " - " __VA_ARGS__); \
        } \
        fprintf(log_file, "\n"); \
        fflush(log_file); \
    } while(0)

// Инициализация логгера
void init_logger();
// Закрытие логгера
void close_logger();
// Глобальная переменная для файла лога
extern FILE* log_file;

#endif