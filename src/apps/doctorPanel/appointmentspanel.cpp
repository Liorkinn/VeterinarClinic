#include "appointmentspanel.h"
#include "ui_appointmentspanel.h"

appointmentsPanel::appointmentsPanel(int p_user_id, Dbworker *p_dbworker, QVariantList p_listAppointments, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::appointmentsPanel)
{
    ui->setupUi(this);
    this->setWindowTitle("Текущие записи");
    dbworker = p_dbworker;
    listAppointments = p_listAppointments;
    userId = p_user_id;
    this->createUI(QStringList()  << ( "ID" )
                                  << ( "Дата" )
                                  << ( "Тип животного" )
                                  << ( "Имя животного" )
                                  << ( "Симптом" )
                                  << ( "Фамилия" )
                                  << ( "Имя" )
                                  << ( "Отчество" )
                                  << ( "Телефон" ));
    addAppointmentItems();
}

void appointmentsPanel::createUI(const QStringList &headers)
{
    ui->table_totalAppointments->setColumnCount(9);
    ui->table_totalAppointments->setShowGrid(true);
    ui->table_totalAppointments->setHorizontalHeaderLabels(headers);
    ui->table_totalAppointments->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_totalAppointments->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_totalAppointments->setSelectionMode(QAbstractItemView::NoSelection);
    ui->table_totalAppointments->verticalHeader()->setVisible(false);
    ui->table_totalAppointments->setRowCount(1);
    ui->table_totalAppointments->horizontalHeader()->resizeSection(1, 120);
    ui->table_totalAppointments->horizontalHeader()->resizeSection(2, 120);
    ui->table_totalAppointments->horizontalHeader()->resizeSection(3, 140);
    ui->table_totalAppointments->horizontalHeader()->setStretchLastSection(true);
    ui->table_totalAppointments->setColumnHidden(0, true);
    ui->table_totalAppointments->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_totalAppointments->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_totalAppointments->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void appointmentsPanel::addAppointmentItems()
{
    ui->table_totalAppointments->setRowCount(0);

    for (const QVariant& appointVariant : listAppointments) {
        QVariantMap appointMap = appointVariant.toMap();
        int row = ui->table_totalAppointments->rowCount();
        ui->table_totalAppointments->insertRow(row);

        ui->table_totalAppointments->setItem(row, 0, new QTableWidgetItem(QString::number(appointMap["id"].toInt())));
        ui->table_totalAppointments->setItem(row, 1, new QTableWidgetItem(appointMap["date"].toString()));
        ui->table_totalAppointments->setItem(row, 2, new QTableWidgetItem(appointMap["animal_type"].toString()));
        ui->table_totalAppointments->setItem(row, 3, new QTableWidgetItem(appointMap["animal_name"].toString()));
        ui->table_totalAppointments->setItem(row, 4, new QTableWidgetItem(appointMap["sympthom"].toString()));
        ui->table_totalAppointments->setItem(row, 5, new QTableWidgetItem(appointMap["surname"].toString()));
        ui->table_totalAppointments->setItem(row, 6, new QTableWidgetItem(appointMap["name"].toString()));
        ui->table_totalAppointments->setItem(row, 7, new QTableWidgetItem(appointMap["patronymic"].toString()));
        ui->table_totalAppointments->setItem(row, 8, new QTableWidgetItem(appointMap["telephone"].toString()));
    }
}

appointmentsPanel::~appointmentsPanel()
{
    delete ui;
}

void appointmentsPanel::on_button_dyagnosis_clicked()
{
    if (ui->table_totalAppointments->selectedItems().isEmpty()) {
        QMessageBox::warning(0, "Постановка диагноза", "Пожалуйста, выберите пациента");
        return;
    }

    int appoinmentId = ui->table_totalAppointments->selectionModel()->currentIndex().siblingAtColumn(0).data().toInt();

    dyagPanel = new dyagnosisPanel(appoinmentId, dbworker);
    QObject::connect(dyagPanel, &dyagnosisPanel::dyagnosisSet, this, &appointmentsPanel::onDyagnosisSet);
    dyagPanel->exec();
}

void appointmentsPanel::onDyagnosisSet()
{
    listAppointments = dbworker->getDoctorAppointments(userId);
    addAppointmentItems();
}
