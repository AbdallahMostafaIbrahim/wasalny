#ifndef NEWCITY_H
#define NEWCITY_H

#include <QDialog>

namespace Ui {
class create;
}
QT_END_NAMESPACE

class newcity : public QDialog
{
    Q_OBJECT

public:
    explicit newcity(QWidget *parent = nullptr);
    ~newcity();

private slots:
    void on_OKButton_clicked();

private:
    Ui::newcity *ui;
};

#endif // NEWCITY_H
