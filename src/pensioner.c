#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pensioner.h"

int read_pensioners(const char *filename, PENSIONER people[], int max_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return 0;
    }
    
    int count = 0;
    while (count < max_count && 
           fscanf(file, "%s %s %s %c %s %f %f %d %d %d %s %[^\n]",
                  people[count].last_name,
                  people[count].first_name,
                  people[count].patronymic,
                  &people[count].gender,
                  people[count].nationality,
                  &people[count].height,
                  &people[count].weight,
                  &people[count].birth_year,
                  &people[count].birth_month,
                  &people[count].birth_day,
                  people[count].phone,
                  people[count].address) == 12) {
        count++;
    }
    
    fclose(file);
    return count;
}

void print_pensioner(PENSIONER p) {
    printf("%s %s %s, %c, %s, %.1fсм, %.1fкг, %d.%d.%d, тел:%s, адрес:%s\n",
           p.last_name, p.first_name, p.patronymic,
           p.gender, p.nationality, p.height, p.weight,
           p.birth_day, p.birth_month, p.birth_year,
           p.phone, p.address);
}

int is_pensioner(PENSIONER p, int current_year) {
    int age = current_year - p.birth_year;
    
    if (p.gender == 'M' || p.gender == 'm') {
        return age >= 65;
    } else {
        return age >= 60;
    }
}

int years_on_pension(PENSIONER p, int current_year) {
    int age = current_year - p.birth_year;
    int pension_age = (p.gender == 'M' || p.gender == 'm') ? 65 : 60;
    
    if (age >= pension_age) {
        return age - pension_age;
    }
    return 0;
}

void save_pensioners_over_5_years(const char *in_filename, const char *out_filename, int current_year) {
    PENSIONER people[MAX_PEOPLE];
    int count = read_pensioners(in_filename, people, MAX_PEOPLE);
    
    if (count == 0) {
        printf("Нет данных для обработки\n");
        return;
    }
    
    FILE *out_file = fopen(out_filename, "w");
    if (out_file == NULL) {
        printf("Ошибка создания файла %s\n", out_filename);
        return;
    }
    
    fprintf(out_file, "Пенсионеры со стажем более 5 лет (текущий год: %d):\n", current_year);
    fprintf(out_file, "------------------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (is_pensioner(people[i], current_year) && 
            years_on_pension(people[i], current_year) > 5) {
            
            fprintf(out_file, "%s %s %s, %c, %s, %.1fсм, %.1fкг, %d.%d.%d, тел:%s, адрес:%s\n",
                    people[i].last_name, people[i].first_name, people[i].patronymic,
                    people[i].gender, people[i].nationality, people[i].height, people[i].weight,
                    people[i].birth_day, people[i].birth_month, people[i].birth_year,
                    people[i].phone, people[i].address);
            found++;
        }
    }
    
    if (found == 0) {
        fprintf(out_file, "Таких пенсионеров не найдено.\n");
    }
    
    fclose(out_file);
    printf("Обработано %d записей. Результат сохранен в %s\n", count, out_filename);
}
