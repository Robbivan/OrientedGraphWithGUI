#ifndef GRAPH_H
#define GRAPH_H
#include "matrix.h"
#include <QPainter>

class Graph
{
public:
    Graph() = default;

    bool IsloadNewGraph(const QString& data);

    void paint(QPainter& painter,const QPoint& center) const;

private:
    Matrix<qint16> matrix_loaded;
};

#endif // GRAPH_H
