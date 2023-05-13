#include "graph_window.h"
#include <QVBoxLayout>
GraphWindow::GraphWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300,300);
}

void GraphWindow::updateGraph(const Graph &graph)
{
    this->graph = graph;
    repaint();
}

void GraphWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawRect(0,0,height(),width());

    QPoint center(height()/2,width()/2);
    graph.paint(painter,center);

    painter.end();
}


