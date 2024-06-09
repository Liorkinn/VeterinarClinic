#include "checkdyagnosispanel.h"
#include "ui_checkdyagnosispanel.h"

checkDyagnosisPanel::checkDyagnosisPanel(QVariantList p_listDyagnosis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkDyagnosisPanel)
{
    ui->setupUi(this);

    listDyagnosis = p_listDyagnosis;

    this->createUI(QStringList()  << ( "Тип животного" )
                                  << ( "Имя животного" )
                                  << ( "ФИО владельца" )
                                  << ( "Телефон" )
                                  << ( "Диагноз" ));

    addDyagnosisItems();
}

void checkDyagnosisPanel::createUI(const QStringList &headers)
{
    ui->table_dyagnosis->setColumnCount(5);
    ui->table_dyagnosis->setShowGrid(true);
    ui->table_dyagnosis->setHorizontalHeaderLabels(headers);
    ui->table_dyagnosis->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_dyagnosis->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_dyagnosis->setSelectionMode(QAbstractItemView::NoSelection);
    ui->table_dyagnosis->verticalHeader()->setVisible(false);
    ui->table_dyagnosis->setRowCount(1);
    ui->table_dyagnosis->horizontalHeader()->resizeSection(1, 120);
    ui->table_dyagnosis->horizontalHeader()->resizeSection(2, 120);
    ui->table_dyagnosis->horizontalHeader()->resizeSection(3, 140);
    ui->table_dyagnosis->horizontalHeader()->setStretchLastSection(true);
   // ui->table_dyagnosis->setColumnHidden(0, true);
    ui->table_dyagnosis->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_dyagnosis->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_dyagnosis->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void checkDyagnosisPanel::addDyagnosisItems()
{
    ui->table_dyagnosis->setRowCount(0);

    for (const QVariant& dyagnosisVariant : listDyagnosis) {
        QVariantMap dyagnosMap = dyagnosisVariant.toMap();
        int row = ui->table_dyagnosis->rowCount();
        ui->table_dyagnosis->insertRow(row);


        ui->table_dyagnosis->setItem(row, 0, new QTableWidgetItem(dyagnosMap["animalType"].toString()));
        ui->table_dyagnosis->setItem(row, 1, new QTableWidgetItem(dyagnosMap["animalName"].toString()));
        ui->table_dyagnosis->setItem(row, 2, new QTableWidgetItem(dyagnosMap["ownerInfo"].toString()));
        ui->table_dyagnosis->setItem(row, 3, new QTableWidgetItem(dyagnosMap["ownerPhone"].toString()));
        ui->table_dyagnosis->setItem(row, 4, new QTableWidgetItem(dyagnosMap["diagnosis"].toString()));
    }
}

checkDyagnosisPanel::~checkDyagnosisPanel()
{
    delete ui;
}
