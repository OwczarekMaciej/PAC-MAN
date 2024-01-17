#include "clyde.h"

Clyde::Clyde(Maze *maze_parent): Enemy(maze_parent), maze(maze_parent) {
    set_each_images("clyde");
}

QPoint Clyde::chase_strategy() {
    QPoint target;
    QPoint player = maze->get_pacman_loc();
    QPoint pacman_dir = maze->get_pacman_dir();
    target = player + 4 * pacman_dir;
    return target;
}

char Clyde::ghost_char()
{
    return 'c';
}

int Clyde::enemy_base_time()
{
    return 3000;
}

