#ifndef NEW_H
#define NEW_H

#include <QDialog>

namespace Ui {
class new;
}

class new : public QDialog
{
    Q_OBJECT

public:
    explicit new (QWidget *parent = nullptr);
    ~new ();

private:
    Ui::new *ui;
};

#endif // NEW_H
