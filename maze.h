#ifndef MAZE_H
#define MAZE_H

class position{
public:
    int row,col;
    int state;
};

class Maze{
public:
    position** matrix;
    int size;
    int pathLength;

    position* path;
    Maze(){}
    void initMaze(int s);
    void createMaze();
    void showMaze();
    void findPath();
};
#endif // MAZE_H
