#include "GestionAdherent.h"
#include "ui_GestionAdherent.h"
#include "adherent.h"
#include "stmp.h"
#include "performance.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDate>
#include "qmessagebox.h"
#include <iostream>
#include "QPainter"
#include "QPdfWriter"
#include "QDesktopServices"
#include "QtPrintSupport/QPrinter"
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMouseEvent>
#include <QScrollArea>
#include <QImageWriter>
#include <QScrollBar>
#include <QSettings>
#include <QApplication>
#include "qrcode2.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <Qmenu>
#include <QAction>
#include <QTimer>
#include <QDateTime>
#include <QPixmap>
#include "exportexcelobjet.h"
#include <QFileDialog>
#include<QTextStream>

const QString getIniPath()
{
    const static QString iniPath( qApp->applicationDirPath() + "/settings.ini" );
    return iniPath;
}
QString saveFormats()
{
    static QString suffix;
    foreach ( const QByteArray & format , QImageWriter::supportedImageFormats() )
        suffix += QString( "%1 ( *.%2 )\n" )
                .arg( QString( format ).toUpper() )
                .arg( QString( format ) );

    return suffix;
}

GestionAdherent::GestionAdherent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionAdherent),
  successfulEncoding(false)
{
    ui->setupUi(this);
    QCompleter *completerCom = new QCompleter();
        completerCom->setModel(A.rechercher_com());
        ui->IdAdrecherche->setCompleter(completerCom);
    player = new QMediaPlayer(this);
        /*vw = new QVideoWidget(this);
        player->setVideoOutput(vw);
        this->setCentralWidget(vw);
        slider = new QSlider(this);
            bar = new QProgressBar(this);

            slider->setOrientation(Qt::Horizontal);

                ui->statusBar->addPermanentWidget(slider);
                ui->statusBar->addPermanentWidget(bar);

                connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
                connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
                connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

                connect(player,&QMediaPlayer::durationChanged,bar,&QProgressBar::setMaximum);
                connect(player,&QMediaPlayer::positionChanged,bar,&QProgressBar::setValue);
*/
    animation = new QPropertyAnimation(ui->pbAjouter,"geometry");
    animation2 = new QPropertyAnimation(ui->ModifierAdButton,"geometry");

    animation->setDuration(10000);
    animation->setStartValue(ui->pbAjouter->geometry());
    animation->setEndValue(QRect(340,100,93,28));
    animation->start();
    animation2->setDuration(10000);
    animation2->setStartValue(ui->ModifierAdButton->geometry());
    animation2->setEndValue(QRect(340,120,93,28));
    animation2->start();
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
    QPixmap pix("C:/Users/Yassine/Downloads/tennislogo.png");
    int w =ui->logo->width();
    int h=ui->logo->height();
    ui->logo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap az("C:/Users/Yassine/Downloads/legends/Azarenka.jpg");
    int w1 =ui->Azarenka->width();
    int h1=ui->Azarenka->height();
    ui->Azarenka->setPixmap(az.scaled(w1,h1,Qt::KeepAspectRatio));

    QPixmap na("C:/Users/Yassine/Downloads/legends/Nadal.jfif");
    int w2 =ui->Nadal->width();
    int h2=ui->Nadal->height();
    ui->Nadal->setPixmap(na.scaled(w2,h2,Qt::KeepAspectRatio));

    QPixmap djo("C:/Users/Yassine/Downloads/legends/Djokovic.jfif");
    int w3 =ui->Djokovic->width();
    int h3=ui->Djokovic->height();
    ui->Djokovic->setPixmap(djo.scaled(w3,h3,Qt::KeepAspectRatio));

    QPixmap fed("C:/Users/Yassine/Downloads/legends/Federer.jpg");
    int w4 =ui->Federer->width();
    int h4=ui->Federer->height();
    ui->Federer->setPixmap(fed.scaled(w4,h4,Qt::KeepAspectRatio));

    QPixmap mu("C:/Users/Yassine/Downloads/legends/Murray.jpg");
    int w5 =ui->Murray->width();
    int h5=ui->Murray->height();
    ui->Murray->setPixmap(mu.scaled(w5,h5,Qt::KeepAspectRatio));

    QPixmap jb("C:/Users/Yassine/Downloads/legends/Jabeur.jpg");
    int w6 =ui->Jabeur->width();
    int h6=ui->Jabeur->height();
    ui->Jabeur->setPixmap(jb.scaled(w6,h6,Qt::KeepAspectRatio));

    QPixmap sl("C:/Users/Yassine/Downloads/legends/Serena.jfif");
    int w7 =ui->Serena->width();
    int h7=ui->Serena->height();
    ui->Serena->setPixmap(sl.scaled(w7,h7,Qt::KeepAspectRatio));

    QPixmap sh("C:/Users/Yassine/Downloads/legends/Maria.jpg");
    int w8 =ui->Sharapova->width();
    int h8=ui->Sharapova->height();
    ui->Sharapova->setPixmap(sh.scaled(w8,h8,Qt::KeepAspectRatio));


    Player =new QMediaPlayer(this);
    btnSound =new QMediaPlayer(this);
    btnSound->setMedia(QUrl::fromLocalFile("C:/Users/Yassine/Downloads/btnsound.mp3"));
    connect(Player,&QMediaPlayer::positionChanged,this,&GestionAdherent::on_positionChanged);
    connect(Player,&QMediaPlayer::durationChanged,this,&GestionAdherent::on_durationChanged);
    mCamera =new QCamera(this);
    mCameraViewfinder= new QCameraViewfinder(this);
    mCameraImageCapture= new QCameraImageCapture(mCamera,this);
    mLayout= new QVBoxLayout;
    moptionMenu= new QMenu("option", this);
    mEnvoyerAction= new QAction("Envoyer",this);
    msupAction= new QAction("supprimer",this);
    mCapturerAction= new QAction("Capturer",this);
    moptionMenu->addActions({mEnvoyerAction,msupAction,mCapturerAction});
    ui->option->setMenu(moptionMenu);
    mCamera->setViewfinder(mCameraViewfinder);


    mLayout->addWidget(mCameraViewfinder);
            mLayout->setMargin(0);
    ui->scrollArea_2->setLayout(mLayout);
    connect(mEnvoyerAction, &QAction::triggered, [&](){
        mCamera->start();
    });
    connect(msupAction, &QAction::triggered, [&](){
        mCamera->stop();
    });
    connect(mCapturerAction, &QAction::triggered, [&](){
        auto filename= QFileDialog::getSaveFileName(this,"Capturer","/", "image(*.jpg;*.jpeg)");
        if(filename.isEmpty()){
            return ;
        }
        mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
        QImageEncoderSettings imageEncoderSettings;
        imageEncoderSettings.setCodec("image/jpeg");
        imageEncoderSettings.setResolution(1600,1200);
        mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
        mCamera->setCaptureMode(QCamera::CaptureStillImage);
        mCamera->start();
        mCamera->searchAndLock();
        mCameraImageCapture->capture(filename);
        mCamera->unlock();



    });


    ui->tabAdherent->setModel(A.afficher_adherent());
    ui->tabperfo->setModel(P.afficher_performance());
    ui->tabaffect->setModel(P.affection());
    ui->IdAd->setValidator(new QIntValidator(0,9999999,this));
    ui->IdAd->setValidator(new QIntValidator(10000000,99999999,this));
    ui->scrollArea->installEventFilter( this );
    ui->sexeop->addItem("Homme");
    ui->sexeop->addItem("Femme");
    ui->sexeop->addItem("Autre");
    ui->languageAd->addItem("Francais");
    ui->languageAd->addItem("English");

    QSettings ini( getIniPath(), QSettings::IniFormat );
    ui->splitter_2->restoreState( ini.value( ui->splitter_2->objectName() ).toByteArray() );
    ui->splitter->restoreState( ini.value( ui->splitter->objectName() ).toByteArray() );
    ui->sBoxScale->setValue( ini.value( ui->sBoxScale->objectName(), 4 ).toInt() );
   // restorestate( ini.value( "State" ).toByteArray() );
    restoreGeometry( ini.value( "Geometry" ).toByteArray() );

    setScale( ui->sBoxScale->value() );
    updateQRImage();
}

GestionAdherent::~GestionAdherent()
{

    delete ui;
}
void GestionAdherent::showTime()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->DigitalClock->setText(time_text);
}
void GestionAdherent::on_pbAjouter_clicked()
{   btnSound->play();
    int id_Adherant=ui->IdAd->text().toInt();
    //std::cout<<id_Adherant;
    QString nom=ui->NomAd->text();
    QString prenom=ui->PrenomAd->text();
    QString sexe=ui->sexeop->currentText();
    QString date=ui->DateAd->text();
    QString email=ui->email_2->text();
    QString adresse=ui->adresse->text();
    int num_tel=ui->numtel->text().toInt();

    Adherent a(id_Adherant,nom,prenom,sexe,date,email,num_tel,adresse);

    //std::cout<<a.getid();
    int x,t;
    bool test=a.ajouter();
    x=a.getmailt();
    t=a.getnumtelt();
    QString id=QString::number(id_Adherant);
            if (test)
            {   ui->mailerror->setText("");
                ui->numtelerror->setText("");
                ui->dateerreur->setText("");
                ui->tabAdherent->setModel(A.afficher_adherent());
                QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Ajout effectué.\n click OK to exit."),QMessageBox::Ok);
                Smtp* smtp;
                const QString mailto=ui->email_2->text();
                   smtp = new Smtp("tennisclubtunis1@gmail.com", "tennis2021", "smtp.gmail.com");
                   //connect(smtp, SIGNAL(clicked()), this, SLOT(on_Mail_clicked()));

                   smtp->sendMail(mailto, mailto , "tennis club","cher "+nom+" "+prenom+"\n votre inscription au tennis club tunnis a bien été enregistrée avec l'id " +id );


            }
            else
               {if(x==1)
                {ui->mailerror->setText("votre mail doit contenir @ et .");}
                 if(t==1)
                {ui->numtelerror->setText("le numero de telephone doit contenir 8 chiffres");
                //QMessageBox::critical(nullptr, QObject::tr("Not ok"),QObject::tr("Ajout non effectué.\n click cancel to exit."),QMessageBox::Cancel);
                }
                 if(a.getdatet()==1)
                 {ui->dateerreur->setText("vous devez avoir plus que 4 ans");}
    }
}

void GestionAdherent::on_supButton_clicked()
{
       btnSound->play();
        A.setid(ui->IdDeleteAdherent->text().toInt());
        bool test=A.supprimer_adherent(A.getid());


        if (test)
          {
            QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Suppression effectuée.\n click OK to exit."),QMessageBox::Ok);


            ui->tabAdherent->setModel(A.afficher_adherent()) ;

        }
        else
           {
            QMessageBox::critical(nullptr, QObject::tr("Not ok"),QObject::tr("Suppression non effectuée.\n click cancel to exit."),QMessageBox::Cancel);

            }
}

void GestionAdherent::on_ModifierAdButton_clicked()
{   btnSound->play();
    int id_Adherant=ui->IdAd->text().toInt();
    std::cout<<id_Adherant;
    /*
     * QString nom=ui->NomAd->text();
    QString prenom=ui->PrenomAd->text();
    QString sexe=ui->sexeop->currentText();
    QString date=ui->DateAd->text();
    QString email=ui->email_2->text();
    QString adresse=ui->adresse->text();
    int num_tel=ui->numtel->text().toInt();
     * */
    QString nom=ui->NomAd->text();
    QString prenom=ui->PrenomAd->text();
    QString sexe=ui->sexeop->currentText();
    QString date=ui->DateAd->text();
    QString email=ui->email_2->text();
    QString adresse=ui->adresse->text();
    int num_tel=ui->numtel->text().toInt();
           //Adherent *A1 = new Adherent(id_Adherant,nom,prenom,sexe,date,email,num_tel,adresse);
           //std::cout<<A1->getid();
    Adherent a(id_Adherant,nom,prenom,sexe,date,email,num_tel,adresse);
qDebug()<<a.getid();
qDebug()<<a.getnumtel();
           bool test=a.modifier();

           if(test)
           {    ui->mailerror->setText("");
               ui->numtelerror->setText("");
               ui->dateerreur->setText("");
               ui->tabAdherent->setModel(A.afficher_adherent());
              /*ui->id_mod->clear();
             ui->nom_mod->clear();
             ui->type_mod->clear();
             ui->prix_mod->clear();*/
               QMessageBox::information(nullptr, QObject::tr("Modification effectue"),
                                 QObject::tr("Produit modifie.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
           }

              /* if(date.year()>2016 ||num_tel<10000000 || num_tel>99999999 || email.indexOf('@')==-1||email.indexOf('.')==-1 )
               { if(num_tel<10000000 || num_tel>99999999)
                   { ui->numtelerror->setText("le numero de telephone doit contenir 8 chiffres");
                   QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                        QObject::tr("numero de telphone non valide !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


               }
                   /*if(date.year()>2016)
                   {
                       ui->dateerreur->setText("vous devez avoir plus que 4 ans");
}
               if(email.indexOf('@')==-1||email.indexOf('.')==-1)
               {    ui->mailerror->setText("votre mail doit contenir @ et .");
                  // ui->email_error->setText("votre email doit contenir @");
                   /*QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                                     QObject::tr("email non valide !.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

               }*/
              else{ QMessageBox::critical(nullptr, QObject::tr("Modification echoue"),
                           QObject::tr("Erreur !.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
         //ui->tabAdherent->setModel(A2.afficher());

}}

/*void GestionAdherent::on_tabAdherent_activated(const QModelIndex &index)
{
    QString val=ui->tabAdherent->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select * from seances where id_seance='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->Ad_id_edit ->setText(qry.value(0).toString());
                        ui->Ad_nom_edit->setText(qry.value(1).toString());
                        ui->AD_edit->setText(qry.value(2).toString());
                        ui->fn_edit->setText(qry.value(3).toString());
                        ui->lieu_edit->setText(qry.value(4).toString());
                        ui->prix_edit->setText(qry.value(5).toString());

                        ui->id_edit ->show();
                        ui-> date_edit->show();
                        ui->db_edit ->show();
                        ui->fn_edit->show();
                        ui->lieu_edit ->show();
                        ui->prix_edit->show();
                        ui->edit_sc ->show();
                        ui->delete_sc ->show();

                    }
        }
}*/

void GestionAdherent::on_pushButton_clicked()
{   btnSound->play();
    int Idperfo=ui->idperfo->text().toInt();
    //std::cout<<id_Adherant;
    int IdAD=ui->idadperfo->text().toInt();
    QDate date=ui->dateperfo->date();
    int serve1speed=ui->speed1perfo->text().toInt();
    int serve2speed=ui->speed2perfo->text().toInt();
    int serve3speed=ui->speed3perfo->text().toInt();


    performance p(Idperfo,IdAD,date,serve1speed,serve2speed,serve3speed);
    //std::cout<<p.getidperfo();

    bool test=p.ajouter();

            if (test)
            {   ui->servicetest->setText("");
                ui->dateperfotest->setText("");
                ui->tabperfo->setModel(P.afficher_performance());
                QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Ajout effectué.\n click OK to exit."),QMessageBox::Ok);


            }
            else
               {
                if(p.getdateperfot()==1)
                {ui->dateperfotest->setText("la date de votre performance ne peut pas etre dans le future");}
                    if(p.getservicetest()==1)
                    {ui->servicetest->setText("la vitesse de votre service ne pas depasser 500");}
    }
                p.affection();
                ui->tabaffect->setModel(P.affection());
}

void GestionAdherent::on_pushButton_2_clicked()
{   btnSound->play();
    int idperfo=ui->Midperfo->text().toInt();
    int idadperfo=ui->Midad->text().toInt();
    QDate date=ui->Mdate->date();
    int serve1=ui->M1st->text().toInt();
    int serve2=ui->M2nd->text().toInt();
    int serve3=ui->M3rd->text().toInt();
           performance *P1 = new performance(idperfo , idadperfo ,date ,serve1 , serve2, serve3);
           //std::cout<<P1->getid();
           bool test=P1->modifier();

           if(test)
           {
               ui->tabperfo->setModel(P.afficher_performance());
              /*ui->id_mod->clear();
             ui->nom_mod->clear();
             ui->type_mod->clear();
             ui->prix_mod->clear();*/
               QMessageBox::information(nullptr, QObject::tr("Modification effectue"),
                                 QObject::tr("Produit modifie.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
           }
           else
               QMessageBox::critical(nullptr, QObject::tr("Modification echoue"),
                           QObject::tr("Erreur !.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
         //ui->tabAdherent->setModel(A2.afficher());

}

void GestionAdherent::on_sup_perfo_clicked()
{   P.setidperfo(ui->Midperfo->text().toInt());
    bool test=P.supprimer(P.getidperfo());



    if (test)
      {
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Suppression effectuée.\n click OK to exit."),QMessageBox::Ok);


        ui->tabperfo->setModel(P.afficher_performance()) ;

    }
    else
       {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),QObject::tr("Suppression non effectuée.\n click cancel to exit."),QMessageBox::Cancel);

        }

}

void GestionAdherent::on_orderservespeed1_clicked()
{
    ui->tabperfo->setModel(P.sortserve1());
}

void GestionAdherent::on_orderservespeed2_clicked()
{
    ui->tabperfo->setModel(P.sortserve2());
}


void GestionAdherent::on_orderservespeed3_clicked()
{
    ui->tabperfo->setModel(P.sortserve3());
}

void GestionAdherent::on_rechercheAd_clicked()
{   if (ui->IdAdrecherche->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP ID!!!!") ;

    }
   else {
   QString idr=ui->IdAdrecherche->text();
    ui->tabrecherche->setModel(A3->chercher_adherent(idr));
   // std::cout<<idr;
}}

void GestionAdherent::on_pushButton_3_clicked()
{
    QPdfWriter pdf("C:/Users/Yassine/Downloads/Code_source_Atelier_Connexion/Atelier_Connexion/liste");
                              QPainter painter(&pdf);
                             int i = 4000;
                                  painter.setPen(Qt::red);
                                  painter.setFont(QFont("Arial", 30));
                                  painter.drawText(2300,1200,"Liste Des Adherents");
                                  painter.setPen(Qt::black);
                                  painter.setFont(QFont("Arial", 50));
                                  //painter.drawText(1100,2000,afficheDC);
                                  painter.drawRect(1500,200,7300,2600);
                                  painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Yassine/Downloads/Code_source_Atelier_Connexion/Atelier_Connexion/tenis.png"));
                                  painter.drawRect(0,3000,9600,500);
                                  painter.setFont(QFont("Arial", 9));
                                  painter.drawText(300,3300,"ID");
                                  painter.drawText(2300,3300,"NOM");
                                  painter.drawText(4300,3300,"PRENOM");
                                  painter.drawText(6300,3300,"Sexe");
                                  painter.drawText(8300,3300,"DATE");




                                  QSqlQuery query;
                                  query.prepare("select * from Adherent");
                                  query.exec();
                                  while (query.next())
                                  {
                                      painter.drawText(300,i,query.value(0).toString());
                                      painter.drawText(2300,i,query.value(1).toString());
                                      painter.drawText(4300,i,query.value(2).toString());
                                      painter.drawText(6300,i,query.value(3).toString());
                                      painter.drawText(8300,i,query.value(4).toString());




                                     i = i +500;
                                  }
                                  int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                                      if (reponse == QMessageBox::Yes)
                                      {

                                          painter.end();
                                      }
                                      if (reponse == QMessageBox::No)
                                      {
                                           painter.end();
                                      }
}

void GestionAdherent::on_email_clicked()
{
     Smtp* smtp;
     const QString mailto="yassinetilouche@gmail.com";

        smtp = new Smtp("tennisclubtunis1@gmail.com", "tennis2021", "smtp.gmail.com");
        //connect(smtp, SIGNAL(clicked()), this, SLOT(on_Mail_clicked()));
        //std::cout<<mailto;

        smtp->sendMail(mailto, mailto , "tennis club","test ");

}

void GestionAdherent::on_statbtn_clicked()
{

     ui->statstable->setModel(P.stats());
}


void GestionAdherent::updateQRImage()
{
    int sizeText = ui->pTextEditQRText->toPlainText().size();
    ui->labelSizeText->setText( QString::number( sizeText ) );

    int levelIndex = 1;
    int versionIndex = 0;
    bool bExtent = true;
    int maskIndex = -1;
    QString encodeString = ui->pTextEditQRText->toPlainText();

    successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data() );
    if ( !successfulEncoding )
    {
        ui->image_label->clear();
        ui->image_label->setText( tr("QR Code...") );
        ui->labelSize->clear();
        ui->pButtonSave->setEnabled( successfulEncoding );
        return;
    }

    int qrImageSize = qrEncode.m_nSymbleSize;

    // Создаем двумерный образ кода
    encodeImageSize = qrImageSize + ( QR_MARGIN * 2 );
    QImage encodeImage( encodeImageSize, encodeImageSize, QImage::Format_Mono );
    encodeImage.fill( 1 );

    // Создать двумерный образ кода
    for ( int i = 0; i < qrImageSize; i++ )
        for ( int j = 0; j < qrImageSize; j++ )
            if ( qrEncode.m_byModuleData[i][j] )
                encodeImage.setPixel( i + QR_MARGIN, j + QR_MARGIN, 0 );

    ui->image_label->setPixmap( QPixmap::fromImage( encodeImage ) );

    setScale(ui->sBoxScale->value());
    ui->pButtonSave->setEnabled( successfulEncoding );
}
void GestionAdherent::setScale(int scale)
{
    if ( successfulEncoding )
    {
        int scale_size = encodeImageSize * scale;

        const QPixmap & scale_image = ui->image_label->pixmap()->scaled( scale_size, scale_size );
        ui->image_label->setPixmap( scale_image );

        const QString & size_info = QString( "%1x%2" ).arg( scale_size ).arg( scale_size );
        ui->labelSize->setText( size_info );
    }
}
void GestionAdherent::on_pButtonSave_clicked()
{
    const QString & path = QFileDialog::getSaveFileName( this, QString::null, "qrcode", saveFormats() );
    if ( path.isNull() )
        return;

    ui->image_label->pixmap()->save( path );
}
void GestionAdherent::on_sBoxScale_valueChanged(int arg1)
{
    setScale( arg1 );
}
void GestionAdherent::on_pTextEditQRText_textChanged()
{
    updateQRImage();
}
void GestionAdherent::on_pButtonQuit_clicked()
{
    close();
}

void GestionAdherent::closeEvent(QCloseEvent *)
{
    QSettings ini( getIniPath(), QSettings::IniFormat );
    ini.setValue( ui->splitter->objectName(), ui->splitter->saveState() );
    ini.setValue( ui->splitter_2->objectName(), ui->splitter_2->saveState() );
    ini.setValue( ui->sBoxScale->objectName(), ui->sBoxScale->value() );
  //  ini.setValue( "State", saveState() );
    ini.setValue( "Geometry", saveGeometry() );

    qApp->quit();
}
bool GestionAdherent::eventFilter( QObject * object, QEvent * event )
{
    QScrollArea * scrollArea = ui->scrollArea;

    if ( object == scrollArea )
    {
        if ( event->type() == QEvent::MouseButtonPress )
        {
            QMouseEvent * mouseEvent = static_cast < QMouseEvent * > ( event );
            if ( mouseEvent->button() == Qt::LeftButton )
            {
                lastPos = mouseEvent->pos();

                if( scrollArea->horizontalScrollBar()->isVisible()
                        || scrollArea->verticalScrollBar()->isVisible() )
                    scrollArea->setCursor( Qt::ClosedHandCursor );
                else
                    scrollArea->setCursor( Qt::ArrowCursor );
            }

        }else if ( event->type() == QEvent::MouseMove )
        {
            QMouseEvent *mouseEvent = static_cast < QMouseEvent * > ( event );

            if ( mouseEvent->buttons() == Qt::LeftButton )
            {
                lastPos -= mouseEvent->pos();

                int hValue = scrollArea->horizontalScrollBar()->value();
                int vValue = scrollArea->verticalScrollBar()->value();

                scrollArea->horizontalScrollBar()->setValue( lastPos.x() + hValue );
                scrollArea->verticalScrollBar()->setValue( lastPos.y() + vValue );

                lastPos = mouseEvent->pos();
            }

        }else if ( event->type() == QEvent::MouseButtonRelease )
            scrollArea->setCursor( Qt::ArrowCursor );
    }

    return QWidget::eventFilter(object, event);
}




void GestionAdherent::on_StartMusicb_clicked()
{
    Player->setMedia(QUrl::fromLocalFile("C:/Users/Yassine/Downloads/Queen_We_Are_The_Champions.mp3"));
    Player->play();
    qDebug() <<Player->errorString();
}

void GestionAdherent::on_StopMusicBtn_clicked()
{
    Player->stop();
}

void GestionAdherent::on_ProgressSlider_sliderMoved(int position)
{
    Player->setPosition(position);
}

void GestionAdherent::on_VolumeSlider_sliderMoved(int position)
{
    Player->setVolume(position);
}

void GestionAdherent::on_positionChanged(qint64 position)
{
    ui->ProgressSlider->setValue(position);
}

void GestionAdherent::on_durationChanged(qint64 position)
{
    ui->ProgressSlider->setMaximum(position);
}

void GestionAdherent::on_exclBbtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                            tr("Fichiers d'extension Excel (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->tabaffect);

            // you can change the column order and
            // choose which colum to export
            obj.addField(0, "Nom", "char(20)");
            obj.addField(1, "prenom", "char(20)");
            obj.addField(2, "Id_Adherent", "char(20)");
            //obj.addField(3, "servespeed1", "number");
          //  obj.addField(4, "servespeed2", "char(20)");
            //obj.addField(5, "servespeed3", "char(20)");


            int retVal = obj.export2Excel();

            if( retVal > 0)
            {
                QMessageBox::information(this, tr("FAIS!"),
                                         QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                         );
            }
}

void GestionAdherent::on_ReadNotes_clicked()
{
    QFile file("C:/Users/Yassine/Desktop/h.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {QMessageBox::warning(this,"tilte","file not open");
}
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);

    file.close();
}

void GestionAdherent::on_WriteNotes_clicked()
{
    QFile file("C:/Users/Yassine/Desktop/h.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {QMessageBox::warning(this,"tilte","file not open");
}
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

/*void GestionAdherent::on_actionopen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open a File","","Video File (*.*)");
        on_actionstop_triggered();

        player->setMedia(QUrl::fromLocalFile(filename));

        on_actionplay_triggered();
}

void GestionAdherent::on_actionplay_triggered()
{
    player->play();
        ui->statusBar->showMessage("Playing");
}

void GestionAdherent::on_actionpause_triggered()
{
    player->pause();
        ui->statusBar->showMessage("Paused...");
}

void GestionAdherent::on_actionstop_triggered()
{
    player->stop();
        ui->statusBar->showMessage("Stopped");
}*/

void GestionAdherent::on_tabWidget_2_currentChanged(int index)
{
performance P;
P.statt(ui->widget);
}

void GestionAdherent::on_pushButton_4_clicked()
{

hide();
Radh= new MainWindow(this);
Radh->show();

}
void GestionAdherent::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/*
 WORKAROUND to escape "protected" limitation and use that freaking static function!
 */
class Kek : public QThread
{
public:
    static void wait(unsigned long)
    {
        QThread::msleep(200);
    }
};

void GestionAdherent::on_makeShot_clicked()
{
    this->hide();
    qApp->processEvents();
#ifdef _WIN32
    //Sleep(3000);
#else
    Kek::wait(200);
#endif

    QPixmap okno = QPixmap::grabWindow(QApplication::desktop()->winId());
    QDateTime t = QDateTime::currentDateTime();
    QString saveWhere = qApp->applicationDirPath() + QString("/Scr_%1-%2-%3-%4-%5-%6.png")
            .arg(t.date().year()).arg(t.date().month()).arg(t.date().day())
            .arg(t.time().hour()).arg(t.time().minute()).arg(t.time().second());
    QString saveAs = QFileDialog::getSaveFileName(NULL, "Save screenshot as...",
                                                  saveWhere,
                                                  "PNG Picture (*.png)",
                                                  nullptr,
                                                  QFileDialog::DontUseNativeDialog);
    if(!saveAs.isEmpty())
        okno.save(saveAs, "PNG");

    this->show();
}
void GestionAdherent::on_google_search_button_clicked()
{
searchEdit.show();
}
void GestionAdherent::on_languageAd_activated(const QString &arg1)
{
    if(ui->languageAd->currentText()=="English")
    {ui->label->setText("Last Name");
     ui->label_2->setText("Fist Name");
     ui->label_3->setText("Birth Date");
     ui->label_4->setText("Gender");
     ui->label_20->setText("E-mail");
     ui->label_21->setText("Phone Number");
     ui->label_22->setText("Adress");
     ui->pbAjouter->setText("Add");
     ui->ModifierAdButton->setText("Modify");
    }
    else
    {ui->label->setText("Nom");
        ui->label_2->setText("Prenom");
        ui->label_3->setText("Date de Naissence");
        ui->label_4->setText("Sexe");
        ui->label_20->setText("Adresse Mail");
        ui->label_21->setText("Numero de Telephone");
        ui->label_22->setText("Adresse");
        ui->pbAjouter->setText("Ajouter");
        ui->ModifierAdButton->setText("Modifier");
    }
}
