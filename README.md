# Maze
use disjoint to create a maze randomly and find the shortest path
1/ 生成迷宫
   输入数值size为迷宫的大小，建立一个size * size 的二维数组，数组中的元素为position（position包含三个成员变量，分别为row，col，state，其中state为1表示该位置为墙，为0表示该位置为通路）。随机选择墙壁，如果选中的墙上下（左右）通路不在同一个等价类中，即两通路不连通，那么将该墙打通，并且将其连接的通路划分到同一个等价类中，直到入口（1，1）与出口（size-2，size-2)被划分到同一个等价类中；
2/ 在迷宫中最短通路
   对于当前已到达的position，将其上下左右可到达的position加入到队列中，并将这些position的state改为已到达位置的state+1，表示路径长度的增加，直到出口被标志；
   值得注意的：因为在寻路之前，每个position的state为0/1，所以，将入口的state修改为2，避免在后面的寻路中引起混淆；
