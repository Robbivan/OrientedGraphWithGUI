#ifndef GRAPH_WINDOW_H
#define GRAPH_WINDOW_H

#include <QWidget>
#include "graph.h"

class GraphWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWindow(QWidget *parent = nullptr);
    void updateGraph(std::unique_ptr<Graph> graph);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::unique_ptr<Graph> graph;
};

#endif // GRAPH_WINDOW_H
