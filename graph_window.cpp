#include "graph_window.h"
#include <QVBoxLayout>
GraphWindow::GraphWindow(QWidget *parent) : QWidget(parent), graph(nullptr)
{
    setFixedSize(400,400);
}

void GraphWindow::updateGraph(std::unique_ptr<Graph> graph)
{
    this->graph = std::move(graph);
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
    if (graph){
         graph->paint(painter,center);
    }
    painter.end();
}


