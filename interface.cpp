#include "interface.h"
#include <QFile>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <stdexcept>
#include <QSizePolicy>

Interface::Interface(QWidget *parent) : QWidget(parent)
{
    graph_window = new GraphWindow(this);

    button_load_graph = new QPushButton("Load graph from file",this);

    error = new QLineEdit(this);

    auto common_layout = new QHBoxLayout(this);
    auto right_layout = new QVBoxLayout(this);
    auto left_layout = new QVBoxLayout(this);

    right_layout->addWidget(graph_window);
    left_layout->addWidget(button_load_graph);
    left_layout->addWidget(error);
    common_layout->addLayout(left_layout);
    common_layout->addLayout(right_layout);
    this->setLayout(common_layout);


    connect(button_load_graph,SIGNAL(clicked()),this,SLOT(openFile()));
}


void Interface::openFile()
{
    QFileDialog file_dialog;
    QString path = file_dialog.getOpenFileName(this, tr("Open graph"), QString(), tr("Text files (*.txt)"));
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        error->setText("Error can't open file");
        return;
    }

    QString data = file.readAll();
    if(data.isEmpty()){
        error->setText("File is empty!");
        return;
    }

    try {
        graph.loadNewGraph(data);

    }  catch (const std::logic_error& exc) {
        error->setText(exc.what());
        return;
    }
    updateGraphWindow();
    error->setText("File opened successfully");
}
void Interface::updateGraphWindow()
{
    graph_window->updateGraph(graph);
}
