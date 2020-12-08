#include "view.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPolygon>
#include <cmath>
#include <QResizeEvent>


const int SQUARE_SIZE = 10;

View::View(QWidget *parent) : QWidget(parent) {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(179, 179, 179));
    setPalette(pal);

    setAutoFillBackground(true);

    cntPoints = 0;
    points.resize(MAX_CNT_POINTS);
}

void View::set_step(double s) {
    step = s;
}

void View::change_display_additional_line() {
    if (displayAdditionalLines) {
        displayAdditionalLines = false;
    } else {
        displayAdditionalLines = true;
    }
}

void View::paintEvent(QPaintEvent *) {
    QPainter ptr{this};
    ptr.setPen(QColor(0, 0, 0));

    if (cntPoints != 0 && displayAdditionalLines) {
        ptr.setPen(Qt::DashLine);
        for (unsigned int i = 0; i < cntPoints - 1; i++) {
            ptr.drawLine(static_cast<int>(points[i].x()) + SQUARE_SIZE / 2,
                         static_cast<int>(points[i].y()) + SQUARE_SIZE / 2,
                         static_cast<int>(points[i + 1].x()) + SQUARE_SIZE / 2,
                         static_cast<int>(points[i + 1].y()) + SQUARE_SIZE / 2);
        }
        ptr.setPen(Qt::SolidLine);
    }

    ptr.setBrush(QColor(0, 0, 0));
    for (unsigned int i = 0; i < cntPoints; i++) {
        QPolygon pol(QRect(static_cast<int>(points[i].x()),
                           static_cast<int>(points[i].y()),
                           SQUARE_SIZE, SQUARE_SIZE));
        ptr.drawPolygon(pol);
    }

    if (cntPoints == 3) {
        // draw Bezier curve
        QPen newPen(QColor(255, 0, 0), 3);
        ptr.setPen(newPen);
        double prevX = points[0].x() + SQUARE_SIZE / 2, prevY = points[0].y() + SQUARE_SIZE / 2;
        for (double t = step; t < 1.; t += step) {
            double x =  std::pow((1. - t), 2.) * (points[0].x() + SQUARE_SIZE / 2) +
                        2. * t * (1. - t) * (points[1].x() + SQUARE_SIZE / 2) +
                        std::pow(t, 2.) * (points[2].x() + SQUARE_SIZE / 2);
            double y =  std::pow((1. - t), 2.) * (points[0].y() + SQUARE_SIZE / 2) +
                        2. * t * (1. - t) * (points[1].y() + SQUARE_SIZE / 2) +
                        std::pow(t, 2.) * (points[2].y() + SQUARE_SIZE / 2);
            ptr.drawLine(static_cast<int>(prevX),
                         static_cast<int>(prevY),
                         static_cast<int>(x),
                         static_cast<int>(y));
            prevX = x;
            prevY = y;
            if (t + step >= 1.) {
                x = points[2].x() + SQUARE_SIZE / 2;
                y = points[2].y() + SQUARE_SIZE / 2;
                ptr.drawLine(static_cast<int>(prevX),
                             static_cast<int>(prevY),
                             static_cast<int>(x),
                             static_cast<int>(y));
            }
        }
    }
}

void View::resizeEvent(QResizeEvent *e) {
    if (e->oldSize().width() == -1 || e->oldSize().height() == -1) {
        return;
    }
    double coef_x = width() / static_cast<double>(e->oldSize().width());
    double coef_y = height() / static_cast<double>(e->oldSize().height());

    for (unsigned int i = 0; i < cntPoints; i++) {
        points[i].rx() *= coef_x;
        points[i].ry() *= coef_y;
    }

    update();
}

void View::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton) {
        if (cntPoints < 3) {
            points[cntPoints] = e->pos();
            cntPoints++;
        }
    }

    update();
}

void View::mouseMoveEvent(QMouseEvent *e) {
    for (unsigned int i = 0; i < cntPoints; i++) {
        if (e->pos().x() >= points[i].x() - 20 && e->pos().x() <= points[i].x() + 20 &&
            e->pos().y() >= points[i].y() - 20 && e->pos().y() <= points[i].y() + 20) {
            points[i] = e->pos();
            break;
        }
    }

    update();
}


