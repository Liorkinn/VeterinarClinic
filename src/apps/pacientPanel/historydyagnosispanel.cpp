#include "historydyagnosispanel.h"
#include "ui_historydyagnosispanel.h"

HistoryDyagnosisPanel::HistoryDyagnosisPanel(QVariantList p_listHistoryDyagnosis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDyagnosisPanel)
{

    ui->setupUi(this);
    this->setWindowTitle("История диагнозов");
    this->setFixedSize(830, 369);

    listHistoryDyagnosis = p_listHistoryDyagnosis;

    this->createUI(QStringList()  << ( "ID" )
                                  << ( "Дата" )
                                  << ( "Диагноз" )
                                  << ( "Тип животного" )
                                  << ( "Кличка" ));

    addHistoryItems();
}

void HistoryDyagnosisPanel::createUI(const QStringList &headers)
{
    ui->table_historyDyagnosis->setColumnCount(5);
    ui->table_historyDyagnosis->setShowGrid(true);
    ui->table_historyDyagnosis->setHorizontalHeaderLabels(headers);
    ui->table_historyDyagnosis->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_historyDyagnosis->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_historyDyagnosis->setSelectionMode(QAbstractItemView::NoSelection);
    ui->table_historyDyagnosis->verticalHeader()->setVisible(false);
    ui->table_historyDyagnosis->setRowCount(1);
    ui->table_historyDyagnosis->horizontalHeader()->resizeSection(1, 120);
    ui->table_historyDyagnosis->horizontalHeader()->resizeSection(2, 120);
    ui->table_historyDyagnosis->horizontalHeader()->resizeSection(3, 140);
    ui->table_historyDyagnosis->horizontalHeader()->setStretchLastSection(true);
    ui->table_historyDyagnosis->setColumnHidden(0, true);
    ui->table_historyDyagnosis->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_historyDyagnosis->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_historyDyagnosis->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void HistoryDyagnosisPanel::addHistoryItems()
{
    ui->table_historyDyagnosis->setRowCount(0);

    for (const QVariant& dyagnosisVariant : listHistoryDyagnosis) {
        QVariantMap dyagnosMap = dyagnosisVariant.toMap();
        int row = ui->table_historyDyagnosis->rowCount();
        ui->table_historyDyagnosis->insertRow(row);


        ui->table_historyDyagnosis->setItem(row, 0, new QTableWidgetItem(dyagnosMap["visit_id"].toString()));
        ui->table_historyDyagnosis->setItem(row, 1, new QTableWidgetItem(dyagnosMap["visit_date"].toString()));
        ui->table_historyDyagnosis->setItem(row, 2, new QTableWidgetItem(dyagnosMap["diagnosis"].toString()));
        ui->table_historyDyagnosis->setItem(row, 3, new QTableWidgetItem(dyagnosMap["animal_type"].toString()));
        ui->table_historyDyagnosis->setItem(row, 4, new QTableWidgetItem(dyagnosMap["animal_name"].toString()));
    }
}

HistoryDyagnosisPanel::~HistoryDyagnosisPanel()
{
    delete ui;
}
