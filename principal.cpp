#include "principal.h"
#include "ui_principal.h"

////////////////////////////
QString version("2.2");
///////////////////////////

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);

    QDir dir;
    dir.mkdir("Temp");

    this->setWindowTitle("Installeur API V" + version);

    manager = new QNetworkAccessManager;

    combo1 = new QComboBox;
    combo2 = new QComboBox;
    combo3 = new QComboBox;
    combo4 = new QComboBox;
    combo5 = new QComboBox;

    combo1->setAccessibleName("Vide");
    combo2->setAccessibleName("Vide");
    combo3->setAccessibleName("Vide");
    combo4->setAccessibleName("Vide");
    combo5->setAccessibleName("Vide");

    combo1->addItem("Aucun");
    combo2->addItem("Aucun");
    combo3->addItem("Aucun");
    combo4->addItem("Aucun");
    combo5->addItem("Aucun");

    check1 = new QCheckBox;
    check2 = new QCheckBox;
    check3 = new QCheckBox;
    check4 = new QCheckBox;
    check5 = new QCheckBox;
    check6 = new QCheckBox;
    check7 = new QCheckBox;
    check8 = new QCheckBox;
    check9 = new QCheckBox;
    check10 = new QCheckBox;
    check11 = new QCheckBox;
    check12 = new QCheckBox;
    check13 = new QCheckBox;
    check14 = new QCheckBox;
    check15 = new QCheckBox;
    check16 = new QCheckBox;
    check17 = new QCheckBox;
    check18 = new QCheckBox;
    check19 = new QCheckBox;
    check20 = new QCheckBox;

    check1->setAccessibleName("Vide");
    check2->setAccessibleName("Vide");
    check3->setAccessibleName("Vide");
    check4->setAccessibleName("Vide");
    check5->setAccessibleName("Vide");
    check6->setAccessibleName("Vide");
    check7->setAccessibleName("Vide");
    check8->setAccessibleName("Vide");
    check9->setAccessibleName("Vide");
    check10->setAccessibleName("Vide");
    check11->setAccessibleName("Vide");
    check12->setAccessibleName("Vide");
    check13->setAccessibleName("Vide");
    check14->setAccessibleName("Vide");
    check15->setAccessibleName("Vide");
    check16->setAccessibleName("Vide");
    check17->setAccessibleName("Vide");
    check18->setAccessibleName("Vide");
    check19->setAccessibleName("Vide");
    check20->setAccessibleName("Vide");

    ui->e1->setAlignment(Qt::AlignHCenter);
    ui->e2->setAlignment(Qt::AlignHCenter);
    ui->e3->setAlignment(Qt::AlignHCenter);
    ui->e4->setAlignment(Qt::AlignHCenter);
    ui->e5->setAlignment(Qt::AlignHCenter);
    ui->e6->setAlignment(Qt::AlignHCenter);
    ui->e7->setAlignment(Qt::AlignHCenter);
    ui->e8->setAlignment(Qt::AlignHCenter);
    ui->e9->setAlignment(Qt::AlignHCenter);
    ui->e10->setAlignment(Qt::AlignHCenter);
    ui->e11->setAlignment(Qt::AlignHCenter);
    ui->e12->setAlignment(Qt::AlignHCenter);
    ui->e13->setAlignment(Qt::AlignHCenter);
    ui->e14->setAlignment(Qt::AlignHCenter);
    ui->e15->setAlignment(Qt::AlignHCenter);
    ui->e16->setAlignment(Qt::AlignHCenter);

    ui->e1->setMinimum(0);
    ui->e2->setMinimum(0);
    ui->e3->setMinimum(0);
    ui->e4->setMinimum(0);
    ui->e5->setMinimum(0);
    ui->e6->setMinimum(0);
    ui->e7->setMinimum(0);
    ui->e8->setMinimum(0);
    ui->e9->setMinimum(0);
    ui->e10->setMinimum(0);
    ui->e11->setMinimum(0);
    ui->e12->setMinimum(0);
    ui->e13->setMinimum(0);
    ui->e14->setMinimum(0);
    ui->e15->setMinimum(0);
    ui->e16->setMinimum(0);

    Preparation();
    Reset(true);

    install = new Installation;
    download = new Telechargement;

    install->start();

    timer = new QTimer;


    connect(ui->bValider, SIGNAL(clicked()), this, SLOT(PrepaTelechargement()));
    connect(install, SIGNAL(debutInstall(QString)), &chargement, SLOT(UpdateInstall(QString)));
    connect(install, SIGNAL(erreur(int,QString)), this, SLOT(TErreur(int,QString)));
    connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(FOptions()));
    connect(download,SIGNAL(Erreur(QString)),this,SLOT(TErreur(QString)));
    connect(download,SIGNAL(finTelechargement(QString)),install,SLOT(debut(QString)));
    connect(download,SIGNAL(avancementDown(qint64,qint64,QString)),&chargement,SLOT(UpdateDown(qint64,qint64,QString)));
}

Principal::~Principal()
{
    delete ui;
}

void Principal::Preparation()
{
    QFile fichierLien("Liens.ini");
    if(!fichierLien.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"Erreur","Ouverture impossible du fichier 'Liens.ini'");
        qApp->exit(0);
    }
    QTextStream flux(&fichierLien);

    while(!flux.atEnd())
    {
        //ex:Général|Antivirus|Avast|http://avast.com/download
        //ex:Onglet|Type|Nom|lien

        QStringList ligne = flux.readLine().split("|");

        if(ligne.count() == 4 && ligne.at(0).at(1) != '/')
        {                
            if(ligne.at(1) != "Divers")
            {
                if(combo1->accessibleName() == ligne.at(1) || combo1->accessibleName() == "Vide")
                {
                    if(combo1->accessibleName() == "Vide")
                    {
                        combo1->setAccessibleName(ligne.at(1));

                        if(ligne.at(0) == "Général")
                            ui->layoutGeneral->addRow(ligne.at(1), combo1);
                        if(ligne.at(0) == "Utilitaire")
                            ui->layoutUtilitaire->addRow(ligne.at(1), combo1);
                        if(ligne.at(0) == "Jeux")
                            ui->layoutJeux->addRow(ligne.at(1), combo1);
                    }

                    combo1->addItem(ligne.at(2),QVariant(ligne.at(3)));
                    combo1->setItemData(combo1->count()-1,QVariant(ligne.at(2) + "|" + ligne.at(3)));
                }
                else if(combo2->accessibleName() == ligne.at(1) || combo2->accessibleName() == "Vide")
                {
                    if(combo2->accessibleName() == "Vide")
                    {
                        combo2->setAccessibleName(ligne.at(1));

                        if(ligne.at(0) == "Général")
                            ui->layoutGeneral->addRow(ligne.at(1), combo2);
                        if(ligne.at(0) == "Utilitaire")
                            ui->layoutUtilitaire->addRow(ligne.at(1), combo2);
                        if(ligne.at(0) == "Jeux")
                            ui->layoutJeux->addRow(ligne.at(1), combo2);
                    }

                    combo2->addItem(ligne.at(2),QVariant(ligne.at(3)));
                    combo2->setItemData(combo2->count()-1,QVariant(ligne.at(2) + "|" + ligne.at(3)));
                }
                else if(combo3->accessibleName() == ligne.at(1) || combo3->accessibleName() == "Vide")
                {
                    if(combo3->accessibleName() == "Vide")
                    {
                        combo3->setAccessibleName(ligne.at(1));

                        if(ligne.at(0) == "Général")
                            ui->layoutGeneral->addRow(ligne.at(1), combo3);
                        if(ligne.at(0) == "Utilitaire")
                            ui->layoutUtilitaire->addRow(ligne.at(1), combo3);
                        if(ligne.at(0) == "Jeux")
                            ui->layoutJeux->addRow(ligne.at(1), combo3);
                    }

                    combo3->addItem(ligne.at(2),QVariant(ligne.at(3)));
                    combo3->setItemData(combo3->count()-1,QVariant(ligne.at(2) + "|" + ligne.at(3)));
                }
                else if(combo4->accessibleName() == ligne.at(1) || combo4->accessibleName() == "Vide")
                {
                    if(combo4->accessibleName() == "Vide")
                    {
                        combo4->setAccessibleName(ligne.at(1));

                        if(ligne.at(0) == "Général")
                            ui->layoutGeneral->addRow(ligne.at(1), combo4);
                        if(ligne.at(0) == "Utilitaire")
                            ui->layoutUtilitaire->addRow(ligne.at(1), combo4);
                        if(ligne.at(0) == "Jeux")
                            ui->layoutJeux->addRow(ligne.at(1), combo4);
                    }

                    combo4->addItem(ligne.at(2),QVariant(ligne.at(3)));
                    combo4->setItemData(combo4->count()-1,QVariant(ligne.at(2) + "|" + ligne.at(3)));
                }
                else if(combo5->accessibleName() == ligne.at(1) || combo5->accessibleName() == "Vide")
                {
                    if(combo5->accessibleName() == "Vide")
                    {
                        combo5->setAccessibleName(ligne.at(1));

                        if(ligne.at(0) == "Général")
                            ui->layoutGeneral->addRow(ligne.at(1), combo5);
                        if(ligne.at(0) == "Utilitaire")
                            ui->layoutUtilitaire->addRow(ligne.at(1), combo5);
                        if(ligne.at(0) == "Jeux")
                            ui->layoutJeux->addRow(ligne.at(1), combo5);
                    }

                    combo5->addItem(ligne.at(2),QVariant(ligne.at(3)));
                    combo5->setItemData(combo5->count()-1,QVariant(ligne.at(2) + "|" + ligne.at(3)));
                }
            }
            else
            {
                if(check1->accessibleName() == "Vide")
                {
                    check1->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check1);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check1);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check1);
                }
                else if(check2->accessibleName() == "Vide")
                {
                    check2->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check2);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check2);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check2);
                }
                else if(check3->accessibleName() == "Vide")
                {
                    check3->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check3);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check3);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check3);
                }
                else if(check4->accessibleName() == "Vide")
                {
                    check4->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check4);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check4);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check4);
                }
                else if(check5->accessibleName() == "Vide")
                {
                    check5->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check5);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check5);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check5);
                }
                else if(check6->accessibleName() == "Vide")
                {
                    check6->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check6);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check6);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check6);
                }
                else if(check7->accessibleName() == "Vide")
                {
                    check7->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check7);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check7);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check7);
                }
                else if(check8->accessibleName() == "Vide")
                {
                    check8->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check8);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check8);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check8);
                }
                else if(check9->accessibleName() == "Vide")
                {
                    check9->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check9);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check9);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check9);
                }
                else if(check10->accessibleName() == "Vide")
                {
                    check10->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check10);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check10);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check10);
                }
                else if(check11->accessibleName() == "Vide")
                {
                    check11->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check11);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check11);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check11);
                }
                else if(check12->accessibleName() == "Vide")
                {
                    check12->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check12);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check12);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check12);
                }
                else if(check13->accessibleName() == "Vide")
                {
                    check13->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check13);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check13);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check13);
                }
                else if(check14->accessibleName() == "Vide")
                {
                    check14->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check14);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check14);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check14);
                }
                else if(check15->accessibleName() == "Vide")
                {
                    check15->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check15);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check15);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check15);
                }
                else if(check16->accessibleName() == "Vide")
                {
                    check16->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check16);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check16);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check16);
                }
                else if(check17->accessibleName() == "Vide")
                {
                    check17->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check17);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check17);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check17);
                }
                else if(check18->accessibleName() == "Vide")
                {
                    check18->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check18);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check18);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check18);
                }
                else if(check19->accessibleName() == "Vide")
                {
                    check19->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check19);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check19);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check19);
                }
                else if(check20->accessibleName() == "Vide")
                {
                    check20->setAccessibleName(ligne.at(2) + "|" + ligne.at(3));

                    if(ligne.at(0) == "Général")
                        ui->layoutGeneral->addRow(ligne.at(2),check20);
                    if(ligne.at(0) == "Utilitaire")
                        ui->layoutUtilitaire->addRow(ligne.at(2),check20);
                    if(ligne.at(0) == "Jeux")
                        ui->layoutJeux->addRow(ligne.at(2),check20);
                }
            }
        }
    }
    //Test
    //ui->layoutUtilitaire->findChildren()
}

void Principal::DebutInstall(QString nom)
{
    qDebug() << "Début";
    QStringList listNom = nom.split("|");

    chargement.UpdateInstall(listNom.at(0));
}

void Principal::PrepaTelechargement()
{
    ui->bValider->setEnabled(false);
    QStringList down;

    Reset(true);

    if(combo1->currentText() != "Aucun")
        down.append(combo1->itemData(combo1->currentIndex()).toString());
    if(combo2->currentText() != "Aucun")
        down.append(combo2->itemData(combo2->currentIndex()).toString());
    if(combo3->currentText() != "Aucun")
        down.append(combo3->itemData(combo3->currentIndex()).toString());
    if(combo4->currentText() != "Aucun")
        down.append(combo4->itemData(combo4->currentIndex()).toString());
    if(combo5->currentText() != "Aucun")
        down.append(combo5->itemData(combo5->currentIndex()).toString());
    if(check1->accessibleName() != "Vide" && check1->isChecked())
        down.append(check1->accessibleName());
    if(check2->accessibleName() != "Vide" && check2->isChecked())
        down.append(check2->accessibleName());
    if(check3->accessibleName() != "Vide" && check3->isChecked())
        down.append(check3->accessibleName());
    if(check4->accessibleName() != "Vide" && check4->isChecked())
        down.append(check4->accessibleName());
    if(check5->accessibleName() != "Vide" && check5->isChecked())
        down.append(check5->accessibleName());
    if(check6->accessibleName() != "Vide" && check6->isChecked())
        down.append(check6->accessibleName());
    if(check7->accessibleName() != "Vide" && check7->isChecked())
        down.append(check7->accessibleName());
    if(check8->accessibleName() != "Vide" && check8->isChecked())
        down.append(check8->accessibleName());
    if(check9->accessibleName() != "Vide" && check9->isChecked())
        down.append(check9->accessibleName());
    if(check10->accessibleName() != "Vide" && check10->isChecked())
        down.append(check10->accessibleName());
    if(check11->accessibleName() != "Vide" && check11->isChecked())
        down.append(check11->accessibleName());
    if(check12->accessibleName() != "Vide" && check12->isChecked())
        down.append(check12->accessibleName());
    if(check13->accessibleName() != "Vide" && check13->isChecked())
        down.append(check13->accessibleName());
    if(check14->accessibleName() != "Vide" && check14->isChecked())
        down.append(check14->accessibleName());
    if(check15->accessibleName() != "Vide" && check15->isChecked())
        down.append(check15->accessibleName());
    if(check16->accessibleName() != "Vide" && check16->isChecked())
        down.append(check16->accessibleName());
    if(check17->accessibleName() != "Vide" && check17->isChecked())
        down.append(check17->accessibleName());
    if(check18->accessibleName() != "Vide" && check18->isChecked())
        down.append(check18->accessibleName());
    if(check19->accessibleName() != "Vide" && check19->isChecked())
        down.append(check19->accessibleName());
    if(check20->accessibleName() != "Vide" && check20->isChecked())
        down.append(check20->accessibleName());

        chargement.init(down.count());

        download->ListTelechargement(down);
}

void Principal::Reset(bool reset)
{
    if(reset)
    {
        ui->l1->setText("Vide");
        ui->l2->setText("Vide");
        ui->l3->setText("Vide");
        ui->l4->setText("Vide");
        ui->l5->setText("Vide");
        ui->l6->setText("Vide");
        ui->l7->setText("Vide");
        ui->l8->setText("Vide");
        ui->l9->setText("Vide");
        ui->l10->setText("Vide");
        ui->l11->setText("Vide");
        ui->l12->setText("Vide");
        ui->l13->setText("Vide");
        ui->l14->setText("Vide");
        ui->l15->setText("Vide");
        ui->l16->setText("Vide");

        ui->l1->hide();
        ui->e1->hide();
        ui->l2->hide();
        ui->e2->hide();
        ui->l3->hide();
        ui->e3->hide();
        ui->l4->hide();
        ui->e4->hide();
        ui->l5->hide();
        ui->e5->hide();
        ui->l6->hide();
        ui->e6->hide();
        ui->l7->hide();
        ui->e7->hide();
        ui->l8->hide();
        ui->e8->hide();
        ui->l9->hide();
        ui->e9->hide();
        ui->l10->hide();
        ui->e10->hide();
        ui->l11->hide();
        ui->e11->hide();
        ui->l12->hide();
        ui->e12->hide();
        ui->l13->hide();
        ui->e13->hide();
        ui->l14->hide();
        ui->e14->hide();
        ui->l15->hide();
        ui->e15->hide();
        ui->l16->hide();
        ui->e16->hide();

        ui->e1->setFormat("En attente");
        ui->e2->setFormat("En attente");
        ui->e3->setFormat("En attente");
        ui->e4->setFormat("En attente");
        ui->e5->setFormat("En attente");
        ui->e6->setFormat("En attente");
        ui->e7->setFormat("En attente");
        ui->e8->setFormat("En attente");
        ui->e9->setFormat("En attente");
        ui->e10->setFormat("En attente");
        ui->e11->setFormat("En attente");
        ui->e12->setFormat("En attente");
        ui->e13->setFormat("En attente");
        ui->e14->setFormat("En attente");
        ui->e15->setFormat("En attente");
        ui->e16->setFormat("En attente");

        ui->e1->setMaximum(0);
        ui->e1->setValue(1);
        ui->e2->setMaximum(0);
        ui->e2->setValue(1);
        ui->e3->setMaximum(0);
        ui->e3->setValue(1);
        ui->e4->setMaximum(0);
        ui->e4->setValue(1);
        ui->e5->setMaximum(0);
        ui->e5->setValue(1);
        ui->e6->setMaximum(0);
        ui->e6->setValue(1);
        ui->e7->setMaximum(0);
        ui->e7->setValue(1);
        ui->e8->setMaximum(0);
        ui->e8->setValue(1);
        ui->e9->setMaximum(0);
        ui->e9->setValue(1);
        ui->e10->setMaximum(0);
        ui->e10->setValue(1);
        ui->e11->setMaximum(0);
        ui->e11->setValue(1);
        ui->e12->setMaximum(0);
        ui->e12->setValue(1);
        ui->e13->setMaximum(0);
        ui->e13->setValue(1);
        ui->e14->setMaximum(0);
        ui->e14->setValue(1);
        ui->e15->setMaximum(0);
        ui->e15->setValue(1);
        ui->e16->setMaximum(0);
        ui->e16->setValue(1);
        qDebug() << "reset";

        if(ui->tabWidget->count() == 4)
            ui->tabWidget->removeTab(3);

        ui->bValider->setText("Télécharger");
        qDebug() << "reset";
    }
    else
    {
        combo1->setCurrentIndex(0);
        combo2->setCurrentIndex(0);
        combo3->setCurrentIndex(0);
        combo4->setCurrentIndex(0);
        combo5->setCurrentIndex(0);

        check1->setChecked(false);
        check2->setChecked(false);
        check3->setChecked(false);
        check4->setChecked(false);
        check5->setChecked(false);
        check6->setChecked(false);
        check7->setChecked(false);
        check8->setChecked(false);
        check9->setChecked(false);
        check10->setChecked(false);
        check11->setChecked(false);
        check12->setChecked(false);
        check13->setChecked(false);
        check14->setChecked(false);
        check15->setChecked(false);
        check16->setChecked(false);
    }
}

void Principal::Erreur(QNetworkReply::NetworkError erreur)
{
    QString rErreur;
    qDebug() << "E3";
    TErreur(0,manager->property("nom").toString());
    if(erreur == QNetworkReply::ConnectionRefusedError)
    {
        rErreur = "La connexion à été refusée";
    }
    else if(erreur == QNetworkReply::RemoteHostClosedError)
    {
        rErreur = "La connexion avec le serveur à été interrompu";
    }
    else if(erreur == QNetworkReply::HostNotFoundError)
    {
        rErreur = "L'hote n'a pas été trouvé";
    }
    else if(erreur == QNetworkReply::TimeoutError)
    {
        rErreur = "Le délais d'attente à été dépassé";
    }
    else if(erreur == QNetworkReply::ContentAccessDenied)
    {
        rErreur = "vous n'etes pas autorisé à récuperé ce fichier";
    }
    else if (erreur == QNetworkReply::ContentNotFoundError)
    {
        rErreur = "Ce fichier n'existe plus sur les serveurs";
    }
    else
    {
        rErreur = "Une erreur inconnu s'est produite lors du téléchargement d'un fichier";
    }
    QMessageBox::warning(this,"Erreur",rErreur);

}

void Principal::TErreur(int retCode, QString nom)
{
    if(retCode != 0)
        QMessageBox::warning(&chargement,"Erreur","Une erreur est survenue dans l'installation de " + nom);

    if(nom != "")
    {
        if(ui->l1->text() == nom)
            ui->e1->setFormat("Erreur");
        if(ui->l2->text() == nom)
            ui->e2->setFormat("Erreur");
        if(ui->l3->text() == nom)
            ui->e3->setFormat("Erreur");
        if(ui->l4->text() == nom)
            ui->e4->setFormat("Erreur");
        if(ui->l5->text() == nom)
            ui->e5->setFormat("Erreur");
        if(ui->l6->text() == nom)
            ui->e6->setFormat("Erreur");
        if(ui->l7->text() == nom)
            ui->e7->setFormat("Erreur");
        if(ui->l8->text() == nom)
            ui->e8->setFormat("Erreur");
        if(ui->l9->text() == nom)
            ui->e9->setFormat("Erreur");
        if(ui->l10->text() == nom)
            ui->e10->setFormat("Erreur");
        if(ui->l11->text() == nom)
            ui->e11->setFormat("Erreur");
        if(ui->l12->text() == nom)
            ui->e12->setFormat("Erreur");
        if(ui->l13->text() == nom)
            ui->e13->setFormat("Erreur");
        if(ui->l14->text() == nom)
            ui->e14->setFormat("Erreur");
        if(ui->l15->text() == nom)
            ui->e15->setFormat("Erreur");
        if(ui->l16->text() == nom)
            ui->e16->setFormat("Erreur");
    }
}

void Principal::TErreur(QString nom)
{
    qDebug() << "Erreur " << nom;
    if(ui->l1->text() == nom)
    {
        ui->e1->setMaximum(1);
        ui->e1->setFormat("Erreur");
    }
    if(ui->l2->text() == nom)
    {
        ui->e2->setMaximum(1);
        ui->e2->setFormat("Erreur");
    }
    if(ui->l3->text() == nom)
    {
        ui->e3->setMaximum(1);
        ui->e3->setFormat("Erreur");
    }
    if(ui->l4->text() == nom)
    {
        ui->e4->setMaximum(1);
        ui->e4->setFormat("Erreur");
    }
    if(ui->l5->text() == nom)
    {
        ui->e5->setMaximum(1);
        ui->e5->setFormat("Erreur");
    }
    if(ui->l6->text() == nom)
    {
        ui->e6->setMaximum(1);
        ui->e6->setFormat("Erreur");
    }
    if(ui->l7->text() == nom)
    {
        ui->e7->setMaximum(1);
        ui->e7->setFormat("Erreur");
    }
    if(ui->l8->text() == nom)
    {
        ui->e8->setMaximum(1);
        ui->e8->setFormat("Erreur");
    }
    if(ui->l9->text() == nom)
    {
        ui->e9->setMaximum(1);
        ui->e9->setFormat("Erreur");
    }
    if(ui->l10->text() == nom)
    {
        ui->e10->setMaximum(1);
        ui->e10->setFormat("Erreur");
    }
    if(ui->l11->text() == nom)
    {
        ui->e11->setMaximum(1);
        ui->e11->setFormat("Erreur");
    }
    if(ui->l12->text() == nom)
    {
        ui->e12->setMaximum(1);
        ui->e12->setFormat("Erreur");
    }
    if(ui->l13->text() == nom)
    {
        ui->e13->setMaximum(1);
        ui->e13->setFormat("Erreur");
    }
    if(ui->l14->text() == nom)
    {
        ui->e14->setMaximum(1);
        ui->e14->setFormat("Erreur");
    }
    if(ui->l15->text() == nom)
    {
        ui->e15->setMaximum(1);
        ui->e15->setFormat("Erreur");
    }
    if(ui->l16->text() == nom)
    {
        ui->e16->setMaximum(1);
        ui->e16->setFormat("Erreur");
    }
}

void Principal::FOptions()
{
    Options *options = new Options;
    options->exec();
}

void Principal::SuppressionFichiers()
{
    QDir dossier;
    dossier.setPath("Temp");
    qDebug() << dossier.absolutePath();
    QStringList fichiers = dossier.entryList(QDir::Files | QDir::NoDotAndDotDot);
qDebug() << fichiers;

    for(int cpt = 0;cpt < fichiers.count();cpt++)
    {

        dossier.remove(fichiers.at(cpt));
    }
}

