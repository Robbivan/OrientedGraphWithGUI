#include "graph.h"
#include <iostream>

#include <QStringList>
#include <math.h>
#include <QDebug>


namespace{
    constexpr int radius = 110;
    constexpr int size_node = 25;
    constexpr int size_arrow = 20;
    constexpr double pi = 3.14159;
}

bool Graph::IsloadNewGraph(const QString& data)
{
    QStringList rows = data.split("\n");

    auto rows_size = rows.size();
    Matrix<qint16> matrix(rows_size);

    for(int i = 0; i< rows_size; ++i){
        QStringList items = rows[i].split(" ");

        if(items.size()!=rows_size){
            std::cerr<<"Количество строк не соответствует количеству столбцов"<<std::endl;
            return false;
        }

        for(int j=0; j<rows_size; ++j){
           matrix[i][j] = items[j].toShort();
        }
    }

    matrix_loaded = matrix;
    return true;
}

void Graph::paint(QPainter& painter,const QPoint& center) const
{

    size_t height = matrix_loaded.col_size();
    if(height == 0){
        return;
    }

    double angular_distance = 2*pi/height;

    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::black);

    auto point = QPoint(0,-radius);

    for(size_t i = 0; i < height;++i){

        double a_cos = cos(angular_distance*i);
        double a_sin = sin(angular_distance*i);

        auto dist_between_points = QPoint( point.x() * a_cos - point.y() * a_sin, point.x() * a_sin + point.y() * a_cos);

        painter.drawEllipse(center + dist_between_points, size_node, size_node);
        painter.drawText(center + dist_between_points + QPoint(-3,4),QString::number(i));
    }

    painter.setPen(Qt::magenta);
    painter.setBrush(Qt::magenta);

    point = QPoint(0,-radius);

    for (size_t i = 0; i < height;++i){
        for (size_t j = 0; j < height; ++j){

            if (matrix_loaded[i][j] && i!=j){

                double a_cos = cos(angular_distance*i);
                double a_sin = sin(angular_distance*i);

                auto first = center + QPoint( point.x() * a_cos - point.y() * a_sin, point.x() * a_sin + point.y() * a_cos);

                a_cos = cos(angular_distance*j);
                a_sin = sin(angular_distance*j);

                auto second = center + QPoint( point.x() * a_cos - point.y() * a_sin, point.x() * a_sin + point.y() * a_cos);

                double disx = second.x() - first.x();
                double disy = second.y() - first.y();

                double angle = atan2(disy, disx);

                QPointF point_sec(second.x() - (size_node+size_arrow) * cos(angle),second.y() - (size_node+size_arrow) * sin(angle));
                QPointF point_fir(first.x() + size_node * cos(angle), first.y() + size_node * sin(angle));


                painter.drawLine(point_fir,point_sec);
                painter.save();
                painter.translate(point_sec);
                painter.rotate(180/pi * angle);


                painter.drawLine(QPoint(0, -size_arrow/4), QPoint(size_arrow, 0));
                painter.drawLine(QPoint(size_arrow, 0), QPoint(0, size_arrow/4));

                painter.restore();
            }
        }
    }
}

