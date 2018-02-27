#include "chargement.h"
#include "ui_chargement.h"

Chargement::Chargement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chargement)
{
    ui->setupUi(this);
}

Chargement::~Chargement()
{
    delete ui;
}

void Chargement::init(int nbDown)
{
    ui->nbInstallation->setMinimum(0);
    ui->nbTelechargement->setMinimum(0);
    ui->nbInstallation->setMaximum(nbDown);
    ui->nbTelechargement->setMaximum(nbDown);
    ui->nbInstallation->setValue(0);
    ui->nbTelechargement->setValue(0);
    ui->installationActuel->setText("");
    ui->telechargementActuel->setText("");

    this->show();
}

void Chargement::UpdateDown(qint64 actuel,qint64 max,QString nom)
{
    double total(QVariant(max/1000).toDouble());
    double act(QVariant(actuel/1000).toDouble());
    QString a("Ko"),t("Ko");
    if(total > 1000)
    {
        total = total / 1000;
        t = "Mo";
    }
    if(act > 1000)
    {
        act = act / 1000;
        a = "Mo";
    }
    int entier = (int)(act * 100.0);
    act = (double)entier / 100.0;
    entier = (int)(total * 100.0);
    total = (double)entier / 100.0;
    ui->telechargementActuel->setText(tr("%0(%1%3/%2%4)").arg(nom).arg(act).arg(total).arg(a).arg(t));
    if(nom != nomDown && max > 100000)
    {
        nomDown = nom;
        ui->nbTelechargement->setValue(ui->nbTelechargement->value()+1);
    }
}

void Chargement::UpdateInstall(QString nom)
{
    ui->installationActuel->setText(nom);
    ui->nbInstallation->setValue(ui->nbInstallation->value()+1);
}
