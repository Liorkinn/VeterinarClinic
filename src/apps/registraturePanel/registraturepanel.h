#ifndef REGISTRATUREPANEL_H
#define REGISTRATUREPANEL_H

#include <QDialog>

#include "changepassword.h"
#include "registerpatient.h"
#include "registeranimal.h"
#include "registervisit.h"

class Dbworker;

namespace Ui {
class registraturePanel;
}

class registraturePanel : public QDialog
{
    Q_OBJECT


    struct RegistratureData {
        int userID;
        QString name;
        QString surname;
        QString patronymic;
        QString age;
        QString telephone;
    };

public:
    explicit registraturePanel(Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~registraturePanel();

/*  Функции сеттеры
 * - setUserData - устанавливает данные о докторе (ФИО, должность и т.д.).
 * - setUserID - устанавливает текущий ид прользователя.
 * - setName - устанавливает имя пользователя.
 * - setSurname - устанавливает фамилию пользователя.
 * - setPatronymic - устанавливает отчество пользователя.
 * - setAge - устанавливает возраст пользователя.
 * - setTelephone - устанавливает телефон пользователя.
*/
public:
    void setUserID          (int p_userID)              { registratureData.userID = p_userID; }
    void setName            (QString p_name)            { registratureData.name = p_name; }
    void setSurname         (QString p_surname)         { registratureData.surname = p_surname; }
    void setPatronymic      (QString p_patronymic)      { registratureData.patronymic = p_patronymic; }
    void setAge             (QString p_age)             { registratureData.age = p_age; }
    void setTelephone       (QString p_telephone)       { registratureData.telephone = p_telephone; }

/*  Функции геттеры
 * - getUserData - получение данных о докторе (ФИО, должность и т.д.).
 * - getUserID - получение текущего ид прользователя.
 * - getName - получение имя пользователя.
 * - getSurname - получение фамилии пользователя.
 * - getPatronymic - получение отчества пользователя.
 * - getAge - получение возраста пользователя.
 * - getTelephone - получение телефона пользователя.
*/
public:
    int getUserID           ()                          { return registratureData.userID; }
    QString getName         ()                          { return registratureData.name; }
    QString getSurname      ()                          { return registratureData.surname; }
    QString getPatronymic   ()                          { return registratureData.patronymic; }
    QString getAge          ()                          { return registratureData.age; }
    QString getTelephone    ()                          { return registratureData.telephone; }

    void setUserData(const int &p_userID, const QString &p_name, const QString &p_surname, const QString &p_patronymic, const QString &p_age, const QString &p_telephone);

private slots:
    void on_button_registerPatient_clicked();
    void on_button_registerAnimal_clicked();
    void on_button_registerVisit_clicked();
    void on_button_changePassword_clicked();

/*  Переменные
 * - dbworker - объект для работы с БД.
 * - registerPatient - объект панели регистрации пациента.
 * - regAnimal - объект панели регистрации животного.
 * - registerVisit - объект панели регистрации на приём.
 * - registratureData - объект структкры данные регистратуры.
 * - changePwd - объект панели смены пароля.
*/
private:
    Ui::registraturePanel *ui;
    Dbworker* dbworker;
    RegisterPatient *registerPatient;
    registerAnimal *regAnimal;
    RegisterVisit *registerVisit;
    RegistratureData registratureData;
    changePassword *changePwd;
};

#endif // REGISTRATUREPANEL_H
