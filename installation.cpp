#include "installation.h"

void Installation::run()
{
    while(1)
    {
        sleep(3);
        installation();
    }
}

void Installation::installation()
{
    if(nom.count() > 0)
    {

        emit debutInstall(nom.at(0));
        QProcess *processus = new QProcess;
        QFile fichier;
        fichier.setFileName("Temp/" + nom.at(0) + "_setup.exe");
        qDebug() << fichier.exists();
        if(fichier.exists())
            processus->start("Temp/" + nom.at(0) + "_setup.exe");
        connect(processus, SIGNAL(finished(int)), this, SLOT(quit()));
        connect(processus, SIGNAL(finished(int)), this, SLOT(Erreur(int)));
        connect(processus,SIGNAL(error(QProcess::ProcessError)), this, SLOT(quit()));

        qDebug() << "install" << nom.at(0);
        exec();
        nom.removeAt(0);
    }
}

bool Installation::debut(QString nom2)
{
    if(nom2 != "")
    {
        nom.append(nom2);
        return true;
    }
    return false;
}

void Installation::Erreur(int retCode)
{
    QString nom2 = nom.at(0).split("|").at(0) + "_setup.exe";

    QFile fichier(nom2);
    qDebug() << fichier.remove();

    if(retCode == 0)
    {
        qDebug() << "inst == 0";
        emit finInst(nom2.split("_").at(0),true);
    }
    else
    {
        qDebug() << "inst else";
        emit erreur(retCode,nom2.split("_").at(0));
        emit finInst(nom2.split("_").at(0),false);
    }
}

void Installation::Fin(QString nom, bool fin)
{
    emit finInst(nom,fin);
}

















