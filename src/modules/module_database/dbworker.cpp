#include "dbworker.h"
#include "patientpanel.h"
#include "doctorpanel.h"

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
            patientPanel = new PatientPanel(this); //error allocation
            patientPanel->show();
            loadUserInfo(userId, accessLevelId);
        }

        if (accessLevelId == DOCTOR) {
           // doctorPanel = new DoctorPanel(this); //error allocation
           // doctorPanel->show();
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

    if (accessLevelId == PATIENT) {
        command = "SELECT name, surname, patronymic, age, telephone FROM users WHERE id = :userId";
    } else if (accessLevelId == DOCTOR) {
        command = "SELECT name, surname, patronymic, age, telephone, cabinet_id, post_id FROM users WHERE id = :userId";
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

        if (accessLevelId == DOCTOR) {
            int cabinetId = query.value(5).toInt();
            int postId = query.value(6).toInt();
            // Здесь можно загрузить дополнительную информацию о кабинете и должности, если это необходимо
        }

        // Передаем данные в форму
        // Например, если у вас есть функция setUserInfo в форме
        if (accessLevelId == PATIENT) {
            patientPanel->setUserData(userId, name, surname, patronymic, age, telephone);
        } else if (accessLevelId == DOCTOR) {
            //doctorPanel->setUserInfo(surname, name, patronymic, age, telephone);
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

//void Dbworker::loadPatientAnimals(int userId) {
//    QSqlQuery query(m_db);
//    QString command = "SELECT a.id, a.name, a.animal_type_id, k.animal_type, a.sympthom FROM animals_patients a "
//                      "JOIN kind_animals k ON a.animal_type_id = k.id "
//                      "WHERE a.user_id = :userId";

//    if (!query.prepare(command)) {
//        qDebug() << "Failed to prepare query:" << query.lastError();
//        return;
//    }

//    query.bindValue(":userId", userId);

//    if (!query.exec()) {
//        qDebug() << "Failed to execute query:" << query.lastError();
//        return;
//    }

//    // Очищаем предыдущий список животных, если он есть
//    // Например, если у вас есть функция clearAnimalList в форме
//    // patientPanel->clearAnimalList();

//    // Заполняем список животных
//    while (query.next()) {
//        int animalId = query.value(0).toInt();
//        QString animalName = query.value(1).toString();
//        int animalTypeId = query.value(2).toInt();
//        QString animalType = query.value(3).toString();
//        QString symptom = query.value(4).toString();

//        qDebug() << animalId;
//        qDebug() << animalName;
//        qDebug() << animalTypeId;
//        qDebug() << animalType;
//        qDebug() << symptom;
//        // Добавляем информацию о животном в форму
//        // Например, если у вас есть функция addAnimalToListView в форме
//        // patientPanel->addAnimalToListView(animalId, animalName, animalType, symptom);
//    }
//}
