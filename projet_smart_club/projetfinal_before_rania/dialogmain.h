#ifndef DIALOGMAIN_H
#define DIALOGMAIN_H
#include "seances.h"
#include "statistiques.h"
#include "cours.h"
#include <QDialog>
#include <QMessageBox>
#include "connection.h"
#include <QStatusBar>
#include "mainwindow.h"
#include <QWidget>
#include <searchbox.h>
namespace Ui {
class Dialogmain;
}

class Dialogmain : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogmain(QWidget *parent = nullptr);
    ~Dialogmain();

private slots:

    void on_nxt_btn_clicked();

    void on_prv_btn_clicked();

    void on_nxt_md_btn_clicked();

    void on_prv_md_btn_clicked();

    void on_add_sc_btn_clicked();

    void on_tabSeances_activated(const QModelIndex &index);
    void on_google_search_button_clicked();
    void on_edit_sc_clicked();

    void on_delete_sc_clicked();



    void on_add_cr_btn_clicked();

    void on_tabCours_activated(const QModelIndex &index);

    void on_edit_cours_clicked();

    void on_delete_cours_clicked();

    void on_id_asc_clicked();

    void on_id_desc_clicked();

    void on_date_desc_clicked();

    void on_date_asc_clicked();

    void on_heuredb_asc_clicked();

    void on_heurefn_asc_clicked();

    void on_heurefn_desc_clicked();

    void on_lieu_asc_clicked();

    void on_heuredb_desc_clicked();

    void on_lieu_desc_clicked();

    void on_prix_asc_clicked();

    void on_prix_desc_clicked();

    void on_search_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_id_asc_2_clicked();

    void on_id_desc_2_clicked();

    void on_titre_asc_clicked();

    void on_titre_desc_clicked();

    void on_nobj_asc_clicked();

    void on_nobj_desc_clicked();

    void on_npar_asc_clicked();

    void on_npar_desc_clicked();

    void on_nsea_asc_clicked();

    void on_nsea_desc_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_dark_btn_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_QR_clicked();

    void on_retour_seance_clicked();

private:
    Ui::Dialogmain *ui;
    seances tmpSceance ;
    cours tmpCours;
    QWidget * Rs;
    SearchBox searchEdit;

};

#endif // DIALOGMAIN_H
