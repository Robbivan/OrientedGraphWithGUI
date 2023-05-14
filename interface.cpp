#include "interface.h"
#include <QFile>
#include <QFileDialog>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QHBoxLayout>

Interface::Interface(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(QStringLiteral("Лучшая прога для графов!!!"));
    graph_window = new GraphWindow(this);

    button_for_loading_graph = new QPushButton("Загрузить новый граф",this);

    message = new QLineEdit(this);


    message->setReadOnly(true);

    auto common_layout = new QHBoxLayout(this);
    auto right_layout = new QVBoxLayout(this);
    auto left_layout = new QVBoxLayout(this);


    right_layout->addWidget(button_for_loading_graph);
    right_layout->addWidget(message);
    left_layout->addWidget(graph_window);

    common_layout->addLayout(left_layout);
    common_layout->addLayout(right_layout);

    this->setLayout(common_layout);
    connect(button_for_loading_graph,SIGNAL(clicked()),this,SLOT(openFile()));
}


void Interface::openFile()
{
    QFileDialog dialog;
    QString path = dialog.getOpenFileName(this, tr("Открыть файл"), QString(), tr("Text files (*.txt)"));
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        message->setText("Ошибка, невозможно открыть файл ");
        return;
    }

    QString data = file.readAll();

    if(data.isEmpty()){
        message->setText("Файл пуст");
        return;
    }

    if(!graph.IsloadNewGraph(data)){
       message->setText("Матрица не квадратная");
       return;
    }

    updateGraphWindow();
    message->setText("Файл успешно открыт");
}
void Interface::updateGraphWindow()
{
    graph_window->updateGraph(std::make_unique<Graph>(graph));
}
