/*
 * 窗口类中编写 初始化控件initWidget() 创建迷宫createMazeBT()
 * 显示迷宫 showMaze(),寻找路径 FindPathBT()，其中，createMazeBT()调用
 * Maze类中的createMaze方法，最后通过showMaze显示迷宫
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStyleFactory>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFocusPolicy(Qt::StrongFocus);
    initWidget();
}
//初始化控件
void MainWindow::initWidget()
{
    ui->spinBox->setStyle(QStyleFactory::create("Macintosh"));
    ui->CreateMazeBT->setStyle(QStyleFactory::create("fusion"));
    ui->ShowPathBT->setStyle(QStyleFactory::create("fusion"));
    connect(ui->CreateMazeBT,SIGNAL(clicked()),this,SLOT(createMazeBT()));
    connect(ui->ShowPathBT,SIGNAL(clicked()),this,SLOT(showPathBT()));

    ui->ShowPathBT->setEnabled(false);

    for(int i=0;i<60;i++){
        for(int j=0;j<60;j++){
            mazeWidgets[i][j] = new QWidget(this);
            mazeWidgets[i][j]->hide();

            charactor[i][j] = new QWidget(this);
            charactor[i][j]->hide();
        }
    }
}
//创建迷宫
void MainWindow::createMazeBT()
{
    xpos = 1;ypos=1;
    //检查是否输入的是奇数
    if(ui->spinBox->value()%2==0){
        QMessageBox::information(this,"警告","必须输入奇数",QMessageBox::Yes);
        return ;
    }
    maze.size = ui->spinBox->value();
    for(int i=0;i<60;i++){
        for(int j=0;j<60;j++){
            mazeWidgets[i][j]->setStyleSheet("");
            mazeWidgets[i][j]->hide();

            charactor[i][j]->setStyleSheet("");
            charactor[i][j]->hide();
        }
    }

    maze.initMaze(ui->spinBox->value());
    maze.createMaze();

    showMaze();
}
//显示迷宫
void MainWindow::showMaze()
{
    if(maze.size*30+80<=320){
        this->setGeometry(40,40,240+maze.size*40,320);
    }else{
        this->setGeometry(40,40,240+maze.size*40,maze.size*40+80);
    }
    ui->groupBox->move(width()-180,10);
    for(int i=0;i<maze.size;i++){
        for(int j=0;j<maze.size;j++){
            mazeWidgets[i][j]->show();
            charactor[i][j]->show();
            mazeWidgets[i][j]->setGeometry(40+j*40,40+i*40,40,40);
            charactor[i][j]->setGeometry(40+j*40,40+i*40,40,40);

            if(maze.matrix[i][j].state==1){
                mazeWidgets[i][j]->setStyleSheet("border-image:url(:/page/image/Wall.png);");//墙的图片
            }else{
                mazeWidgets[i][j]->setStyleSheet("border-image:url(:/page/image/Road.png);");//路的图片
            }
        }

    }
    mazeWidgets[1][0]->setStyleSheet("border-image:url(:/page/image/path.png);");//入口图片
    charactor[1][1]->setStyleSheet("border-image:url(:/page/image/path.png);");
    mazeWidgets[maze.size-2][maze.size-1]->setStyleSheet("border-image:url(:/page/image/exit.png);");//出口图片

    ui->ShowPathBT->setEnabled(true);
}
//显示路径
void MainWindow::showPathBT()
{
    maze.findPath();
    mazeWidgets[xpos][ypos]->setStyleSheet("");
    for(int i=0;i<maze.pathLength;i++){
        int row = maze.path[i].row;
        int col = maze.path[i].col;
        mazeWidgets[row][col]->setStyleSheet("border-image:url(:/page/image/path.png);");//通路的图片
    }
}
//控制人物
void MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_W :
            if(maze.matrix[xpos-1][ypos].state==0){
                charactor[xpos][ypos]->setStyleSheet("");
                charactor[xpos-1][ypos]->setStyleSheet("border-image:url(:/page/image/path.png);");
                xpos--;
            }
            break;
    case Qt::Key_S :
        if(maze.matrix[xpos+1][ypos].state==0){
            charactor[xpos+1][ypos]->show();
            charactor[xpos][ypos]->setStyleSheet("");
            charactor[xpos+1][ypos]->setStyleSheet("border-image:url(:/page/image/path.png);");
            xpos++;
         }
        break;
    case Qt::Key_A:
        if(maze.matrix[xpos][ypos-1].state==0){
            charactor[xpos][ypos-1]->show();
            charactor[xpos][ypos]->setStyleSheet("");
            charactor[xpos][ypos-1]->setStyleSheet("border-image:url(:/page/image/path.png);");
            ypos--;
         }
        break;
    case Qt::Key_D:
        if(maze.matrix[xpos][ypos+1].state==0){
            charactor[xpos][ypos+1]->show();
            charactor[xpos][ypos]->setStyleSheet("");
            charactor[xpos][ypos+1]->setStyleSheet("border-image:url(:/page/image/path.png);");
            ypos++;
         }
        break;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
