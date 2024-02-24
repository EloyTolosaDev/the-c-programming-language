#include <stdio.h>

/**
 * Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers 
 * instead of indexing. 
 * */
 
int day_of_year_p(int year, int month, int day);
void month_day_p(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = { 
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, 
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} 
};

void exercise_5_9() {
    /**
     * TODO: no fucking clue
     * */
}


/**
 * day_of_year: set day of year from month & day. Returns -1 on error.
 * */
int day_of_year_p(int year, int month, int day) { 
    int i, leap;
    
    if (year < 0 || month <= 0 || day <= 0 || month > 12)
        return -1;
    
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (day > daytab[leap][month] )
        return -1;
    
    for (i = 1; i < month; i++) 
        day += daytab[leap][i];
    
    return day; 
} 

/**
 * month_day: set month, day from day of year
 * */
void month_day_p(int year, int yearday, int *pmonth, int *pday) { 
    int i, leap;
    
    if (year < 0 || yearday <= 0)
        return; /* pmonth and pday remain uninitialized */
    
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0; 
    for (i = 1; yearday > daytab[leap][i]; i++) 
        yearday -= daytab[leap][i]; 
    
    *pmonth = i; 
    *pday = yearday; 
}