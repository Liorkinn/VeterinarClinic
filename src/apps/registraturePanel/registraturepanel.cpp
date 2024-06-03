#include "registraturepanel.h"
#include "ui_registraturepanel.h"

#include "dbworker.h"

registraturePanel::registraturePanel(Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registraturePanel),
    dbworker(p_dbworker)
{
    ui->setupUi(this);

}

registraturePanel::~registraturePanel()
{
    delete ui;
}

void registraturePanel::on_button_registerPatient_clicked()
{
    registerPatient = new RegisterPatient(dbworker);
    registerPatient->setWindowTitle("Регистрация");
    registerPatient->show();
}

void registraturePanel::on_button_registerAnimal_clicked()
{
    QVariantList patients = dbworker->getPatientData();
    regAnimal = new registerAnimal(patients, dbworker);
    regAnimal->setWindowTitle("Регистрация животного");
    regAnimal->show();
}

void registraturePanel::on_button_registerVisit_clicked()
{
    QVariantList listDoctors = dbworker->getAllDoctors();
    QVariantList listAnimals = dbworker->getAllAnimalsWithOwners();
    registerVisit = new RegisterVisit(dbworker, listDoctors, listAnimals);
    registerVisit->show();
}
