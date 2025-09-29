#include "logging.h"
#include <stdio.h>
#include <stdlib.h>

FILE* log_file = NULL;

void init_logger() {
    log_file = fopen("tetris.log", "w");
    if (log_file == NULL) {
        fprintf(stderr, "Error: Could not open log file\n");
        exit(1);
    }
    
    time_t now = time(0);
    char* time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';
    
    fprintf(log_file, "[INIT] %s: Logger initialized\n", time_str);
    fflush(log_file);
}

void close_logger() {
    if (log_file != NULL) {
        time_t now = time(0);
        char* time_str = ctime(&now);
        time_str[strlen(time_str) - 1] = '\0';
        
        fprintf(log_file, "[CLOSE] %s: Logger closed\n", time_str);
        fclose(log_file);
        log_file = NULL;
    }
}