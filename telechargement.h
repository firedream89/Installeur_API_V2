#ifndef TELECHARGEMENT_H
#define TELECHARGEMENT_H

#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QProcess>
#include <QDir>
#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>
#include <QWebView>
#include <QWebFrame>
#include <QNetworkCookieJar>

class Telechargement : public QWidget
{
    Q_OBJECT
public:
    explicit Telechargement();
    ~Telechargement();
    bool LancementTelechargement(QString lien);
    QStringList VerificationLien(QStringList liens);
    bool ListTelechargement(QStringList liens);

private slots:
    void DownProgress(qint64 actuel,qint64 max);
    void Erreur(QNetworkReply::NetworkError);
    void LancementTelechargement(QNetworkReply* reply);
    void OuverturePage(QString lien);

signals:
    void finTelechargement(QString);
    void avancementDown(qint64 actuel,qint64 max,QString temps,QString file);
    void avancementDown(qint64 actuel, qint64 max, QString file);
    void Erreur(QString file);
    void pret();
    void listPrete();

private:
    QNetworkCookieJar *cookieJar;
    QString temps;
    QTimer timer;
    QString enCours;
    double aActuel;
    QStringList moyenne;
    QStringList listLiens;
    QWebView *web;
    bool finDown;
};

#endif // TELECHARGEMENT_H
