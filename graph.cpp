#include "graph.h"
#include <stdexcept>
#include <QStringList>
#include <math.h>
#include <QDebug>

Graph::Graph()
{

}

void Graph::loadNewGraph(const QString &data)
{
    QStringList rows = data.split("\n");
    int rows_size = rows.size();

    Matrix<qint16> matrix(rows_size);

    for(int i = 0; i< rows_size; i++){
        QStringList elems = rows[i].split(" ");
        if(elems.size()!=rows_size){
            throw std::logic_error("the number of rows does not match the number of columns");
        }
        for(int j=0; j<rows_size; j++){
           matrix[i][j] = elems[j].toShort(); //без toShort возращает ошибку
        }
    }

    loaded_matrix = matrix;
}

void Graph::paint(QPainter& painter,const QPoint& center) const
{
    std::size_t height = loaded_matrix.hieght();
    if(height == 0) return;

    double degree_between_vertex = 2*3.14/height;

    int radius = 120;
    int size_node = 20;

    painter.setBrush(Qt::green);
    painter.setPen(Qt::black);

    auto point = QPoint(0,-radius);

    for(std::size_t i = 0; i < height;i++){
        auto angle_cos = cos(degree_between_vertex*i);
        auto angle_sin = sin(degree_between_vertex*i);
        auto diff_point = QPoint( point.x() * angle_cos - point.y() * angle_sin,
                                  point.x() * angle_sin + point.y() * angle_cos);
        painter.drawEllipse(center+diff_point,size_node,size_node);
        painter.drawText(center+diff_point+QPoint(-2,4),QString::number(i));
    }
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    point = QPoint(0,-radius);
    for(std::size_t i = 0; i < height;i++){
        for(std::size_t j= 0; j<height; j++){
            if(loaded_matrix[i][j] != 0 && i!=j){
                auto angle_cos = cos(degree_between_vertex*i);
                auto angle_sin = sin(degree_between_vertex*i);
                auto first = center+QPoint( point.x() * angle_cos - point.y() * angle_sin,
                                          point.x() * angle_sin + point.y() * angle_cos);
                angle_cos = cos(degree_between_vertex*j);
                angle_sin = sin(degree_between_vertex*j);
                auto second = center+QPoint( point.x() * angle_cos - point.y() * angle_sin,
                                          point.x() * angle_sin + point.y() * angle_cos);

                double dx = second.x() - first.x();
                double dy = second.y() - first.y();
                double angle = atan2(dy, dx);

                int size_arrow = 10;
                QPointF p2(second.x() - (size_node+size_arrow) * cos(angle),
                                   second.y() - (size_node+size_arrow) * sin(angle));
                QPointF p1(first.x() + size_node * cos(angle),
                                   first.y() + size_node * sin(angle));

                painter.drawLine(p1,p2);

//                QPolygon arrow;
//                arrow << QPoint(0, -size_arrow/4)
//                      << QPoint(size_arrow, 0)
//                      << QPoint(0, size_arrow/4);


                painter.save();
                painter.translate(p2);
                painter.rotate(180/3.14159 * angle);
                painter.drawLine(QPoint(0, -size_arrow/4),QPoint(size_arrow, 0));
                painter.drawLine(QPoint(size_arrow, 0), QPoint(0, size_arrow/4));

//                painter.drawConvexPolygon(arrow);
                painter.restore();
            }
        }
    }
}

