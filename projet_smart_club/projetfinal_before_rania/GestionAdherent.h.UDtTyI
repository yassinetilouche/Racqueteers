#ifndef GestionAdherent_H
#define GestionAdherent_H
#include "adherent.h"
#include"performance.h"
#include <QMainWindow>
#include "qrcode2.h"
#include <QMediaPlayer>
#include <QDebug>
#include <QPropertyAnimation>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QWidget>
#include "mainwindow.h"
#include <searchbox.h>

QT_BEGIN_NAMESPACE


namespace Ui {
class GestionAdherent;
}QT_END_NAMESPACE


class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;


class GestionAdherent : public QMainWindow
{
    Q_OBJECT

public:
    Ui::GestionAdherent *ui;
    explicit GestionAdherent(QWidget *parent = nullptr);
    ~GestionAdherent();
        int mailcontrole;

private slots:
     /*   void on_actionOpen_triggered();

            void on_actionPlay_triggered();

            void on_actionPause_triggered();

            void on_actionStop_triggered();*/
    void on_pbAjouter_clicked();

    void on_supButton_clicked();

    void on_ModifierAdButton_clicked();

   // void on_tabAdherent_activated(const QModelIndex &index);

    void on_pushButton_clicked();
void on_google_search_button_clicked();
    void on_pushButton_2_clicked();

    void on_sup_perfo_clicked();

    void on_orderservespeed1_clicked();

    void on_orderservespeed2_clicked();

    void on_orderservespeed3_clicked();

    void on_rechercheAd_clicked();

    void on_pushButton_3_clicked();

    void on_email_clicked();

    //void on_statstable_activated(const QModelIndex &index);

    void on_statbtn_clicked();
    void on_pButtonSave_clicked();

    void on_pButtonQuit_clicked();
    void on_sBoxScale_valueChanged(int arg1);
    void on_pTextEditQRText_textChanged();

    void showTime();


    void on_StartMusicb_clicked();

    void on_StopMusicBtn_clicked();

    void on_ProgressSlider_sliderMoved(int position);

    void on_VolumeSlider_sliderMoved(int position);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);

    void on_exclBbtn_clicked();

    void on_ReadNotes_clicked();
    void on_languageAd_activated(const QString &arg1);


    void on_WriteNotes_clicked();

    /*void on_actionopen_triggered();

    void on_actionplay_triggered();

    void on_actionpause_triggered();

    void on_actionstop_triggered();*/

    void on_tabWidget_2_currentChanged(int index);

    void on_pushButton_4_clicked();

private:
    void updateQRImage();
    void setScale(int);
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_makeShot_clicked();
private:
    QPropertyAnimation *animation,*animation2;
    //Ui::GestionAdherent *ui;
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;
    QMenu *moptionMenu;
    QAction *mEnvoyerAction;
    QAction *msupAction;
    QAction *mCapturerAction;
    Adherent A;
    Adherent *A3;
    performance P;

    CQR_Encode qrEncode;
    bool successfulEncoding;
    int encodeImageSize;
    QWidget * Radh;
    QPoint lastPos;
    QMediaPlayer *Player;
     QMediaPlayer *btnSound;
     QMediaPlayer* player;
         QVideoWidget* vw;
         QProgressBar* bar;
         QSlider* slider;
         SearchBox searchEdit;

protected:
    void closeEvent(QCloseEvent *);
    bool eventFilter( QObject * object, QEvent * event );
};

#endif // GestionAdherent_H
