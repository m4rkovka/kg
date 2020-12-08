#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QPointF>
#include <vector>

const unsigned int MAX_CNT_POINTS = 3;

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    void set_step(double s);
    void change_display_additional_line();
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    double step = 0.025;
    bool displayAdditionalLines = false;
    unsigned int cntPoints;
    std::vector<QPointF> points;
signals:

public slots:
};

#endif // VIEW_H
