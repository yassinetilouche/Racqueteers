#ifndef BIENVENUE_H
#define BIENVENUE_H

#include <QWidget>

namespace Ui {
class bienvenue;
}

class bienvenue : public QWidget
{
    Q_OBJECT

public:
    explicit bienvenue(QWidget *parent = nullptr);
    ~bienvenue();

private:
    Ui::bienvenue *ui;
};

#endif // BIENVENUE_H
