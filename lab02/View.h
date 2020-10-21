#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <obelisk.h>

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    int get_center_x();
    int get_center_y();
    Obelisk &get_obelisk();
private:
    int center_x;
    int center_y;
    int step;
    Obelisk fig;
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
signals:

public slots:
};

#endif // VIEW_H
