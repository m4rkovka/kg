#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"
#include "panel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    View *vw;
    Panel *pan;
    float precisionValue[10];
public slots:
    void change_appr(int sliderValue);
    void change_pos_fig_x(int);
    void change_pos_fig_y(int);
    void change_pos_fig_z(int);
    void plus_scale();
    void minus_scale();
    void display_carcass(bool);
    void change_pos_lamp();
    void first_point_changed_x(int);
    void first_point_changed_y(int);
    void first_point_changed_z(int);
    void second_point_changed_x(int);
    void second_point_changed_y(int);
    void second_point_changed_z(int);
    void third_point_changed_x(int);
    void third_point_changed_y(int);
    void third_point_changed_z(int);
    void fourth_point_changed_x(int);
    void fourth_point_changed_y(int);
    void fourth_point_changed_z(int);
    void fifth_point_changed_x(int);
    void fifth_point_changed_y(int);
    void fifth_point_changed_z(int);
    void sixth_point_changed_x(int);
    void sixth_point_changed_y(int);
    void sixth_point_changed_z(int);
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
