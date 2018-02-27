#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT
    
public:
    explicit Options(QWidget *parent = 0);
    ~Options();

private slots:
    void Liste(QString nom);
    void Preparation();
    void Ajout();
    void Enregistrer();
    bool Controle();
    
private:
    Ui::Options *ui;
};

#endif // OPTIONS_H
