#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "bronzestyle.h"
/*#include "dialogmain.h"*/
#include <QFile>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // QApplication::setStyle(new BronzeStyle);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    QTranslator t;
        QTranslator guiTranslator;

        QStringList languages;
        languages << "English" << "French" << "العربية";
        QString lang = QInputDialog::getItem(NULL,"Select Language","Language",languages);
        if (lang=="French")
        {
          t.load(":/new/prefix1/french.qm");
          guiTranslator.load("D:/qt/qt_5/5.9.9/mingw53_32/translations/qtbase_fr.qm");
        }else if (lang=="العربية")
        {
            t.load(":/new/prefix1/arabic.qm");
            guiTranslator.load("D:/qt/qt_5/5.9.9/mingw53_32/translations/qtbase_ar.qm");
        }
        if (lang != "English")
        {
            a.installTranslator(&t);
        }

    if(test)
    {w.setWindowTitle("gestion equipement & fournisseur");

        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
