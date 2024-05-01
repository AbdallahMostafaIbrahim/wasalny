#ifndef CREATENEWCITY_H
#define CREATENEWCITY_H

#include <QDialog>

namespace Ui {
class createnewcity;
}

class createnewcity : public QDialog
{
    Q_OBJECT

public:
    explicit createnewcity(QWidget *parent = nullptr);
    ~createnewcity();

private slots:
    void on_OKButton_clicked();

private:
    Ui::createnewcity *ui;
};

#endif // CREATENEWCITY_H
