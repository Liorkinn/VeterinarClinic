#ifndef DBWORKER_H
#define DBWORKER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class PatientPanel;
class DoctorPanel;

typedef enum {
    PATIENT = 1,
    DOCTOR = 2
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

private:
    QSqlDatabase m_db;
    PatientPanel *patientPanel;
    DoctorPanel *doctorPanel;
};

#endif // DBWORKER_H
