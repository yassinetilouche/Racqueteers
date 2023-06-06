#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "dialogmain.h"
#include "gestionequipement.h"
#include "gestionfinance.h"
#include "GestionAdherent.h"
#include "gestionpersonnel.h"
#include "gestionevenement.h"
#include <QWidget>

#include "login.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_gestion_materiels_clicked();

    void on_pushButton_singIn_clicked();

    void on_pushButton_singUp_clicked();

    void on_pushButton_enregistrer_clicked();

    void on_pb_gestion_finance_clicked();

    void on_pushButton_close_clicked();

    void on_pb_annuler_Enregistrement_clicked();

    void on_pb_gestion_adherents_clicked();

    void on_pb_gestion_cours_clicked();

    void on_pb_gestion_personnel_clicked();

    void on_pb_gestion_sponsors_clicked();

private:
    QWidget *GE;
    QWidget *GF;
    QWidget *GP;

    QWidget *GA;
    Ui::MainWindow *ui;
    login L;
    QWidget *GS;
    QWidget *GEV;

};

#endif // MAINWINDOW_H
