#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include "graph_window.h"
#include "graph.h"
#include <QPushButton>
#include <QLineEdit>

class Interface : public QWidget
{
    Q_OBJECT
public:
    explicit Interface(QWidget *parent = nullptr);
    void updateGraphWindow();

public slots:
    void openFile();

private:
    Graph graph;

    QLineEdit* message;
    GraphWindow* graph_window;
    QPushButton* button_for_loading_graph;

};

#endif // INTERFACE_H
