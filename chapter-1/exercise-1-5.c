#include <stdio.h>

int main(int argc, char *argv[]) {
    /*
     * Program to create a celsius to fahrenheit conversion
     * as a printed table, BUT REVERSED
     * */
    printf("FAHRENHEIT | CELSIUS \n");
    for (float fahr = 300; fahr > 0; fahr -= 10) {
        float cels = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f F      | %3.1f ºC\n", fahr, cels);
    }

    return 0;
}
