#include <stdio.h>

/* I KNOW the tabs are inconsistent i changed my settings in between these
 * exercises dont kill me */

float fahr_to_celsius(float fahr)
{
	return (5.0/9.0) * (fahr-32.0);
}

int main() 
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("┌───────┬─────────┐\n");
    printf("│   F   │    C    │\n");
    printf("├───────┼─────────┤\n");

    fahr = lower;
    while (fahr <= upper) {
        celsius = fahr_to_celsius(fahr);
        printf("│   %3.0f │  %6.1f │\n", fahr, celsius);
        fahr = fahr + step;
    }
    printf("└───────┴─────────┘\n");
}
