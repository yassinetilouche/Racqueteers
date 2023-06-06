#ifndef gestionevenement_H
#define gestionevenement_H

#include <QMainWindow>
#include "evenement.h"
#include "sponsors.h"
#include "arduino.h"
#include <QTimer>
#include <QWidget>
#include "mainwindow.h"
#include <searchbox.h>

QT_BEGIN_NAMESPACE
namespace Ui { class gestionevenement; }
QT_END_NAMESPACE

class gestionevenement : public QMainWindow
{
    Q_OBJECT

public:
    gestionevenement(QWidget *parent = nullptr);
    ~gestionevenement();

private:
    QString Fetch_Month(int);
    void update_graph();
    //void french();
    //void english();
private slots:
    void on_pb_ajouter_clicked();

    void on_pb_reset_clicked();

    void on_tab_evenement_activated(const QModelIndex &index);
    void on_google_search_button_clicked();
    void on_pb_supp_clicked();

    void on_pb_search_clicked();

    void on_pb_annuler_clicked();

    void on_pb_mod_clicked();


    void on_pb_c_clicked();

    void on_pb_a_clicked();

    void on_pb_print_clicked();

    void on_pb_ajouterS_clicked();

    void on_tab_sponsors_activated(const QModelIndex &index);

    void on_supprimerS_clicked();

    void on_modifierS_clicked();

    void on_searchS_pb_clicked();

    void on_annulerS_pb_clicked();

    void on_up_clicked();

    void on_down_clicked();

    void update_label();

    void on_pb_mail_clicked();

    void real_Time_status();

    void stats();

    void on_excel_clicked();

    void on_retour_evenement_clicked();

private:
    Ui::gestionevenement *ui;
    QWidget * Rev;
    Evenement e;
    Sponsors sp;
    int n;
    Arduino A;
    QByteArray data;
    QTimer *timer;
    SearchBox searchEdit;
};
#endif // gestionevenement_H
