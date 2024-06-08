#ifndef DBWORKER_H
#define DBWORKER_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

class MainWindow; //***
class PatientPanel;
class DoctorPanel;
class registraturePanel;

typedef enum {
    PATIENT = 1,
    DOCTOR = 2,
    REGISTRATURE = 3
} roleStatus;


class Dbworker
{
public:
    Dbworker();

public:
    bool databaseConnection(const QString &hostname, const int &port, const QString &database, const QString &password = "null");
    bool authenticateUser(const QString &login, const QString &password);
    void loadUserInfo(int userId, int accessLevelId);
    QVariantList loadPatientAnimals(int userId);
    bool changeUserPassword(int userId, const QString &oldPassword, const QString &newPassword);
    bool checkUserPassword(int userId, const QString &oldPassword);
    bool registerPatient(const QString &name, const QString &surname, const QString &patronymic, int age, const QString &telephone, const QString &login, const QString &password);
    bool registerAnimal(int userId, int animalTypeId, const QString &name, const QString &symptom);
    QVariantList getPatientData();
    QMap<int, QString> getAnimalTypes();
    bool bookAppointment(int animalId, int doctorId, const QDateTime &date);
    QVariantList getAllAnimalsWithOwners();
    QVariantList getAllDoctors();
    bool isDoctorBusy(int doctorId, const QDateTime &date);
    QDateTime getLastDoctorVisitDate(int doctorId);
    bool isDoctorAvailable(int doctorId, const QDateTime &selectedDateTime);
    QVariantList getDoctorAppointments(int doctorId);
    bool addVisitWithDiagnosis(int appointmentId, const QString &diagnosis);
    bool deleteAppointment(int appointmentId);
private:
    QSqlDatabase m_db;
    PatientPanel *patientPanel;
    DoctorPanel *doctorPanel;
    registraturePanel *regPanel;
};

#endif // DBWORKER_H
