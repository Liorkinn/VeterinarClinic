#include "registeranimal.h"
#include "ui_registeranimal.h"

registerAnimal::registerAnimal(QVariantList p_listUsers, Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerAnimal)
{
    ui->setupUi(this);
    listUsers = p_listUsers;
    dbworker = p_dbworker;

    this->createUI(QStringList()  << ( "ID" )
                                  << ( "Имя" )
                                  << ( "Фамилия" )
                                  << ( "Отчество" )
                                  << ( "Возраст" )
                                  << ( "Телефон" ));
    setItemTableUsers();
    setItemComboBoxAnimals();
    ui->lineEdit_searchTelephone->setPlaceholderText("Введите номер телефона");

    QObject::connect(ui->lineEdit_searchTelephone, &QLineEdit::textChanged, [&](const QString &text) {
            QList<QTableWidgetItem*> items = ui->tableWidget_users->findItems(text, Qt::MatchExactly);
            if (!items.isEmpty()) {
                ui->tableWidget_users->selectRow(items.first()->row());
            } else {
                // Совпадений нет, снимаем выделение
                ui->tableWidget_users->clearSelection();
            }
        });
}

registerAnimal::~registerAnimal()
{
    delete ui;
}

void registerAnimal::createUI(const QStringList &headers)
{
    ui->tableWidget_users->setColumnCount(6);
    ui->tableWidget_users->setShowGrid(true);
    ui->tableWidget_users->setHorizontalHeaderLabels(headers);
    ui->tableWidget_users->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_users->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_users->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_users->verticalHeader()->setVisible(false);
    ui->tableWidget_users->setRowCount(1);
    ui->tableWidget_users->horizontalHeader()->resizeSection(1, 120);
    ui->tableWidget_users->horizontalHeader()->resizeSection(2, 120);
    ui->tableWidget_users->horizontalHeader()->resizeSection(3, 140);
    ui->tableWidget_users->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_users->setColumnHidden(0, true);
    ui->tableWidget_users->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_users->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_users->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void registerAnimal::setItemTableUsers()
{
    ui->tableWidget_users->setRowCount(0);
    for (const QVariant& usersVariant : listUsers) {
        QVariantMap usersMap = usersVariant.toMap();
        int row = ui->tableWidget_users->rowCount();
        ui->tableWidget_users->insertRow(row);
        ui->tableWidget_users->setItem(row, 0, new QTableWidgetItem(QString::number(usersMap["id"].toInt())));
        ui->tableWidget_users->setItem(row, 1, new QTableWidgetItem(usersMap["name"].toString()));
        ui->tableWidget_users->setItem(row, 2, new QTableWidgetItem(usersMap["surname"].toString()));
        ui->tableWidget_users->setItem(row, 3, new QTableWidgetItem(usersMap["patronymic"].toString()));
        ui->tableWidget_users->setItem(row, 4, new QTableWidgetItem(QString::number(usersMap["age"].toInt())));
        ui->tableWidget_users->setItem(row, 5, new QTableWidgetItem(usersMap["telephone"].toString()));
    }
}

void registerAnimal::setItemComboBoxAnimals()
{
    animalTypes = dbworker->getAnimalTypes();

    for (auto it = animalTypes.begin(); it != animalTypes.end(); ++it) {
            ui->comboBox_animals->addItem(it.value(), it.key());
        }
}

void registerAnimal::on_button_registrationAnimal_clicked()
{
    int userId = ui->tableWidget_users->selectionModel()->currentIndex().siblingAtColumn(0).data().toInt();
    QString currentAnimal = ui->comboBox_animals->currentText();

    int animalTypeId = -1;

    for (auto it = animalTypes.begin(); it != animalTypes.end(); ++it) {
        if (it.value() == currentAnimal) {
            animalTypeId = it.key(); // Нашли соответствие, сохраняем ключ
            break;
        }
    }
    QString animalName = ui->lineEdit_name->text();
    QString animalSympthom = ui->lineEdit_sympthom->text();

    if (userId == 0 || animalName.isEmpty() || animalSympthom.isEmpty()) {
        QMessageBox::information(0, "Регистрация животного", "Пожалуйста, заполните все поля");
        return;
    }

    bool success = dbworker->registerAnimal(userId, animalTypeId, animalName, animalSympthom);

    if (success) {
        QMessageBox::information(0, "Регистрация животного", "Регистрация прошла успешно");
    } else {
        QMessageBox::critical(0, "Регистрация животного", "Животное не зарегистрировано");
    }

}
