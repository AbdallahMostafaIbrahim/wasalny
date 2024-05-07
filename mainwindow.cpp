#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "edge.h"
#include "mapscene.h"
#include "map.h"
#include <QRandomGenerator>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <string>
#include <QList>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(new MapScene(this))
{

    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->stackedWidget->setCurrentIndex(HOME_UI);
    QFile mapfile(":/map.txt");



    map=Loader::loadMap();
    if(map.getCities().size()==0)
    {

        map.addCity("Cairo", 250, 250);
        map.addCity("Alexandria", 50, 50);
        map.addCity("October", 80, 200);
        map.addCity("Aswan", 300, 100);
        map.addEdge("Cairo", "Alexandria", 5);
        map.addEdge("Cairo", "October", 8);
        map.addEdge("Alexandria", "October", 12);
        map.addEdge("Aswan", "Cairo", 8);
        map.addEdge("Aswan", "Alexandria", 10);
    }

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
    updateAllComboboxes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Map *MainWindow::getMap()
{
    return &map;
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

void MainWindow::updateAllComboboxes()
{
    QList<QString> cities;
    for(const auto& city : map.getCities()) {
        cities.append(QString::fromStdString(city));
    }
    ui->cityRouteSelector->clear();
    ui->cityRouteSelector->addItems(cities);
    ui->fromCombobox->clear();
    ui->fromCombobox->addItems(cities);
    ui->toCombobox->clear();
    ui->toCombobox->addItems(cities);
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
    QString city = ui->createCityName->text();
    map.addCity(city.toStdString(), 10, 10);
    createNode(10, 10, city);
    scene->update();
    ui->createCityName->clear();
    updateAllComboboxes();
}


void MainWindow::on_searchButton_clicked()
{
    string from = ui -> fromCombobox -> currentText().toStdString();
    string to = ui -> toCombobox -> currentText().toStdString();
    int distance = 0;
    vector<string> path;
    map.findShortestPath(from, to, distance, path);
    ui -> distanceCalculatedLabel -> setText(QString :: number(distance));
    QString pathText;
    for (size_t i = 0; i < path.size(); ++i) {
        if(i != path.size() - 1) {
            for(auto& edge: edges) {
                if(path[i] == edge->getFromCity().toStdString() && path[i+1] == edge->getToCity().toStdString()) {
                    edge->focusIn();
                    break;
                }
            }
        }

        if (i > 0) {
            pathText += " -> ";
        }
        pathText += QString::fromStdString(path[i]);
    }
    ui->pathCalculatedLabel->setText(pathText);
}

void MainWindow::on_deleteNodeButton_clicked()
{
    if(uiState == NODE_UI && currentNode) {
        map.removeCity(currentNode->getCity().toStdString());
        removeAndDeleteNode(currentNode->getCity());
        drawEdges();
        scene->update();
        updateAllComboboxes();
        uiState = HOME_UI;
        ui->stackedWidget->setCurrentIndex(HOME_UI);
    }
}

void MainWindow::on_addRouteButton_clicked()
{
    QString toCity = ui->cityRouteSelector->currentText();
    if(toCity.isEmpty()) return;
    QString fromCity = currentNode->getCity();
    int distance = ui->distanceLineEdit->text().toInt();
    map.addEdge(fromCity.toStdString(), toCity.toStdString(), distance);
    drawEdges();
    ui->distanceLineEdit->clear();
    ui->cityRouteSelector->setCurrentIndex(-1);
}

void MainWindow::on_deleteEdgeButton_clicked()
{
    map.deleteEdge(currentEdge->getFromCity().toStdString(), currentEdge->getToCity().toStdString());
    uiState = HOME_UI;
    ui->stackedWidget->setCurrentIndex(HOME_UI);
    drawEdges();
}

void MainWindow::on_updateDistanceButton_clicked()
{
    int distance = ui->changeDistanceLineEdit->text().toInt();
    map.addEdge(currentEdge->getFromCity().toStdString(), currentEdge->getToCity().toStdString(), distance);
    drawEdges();
}

