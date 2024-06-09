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
            loadUserInfo(userId, accessLevelId);
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
    if (accessLevelId == PATIENT || accessLevelId == REGISTRATURE) {
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
        } else if (accessLevelId == REGISTRATURE) {
            regPanel->setUserData(userId, name, surname, patronymic, age, telephone);
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

bool Dbworker::isDoctorBusy(int doctorId, const QDateTime& date) {
    QSqlQuery query(m_db);
    QString sql = "SELECT COUNT(*) FROM appointments WHERE doctor_id = :doctor_id AND date BETWEEN :start_time AND :end_time";
    query.prepare(sql);
    query.bindValue(":doctor_id", doctorId);
    query.bindValue(":start_time", date);
    query.bindValue(":end_time", date.addSecs(3600));

    if (!query.exec()) {
        qDebug() << "Error: check doctor busy failed";
        qDebug() << query.lastError().text();
        return true; // Возвращаем true, чтобы записать животного, если не удается проверить занятость
    }

    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}

bool Dbworker::bookAppointment(int animalId, int doctorId, const QDateTime& date) {

    if (isDoctorBusy(doctorId, date)) {
            return false;
        }

        QSqlQuery query(m_db);
        query.prepare("INSERT INTO appointments (animal_id, doctor_id, date) VALUES (:animal_id, :doctor_id, :date)");
        query.bindValue(":animal_id", animalId);
        query.bindValue(":doctor_id", doctorId);
        query.bindValue(":date", date);

        if (!query.exec()) {
            qDebug() << "Error: insert failed";
            qDebug() << query.lastError().text();
        } else {
            qDebug() << "Record added successfully!";
        }
    return true;
}

QVariantList Dbworker::getAllDoctors() {

    QSqlQuery query(m_db);
    QVariantList resultList;

    QString command = "SELECT d.id AS doctor_id, u.name AS doctor_name, u.surname AS doctor_surname, p.post_type AS doctor_post, c.cabinet_number AS cabinet_number, u.telephone AS telephone "
                  "FROM doctors d "
                  "JOIN users u ON d.user_id = u.id "
                  "JOIN post_type p ON d.post_id = p.id "
                  "JOIN cabinets c ON d.cabinet_id = c.id";

    if (!query.exec(command)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
    } else {
        while (query.next()) {
            QVariantMap result;
            result["doctor_id"] = query.value(0);
            result["doctor_name"] = query.value(1);
            result["doctor_surname"] = query.value(2);
            result["doctor_post"] = query.value(3);
            result["cabinet_number"] = query.value(4);
            result["telephone"] = query.value(5);
            resultList.append(result);
        }
    }
    return resultList;
}

QVariantList Dbworker::getAllAnimalsWithOwners() {
    QSqlQuery query(m_db);
    QVariantList resultList;

    QString sql = "SELECT a.id AS animal_id, a.name AS animal_name, a.sympthom, u.name AS owner_name, u.surname AS owner_surname, u.telephone AS telephone, k.animal_type AS animal_type "
                  "FROM animals_patients a "
                  "JOIN users u ON a.user_id = u.id "
                  "JOIN kind_animals k ON a.animal_type_id = k.id";

    if (!query.exec(sql)) {
        qDebug() << "Error: query failed";
        qDebug() << query.lastError().text();
    } else {
        while (query.next()) {
            QVariantMap result;
            result["animal_id"] = query.value(0);
            result["animal_name"] = query.value(1);
            result["sympthom"] = query.value(2);
            result["owner_name"] = query.value(3);
            result["owner_surname"] = query.value(4);
            result["owner_telephone"] = query.value(5);
            result["animal_type"] = query.value(6);
            resultList.append(result);
        }
    }

    return resultList;
}

bool Dbworker::isDoctorAvailable(int doctorId, const QDateTime& selectedDateTime) {

    QSqlQuery query(m_db);
    query.prepare("SELECT MAX(a.date) FROM appointments a "
                  "WHERE a.doctor_id = :doctorId");
    query.bindValue(":doctorId", doctorId);

    if (!query.exec()) {
        qDebug() << "Error: query execution failed";
        return false;
    }

    // Обработка результатов запроса
    if (query.next()) {
        QDateTime lastVisitDate = query.value(0).toDateTime();
        // Добавляем 1 час к последнему визиту
        QDateTime lastVisitPlusOneHour = lastVisitDate.addSecs(3600);

        // Сравниваем с выбранным временем
        if (lastVisitPlusOneHour < selectedDateTime) {
            return true; // Доктор доступен, так как последний визит + 1 час меньше выбранного времени
        } else {
            return false; // Доктор недоступен, так как последний визит + 1 час не меньше выбранного времени
        }
    } else {
        return true; // Если нет записей о визитах, то доктор доступен
    }
}

QVariantList Dbworker::getDoctorAppointments(int doctorId) {
    QVariantList appointmentsList;

    QSqlQuery query(m_db);

    query.prepare("SELECT a.id, a.date, ap.name AS animal_name, ka.animal_type AS animal_type, u.surname, u.name, u.patronymic, u.telephone, ap.sympthom "
                      "FROM appointments a "
                      "JOIN animals_patients ap ON a.animal_id = ap.id "
                      "JOIN kind_animals ka ON ap.animal_type_id = ka.id "
                      "JOIN users u ON ap.user_id = u.id "
                      "WHERE a.doctor_id = (SELECT id FROM doctors WHERE user_id = :doctorId) "
                      "AND a.id NOT IN (SELECT appointment_id FROM visits WHERE dyagnosis IS NOT NULL)");


    query.bindValue(":doctorId", doctorId);

    if (!query.exec()) {
        qDebug() << "Error: query execution failed";
        return appointmentsList;
    }

    // Заполнение списка данными из запроса
    while (query.next()) {
        qDebug() << "da";
        QVariantMap appointment;
        appointment["id"] = query.value(0).toInt();
        qDebug() << query.value(0).toInt();
        appointment["date"] = query.value(1).toString();
        appointment["animal_name"] = query.value(2).toString();
        appointment["animal_type"] = query.value(3).toString();
        appointment["surname"] = query.value(4).toString();
        appointment["name"] = query.value(5).toString();
        appointment["patronymic"] = query.value(6).toString();
        appointment["telephone"] = query.value(7).toString();
        appointment["sympthom"] = query.value(8).toString();
        appointmentsList.append(appointment);
    }
    return appointmentsList;
}


bool Dbworker::addVisitWithDiagnosis(int appointmentId, const QString& diagnosis) {
        QSqlQuery query(m_db);
        query.prepare("INSERT INTO visits (appointment_id, dyagnosis) VALUES (:appointmentId, :diagnosis)");
        query.bindValue(":appointmentId", appointmentId);
        query.bindValue(":diagnosis", diagnosis);

        if (!query.exec()) {
            qDebug() << "Error: query execution failed" << query.lastError();
            return false;
        }

        return true;
}

QVariantList Dbworker::getDoctorVisitDetails(int userId) {

    QSqlQuery query(m_db);

    query.prepare("SELECT ka.animal_type, ap.name, u.name || ' ' || u.surname || ' ' || u.patronymic AS owner_info, u.telephone, v.dyagnosis "
                  "FROM visits v "
                  "JOIN appointments a ON v.appointment_id = a.id "
                  "JOIN animals_patients ap ON a.animal_id = ap.id "
                  "JOIN users u ON ap.user_id = u.id "
                  "JOIN kind_animals ka ON ap.animal_type_id = ka.id "
                  "JOIN doctors d ON a.doctor_id = d.id "
                  "WHERE d.user_id = :userId");

    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Error: query execution failed";
        qDebug() << query.lastError().text();
        return QVariantList();
    }

    QVariantList resultList;
    while (query.next()) {
        QVariantMap resultMap;
        resultMap["animalType"] = query.value(0).toString();
        resultMap["animalName"] = query.value(1).toString();
        resultMap["ownerInfo"] = query.value(2).toString();
        resultMap["ownerPhone"] = query.value(3).toString();
        resultMap["diagnosis"] = query.value(4).toString();
        resultList.append(resultMap);
    }
    return resultList;
}

QVariantList Dbworker::getVisitHistoryForUser(int userId) {

    QSqlQuery query(m_db);

    query.prepare("SELECT v.id AS visit_id, a.date AS visit_date, v.dyagnosis AS diagnosis, ka.animal_type, ap.name AS animal_name "
                  "FROM visits v "
                  "JOIN appointments a ON v.appointment_id = a.id "
                  "JOIN animals_patients ap ON a.animal_id = ap.id "
                  "JOIN kind_animals ka ON ap.animal_type_id = ka.id "
                  "WHERE ap.user_id = :userId AND ap.user_id IN (SELECT id FROM users WHERE access_level_id = 1)");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Error: query execution failed";
        qDebug() << query.lastError().text();
        return QVariantList();
    }

    QVariantList resultList;
    while (query.next()) {
        QVariantMap resultMap;
        resultMap["visit_id"] = query.value(0).toInt();
        resultMap["visit_date"] = query.value(1).toDateTime();
        resultMap["diagnosis"] = query.value(2).toString();
        resultMap["animal_type"] = query.value(3).toString();
        resultMap["animal_name"] = query.value(4).toString();
        resultList.append(resultMap);
    }
    return resultList;
}


QVariantList Dbworker::getUserAppointments(int userId) {

    QSqlQuery query(m_db);
    query.prepare("SELECT a.id AS appointment_id, a.date AS appointment_date, ka.animal_type, ap.name AS animal_name, "
                  "u.name || ' ' || u.surname AS doctor_full_name, u.telephone AS doctor_phone, "
                  "pt.post_type, c.cabinet_name "
                  "FROM appointments a "
                  "JOIN animals_patients ap ON a.animal_id = ap.id "
                  "JOIN kind_animals ka ON ap.animal_type_id = ka.id "
                  "JOIN doctors d ON a.doctor_id = d.id "
                  "JOIN users u ON d.user_id = u.id "
                  "JOIN post_type pt ON d.post_id = pt.id "
                  "JOIN cabinets c ON d.cabinet_id = c.id "
                  "WHERE ap.user_id = :userId AND a.id NOT IN (SELECT appointment_id FROM visits)");

    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Error: query execution failed";
        qDebug() << query.lastError().text();
        return QVariantList();
    }

    QVariantList resultList;
    while (query.next()) {
        QVariantMap resultMap;
        resultMap["appointment_id"] = query.value(0).toInt();
        resultMap["appointment_date"] = query.value(1).toDateTime();
        resultMap["animal_type"] = query.value(2).toString();
        resultMap["animal_name"] = query.value(3).toString();
        resultMap["doctor_full_name"] = query.value(4).toString();
        resultMap["doctor_phone"] = query.value(5).toString();
        resultMap["post_type"] = query.value(6).toString();
        resultMap["cabinet_name"] = query.value(7).toString();
        resultList.append(resultMap);
    }
    return resultList;
}

bool Dbworker::deleteAppointment(int appointmentId) {

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM appointments WHERE id = :appointmentId");
    query.bindValue(":appointmentId", appointmentId);

    if (!query.exec()) {
        qDebug() << "Error: delete query execution failed";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

