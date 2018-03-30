#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "maze.h"
#include <QMainWindow>
#include <QWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Maze maze;
    QWidget* mazeWidgets[60][60];
    QWidget* charactor[60][60];

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int xpos,ypos;
    void initWidget();//初始化控件
    void showMaze();//显示迷宫

private:
    Ui::MainWindow *ui;

private slots:
    void createMazeBT();//创建迷宫按钮
    void showPathBT();//显示路径按钮

protected:
    void keyPressEvent(QKeyEvent * event);

};

#endif // MAINWINDOW_H
