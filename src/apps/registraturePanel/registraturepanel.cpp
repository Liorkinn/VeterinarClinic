#include "registraturepanel.h"
#include "ui_registraturepanel.h"

#include "dbworker.h"

registraturePanel::registraturePanel(Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registraturePanel),
    dbworker(p_dbworker)
{
    ui->setupUi(this);
    this->setFixedSize(404, 283);
}

registraturePanel::~registraturePanel()
{
    delete ui;
}

void registraturePanel::setUserData(const int& p_userID, const QString &p_name, const QString &p_surname, const QString &p_patronymic, const QString &p_age, const QString &p_telephone)
{
    QString name = p_name;
    QString surname = p_surname;
    QString patronymic = p_patronymic;
    QString age = p_age;
    QString telephone = p_telephone;

    QString textInitialUser = QString("%1 %2 %3").arg(name).arg(surname).arg(patronymic);
    QString textAge = QString("%1 %2").arg("Возраст: ").arg(age);
    QString textTelephone = QString("%1 %2").arg("Телефон:").arg(telephone);

    if (textInitialUser.isEmpty() || textAge.isEmpty() || textTelephone.isEmpty()) {
        return;
    }

    setUserID(p_userID);
    setName(p_name);
    setSurname(p_surname);
    setPatronymic(p_patronymic);
    setAge(p_age);
    setTelephone(p_telephone);

    ui->label_FIO->setText(textInitialUser);
    ui->label_age->setText(textAge);
    ui->label_telephone->setText(textTelephone);
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

void registraturePanel::on_button_changePassword_clicked()
{
    changePwd = new changePassword(getUserID(), dbworker);
    changePwd->setWindowTitle("Изменение пароля");
    changePwd->show();
}
