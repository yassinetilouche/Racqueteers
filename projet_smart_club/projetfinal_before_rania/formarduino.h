#ifndef FORMARDUINO_H
#define FORMARDUINO_H

#include <QWidget>

namespace Ui {
class FormArduino;
}

class FormArduino : public QWidget
{
    Q_OBJECT

public:
    explicit FormArduino(QWidget *parent = nullptr);
    ~FormArduino();

private:
    Ui::FormArduino *ui;
};

#endif // FORMARDUINO_H
