#include "pinky.h"
#include <random>

Pinky::Pinky(Maze *maze_parent): Enemy(maze_parent), maze(maze_parent) {
    set_each_images("pinky");
    srand(time(NULL));
}

QPoint Pinky::chase_strategy()
{
    int i_num = (rand() % 31) + 1;
    int j_num = (rand() % 28) + 1;

    QPoint target = QPoint(i_num, j_num);

    return target;
}

char Pinky::ghost_char()
{
    return 'p';
}

int Pinky::enemy_base_time()
{
    return 6000;
}
