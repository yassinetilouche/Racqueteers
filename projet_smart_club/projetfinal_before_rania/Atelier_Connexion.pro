#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
QT       += core gui sql printsupport network
QT       += core gui sql charts
QT += widgets
QT      +=  network widgets
QT  += core gui sql printsupport network multimedia multimediawidgets
QT += serialport
QT       += printsupport  serialport charts network testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    GestionAdherent.cpp \
    abonnemet.cpp \
    adherent.cpp \
    arduino.cpp \
    bronzestyle.cpp \
    commande.cpp \
    cours.cpp \
    dialogmain.cpp \
    employee.cpp \
    entreprise.cpp \
    equipement.cpp \
    evenement.cpp \
    exportexcelobjet.cpp \
    finance.cpp \
    fournisseur.cpp \
    gestionequipement.cpp \
    gestionevenement.cpp \
    gestionfinance.cpp \
    gestionpersonnel.cpp \
    googlesuggest.cpp \
    login.cpp \
        main.cpp \
    connection.cpp \
    mainwindow.cpp \
    match.cpp \
    performance.cpp \
    poste.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    qrcode2.cpp \
    screenshot.cpp \
    seances.cpp \
    searchbox.cpp \
    sponsors.cpp \
    statcours.cpp \
    statistiques.cpp \
    stmp.cpp \
    translations.cpp

HEADERS += \
    GestionAdherent.h \
    SmtpMime \
    abonnemet.h \
    adherent.h \
    arduino.h \
    bronzestyle.h \
    commande.h \
    cours.h \
    dialogmain.h \
    employee.h \
    entreprise.h \
    equipement.h \
    exportexcelobjet.h \
    finance.h \
    fournisseur.h \
    gestionequipement.h \
    gestionevenement.h \
    gestionfinance.h \
    gestionpersonnel.h \
    googlesuggest.h \
    login.h \
    connection.h \
    mainwindow.h \
    match.h \
    performance.h \
    poste.h \
    qcustomplot.h \
    qrcode.h \
    qrcode2.h \
    screenshot.h \
    seances.h \
    searchbox.h \
    sponsors.h \
    statcours.h \
    statistiques.h \
    stmp.h

FORMS += \
    GestionAdherent.ui \
    dialogmain.ui \
    dialogseance.ui \
    gestionequipement.ui \
    gestionevenement.ui \
    gestionfinance.ui \
    gestionpersonnel.ui \
    mainwindow.ui \
    statcours.ui \
    statistiques.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressource.qrc \
    translations.qrc

DISTFILES += \
    arabic.qm \
    arabic.ts \
    dark.qss \
    french.qm \
    french.ts
