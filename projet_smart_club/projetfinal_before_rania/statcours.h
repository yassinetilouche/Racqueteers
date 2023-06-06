#ifndef STATCOURS_H
#define STATCOURS_H

#include <QDialog>

namespace Ui {
class statcours;
}

class statcours : public QDialog
{
    Q_OBJECT

public:
    explicit statcours(QWidget *parent = nullptr);
    ~statcours();

private:
    Ui::statcours *ui;
};

#endif // STATCOURS_H
