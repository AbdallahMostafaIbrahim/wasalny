#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "edge.h"
#include <QRandomGenerator>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include "createnewcity.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);

    map.addCity("Cairo", 250, 250);
    map.addCity("Alexandria", 50, 50);
    map.addCity("October", 80, 200);
    map.addEdge("Cairo", "Alexandria", 5);
    map.addEdge("Cairo", "October", 8);
    map.addEdge("Alexandria", "October", 12);

    displayMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayMap() {
    scene->clear();

    for (const auto& city : map.getCities()) {
        auto fromCoord = map.getCityCoordinate(city);
        float x = fromCoord.x;
        float y = fromCoord.y;

        Node* node = new Node(x, y, 20, 20, QString::fromStdString(city));
        scene->addItem(node);
        connect(node, &Node::positionChanged, this, [this, city](const QPointF& newPos) {
            map.setCityCoordinate(city, newPos.x() + 20 / 2, newPos.y() + 20 / 2);
            drawEdges();
            scene->update();
        });
    }

    drawEdges();
}

void MainWindow::drawEdges() {

    for (auto* edge : edges) {
        scene->removeItem(edge);
        delete edge;
    }
    edges.clear();

    for (const auto& city : map.getCities()) {
        MapCoordinates fromCoord = map.getCityCoordinate(city);
        for (const auto& edge : map.getEdges(city)) {
            MapCoordinates toCoord = map.getCityCoordinate(edge.first);
            Edge* e = new Edge(QPointF(fromCoord.x, fromCoord.y), QPointF(toCoord.x, toCoord.y), edge.second);
            scene->addItem(e);
            edges.append(e);
        }
    }
}

void MainWindow::on_createButton_clicked()
{
    //open crete a new window tab
    createnewcity *createWindow = new createnewcity();
    createWindow->show();
    //hide();
}


void MainWindow::on_searchButton_clicked()
{

}

