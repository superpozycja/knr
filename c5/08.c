#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day)
{
	int i, leap;
	if (year <= 0 || month <= 0 || day <= 0)
		return 0;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	if (year <= 0 || yearday <= 0)
		return;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

int main()
{
	int m, d;
	month_day(1988, 60, &m, &d);
	printf("%d/%d\n", d, m);
	int doy = day_of_year(1988, m, d);
	printf("%d\n", doy);

	month_day(1988, -3, &m, &d);
	printf("%d/%d\n", d, m);
	doy = day_of_year(1988, m, -d);
	printf("%d\n", doy);
	return 0;
}
