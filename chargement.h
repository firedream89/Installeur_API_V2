#ifndef CHARGEMENT_H
#define CHARGEMENT_H

#include <QDialog>
#include <QDebug>
#include <math.h>

namespace Ui {
class Chargement;
}

class Chargement : public QDialog
{
    Q_OBJECT

public:
    explicit Chargement(QWidget *parent = 0);
    ~Chargement();
    void init(int nbDown);

public slots:
    void UpdateDown(qint64 actuel, qint64 max, QString nom = 0);
    void UpdateInstall(QString nom);

private:
    Ui::Chargement *ui;
    QString nomDown;
};

#endif // CHARGEMENT_H
