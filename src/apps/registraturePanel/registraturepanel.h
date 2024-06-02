#ifndef REGISTRATUREPANEL_H
#define REGISTRATUREPANEL_H

#include <QDialog>
#include "registerpatient.h"
#include "registeranimal.h"

class Dbworker;

namespace Ui {
class registraturePanel;
}

class registraturePanel : public QDialog
{
    Q_OBJECT

public:
    explicit registraturePanel(Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~registraturePanel();

private slots:
    void on_button_registerPatient_clicked();

    void on_button_registerAnimal_clicked();

private:
    Ui::registraturePanel *ui;
    Dbworker* dbworker;
    RegisterPatient *registerPatient;
    registerAnimal *regAnimal;
};

#endif // REGISTRATUREPANEL_H
