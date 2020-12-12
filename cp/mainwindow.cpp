#include "mainwindow.h"
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pan = new Panel();
    QDockWidget *dock = new QDockWidget("panel");
    dock->setWidget(pan);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    vw = new View();
    setCentralWidget(vw);

    precisionValue[0] = 0.025f; precisionValue[1] = 0.05f; precisionValue[2] = 0.075f;
    precisionValue[3] = 0.1f; precisionValue[4] = 0.125f; precisionValue[5] = 0.15f;
    precisionValue[6] = 0.175f; precisionValue[7] = 0.2f; precisionValue[8] = 0.25f;
    precisionValue[9] = 0.3f;

    pan->positionsOfPoints[0][0]->setValue(26);
    pan->positionsOfPoints[0][1]->setValue(13);
    pan->positionsOfPoints[1][0]->setValue(30);
    pan->positionsOfPoints[2][0]->setValue(20);
    pan->positionsOfPoints[2][1]->setValue(-13);
    pan->positionsOfPoints[3][0]->setValue(-26);
    pan->positionsOfPoints[3][1]->setValue(13);
    pan->positionsOfPoints[4][0]->setValue(-30);
    pan->positionsOfPoints[5][0]->setValue(-20);
    pan->positionsOfPoints[5][1]->setValue(-13);

    vw->change_points1(26, 0, 0);
    vw->change_points1(13, 0, 1);
    vw->change_points1(30, 1, 0);
    vw->change_points1(20, 2, 0);
    vw->change_points1(-13, 2, 1);
    vw->change_points2(-26, 0, 0);
    vw->change_points2(13, 0, 1);
    vw->change_points2(-30, 1, 0);
    vw->change_points2(-20, 2, 0);
    vw->change_points2(-13, 2, 1);

    connect(pan, SIGNAL(approximation_changed(int)),
            this, SLOT(change_appr(int)));
    connect(pan, SIGNAL(pos_fig_x_changed(int)),
            this, SLOT(change_pos_fig_x(int)));
    connect(pan, SIGNAL(pos_fig_y_changed(int)),
            this, SLOT(change_pos_fig_y(int)));
    connect(pan, SIGNAL(pos_fig_z_changed(int)),
            this, SLOT(change_pos_fig_z(int)));
    connect(pan, SIGNAL(plus_scale()),
            this, SLOT(plus_scale()));
    connect(pan, SIGNAL(minus_scale()),
            this, SLOT(minus_scale()));
    connect(pan, SIGNAL(display_carcass(bool)),
            this, SLOT(display_carcass(bool)));
    connect(pan, SIGNAL(push_apply()),
            this, SLOT(change_pos_lamp()));
    connect(pan, SIGNAL(first_point_changed_x(int)),
            this, SLOT(first_point_changed_x(int)));
    connect(pan, SIGNAL(first_point_changed_y(int)),
            this, SLOT(first_point_changed_y(int)));
    connect(pan, SIGNAL(first_point_changed_z(int)),
            this, SLOT(first_point_changed_z(int)));
    connect(pan, SIGNAL(second_point_changed_x(int)),
            this, SLOT(second_point_changed_x(int)));
    connect(pan, SIGNAL(second_point_changed_y(int)),
            this, SLOT(second_point_changed_y(int)));
    connect(pan, SIGNAL(second_point_changed_z(int)),
            this, SLOT(second_point_changed_z(int)));
    connect(pan, SIGNAL(third_point_changed_x(int)),
            this, SLOT(third_point_changed_x(int)));
    connect(pan, SIGNAL(third_point_changed_y(int)),
            this, SLOT(third_point_changed_y(int)));
    connect(pan, SIGNAL(third_point_changed_z(int)),
            this, SLOT(third_point_changed_z(int)));
    connect(pan, SIGNAL(fourth_point_changed_x(int)),
            this, SLOT(fourth_point_changed_x(int)));
    connect(pan, SIGNAL(fourth_point_changed_y(int)),
            this, SLOT(fourth_point_changed_y(int)));
    connect(pan, SIGNAL(fourth_point_changed_z(int)),
            this, SLOT(fourth_point_changed_z(int)));
    connect(pan, SIGNAL(fifth_point_changed_x(int)),
            this, SLOT(fifth_point_changed_x(int)));
    connect(pan, SIGNAL(fifth_point_changed_y(int)),
            this, SLOT(fifth_point_changed_y(int)));
    connect(pan, SIGNAL(fifth_point_changed_z(int)),
            this, SLOT(fifth_point_changed_z(int)));
    connect(pan, SIGNAL(sixth_point_changed_x(int)),
            this, SLOT(sixth_point_changed_x(int)));
    connect(pan, SIGNAL(sixth_point_changed_y(int)),
            this, SLOT(sixth_point_changed_y(int)));
    connect(pan, SIGNAL(sixth_point_changed_z(int)),
            this, SLOT(sixth_point_changed_z(int)));
}

MainWindow::~MainWindow() {

}

void MainWindow::change_appr(int sliderValue) {
    vw->set_step(precisionValue[sliderValue - 1]);
    vw->updateGL();
}

void MainWindow::change_pos_fig_x(int newAngle) {
    vw->set_angle_x(newAngle);
    vw->updateGL();
}

void MainWindow::change_pos_fig_y(int newAngle) {
    vw->set_angle_y(newAngle);
    vw->updateGL();
}

void MainWindow::change_pos_fig_z(int newAngle) {
    vw->set_angle_z(newAngle);
    vw->updateGL();
}

void MainWindow::plus_scale() {
    vw->change_scale(0.25f);
    vw->updateGL();
}

void MainWindow::minus_scale() {
    if (vw->get_scale() <= 0.25f) {
        return;
    }
    vw->change_scale(-0.25f);
    vw->updateGL();
}

void MainWindow::display_carcass(bool) {
    vw->change_display_carcass();
    vw->updateGL();
}

void MainWindow::change_pos_lamp() {
    vw->set_light_position_x(pan->get_lamp_pos_x());
    vw->set_light_position_y(pan->get_lamp_pos_y());
    vw->set_light_position_z(pan->get_lamp_pos_z());
    vw->updateGL();
}

void MainWindow::first_point_changed_x(int value) {
    vw->change_points1(static_cast<float>(value), 0, 0);
    vw->updateGL();
}

void MainWindow::first_point_changed_y(int value) {
    vw->change_points1(static_cast<float>(value), 0, 1);
    vw->updateGL();
}

void MainWindow::first_point_changed_z(int value) {
    vw->change_points1(static_cast<float>(value), 0, 2);
    vw->updateGL();
}

void MainWindow::second_point_changed_x(int value) {
    vw->change_points1(static_cast<float>(value), 1, 0);
    vw->updateGL();
}

void MainWindow::second_point_changed_y(int value) {
    vw->change_points1(static_cast<float>(value), 1, 1);
    vw->updateGL();
}

void MainWindow::second_point_changed_z(int value) {
    vw->change_points1(static_cast<float>(value), 1, 2);
    vw->updateGL();
}

void MainWindow::third_point_changed_x(int value) {
    vw->change_points1(static_cast<float>(value), 2, 0);
    vw->updateGL();
}

void MainWindow::third_point_changed_y(int value) {
    vw->change_points1(static_cast<float>(value), 2, 1);
    vw->updateGL();
}

void MainWindow::third_point_changed_z(int value) {
    vw->change_points1(static_cast<float>(value), 2, 2);
    vw->updateGL();
}

void MainWindow::fourth_point_changed_x(int value) {
    vw->change_points2(static_cast<float>(value), 0, 0);
    vw->updateGL();
}

void MainWindow::fourth_point_changed_y(int value) {
    vw->change_points2(static_cast<float>(value), 0, 1);
    vw->updateGL();
}

void MainWindow::fourth_point_changed_z(int value) {
    vw->change_points2(static_cast<float>(value), 0, 2);
    vw->updateGL();
}

void MainWindow::fifth_point_changed_x(int value) {
    vw->change_points2(static_cast<float>(value), 1, 0);
    vw->updateGL();
}

void MainWindow::fifth_point_changed_y(int value) {
    vw->change_points2(static_cast<float>(value), 1, 1);
    vw->updateGL();
}

void MainWindow::fifth_point_changed_z(int value) {
    vw->change_points2(static_cast<float>(value), 1, 2);
    vw->updateGL();
}

void MainWindow::sixth_point_changed_x(int value) {
    vw->change_points2(static_cast<float>(value), 2, 0);
    vw->updateGL();
}

void MainWindow::sixth_point_changed_y(int value) {
    vw->change_points2(static_cast<float>(value), 2, 1);
    vw->updateGL();
}

void MainWindow::sixth_point_changed_z(int value) {
    vw->change_points2(static_cast<float>(value), 2, 2);
    vw->updateGL();
}
