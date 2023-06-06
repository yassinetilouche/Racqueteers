#ifndef GESTIONPERSONNEL_H
#define GESTIONPERSONNEL_H
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMainWindow>
#include "employee.h"
#include "poste.h"
#include "arduino.h"
#include "googlesuggest.h"
#include "match.h"
#include <QSystemTrayIcon>
#include<QCompleter>
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <SmtpMime>
#include <stmp.h>
#include <QWidget>
#include "mainwindow.h"
#include <QtNetwork>
#include <searchbox.h>

QT_BEGIN_NAMESPACE

namespace Ui {
class gestionpersonnel;
}
QT_END_NAMESPACE
class gestionpersonnel : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestionpersonnel(QWidget *parent = nullptr);
    bool ok;
    ~gestionpersonnel();

private slots:
    void on_ajouter_button_clicked();

    void on_supprimer_button_clicked();

    void on_modifier_button_clicked();

    void on_ajouter_button_poste_clicked();

    void on_supprimer_button_poste_clicked();

    void on_pushButton_clicked();

    void on_stat_employee_button_clicked();

    void on_radioButton_ancien_employee_clicked();

    void on_radioButton_id_employee_clicked();

    void on_radioButton_age_employee_clicked();

    void on_radioButton_niveau_poste_clicked();

    void on_radioButton_salary_poste_clicked();

    void on_radioButton_nb_poste_clicked();

    void on_pushButton_rechercherEmployee_clicked();

    void on_radioButton_employee_retour_clicked();

    void on_pushButton_recherche_poste_clicked();

    void on_radioButton_poste_retour_clicked();

    void on_ficher_paie_button_clicked();

    void on_validerMod_button_clicked();

    void on_modifier_button_2_clicked();

    void on_validerMod_button_poste_clicked();

    void on_editline_print_clicked();


    //arduino
    void update_label();

    void on_game_over_clicked();

    void on_french_clicked();

    void on_english_clicked();



    void on_real_stat_emp_button_clicked();


    void on_mail_send_edit_clicked();

    void on_google_search_button_clicked();

    void on_retour_personnel_clicked();

    void on_start_game_clicked();

private:
    Ui::gestionpersonnel *ui;
    Employee E;
    Poste P;
    QByteArray data;
    QSystemTrayIcon *mysystem;
   QSqlQuery qry;
   QWidget *Rp;
    Arduino A;
    Match M;
SearchBox searchEdit;
};

#endif // MAINWINDOW_H
