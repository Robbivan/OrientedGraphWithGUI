#ifndef GRAPH_WINDOW_H
#define GRAPH_WINDOW_H

#include <QWidget>
#include "graph.h"

class GraphWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWindow(QWidget *parent = nullptr);
    void updateGraph(const Graph& graph);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Graph graph;
};

#endif // GRAPH_WINDOW_H
