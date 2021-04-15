#ifndef ROOM_H
#define ROOM_H

#include <stdio.h> 
#include "scene.h"

enum { ROOM_LEFT = 0, ROOM_BACK, ROOM_RIGHT, ROOM_FRONT, ROOM_TOP, ROOM_BOTTOM }; 
unsigned int roombox[6]; /*the ids for the textures*/

void init_room();

void room_draw(struct Scene* scene, double size);

#endif /* ROOM_H */