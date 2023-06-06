#ifndef SCREENSHOT_H
#define SCREENSHOT_H


#include <QPixmap>
#include <QWidget>

QT_BEGIN_NAMESPACE

class QGridLayout;

class QHBoxLayout;
class QLabel;
class QPushButton;

class QVBoxLayout;
QT_END_NAMESPACE

class Screenshot : public QWidget
{
    Q_OBJECT

public:
    Screenshot();

private slots:
    void newScreenshot();
    void saveScreenshot();
    void shootScreen();

private:
    void updateScreenshotLabel();

    QPixmap originalPixmap;

    QLabel *screenshotLabel;
    QPushButton *newScreenshotButton;
};

#endif // SCREENSHOT_H
