#include "blinky.h"

Blinky::Blinky(Maze *maze_parent): Enemy(maze_parent), maze(maze_parent) {
    set_each_images("blinky");
}

QPoint Blinky::chase_strategy()
{
    QPoint pacman_pos = maze->get_pacman_loc();
    return pacman_pos;
}

char Blinky::ghost_char()
{
    return 'b';
}

int Blinky::enemy_base_time()
{
    return 0;
}
