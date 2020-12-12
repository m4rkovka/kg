#include "panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

const unsigned int MAX_CNT_POINTS = 3;

Panel::Panel(QWidget *parent) : QWidget(parent) {
    nameApproximation = new QLabel("Approximation", this);

    approximation = new QSlider(Qt::Horizontal);
    approximation->setMinimum(1);
    approximation->setMaximum(10);
    approximation->setTickPosition(QSlider::TicksAbove);
    approximation->setTickInterval(1);
    approximation->setValue(1);

    pos_fig_x = new QSlider(Qt::Horizontal);
    pos_fig_x->setMinimum(0);
    pos_fig_x->setMaximum(360);
    pos_fig_x->setTickPosition(QSlider::TicksAbove);
    pos_fig_x->setTickInterval(5);
    pos_fig_x->setValue(0);

    pos_fig_y = new QSlider(Qt::Horizontal);
    pos_fig_y->setMinimum(0);
    pos_fig_y->setMaximum(360);
    pos_fig_y->setTickPosition(QSlider::TicksAbove);
    pos_fig_y->setTickInterval(5);
    pos_fig_y->setValue(0);

    pos_fig_z = new QSlider(Qt::Horizontal);
    pos_fig_z->setMinimum(0);
    pos_fig_z->setMaximum(360);
    pos_fig_z->setTickPosition(QSlider::TicksAbove);
    pos_fig_z->setTickInterval(5);
    pos_fig_z->setValue(0);

    plusScale = new QPushButton("+", this);
    minusScale = new QPushButton("-", this);

    displayCarcass = new QCheckBox("Display carcass", this);
    displayCarcass->setChecked(true);

    firstCurve = new QLabel("First Bezie curve", this);
    secondCurve = new QLabel("Second Bezie curve", this);

    for (unsigned int i = 0; i < 2 * MAX_CNT_POINTS; i++) {
        std::vector<QSpinBox *> help_vector(3);
        for (unsigned int j = 0; j < 3; j++) {
            help_vector[j] = new QSpinBox(this);
            help_vector[j]->setMinimum(-50);
            help_vector[j]->setMaximum(50);
            help_vector[j]->setSingleStep(1);
            help_vector[j]->setValue(0);
        }
        positionsOfPoints.push_back(help_vector);
    }

    lamp_x = new QLabel("Lamp position x:", this);
    lamp_x_input = new QLineEdit(this);
    lamp_y = new QLabel("Lamp position y:", this);
    lamp_y_input = new QLineEdit(this);
    lamp_z = new QLabel("Lamp position z:", this);
    lamp_z_input = new QLineEdit(this);
    apply = new QPushButton("Apply", this);

    QVBoxLayout *lout = new QVBoxLayout;
    lout->addWidget(nameApproximation);
    lout->addWidget(approximation);
    lout->addWidget(pos_fig_x);
    lout->addWidget(pos_fig_y);
    lout->addWidget(pos_fig_z);
    QHBoxLayout *layoutScale = new QHBoxLayout;
    layoutScale->addWidget(plusScale);
    layoutScale->addWidget(minusScale);
    lout->addItem(layoutScale);
    lout->addWidget(displayCarcass);
    lout->addWidget(firstCurve);
    QHBoxLayout *houtArr[MAX_CNT_POINTS];
    for (unsigned int i = 0; i < MAX_CNT_POINTS; i++) {
        QHBoxLayout *hout = new QHBoxLayout;
        for (unsigned int j = 0; j < 3; j++) {
            hout->addWidget(positionsOfPoints[i][j]);
        }
        houtArr[i] = hout;
    }
    for (unsigned int i = 0; i < MAX_CNT_POINTS; i++) {
        lout->addItem(houtArr[i]);
    }
    lout->addWidget(secondCurve);
    for (unsigned int i = 0; i < MAX_CNT_POINTS; i++) {
        QHBoxLayout *hout = new QHBoxLayout;
        for (unsigned int j = 0; j < 3; j++) {
            hout->addWidget(positionsOfPoints[i + MAX_CNT_POINTS][j]);
        }
        houtArr[i] = hout;
    }
    for (unsigned int i = 0; i < MAX_CNT_POINTS; i++) {
        lout->addItem(houtArr[i]);
    }
    lout->addWidget(lamp_x);
    lout->addWidget(lamp_x_input);
    lout->addWidget(lamp_y);
    lout->addWidget(lamp_y_input);
    lout->addWidget(lamp_z);
    lout->addWidget(lamp_z_input);
    lout->addWidget(apply);
    lout->addStretch();
    setLayout(lout);

    connect(approximation, SIGNAL(valueChanged(int)),
            this, SIGNAL(approximation_changed(int)));
    connect(pos_fig_x, SIGNAL(valueChanged(int)),
            this, SIGNAL(pos_fig_x_changed(int)));
    connect(pos_fig_y, SIGNAL(valueChanged(int)),
            this, SIGNAL(pos_fig_y_changed(int)));
    connect(pos_fig_z, SIGNAL(valueChanged(int)),
            this, SIGNAL(pos_fig_z_changed(int)));
    connect(plusScale, SIGNAL(pressed()),
            this, SIGNAL(plus_scale()));
    connect(minusScale, SIGNAL(pressed()),
            this, SIGNAL(minus_scale()));
    connect(displayCarcass, SIGNAL(clicked(bool)),
            this, SIGNAL(display_carcass(bool)));
    connect(apply, SIGNAL(pressed()),
                this, SIGNAL(push_apply()));
    connect(positionsOfPoints[0][0], SIGNAL(valueChanged(int)),
            this, SIGNAL(first_point_changed_x(int)));
    connect(positionsOfPoints[0][1], SIGNAL(valueChanged(int)),
            this, SIGNAL(first_point_changed_y(int)));
    connect(positionsOfPoints[0][2], SIGNAL(valueChanged(int)),
            this, SIGNAL(first_point_changed_z(int)));
    connect(positionsOfPoints[1][0], SIGNAL(valueChanged(int)),
            this, SIGNAL(second_point_changed_x(int)));
    connect(positionsOfPoints[1][1], SIGNAL(valueChanged(int)),
            this, SIGNAL(second_point_changed_y(int)));
    connect(positionsOfPoints[1][2], SIGNAL(valueChanged(int)),
            this, SIGNAL(second_point_changed_z(int)));
    connect(positionsOfPoints[2][0], SIGNAL(valueChanged(int)),
            this, SIGNAL(third_point_changed_x(int)));
    connect(positionsOfPoints[2][1], SIGNAL(valueChanged(int)),
            this, SIGNAL(third_point_changed_y(int)));
    connect(positionsOfPoints[2][2], SIGNAL(valueChanged(int)),
            this, SIGNAL(third_point_changed_z(int)));
    connect(positionsOfPoints[3][0], SIGNAL(valueChanged(int)),
            this, SIGNAL(fourth_point_changed_x(int)));
    connect(positionsOfPoints[3][1], SIGNAL(valueChanged(int)),
            this, SIGNAL(fourth_point_changed_y(int)));
    connect(positionsOfPoints[3][2], SIGNAL(valueChanged(int)),
            this, SIGNAL(fourth_point_changed_z(int)));
    connect(positionsOfPoints[4][0], SIGNAL(valueChanged(int)),
            this, SIGNAL(fifth_point_changed_x(int)));
    connect(positionsOfPoints[4][1], SIGNAL(valueChanged(int)),
            this, SIGNAL(fifth_point_changed_y(int)));
    connect(positionsOfPoints[4][2], SIGNAL(valueChanged(int)),
            this, SIGNAL(fifth_point_changed_z(int)));
    connect(positionsOfPoints[5][0], SIGNAL(valueChanged(int)),
            this, SIGNAL(sixth_point_changed_x(int)));
    connect(positionsOfPoints[5][1], SIGNAL(valueChanged(int)),
            this, SIGNAL(sixth_point_changed_y(int)));
    connect(positionsOfPoints[5][2], SIGNAL(valueChanged(int)),
            this, SIGNAL(sixth_point_changed_z(int)));
}

float Panel::get_lamp_pos_x() {
    return lamp_x_input->text().toFloat();
}

float Panel::get_lamp_pos_y() {
    return lamp_y_input->text().toFloat();
}

float Panel::get_lamp_pos_z() {
    return lamp_z_input->text().toFloat();
}

void Panel::set_lamp_pos_x(float x) {
    lamp_x_input->setText(QString::number(static_cast<double>(x)));
}

void Panel::set_lamp_pos_y(float y) {
    lamp_y_input->setText(QString::number(static_cast<double>(y)));
}

void Panel::set_lamp_pos_z(float z) {
    lamp_z_input->setText(QString::number(static_cast<double>(z)));
}
