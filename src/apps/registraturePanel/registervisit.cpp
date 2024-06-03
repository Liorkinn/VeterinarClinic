#include "registervisit.h"
#include "ui_registervisit.h"

RegisterVisit::RegisterVisit(Dbworker *p_dbworker, QVariantList p_listDoctors, QVariantList p_listAnimals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterVisit)
{
    ui->setupUi(this);

    dbworker = p_dbworker;
    listAnimals = p_listAnimals;
    listDoctors = p_listDoctors;

    this->createUIDoctors(QStringList()  << ( "ID" )
                                         << ( "Имя" )
                                         << ( "Фамилия" )
                                         << ( "Должность" )
                                         << ( "Кабинет" )
                                         << ( "Телефон" ));

    this->createUIAnimals(QStringList()  << ( "ID" )
                                         << ( "Кличка" )
                                         << ( "Тип животного" )
                                         << ( "Симптом" )
                                         << ( "Имя владельца" )
                                         << ( "Фамилия владельца" )
                                         << ( "Телефон" ));

    addItemDoctors();
    addItemAnimals();

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &RegisterVisit::checkEvenTime);
}

void RegisterVisit::createUIAnimals(const QStringList &headers)
{
    ui->tableWidget_animals->setColumnCount(6);
    ui->tableWidget_animals->setShowGrid(true);
    ui->tableWidget_animals->setHorizontalHeaderLabels(headers);
    ui->tableWidget_animals->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_animals->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_animals->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_animals->verticalHeader()->setVisible(false);
    ui->tableWidget_animals->setRowCount(1);
    ui->tableWidget_animals->horizontalHeader()->resizeSection(1, 120);
    ui->tableWidget_animals->horizontalHeader()->resizeSection(2, 120);
    ui->tableWidget_animals->horizontalHeader()->resizeSection(3, 140);
    ui->tableWidget_animals->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_animals->setColumnHidden(0, true);
    ui->tableWidget_animals->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_animals->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_animals->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void RegisterVisit::createUIDoctors(const QStringList &headers)
{
    ui->tableWidget_doctors->setColumnCount(6);
    ui->tableWidget_doctors->setShowGrid(true);
    ui->tableWidget_doctors->setHorizontalHeaderLabels(headers);
    ui->tableWidget_doctors->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_doctors->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_doctors->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_doctors->verticalHeader()->setVisible(false);
    ui->tableWidget_doctors->setRowCount(1);
    ui->tableWidget_doctors->horizontalHeader()->resizeSection(1, 120);
    ui->tableWidget_doctors->horizontalHeader()->resizeSection(2, 120);
    ui->tableWidget_doctors->horizontalHeader()->resizeSection(3, 140);
    ui->tableWidget_doctors->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_doctors->setColumnHidden(0, true);
    ui->tableWidget_doctors->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_doctors->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_doctors->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void RegisterVisit::addItemDoctors()
{
    ui->tableWidget_doctors->setRowCount(0);
    for (const QVariant& doctorVariant : listDoctors) {
        QVariantMap doctorsMap = doctorVariant.toMap();

        int row = ui->tableWidget_doctors->rowCount();
        ui->tableWidget_doctors->insertRow(row);
        ui->tableWidget_doctors->setItem(row, 0, new QTableWidgetItem(QString::number(doctorsMap["doctor_id"].toInt())));
        ui->tableWidget_doctors->setItem(row, 1, new QTableWidgetItem(doctorsMap["doctor_name"].toString()));
        ui->tableWidget_doctors->setItem(row, 2, new QTableWidgetItem(doctorsMap["doctor_surname"].toString()));
        ui->tableWidget_doctors->setItem(row, 3, new QTableWidgetItem(doctorsMap["doctor_post"].toString()));
        ui->tableWidget_doctors->setItem(row, 4, new QTableWidgetItem(QString::number(doctorsMap["cabinet_number"].toInt())));
        ui->tableWidget_doctors->setItem(row, 5, new QTableWidgetItem(doctorsMap["telephone"].toString()));
    }
}

void RegisterVisit::addItemAnimals()
{
    ui->tableWidget_animals->setRowCount(0);
    for (const QVariant& usersVariant : listAnimals) {
        QVariantMap usersMap = usersVariant.toMap();
        int row = ui->tableWidget_animals->rowCount();
        ui->tableWidget_animals->insertRow(row);
        ui->tableWidget_animals->setItem(row, 0, new QTableWidgetItem(QString::number(usersMap["animal_id"].toInt())));
        ui->tableWidget_animals->setItem(row, 1, new QTableWidgetItem(usersMap["animal_name"].toString()));
        ui->tableWidget_animals->setItem(row, 2, new QTableWidgetItem(usersMap["animal_type"].toString()));
        ui->tableWidget_animals->setItem(row, 3, new QTableWidgetItem(usersMap["sympthom"].toString()));
        ui->tableWidget_animals->setItem(row, 4, new QTableWidgetItem(usersMap["owner_name"].toString()));
        ui->tableWidget_animals->setItem(row, 5, new QTableWidgetItem(usersMap["owner_surname"].toString()));
        ui->tableWidget_animals->setItem(row, 6, new QTableWidgetItem(usersMap["owner_telephone"].toString()));
    }
}

RegisterVisit::~RegisterVisit()
{
    delete ui;
}

void RegisterVisit::checkEvenTime(const QDateTime &newDateTime)
{
    int hour = newDateTime.time().hour();
    if (hour % 2 != 0) {
        // Установите время на ближайшее четное
        QDateTime newDateTimeEven = newDateTime;
        newDateTimeEven.setTime(QTime(hour % 2 == 0 ? hour : hour + 1, 0));
        ui->dateTimeEdit->setDateTime(newDateTimeEven);
    }
}

void RegisterVisit::on_button_registerVisit_clicked()
{
    QDateTime selectedDateTime = ui->dateTimeEdit->dateTime();
    int animalId = ui->tableWidget_animals->selectionModel()->currentIndex().siblingAtColumn(0).data().toInt();
    int doctorId = ui->tableWidget_doctors->selectionModel()->currentIndex().siblingAtColumn(0).data().toInt();

    if (animalId == 0 || doctorId == 0) {
        QMessageBox::critical(0, "Запись на приём", "Пожалуйста, заполните все поля.");
        return;
    }

    bool isBusy = dbworker->isDoctorAvailable(doctorId, selectedDateTime);

    if (!isBusy) {
        QMessageBox::critical(0, "Запись на приём", "Доктор занят. Пожалуйста, выберите другого доктора или время.");
        return;
    }

    bool isRegistrated = dbworker->bookAppointment(animalId, doctorId, selectedDateTime);

    if (!isRegistrated) {
        QMessageBox::critical(0, "Запись на приём", "Доктор занят. Пожалуйста, выберите другого доктора или время.");
        return;
    } else {
        QMessageBox::information(0, "Запись на приём", "Пациент записан успешно.");
    }
}
