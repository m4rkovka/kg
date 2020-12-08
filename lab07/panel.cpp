#include "panel.h"
#include <QVBoxLayout>

Panel::Panel(QWidget *parent) : QWidget(parent) {
    nameApproximation = new QLabel("Approximation", this);

    approximation = new QSlider(Qt::Horizontal);
    approximation->setMinimum(1);
    approximation->setMaximum(10);
    approximation->setTickPosition(QSlider::TicksAbove);
    approximation->setTickInterval(1);
    approximation->setValue(1);

    dispalyAdditionalLines = new QCheckBox("Display additional lines", this);

    QVBoxLayout *lout = new QVBoxLayout;
    lout->addWidget(nameApproximation);
    lout->addWidget(approximation);
    lout->addWidget(dispalyAdditionalLines);
    lout->addStretch();
    setLayout(lout);

    connect(approximation, SIGNAL(valueChanged(int)),
            this, SIGNAL(approximation_changed(int)));
    connect(dispalyAdditionalLines, SIGNAL(clicked(bool)),
            this, SIGNAL(clicked_display_additional_lines(bool)));
}
