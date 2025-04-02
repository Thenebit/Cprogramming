//Exercise 5-9. Rewrite the routine day_of_year and month_day with pointers 
//instead of indexing

#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 31, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 31, 31}
};

//day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day)
{
        int i, leap;

        if(month < 1 || month > 12){
		printf("invalid month (%d) !!\n", month);

	      	return -1;
        }

        // determine if the year is a leap year
        leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

        if(day < 1 || day > *(*(daytab + leap) + month)){
                printf("invalid day(%d) !!\n", day);

                return -1;
        }

        // calculate day of the year
        for (i = 1; i < month; i++) {
                day += *(*(daytab + leap) + i);
        }

        return day;
}

//month_day: set month, day from day of year
void month_day(int year, int yearday, int *ptrmonth, int *ptrday)
{
        int i, leap;

        leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

        if( !(yearday >= 1 && yearday <= (leap ? 366 : 365))){
		*ptrmonth = *ptrday = -1;

		return;
	}

        for(i = 1; yearday > *(*(daytab + leap) + i); i++)
                yearday -= *(*(daytab + leap) + i);

        *ptrmonth = i;
        *ptrday = yearday;
}

int main(void)
{
        int year, month, day, yearday, result;

        //first test on  day of the year
        year = 2025;
        month = 5;
        day = 29;
        result = day_of_year(year, month, day);

        if(result != -1){
                printf("%d|%d|%d = %d\n", year, month, day, result);
        }else{
                printf("invalid input(%d, %d, %d)\n", year, month, day);

                return -1;
	}

        //second test for month_day
        yearday = 50;
        int pmonth, pday;
        month_day(year, yearday, &pmonth, &pday);

        if(pmonth != -1 && pday != -1)
                printf("month and day for day %d of year %d = %d|%d\n", yearday, year, pmonth, pday);
        else
                printf("invalid input for month_day(%d, %d)\n", year, yearday);

        return 0;
}
