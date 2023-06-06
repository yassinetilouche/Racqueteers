#ifndef MWIDGET_H
#define MWIDGET_H

#include <QWidget>

namespace Ui {
class Mwidget;
}

class Mwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Mwidget(QWidget *parent = nullptr);
    ~Mwidget();

private:
    Ui::Mwidget *ui;
};

#endif // MWIDGET_H
