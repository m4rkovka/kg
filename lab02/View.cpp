#include "View.h"
#include <QPainter>
#include <vector>
#include <QResizeEvent>
#include <algorithm>
#include <cmath>

View::View(QWidget *parent) : QWidget(parent), step(50)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);

    setAutoFillBackground(true);

    std::vector<double> a{2. * step, -2. * step, 0, 1};
    std::vector<double> b{-2. * step, -2. * step, 0, 1};
    std::vector<double> c{-2. * step, 2. * step, 0, 1};
    std::vector<double> d{2. * step, 2. * step, 0, 1};
    std::vector<double> a1{1. * step, -1.5 * step, static_cast<double>(step), 1};
    std::vector<double> b1{-1. * step, -1.5 * step, static_cast<double>(step), 1};
    std::vector<double> c1{-1. * step, 1.5 * step, static_cast<double>(step), 1};
    std::vector<double> d1{1. * step, 1.5 * step, static_cast<double>(step), 1};

    Polygon p;

    p.add_vertex(a);
    p.add_vertex(a1);
    p.add_vertex(d1);
    p.add_vertex(d);
    fig.add_polygon(p);
    p.clear_verticies();

    p.add_vertex(b);
    p.add_vertex(b1);
    p.add_vertex(a1);
    p.add_vertex(a);
    fig.add_polygon(p);
    p.clear_verticies();

    p.add_vertex(c);
    p.add_vertex(c1);
    p.add_vertex(b1);
    p.add_vertex(b);
    fig.add_polygon(p);
    p.clear_verticies();

    p.add_vertex(d);
    p.add_vertex(d1);
    p.add_vertex(c1);
    p.add_vertex(c);
    fig.add_polygon(p);
    p.clear_verticies();

    p.add_vertex(a1);
    p.add_vertex(b1);
    p.add_vertex(c1);
    p.add_vertex(d1);
    fig.add_polygon(p);
    p.clear_verticies();

    p.add_vertex(b);
    p.add_vertex(a);
    p.add_vertex(d);
    p.add_vertex(c);
    fig.add_polygon(p);
    p.clear_verticies();
}

Obelisk &View::get_obelisk() {
    return fig;
}

void View::paintEvent(QPaintEvent *) {
    QPainter ptr{this};
    ptr.setPen(QPen(Qt::black, 2));

    center_x = width() / 2;
    center_y = height() / 2;

    /***************************/
    fig.draw(&ptr, center_x, center_y);
    /***************************/
}

void View::resizeEvent(QResizeEvent *e) {
    if (e->oldSize().width() == -1 || e->oldSize().height() == -1)
        return;
    double coef_x = width() / static_cast<double>(e->oldSize().width());
    double coef_y = height() / static_cast<double>(e->oldSize().height());
    double coef_z = sqrt(std::pow(width(), 2) + std::pow(height(), 2))
                    / sqrt(std::pow(static_cast<double>(e->oldSize().width()), 2) + std::pow(static_cast<double>(e->oldSize().height()), 2));
    std::vector<std::vector<double>> matrix_s{
        std::vector<double>{coef_x, 0, 0, 0},
        std::vector<double>{0, coef_y, 0, 0},
        std::vector<double>{0, 0, coef_z, 0},
        std::vector<double>{0, 0, 0, 1}
    };
    fig.change_all_polygons(matrix_s);
    update();
}

