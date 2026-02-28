#ifndef PENSIONER_H
#define PENSIONER_H

#define MAX_PEOPLE 100
#define MAX_STR_LEN 100

typedef struct {
    char last_name[50];
    char first_name[50];
    char patronymic[50];
    char gender;
    char nationality[30];
    float height;
    float weight;
    int birth_year;
    int birth_month;
    int birth_day;
    char phone[15];
    char address[150];
} PENSIONER;

int read_pensioners(const char *filename, PENSIONER people[], int max_count);
void print_pensioner(PENSIONER p);
int is_pensioner(PENSIONER p, int current_year);
int years_on_pension(PENSIONER p, int current_year);
void save_pensioners_over_5_years(const char *in_filename, const char *out_filename, int current_year);

#endif
