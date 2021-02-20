#ifndef BRICK_H
#define BRICK_H

typedef struct Brick
{
    double a;
    double b;
    double c;
} Brick;
/**
* Set the data if the brick
*/

double set_size(Brick* brick, double a, double b, double c);

/**
*Calculate the volume of the brick
*/

double calc_volume(const Brick* brick);

/**
*Calculate the surface of the brick
*/

double calc_surface(const Brick* brick);

/**
*Searches for a square in the brick
*/

void do_square_exist(const Brick* brick);

#endif 