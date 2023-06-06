#ifndef GESTIONEQUIPEMENT_H
#define GESTIONEQUIPEMENT_H

#include "searchbox.h"
#include <QMainWindow>
#include "mainwindow.h"
#include "equipement.h"
#include "fournisseur.h"
#include "screenshot.h"
#include "entreprise.h"
#include "searchbox.h"
#include "arduino.h"
#include "commande.h"
#include "login.h"
#include "finance.h"
#include "abonnemet.h"
#include "stmp.h"
#include <QDate>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include<QSqlQuery>
#include <QTimer>
#include <QWidget>
QT_BEGIN_NAMESPACE


namespace Ui {
class gestionequipement;
}
QT_END_NAMESPACE


class gestionequipement : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestionequipement(QWidget *parent = nullptr);
    ~gestionequipement();
    QSortFilterProxyModel *proxyModel;
    QSqlQuery o;
    bool ok;
    int etat_voiture;

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_changer_clicked();

    void on_pb_charger_clicked();

    void on_pb_trier_clicked();

    void on_pb_pfd_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_supprimer_f_clicked();

    void on_pb_changer_f_clicked();

    void on_pb_ajoute_f_clicked();

    void on_pb_pfd_f_clicked();

    void on_tab_fournisseur_activated(const QModelIndex &index);

    void on_tab_equipement_activated(const QModelIndex &index);

    void on_pb_imprime_pdf_clicked();

    void on_pb_afficher_f_clicked();

    void on_pb_screenshott_clicked();
//    void resizeEvent(QResizeEvent *event) override;

    void on_le_filtre_textChanged(const QString &arg1);

    void on_comboBoxfiltre_currentIndexChanged(int index);

    void on_pb_ajoute_e_clicked();

    void on_pb_changer_e_clicked();

    void on_tab_entreprise_activated(const QModelIndex &index);

    void on_pb_afficher_e_clicked();

    void on_pb_supprimer_e_clicked();

    void on_pb_rechercher_e_clicked();

    void on_pb_trier_e_clicked();

    void on_pb_search_clicked();

    void on_pb_email_clicked();

    void on_pb_excel_clicked();

    int update_label();

    void park(int etat_voiture);

  //  void on_pb_etat_voiture_clicked();

    void on_pb_ajoute_c_clicked();

    void on_pb_changer_c_clicked();

    void on_pb_trier_c_clicked();

    void on_pb_supprimer_c_clicked();

    void on_pb_afficher_c_clicked();

    void on_pb_rechercher_c_clicked();

    void on_tab_commande_activated(const QModelIndex &index);

    void on_pb_QrCode_clicked();

    void timere();


    void on_retour_eq_clicked();

private:
   void Menu();
   QByteArray data;
   QGraphicsRectItem *Rectangle1;
   QGraphicsRectItem *Rectangle2;
   QGraphicsRectItem *Rectangle3;
   QGraphicsRectItem *Rectangle4;
   QGraphicsRectItem *Rectangle5;
   QGraphicsRectItem *Rectangle6;
   QGraphicsRectItem *Rectangle7;
   QGraphicsRectItem *Rectangle8;

   QGraphicsScene *scene;
   //  QPixmap originalPixmap;
    Ui::gestionequipement *ui;
    QWidget * Re;
    Equipement E;
    Fournisseur F;
    Screenshot s;
    Entreprise EN;
     SearchBox searchEdit;
QRegExpValidator *validator;
Arduino arduino;
commande c;
void animateObj(QWidget* widget, int current=255);
    void animateObjWhite(QWidget* widget, int current);
     QTimer *timer= new QTimer(this);

};


#endif // GESTIONEQUIPEMENT_H
