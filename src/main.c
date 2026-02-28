#include <stdio.h>
#include <time.h>
#include "pensioner.h"

int main(void) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900;
    
    printf("=== Программа обработки данных пенсионеров ===\n");
    printf("Текущий год: %d\n", current_year);
    
    char in_filename[100] = "data/pensioners.txt";
    char out_filename[100] = "data/pensioners_over_5_years.txt";
    
    save_pensioners_over_5_years(in_filename, out_filename, current_year);
    
    printf("Программа завершена.\n");
    return 0;
}
