#include "dbworker.h"
#include "patientpanel.h"
#include "doctorpanel.h"
#include "registraturepanel.h"

Dbworker::Dbworker()
{

}

bool Dbworker::databaseConnection(const QString &hostname, const int &port, const QString &database, const QString &password)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(hostname);
    m_db.setPort(port);
    m_db.setDatabaseName(database);
    m_db.setUserName("postgres");
    m_db.setPassword(password);
    m_db.setConnectOptions("connect_timeout=1");

    if (!m_db.open()) {
        qDebug() << QString("Ошибка подключения к БД: %1").arg(database);
        return false;
    }
    return true;
}

bool Dbworker::authenticateUser(const QString& login, const QString& password) {
    QSqlQuery query(m_db);
    QString command = "SELECT id, access_level_id FROM users WHERE login = :login AND password = :password";

    if (!query.prepare(command)) {
        qDebug() << "Failed to prepare query:" << query.lastError();
        return false;
    }

    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError();
        return false;
    }

    int userId = int();
    int accessLevelId = int();

    if (query.next()) {
        userId = query.value(0).toInt();
        accessLevelId = query.value(1).toInt();
        qDebug() << "User authenticated. User ID:" << userId << "Access Level ID:" << accessLevelId;


        if (accessLevelId == PATIENT) {
            patientPanel = new PatientPanel(this);
            patientPanel->setWindowTitle("Личный кабинет владельца животных");
            patientPanel->show();
            loadUserInfo(userId, accessLevelId);
        }

        if (accessLevelId == DOCTOR) {
            doctorPanel = new DoctorPanel(this);
            doctorPanel->show();
            doctorPanel->setWindowTitle("Личный кабинет доктора");
            loadUserInfo(userId, accessLevelId);
        }

        if (accessLevelId == REGISTRATURE) {
            regPanel = new registraturePanel(this);
            regPanel->show();
            regPanel->setWindowTitle("Личный кабинет регистратуры");
          //  loadUserInfo(userId, accessLevelId);
        }
        return true;
    } else {
        qDebug() << "Authentication failed. Invalid login or password.";
        return false;
    }
}

void Dbworker::loadUserInfo(int userId, int accessLevelId)
{
    QSqlQuery query(m_db);
    QString command;
    qDebug() << "ACCESS:" << accessLevelId;
    if (accessLevelId == PATIENT) {
        command = "SELECT name, surname, patronymic, age, telephone FROM users WHERE id = :userId";
    } else if (accessLevelId == DOCTOR) {
        command = QString("SELECT "
                          "u.name, "
                          "u.surname, "
                          "u.patronymic, "
                          "u.age, "
                          "u.telephone, "
                          "c.cabinet_number, "
                          "c.cabinet_name, "
                          "pt.post_type "
                          "FROM "
                          "users u "
                          "JOIN doctors d ON u.id = d.user_id "
                          "JOIN cabinets c ON d.cabinet_id = c.id "
                          "JOIN post_type pt ON d.post_id = pt.id "
                          "WHERE u.id = :userId");
    }

    if (!query.prepare(command)) {
        qDebug() << "Failed to prepare query:" << query.lastError();
        return;
    }

    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError();
        return;
    }

    if (query.next()) {
        QString name = query.value(0).toString();
        QString surname = query.value(1).toString();
        QString patronymic = query.value(2).toString();
        QString age = query.value(3).toString();
        QString telephone = query.value(4).toString();

        if (accessLevelId == PATIENT) {
            patientPanel->setUserData(userId, name, surname, patronymic, age, telephone);
        } else if (accessLevelId == DOCTOR) {
            QString cabinetNumber = query.value(5).toString();
            QString cabinetName = query.value(6).toString();
            QString postType = query.value(7).toString();
            doctorPanel->setUserData(userId, name, surname, patronymic, age, telephone, cabinetNumber, cabinetName, postType);
        }
    }
}

QVariantList Dbworker::loadPatientAnimals(int userId) {
    QSqlQuery query(m_db);
    QString command = "SELECT a.id, a.name, a.animal_type_id, k.animal_type, a.sympthom FROM animals_patients a "
                      "JOIN kind_animals k ON a.animal_type_id = k.id "
                      "WHERE a.user_id = :userId";

    if (!query.prepare(command)) {
        qDebug() << "Failed to prepare query:" << query.lastError();
        return QVariantList();
    }

    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError();
        return QVariantList();
    }

    QVariantList animalsList;

    while (query.next()) {
        QVariantMap animalInfo;
        animalInfo["id"] = query.value(0).toInt();
        animalInfo["name"] = query.value(1).toString();
        animalInfo["animal_type_id"] = query.value(2).toInt();
        animalInfo["animal_type"] = query.value(3).toString();
        animalInfo["sympthom"] = query.value(4).toString();

        animalsList.append(animalInfo);
    }

    return animalsList;
}

bool Dbworker::changeUserPassword(int userId, const QString& oldPassword, const QString& newPassword) {

    if (!checkUserPassword(userId, oldPassword)) {
        qDebug() << "Incorrect old password.";
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("UPDATE public.users SET password = :newPassword WHERE id = :userId");
    query.bindValue(":newPassword", newPassword);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to update password:" << query.lastError();
        return false;
    }
    return true;
}

bool Dbworker::checkUserPassword(int userId, const QString& oldPassword) {

    QSqlQuery query(m_db);
    query.prepare("SELECT password FROM public.users WHERE id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to fetch user password:" << query.lastError();
        return false;
    }

    QString storedPassword = query.value(0).toString();

    return bool (storedPassword == oldPassword);
}

bool Dbworker::registerPatient(const QString& name, const QString& surname, const QString& patronymic, int age, const QString& telephone, const QString& login, const QString& password) {

    QSqlQuery query(m_db);

    query.prepare("INSERT INTO public.users (name, surname, patronymic, age, telephone, login, password, access_level_id) "
                  "VALUES (:name, :surname, :patronymic, :age, :telephone, :login, :password, 1)");

    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":patronymic", patronymic);
    query.bindValue(":age", age);
    query.bindValue(":telephone", telephone);
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed to register patient:" << query.lastError();
        return false;
    }
    return true;
}

bool Dbworker::registerAnimal(int userId, int animalTypeId, const QString& name, const QString& symptom) {

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO public.animals_patients (user_id, animal_type_id, name, sympthom) "
                  "VALUES (:userId, :animalTypeId, :name, :symptom)");
    query.bindValue(":userId", userId);
    query.bindValue(":animalTypeId", animalTypeId);
    query.bindValue(":name", name);
    query.bindValue(":symptom", symptom);

    if (!query.exec()) {
        qDebug() << "Failed to register animal:" << query.lastError();
        return false;
    }
    return true;
}

QVariantList Dbworker::getPatientData() {

    QVariantList patientList;
    QSqlQuery query(m_db);

    query.prepare("SELECT id, name, surname, patronymic, age, telephone FROM public.users WHERE access_level_id = 1"); // Предполагаем, что access_level_id = 1 для пациентов

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError();
        return patientList;
    }

    while (query.next()) {
        QVariantMap patientData;
        patientData["id"] = QString::number(query.value(0).toInt());
        patientData["name"] = query.value(1).toString();
        patientData["surname"] = query.value(2).toString();
        patientData["patronymic"] = query.value(3).toString();
        patientData["age"] = QString::number(query.value(4).toInt());
        patientData["telephone"] = query.value(5).toString();
        patientList.append(patientData);
    }
    return patientList;
}

QMap<int, QString> Dbworker::getAnimalTypes() {

    QMap<int, QString> animalTypes;

    QSqlQuery query(m_db);
    query.prepare("SELECT id, animal_type FROM kind_animals");

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError();
        return animalTypes;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString typeName = query.value(1).toString();
        animalTypes[id] = typeName;
    }
    return animalTypes;
}
