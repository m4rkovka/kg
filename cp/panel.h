#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <vector>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>

class Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);
    float get_lamp_pos_x();
    float get_lamp_pos_y();
    float get_lamp_pos_z();
    void set_lamp_pos_x(float x);
    void set_lamp_pos_y(float y);
    void set_lamp_pos_z(float z);

    std::vector<std::vector<QSpinBox *>> positionsOfPoints;
private:
    QLabel *nameApproximation;
    QSlider *approximation;
    QSlider *pos_fig_x;
    QSlider *pos_fig_y;
    QSlider *pos_fig_z;
    QPushButton *plusScale;
    QPushButton *minusScale;
    QCheckBox *displayCarcass;
    QLabel *firstCurve;
    QLabel *secondCurve;
    QLabel *lamp_x;
    QLineEdit *lamp_x_input;
    QLabel *lamp_y;
    QLineEdit *lamp_y_input;
    QLabel *lamp_z;
    QLineEdit *lamp_z_input;
    QPushButton *apply;
signals:
    void approximation_changed(int);
    void pos_fig_x_changed(int);
    void pos_fig_y_changed(int);
    void pos_fig_z_changed(int);
    void plus_scale();
    void minus_scale();
    void display_carcass(bool);
    void push_apply();
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
public slots:
};

#endif // PANEL_H
