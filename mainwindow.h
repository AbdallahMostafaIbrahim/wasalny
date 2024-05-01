#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QList>
#include "edge.h"
#include "map.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

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
    QGraphicsScene *scene;
    QList<Edge*> edges;
    Map map;
    void displayMap();
    void drawEdges();

};
#endif // MAINWINDOW_H
