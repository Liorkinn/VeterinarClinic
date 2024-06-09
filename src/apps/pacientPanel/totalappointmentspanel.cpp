#include "totalappointmentspanel.h"
#include "ui_totalappointmentspanel.h"

totalAppointmentsPanel::totalAppointmentsPanel(Dbworker *p_dbworker, QVariantList p_listAppoint, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::totalAppointmentsPanel)
{
    ui->setupUi(this);
    this->setFixedSize(771, 336);
    dbworker = p_dbworker;
    listAppointment = p_listAppoint;

    this->createUI(QStringList()  << ( "ID" )
                                  << ( "Дата" )
                                  << ( "Тип животного" )
                                  << ( "Имя животного" )
                                  << ( "ФИО доктора" )
                                  << ( "Телефон доктора" )
                                  << ( "Должность доктора" )
                                  << ( "Кабинет" ));
    addAppointItems();
}

totalAppointmentsPanel::~totalAppointmentsPanel()
{
    delete ui;
}

void totalAppointmentsPanel::createUI(const QStringList &headers)
{
    ui->table_appointmens->setColumnCount(8);
    ui->table_appointmens->setShowGrid(true);
    ui->table_appointmens->setHorizontalHeaderLabels(headers);
    ui->table_appointmens->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_appointmens->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_appointmens->setSelectionMode(QAbstractItemView::NoSelection);
    ui->table_appointmens->verticalHeader()->setVisible(false);
    ui->table_appointmens->setRowCount(1);
    ui->table_appointmens->horizontalHeader()->resizeSection(1, 120);
    ui->table_appointmens->horizontalHeader()->resizeSection(2, 120);
    ui->table_appointmens->horizontalHeader()->resizeSection(3, 140);
    ui->table_appointmens->horizontalHeader()->setStretchLastSection(true);
    ui->table_appointmens->setColumnHidden(0, true);
    ui->table_appointmens->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_appointmens->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_appointmens->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void totalAppointmentsPanel::addAppointItems()
{
    ui->table_appointmens->setRowCount(0);

    for (const QVariant& dyagnosisVariant : listAppointment) {
        QVariantMap dyagnosMap = dyagnosisVariant.toMap();
        int row = ui->table_appointmens->rowCount();
        ui->table_appointmens->insertRow(row);


        ui->table_appointmens->setItem(row, 0, new QTableWidgetItem(QString::number(dyagnosMap["appointment_id"].toInt())));
        ui->table_appointmens->setItem(row, 1, new QTableWidgetItem(dyagnosMap["appointment_date"].toString()));
        ui->table_appointmens->setItem(row, 2, new QTableWidgetItem(dyagnosMap["animal_type"].toString()));
        ui->table_appointmens->setItem(row, 3, new QTableWidgetItem(dyagnosMap["animal_name"].toString()));
        ui->table_appointmens->setItem(row, 4, new QTableWidgetItem(dyagnosMap["doctor_full_name"].toString()));
        ui->table_appointmens->setItem(row, 5, new QTableWidgetItem(dyagnosMap["doctor_phone"].toString()));
        ui->table_appointmens->setItem(row, 6, new QTableWidgetItem(dyagnosMap["post_type"].toString()));
        ui->table_appointmens->setItem(row, 7, new QTableWidgetItem(dyagnosMap["cabinet_name"].toString()));
    }
}

void totalAppointmentsPanel::on_button_removeAppointment_clicked()
{
    int appointId = ui->table_appointmens->selectionModel()->currentIndex().siblingAtColumn(0).data().toInt();
    int selectedRow = ui->table_appointmens->currentRow();

    if (ui->table_appointmens->selectedItems().isEmpty()) {
        QMessageBox::warning(0, "Отмена записи на приём", "Пожалуйста, выберите прием");
        return;
    }

    bool isDeleteAppoint = dbworker->deleteAppointment(appointId);

    if (isDeleteAppoint) {
        ui->table_appointmens->removeRow(selectedRow);
        QMessageBox::information(0, "Отмена записи на приём", "Запись на приём отменен");
    } else {
        QMessageBox::information(0, "Отмена записи на приём", "Ошибка отмены записи на приём.");
    }
}












