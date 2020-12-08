#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"
#include "panel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    View *vw;
    Panel *pan;
    double precisionValue[10];
public slots:
    void change_appr(int sliderValue);
    void display_additional_lines(bool);
};

#endif // MAINWINDOW_H
