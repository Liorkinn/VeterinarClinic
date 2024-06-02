#ifndef DOCTORPANEL_H
#define DOCTORPANEL_H

#include <QDialog>

class Dbworker;

namespace Ui {
class DoctorPanel;
}

struct DoctorData {
    int userID;
    QString name;
    QString surname;
    QString patronymic;
    QString age;
    QString telephone;
    QString cabinetNumber;
    QString cabinetName;
    QString postType;
};

class DoctorPanel : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorPanel(Dbworker *dbworker, QWidget *parent = nullptr);
    ~DoctorPanel();

    void setUserData(const int &p_userID, const QString &p_name, const QString &p_surname,
                     const QString &p_patronymic, const QString &p_age, const QString &p_telephone,
                     const QString &p_cabinetNumber, const QString &p_cabinetName, const QString &p_postType);

public:
    void setUserData        (const int& p_userID, const QString &p_name, const QString &p_surname, const QString &p_patronymic, const QString &p_age, const QString &p_telephone);

    void setUserID          (int p_userID)              { doctorData.userID = p_userID; }
    void setName            (QString p_name)            { doctorData.name = p_name; }
    void setSurname         (QString p_surname)         { doctorData.surname = p_surname; }
    void setPatronymic      (QString p_patronymic)      { doctorData.patronymic = p_patronymic; }
    void setAge             (QString p_age)             { doctorData.age = p_age; }
    void setTelephone       (QString p_telephone)       { doctorData.telephone = p_telephone; }
    void setCabinetNumber   (QString p_cabinetNum)      { doctorData.telephone = p_cabinetNum; }
    void setCabinetName     (QString p_cabinetName)     { doctorData.telephone = p_cabinetName; }
    void setPostType        (QString p_cabinetType)     { doctorData.telephone = p_cabinetType; }

    int getUserID           ()                          { return doctorData.userID; }
    QString getName         ()                          { return doctorData.name; }
    QString getSurname      ()                          { return doctorData.surname; }
    QString getPatronymic   ()                          { return doctorData.patronymic; }
    QString getAge          ()                          { return doctorData.age; }
    QString getTelephone    ()                          { return doctorData.telephone; }
    QString getCabinetNumber   (QString p_cabinetNum)      { return doctorData.cabinetNumber; }
    QString getCabinetName     (QString p_cabinetName)     { return doctorData.cabinetName; }
    QString getPostType        (QString p_cabinetType)     { return doctorData.postType; }


private:
    Ui::DoctorPanel *ui;
    Dbworker* dbworker;
    DoctorData doctorData;
};

#endif // DOCTORPANEL_H
