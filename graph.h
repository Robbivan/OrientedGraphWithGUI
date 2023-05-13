#ifndef GRAPH_H
#define GRAPH_H
#include "matrix.h"
#include <QPainter>

class Graph
{
public:
    Graph();
    void loadNewGraph(const QString& data);
    void paint(QPainter& painter,const QPoint& center) const;
private:
    Matrix<qint16> loaded_matrix;
};

#endif // GRAPH_H
