#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "edge.h"
#include "mapscene.h"
#include "map.h"
#include <QRandomGenerator>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <string>
#include "createnewcity.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(new MapScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->stackedWidget->setCurrentIndex(HOME_UI);

    map.addCity("Cairo", 250, 250);
    map.addCity("Alexandria", 50, 50);
    map.addCity("October", 80, 200);
    map.addCity("Aswan", 300, 100);
    map.addEdge("Cairo", "Alexandria", 5);
    map.addEdge("Cairo", "October", 8);
    map.addEdge("Alexandria", "October", 12);
    map.addEdge("Aswan", "Cairo", 8);
    map.addEdge("Aswan", "Alexandria", 15);



    connect(scene, &MapScene::unFocusEverything, this, [this]() {
        // Unfocus the nodes and edges if I press anywhere outside them
        for(const auto& n: nodes) {
            n->focusOut();
        }
        for(const auto& e: edges) {
            e->focusOut();
        }
        uiState = HOME_UI;
        ui->stackedWidget->setCurrentIndex(HOME_UI);
    });

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

        createNode(x, y, QString::fromStdString(city));
    }

    drawEdges();
}

void MainWindow::createNode(int x, int y, QString city)
{
    Node* node = new Node(x, y, 20, 20, city);
    scene->addItem(node);
    connect(node, &Node::positionChanged, this, [this, city](const QPointF& newPos) {
        map.setCityCoordinate(city.toStdString(), newPos.x() + 20 / 2, newPos.y() + 20 / 2);
        drawEdges();
        scene->update();
    });
    connect(node, &Node::focused, this, [this, node]() {
        for(const auto& n: nodes) {
            if(n != node) {
                n->focusOut();
            }
        }
        for(const auto& e: edges) {
            e->focusOut();
        }
        uiState = NODE_UI;
        currentNode = node;
        ui->stackedWidget->setCurrentIndex(NODE_UI);
        scene->update();
    });
    nodes.append(node);
}

void MainWindow::removeAndDeleteNode(QString city)
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Node* item = *it;
        if (item->getCity() == city) {
            it = nodes.erase(it);
            scene->removeItem(item);
            delete item;
            break;
        }
    }
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
            Edge* e = new Edge(QPointF(fromCoord.x, fromCoord.y), QPointF(toCoord.x, toCoord.y), QString::fromStdString(city), QString::fromStdString(edge.first), edge.second);
            connect(e, &Edge::focused, this, [this, e]() {
                for(const auto& ed: edges) {
                    if(e != ed) {
                        ed->focusOut();
                    }
                }
                for(const auto& n: nodes) {
                    n->focusOut();
                }
                uiState = EDGE_UI;
                currentEdge = e;
                ui->stackedWidget->setCurrentIndex(EDGE_UI);
                scene->update();
            });
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
    // for ( auto &city : getCities()){   //check if cities are there
    //     string current = city;
    //     if (current )
    //             return;
    // }
    // if(ui -> fromLineedit -> text() == "" || ui -> toLineedit -> text())
    //     return;
    string from = ui -> fromLineedit -> text().toStdString();
    string to = ui -> toLineedit -> text().toStdString();
    int distance = 0;
    vector<string> path;
    map.findShortestPath(from, to, distance, path);
    ui -> DistanceCalculated_label -> setText(QString :: number(distance));
    for (auto &Path :path)
        ui -> PathCalculated_label -> setText(QString::fromStdString(Path));

}

void MainWindow::on_deleteNodeButton_clicked()
{
    if(uiState == NODE_UI && currentNode) {
        map.removeCity(currentNode->getCity().toStdString());
        removeAndDeleteNode(currentNode->getCity());
        drawEdges();
        scene->update();
    }
}

