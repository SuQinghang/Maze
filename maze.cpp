#include <iostream>
#include <ctime>
#include <windows.h>
#include <queue>
#include "maze.h"
#include "equivclass.h"
using namespace std;
//随机数产生
int randEx(){
    LARGE_INTEGER seed;
    QueryPerformanceFrequency(&seed);
    QueryPerformanceCounter(&seed);
    srand(seed.QuadPart);
    return rand();}
//maze的方法
//s应该为奇数
void Maze:: initMaze(int s){
    size = s;
    matrix  =new position*[size];
    for(int i=0;i<size;i++){
        matrix[i] = new position[size];
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            matrix[i][j].row = i;matrix[i][j].col = j;
            if(i%2==0||j%2==0){matrix[i][j].state=1;}
            else {matrix[i][j].state = 0;}
        }
    }
}
//选墙
void Maze::createMaze(){
        EquivClass equiv;
        equiv.initialize((size/2)*(size/2));

        int ypos1[size/2-1],ypos2[size/2];//当随机的横坐标为奇数，在ypos1中随机纵坐标，为偶数，在ypos2中
        for(int i=1;i<=size/2-1;i++){ypos1[i-1] = 2*i;}
        for(int i=0;i<size/2;i++){ypos2[i] = 2*i+1;}

        int xwall,ywall;
        while(equiv.find(0)!=equiv.find((size/2)*(size/2)-1)){
            xwall= randEx()%(size-2)+1;

            if(xwall%2==1){ywall = ypos1[randEx()%((size/2)-1)];}
                else{ywall = ypos2[randEx()%(size/2)];}

            //该墙为上下通路的分界线
            if(xwall%2==0){
                int up = ((xwall-1)/2)*(size/2)+ywall/2;
                int down = ((xwall+1)/2)*(size/2)+ywall/2;
                if(equiv.find(up)!=equiv.find(down)){
                    matrix[xwall][ywall].state=0;
                    equiv.combine(up,down);
                }else{continue;}
            }else{
                int left  = (xwall/2)*(size/2)+(ywall-1)/2;
                int right = (xwall/2)*(size/2)+(ywall+1)/2;
                if(equiv.find(left)!=equiv.find(right)){
                    matrix[xwall][ywall].state =0;
                    equiv.combine(left,right);
                }else{continue;}
            }
        }//while
        //最后把不连通的路都改成墙
        for(int i=0;i<(size/2)*(size/2);i++){
            if(equiv.find(i)!=equiv.find(0)){
                int x = 2*(i/(size/2))+1;//横坐标
                int y = 2*(i%(size/2))+1;//纵坐标
                matrix[x][y].state=1;
                matrix[x-1][y].state = 1;
                matrix[x+1][y].state = 1;
                matrix[x][y-1].state = 1;
                matrix[x][y+1].state = 1;
            }
        }
    }
void Maze::showMaze(){
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    cout<<matrix[i][j].state<<"\t";
                }
                cout<<endl;
            }
    }
void Maze::findPath(){
        position start,finish;
        start.row = 1;start.col = 1;
        finish.row = size-2;finish.col = size-2;
        if((start.row==finish.row)&&(start.col == finish.col)){
            return;
        }
        position offset[4];
        offset[0].row = 0;offset[0].col=1;//右
        offset[1].row = 1;offset[1].col=0;//下
        offset[2].row = 0;offset[2].col=-1;//左
        offset[3].row = -1;offset[3].col = 0;//上

        int NumOfNbrs = 4;
        position here ,nbr;
        here.row = start.row; here.col = start.col;

        matrix[start.row][start.col].state = 2;

        queue<position> Q;
        do{
            for(int k=0;k<NumOfNbrs;k++){
                nbr.row = here.row + offset[k].row;
                nbr.col = here.col + offset[k].col;

                if(matrix[nbr.row][nbr.col].state==0){
                    matrix[nbr.row][nbr.col].state= matrix[here.row][here.col].state+1;
                    Q.push(nbr);
                    if((nbr.row==finish.row)&&(nbr.col ==finish.col))
                        break;
                }//if
            }//for
            if((nbr.row==finish.row)&&(nbr.col == finish.col))//如果到达出口
            {
                break;
            }

            if(Q.empty()){
                break;//如果没有可走的路径
            }
            here = Q.front();//移动到nbr
            Q.pop();
        }while(true);

        pathLength = matrix[finish.row][finish.col].state-1;
        path = new position[pathLength];
        here = finish;
        for(int k = pathLength-1;k>=0;k--){
            path[k] = here;
            for(int m = 0;m<NumOfNbrs;m++){
                nbr.row = here.row + offset[m].row;
                nbr.col = here.col + offset[m].col;
                if(matrix[nbr.row][nbr.col].state==matrix[here.row][here.col].state-1)break;
            }
            here = nbr;
        }//for
    }

