#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pan = new Panel();
    QDockWidget *dock = new QDockWidget("panel");
    dock->setWidget(pan);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    vw = new View();
    setCentralWidget(vw);

    precisionValue[0] = 0.025; precisionValue[1] = 0.05; precisionValue[2] = 0.075;
    precisionValue[3] = 0.1; precisionValue[4] = 0.125; precisionValue[5] = 0.15;
    precisionValue[6] = 0.175; precisionValue[7] = 0.2; precisionValue[8] = 0.25;
    precisionValue[9] = 0.3;

    connect(pan, SIGNAL(approximation_changed(int)),
            this, SLOT(change_appr(int)));
    connect(pan, SIGNAL(clicked_display_additional_lines(bool)),
            this, SLOT(display_additional_lines(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change_appr(int sliderValue) {
    vw->set_step(precisionValue[sliderValue - 1]);
    vw->update();
}

void MainWindow::display_additional_lines(bool) {
    vw->change_display_additional_line();
    vw->update();
}
