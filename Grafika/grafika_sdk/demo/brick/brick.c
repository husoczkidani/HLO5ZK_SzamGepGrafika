#include "brick.h"

#include <math.h>

double set_size(Brick* brick, double a, double b, double c)
{
    if(a>0)
    {
        brick->a = a;
    }else
    {
        brick->a = NAN;
    }

    if(b>0)
    {
        brick->b = b;
    }else
    {
        brick->b = NAN;
    }

    if(c>0)
    {
        brick->c = c;
    }else
    {
        brick->c = NAN;
    }
}

double calc_volume(const Brick* brick)
{
    double volume = brick->a * brick->b * brick->c;
    return volume;
}

double calc_surface(const Brick* brick)
{
    double surface = 2 * brick->a * brick->c + 2 * brick->a * brick->b + 2 * brick->b * brick->c;
    return surface;
}
void do_square_exist(const Brick* brick)
{
    if(brick->a == brick->b || brick->a == brick->c || brick->b == brick->c)
    {
        printf("Van negyzet alaku oldala!");
    }
    else
    {
        printf("Nincs negyzet alaku oldala!");
    }
}