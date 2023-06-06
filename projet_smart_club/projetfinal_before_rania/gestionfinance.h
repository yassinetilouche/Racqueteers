#ifndef GESTIONFINANCE_H
#define GESTIONFINANCE_H

#include "login.h"
#include <QMainWindow>
#include "mainwindow.h"
#include "finance.h"
#include "abonnemet.h"
#include<QSystemTrayIcon>
#include "gestionpersonnel.h"
#include"arduino.h"
#include "QWidget"
#include <searchbox.h>
QT_BEGIN_NAMESPACE

namespace Ui { class gestionfinance; }

QT_END_NAMESPACE

class gestionfinance : public QMainWindow
{
    Q_OBJECT

public:
    gestionfinance(QWidget *parent = nullptr);
    ~gestionfinance();


private slots:

    void on_pushButton_2_clicked();

    void on_supprimer_2_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_pushButton_valider_2_clicked();

    void on_pushButton_ajouterAbonnement_2_clicked();

    void on_supprimerAbonnement_2_clicked();

    void on_tri_2_clicked();
    void on_google_search_button_clicked();
    void on_rechercher_2_clicked();

    void on_pushButton_pdf_2_clicked();

    void on_pushButton_deconnecter_2_clicked();

    void on_pushButton_QrCode_clicked();

    void on_pushButton_save_clicked();

    void on_rechercherAbonnement_4_clicked();

    void on_modifierAbonnement_2_clicked();

    void on_validerModification_2_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_mail_clicked();

    void on_pushButton_clicked();
    void arduinoo();


    void on_arduino_enter_clicked();

    void on_arduino_test_clicked();

private:
    QSystemTrayIcon *notification;
    Ui::gestionfinance *ui;
    QWidget *Rf;
    finance F;
    abonnemet A;
    login L;
    Arduino Ar;

    SearchBox searchEdit;
};

#endif // GESTIONFINANCE_H
