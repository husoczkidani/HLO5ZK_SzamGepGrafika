#include "brick.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    Brick brick;
    double volume;
    double surface;

    set_size(&brick, 2, 5 ,5);

    volume = calc_volume(&brick);
    printf("Brick volume: %lf \n", volume);

    printf("\n");

    surface = calc_surface(&brick);
    printf("Brick surface: %lf \n", surface);

    printf("\n");
    do_square_exist(&brick);

}