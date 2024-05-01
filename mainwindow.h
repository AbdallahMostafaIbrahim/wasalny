#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QList>
#include "edge.h"
#include "node.h"
#include "map.h"
#include "mapscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum UIState {
    HOME_UI,
    EDGE_UI,
    NODE_UI
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    MapScene *scene;
    QList<Edge*> edges;
    QList<Node*> nodes;
    Map map;
    UIState uiState;
    void displayMap();
    void drawEdges();
    void createNode(int x, int y, QString city);

};
#endif // MAINWINDOW_H
