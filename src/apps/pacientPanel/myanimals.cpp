#include "myanimals.h"
#include "ui_myanimals.h"

MyAnimals::MyAnimals(QVariantList p_listAnimals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyAnimals)
{
    ui->setupUi(this);
    listAnimals = p_listAnimals;

    this->createUI(QStringList()  << ( "ID" )
                                  << ( "Кличка" )
                                  << ( "ID животного" )
                                  << ( "Тип животного" )
                                  << ( "Жалоба" ));
    setAnimalsItem();
}

void MyAnimals::createUI(const QStringList &headers)
{
    ui->table_Animals->setColumnCount(5);
    ui->table_Animals->setShowGrid(true);
    ui->table_Animals->setHorizontalHeaderLabels(headers);

    ui->table_Animals->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_Animals->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_Animals->setSelectionMode(QAbstractItemView::NoSelection);
    ui->table_Animals->verticalHeader()->setVisible(false);
    ui->table_Animals->setRowCount(1);
    ui->table_Animals->horizontalHeader()->resizeSection(1, 120);
    ui->table_Animals->horizontalHeader()->resizeSection(2, 120);
    ui->table_Animals->horizontalHeader()->resizeSection(3, 140);
    ui->table_Animals->horizontalHeader()->setStretchLastSection(true);
    ui->table_Animals->setColumnHidden(0, true);
    ui->table_Animals->setColumnHidden(2, true);
}

void MyAnimals::setAnimalsItem()
{
    ui->table_Animals->setRowCount(0);
    for (const QVariant& animalVariant : listAnimals) {
        QVariantMap animalMap = animalVariant.toMap();
        int row = ui->table_Animals->rowCount();
        ui->table_Animals->insertRow(row);
        ui->table_Animals->setItem(row, 0, new QTableWidgetItem(QString::number(animalMap["id"].toInt())));
        ui->table_Animals->setItem(row, 1, new QTableWidgetItem(animalMap["name"].toString()));
        ui->table_Animals->setItem(row, 2, new QTableWidgetItem(QString::number(animalMap["animal_type_id"].toInt())));
        ui->table_Animals->setItem(row, 3, new QTableWidgetItem(animalMap["animal_type"].toString()));
        ui->table_Animals->setItem(row, 4, new QTableWidgetItem(animalMap["sympthom"].toString()));
   }
}

MyAnimals::~MyAnimals()
{
    delete ui;
}
