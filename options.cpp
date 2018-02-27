#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);

    ui->eListe->setEnabled(false);

    Preparation();

    connect(ui->bAjouter,SIGNAL(clicked()),this,SLOT(Ajout()));
    connect(ui->cType,SIGNAL(currentTextChanged(QString)),this,SLOT(Liste(QString)));
    connect(ui->bEnregistrer,SIGNAL(clicked()),this,SLOT(Enregistrer()));
}

Options::~Options()
{
    delete ui;
}

void Options::Preparation()
{
    QFile fichier("Liens.ini");

    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream flux(&fichier);

        while(!flux.atEnd())
        {
            ui->eText->append(flux.readLine());
        }
    }
}

void Options::Liste(QString nom)
{
    if(nom == "Case à cocher")
    {
        ui->eListe->setEnabled(false);
    }
    else
    {
        ui->eListe->setEnabled(true);
    }
}

void Options::Ajout()
{
    QString resultat;

    resultat.append(ui->cOnglet->currentText() + "|");

    if(ui->cType->currentText() == "Case à cocher")
    {
        resultat.append("Divers|");
    }
    else
    {
        resultat.append(ui->eListe->text() + "|");
    }
    resultat.append(ui->eNom->text() + "|");
    resultat.append(ui->eLien->text());

    ui->eText->append(resultat);
}

void Options::Enregistrer()
{
    QFile fichier("Liens.ini");
    fichier.resize(0);
    if(fichier.open(QIODevice::ReadWrite) && Controle())
    {
        QTextStream flux(&fichier);
        flux << ui->eText->toPlainText();
        QMessageBox::information(this,"Terminer","Le fichier à été mis à jour avec succès !");
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Le fichier n'a pa pu être écrit");
    }
}

bool Options::Controle()
{
    QStringList list = ui->eText->toPlainText().split("\n");
    QStringList test;
    int test2 = 0;

    for(int cpt = 0;cpt < list.count();cpt++)
    {
        if(list.at(cpt).split("|").at(1) == "Divers")
        {
            test2++;
        }
        else
        {
            bool test4 = false;
            for(int cpt2 = 0;cpt2 < test.count();cpt2++)
            {
                if(test.at(cpt2) == list.at(cpt).split("|").at(1))
                    test4 = true;
            }
            if(!test4)
            {
                test.append(list.at(cpt).split("|").at(1));
            }
        }
    }
    if(test.count() > 5)
    {
        QMessageBox::warning(this,"Erreur","Maximum 5 listes autorisées");
        return false;
    }
    if(test2 > 20)
    {
        QMessageBox::warning(this,"Erreur","Maximum 20 cases à cocher autorisées");
        return false;
    }
    return true;
}



























