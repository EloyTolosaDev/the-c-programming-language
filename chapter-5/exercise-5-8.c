#include <stdio.h>

/**
 * Exercise 5-8. There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 * */

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

#define ERROR(s) printf("[Error]: %s.\n ", s)
#define DEBUG(s) printf("[Debug]: %s.\n ", s)

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main(int argc, char **args) {
    int result = day_of_year(-1, 12, 12);
    if (result == -1)
	ERROR("year is negative");

    result = day_of_year(1, 0, 12);
    if (result == -1)
	ERROR("month 1/0/12 is negative or zero");

    result = day_of_year(12, 12, 0);
    if (result == -1)
	ERROR("day 12/12/0 is negative or zero");

    /**
     * Let's pick a 29 of february of last year. It should give an error
     * because last year was not a lap year.
     * */
    result = day_of_year(2023, 02, 29);
    if (result == -1)
	ERROR("day 29/02/2023 is out of bounds");

    result = day_of_year(2024, 02, 29);
    if (result > 0)
	DEBUG("Correct, 29/02/2024 is a correct date");
}

/**
 * day_of_year: set day of year from month & day. Returns -1 on error.
 * */
int day_of_year(int year, int month, int day) {
    int i, leap;

    if (year < 0 || month <= 0 || day <= 0 || month > 12)
	return -1;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (day > daytab[leap][month])
	return -1;

    for (i = 1; i < month; i++)
	day += daytab[leap][i];

    return day;
}

/**
 * month_day: set month, day from day of year
 * */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    if (year < 0 || yearday <= 0)
	return;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
	yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;
}
