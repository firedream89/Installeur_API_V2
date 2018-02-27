#include "telechargement.h"

Telechargement::Telechargement()
{
    connect(&timer,SIGNAL(timeout()),&timer,SLOT(stop()));
    web = new QWebView;
    web->page()->setForwardUnsupportedContent(true);
    cookieJar = new QNetworkCookieJar;
    web->page()->networkAccessManager()->setCookieJar(cookieJar);
    connect(web->page(),SIGNAL(unsupportedContent(QNetworkReply*)),this,SLOT(LancementTelechargement(QNetworkReply*)));
}

Telechargement::~Telechargement()
{

}
bool Telechargement::LancementTelechargement(QString lien)
{
    qDebug() << "down0" << lien;
    enCours = lien.split("|").at(0);
    qDebug() << "down1";
    QEventLoop *loop = new QEventLoop;
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(lien.split("|").at(1),QUrl::TolerantMode)));

    qDebug() << "down2";
    connect(reply, SIGNAL(finished()), loop, SLOT(quit()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), SLOT(DownProgress(qint64,qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(Erreur(QNetworkReply::NetworkError)));
    qDebug() << "down3";

    loop->exec();

    qDebug() << "down4";
    QFile fichier;

    if(lien.split("|").at(1).split(".").last() == "exe")
        fichier.setFileName("Temp/" + lien.split("|").at(0) + "_setup." + lien.split("|").at(1).split(".").last());
    else if(lien.split("|").at(1).split(".").last().count() > 3)
        fichier.setFileName("Temp/" + lien.split("|").at(0) + "_temp.txt");
    else
        fichier.setFileName("Temp/" + lien.split("|").at(0) + "." + lien.split("|").at(1).split(".").last());
    if(!fichier.open(QIODevice::WriteOnly))
        qDebug() << "erreur ouverture fichier";
    fichier.write(reply->readAll());

    if(fichier.size() < 100000)
        return false;
    return true;

}

void Telechargement::LancementTelechargement(QNetworkReply* reply)
{
    qDebug() << "down" << enCours;
    QString nom = enCours;
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),this, SLOT(DownProgress(qint64,qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(Erreur(QNetworkReply::NetworkError)));
    loop.exec();

    QFile fichier("Temp/" + enCours + "_setup.exe");
    fichier.open(QIODevice::WriteOnly);
    fichier.write(reply->readAll());
    if(fichier.size() > 1000)
        emit finTelechargement(nom);
    qDebug() << "down terminé" << enCours;
}

void Telechargement::OuverturePage(QString lien)
{
    QEventLoop loop;
    connect(web,SIGNAL(loadFinished(bool)),&loop,SLOT(quit()));
    web->load(QUrl(lien));
    loop.exec();
    //QWebFrame *frame = web->page()->mainFrame();
    //frame->evaluateJavaScript("document.getElementById('dlButton').click();");
}

void Telechargement::Erreur(QNetworkReply::NetworkError)
{
    qDebug() << "erreur down reply";
    emit Erreur(enCours);
}

void Telechargement::DownProgress(qint64 actuel,qint64 max)
{
    /*if(actuel != 0 && max != 0)
    {
        if(!timer.isActive())
        {
            double max3 = QVariant(max/1000).toDouble();
            double actuel2 = QVariant(actuel/1000).toDouble();
            double debit = (QVariant(actuel/1000).toDouble()) - aActuel;
            aActuel = QVariant(actuel/1000).toDouble();

            if(moyenne.count() < 5)
            {
                moyenne.append(QString::number(debit));
            }
            else
            {
                if(moyenne.count() > 50)
                    moyenne.removeAt(0);

                moyenne.append(QString::number(debit));
                debit = 0;
                for(int cpt = 0;cpt<moyenne.count();cpt++)
                {
                    debit += moyenne.at(cpt).toDouble();
                }
                debit /= moyenne.count();

                //debit = (moyenne.at(0).toDouble() + moyenne.at(1).toDouble() + moyenne.at(2).toDouble() + moyenne.at(3).toDouble() + moyenne.at(4).toDouble()) / 5;
                int sec = (max3 / debit) - (actuel2 / debit);
                if(sec > 60)
                {
                    double mn = sec / 60;
                    temps = QString::number(mn) + "mn";
                }
                else
                {
                    temps = QString::number(sec) + "s";
                }
            }
            timer.start(1000);
        }*/
        emit avancementDown(actuel,max,enCours);

}

QStringList Telechargement::VerificationLien(QStringList liens)
{
    for(int cpt(0);cpt<liens.count();cpt++)
    {
        if(liens.at(cpt).split("|").at(1).split(".").last().count() > 3)
        {
            qDebug() << "verifLien0";
            LancementTelechargement(liens.at(cpt));
            qDebug() << "verifLien1";
            QFile fichier;
            fichier.setFileName("Temp/" + liens.at(cpt).split("|").at(0) + "_temp.txt");
            fichier.open(QIODevice::ReadOnly);
            QTextStream flux(&fichier);
            QString url2 = "";

            while(!flux.atEnd())
            {
                //Contrôle CommentCaMarche
                QStringList temp = flux.readLine().split("\"");
                if(temp.count() > 3)
                {
                    for(int cpt2 = 0;cpt2<temp.count();cpt2++)
                    {
                        if(temp.at(cpt2) == "marB10")
                        {
                            url2 = temp.at(3);
                            liens.replace(cpt,liens.at(cpt).split("|").at(0) + "|" + url2);
                            fichier.close();
                        }
                        else if(temp.at(temp.count()-2) == "dlButton")
                        {
                            url2 = temp.at(1);
                            liens.replace(cpt,liens.at(cpt).split("|").at(0) + "|" + url2);
                            fichier.close();
                        }
                        else if(temp.at(cpt2) == "new-dl-btn")
                        {
                            url2 = temp.at(3);
                            liens.replace(cpt,liens.at(cpt).split("|").at(0) + "|" + url2);
                            fichier.close();
                        }
                    }
                }
            }
            fichier.remove();
        }

        /*
        else if(down.at(cpt).split(";").count() > 1)
        {

            QStringList valeur = down.at(cpt).split("|");
qDebug() << "OK" << valeur;
                QStringList valeur2 = valeur.at(valeur.count()-1).split(";");
                if(valeur2.count() > 1)
                {
                    qDebug() << "OK";
                    for(int cpt3 = 0;cpt3 < valeur2.count();cpt3++)
                    {
                        qDebug() << "OK" << valeur2;
                        if(cpt3 == 0)
                        {
                            down.append(valeur.at(0) + "|" + valeur2.at(cpt3));
                        }
                        else
                        {
                            down.append(valeur2.at(cpt3) + "|" + valeur2.at(cpt3+1));
                            cpt3++;
                        }
                    }
                }
qDebug() << "OK";
            down.removeAt(cpt);
        }*/
    }
    qDebug() << liens;
    return liens;
}

bool Telechargement::ListTelechargement(QStringList liens)
{
    qDebug() << "listDown1";
    liens = VerificationLien(liens);
qDebug() << "listDown2";
    emit pret();
    for(int cpt = 0;cpt<liens.count();cpt++)
    {
        finDown = false;
        enCours = liens.at(cpt).split("|").at(0);
        OuverturePage(liens.at(cpt).split("|").last());

        moyenne.clear();
        temps.clear();
        timer.stop();
        aActuel = 0;

    }
    return true;
}
