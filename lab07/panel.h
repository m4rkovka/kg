#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QCheckBox>
#include <QSlider>
#include <QLabel>

class Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);
private:
    QLabel *nameApproximation;
    QSlider *approximation;
    QCheckBox *dispalyAdditionalLines;
signals:
    void approximation_changed(int);
    void clicked_display_additional_lines(bool);
public slots:
};

#endif // PANEL_H
