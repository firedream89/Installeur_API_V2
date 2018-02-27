#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QComboBox>
#include <QCheckBox>
#include <QDebug>
#include <QGroupBox>
#include <QDir>
#include <QtNetwork>
#include "installation.h"
#include "options.h"
#include <QObjectUserData>
#include <QObjectData>
#include "telechargement.h"
#include "chargement.h"

namespace Ui {
class Principal;
}

class Principal : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();

private slots:
    void Preparation();    
    void PrepaTelechargement();
    void DebutInstall(QString nom);
    void Reset(bool reset);
    void TErreur(int retCode, QString nom = 0);
    void TErreur(QString nom);
    void FOptions();
    void SuppressionFichiers();
    void Erreur(QNetworkReply::NetworkError erreur);
    
private:
    Ui::Principal *ui;

    Installation *install;
    Telechargement *download;
    Chargement chargement;
    QNetworkAccessManager *manager;
    QComboBox *combo1;
    QComboBox *combo2;
    QComboBox *combo3;
    QComboBox *combo4;
    QComboBox *combo5;

    QCheckBox *check1;
    QCheckBox *check2;
    QCheckBox *check3;
    QCheckBox *check4;
    QCheckBox *check5;
    QCheckBox *check6;
    QCheckBox *check7;
    QCheckBox *check8;
    QCheckBox *check9;
    QCheckBox *check10;
    QCheckBox *check11;
    QCheckBox *check12;
    QCheckBox *check13;
    QCheckBox *check14;
    QCheckBox *check15;
    QCheckBox *check16;
    QCheckBox *check17;
    QCheckBox *check18;
    QCheckBox *check19;
    QCheckBox *check20;

    qint64 max2;
    double aActuel;
    QString temps;
    QTimer *timer;
    QStringList moyenne;
};

#endif // PRINCIPAL_H
