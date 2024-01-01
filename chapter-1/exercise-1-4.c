#include <stdio.h>

int main(int argc, char *argv[]) {
    /*
     * Program to create a celsius to fahrenheit conversion
     * as a printed table
     * */

    int min, max, step;
    float cels, fahr;

    min = 0;
    max = 300;
    step = 10;
    fahr = min;

    printf("FAHRENHEIT | CELSIUS\n");
    while (fahr <= max) {
        // .0 indicates that number is a float
        cels = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f F    | %3.3f ºC\n", fahr, cels);
        fahr = fahr + step;
    }

    return 0;
}
