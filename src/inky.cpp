#include "inky.h"

Inky::Inky(Maze *maze_parent): Enemy(maze_parent), maze(maze_parent) {
    set_each_images("inky");
}

QPoint Inky::chase_strategy()
{
    QPoint target;
    QPoint player = maze->get_pacman_loc();
    QPoint pacman_dir = maze->get_pacman_dir();
    target = player - 4 * pacman_dir;
    return target;
}

char Inky::ghost_char()
{
    return 'i';
}

int Inky::enemy_base_time()
{
    return 9000;
}
