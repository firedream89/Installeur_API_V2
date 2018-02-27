#ifndef INSTALLATION_H
#define INSTALLATION_H
#include <QThread>
#include <QDebug>
#include <QProcess>
#include <QDir>

class Installation : public QThread
{
    Q_OBJECT
public:
    void run();
    void installation();

public slots:
    bool debut(QString nom2);

private slots:
    void Erreur(int retCode);
    void Fin(QString nom,bool fin);

signals:
    void finInst(QString nom, bool fin);
    void debutInstall(QString nom);
    void finInstall(QString nom);
    void erreur(int retCode = 0,QString nom = 0);

private:
    QStringList nom;
};

#endif // INSTALLATION_H
