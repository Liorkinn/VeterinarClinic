#ifndef PATIENTPANEL_H
#define PATIENTPANEL_H

#include <QDialog>
#include <QDebug>
#include "myanimals.h"
#include "changepassword.h"

class Dbworker;

namespace Ui {
class PatientPanel;
}

struct UserData {
    int userID;
    QString name;
    QString surname;
    QString patronymic;
    QString age;
    QString telephone;
};

class PatientPanel : public QDialog
{
    Q_OBJECT

public:
    explicit PatientPanel(Dbworker *dbworker, QWidget *parent = nullptr);
    ~PatientPanel();

public:
    void setUserData        (const int& p_userID, const QString &p_name, const QString &p_surname, const QString &p_patronymic, const QString &p_age, const QString &p_telephone);

    void setUserID          (int p_userID)              { userdata.userID = p_userID; }
    void setName            (QString p_name)            { userdata.name = p_name; }
    void setSurname         (QString p_surname)         { userdata.surname = p_surname; }
    void setPatronymic      (QString p_patronymic)      { userdata.patronymic = p_patronymic; }
    void setAge             (QString p_age)             { userdata.age = p_age; }
    void setTelephone       (QString p_telephone)       { userdata.telephone = p_telephone; }

    int getUserID           ()                          { return userdata.userID; }
    QString getName         ()                          { return userdata.name; }
    QString getSurname      ()                          { return userdata.surname; }
    QString getPatronymic   ()                          { return userdata.patronymic; }
    QString getAge          ()                          { return userdata.age; }
    QString getTelephone    ()                          { return userdata.telephone; }

    void addAnimalsItem     ();

private slots:
    void on_button_myAnimals_clicked();

    void on_button_changePassword_clicked();

private:
    Ui::PatientPanel *ui;
    UserData userdata;
    MyAnimals *animals;
    changePassword *changePwd;
    Dbworker* dbworker;
};

#endif // PATIENTPANEL_H
