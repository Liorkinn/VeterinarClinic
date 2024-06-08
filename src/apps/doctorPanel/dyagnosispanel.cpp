#include "dyagnosispanel.h"
#include "ui_dyagnosispanel.h"

dyagnosisPanel::dyagnosisPanel(int p_appointment_id, Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dyagnosisPanel)
{
    ui->setupUi(this);
    this->setWindowTitle("Постановка диагноза");
    dbworker = p_dbworker;
    appointmentID = p_appointment_id;
}

dyagnosisPanel::~dyagnosisPanel()
{
    delete ui;
}

void dyagnosisPanel::on_button_setDyagnosis_clicked()
{
    QString currentDyagnosis = ui->textEdit_dyagnosis->toPlainText();

    if (currentDyagnosis.isEmpty()) {
        QMessageBox::warning(0, "Постановка диагноза", "Пожалуйста, поставьте диагноз");
        return;
    }

    bool isInsertDyagnosis = dbworker->addVisitWithDiagnosis(appointmentID, currentDyagnosis);

    if (isInsertDyagnosis) {
        emit dyagnosisSet();
        QMessageBox::information(0, "Постановка диагноза", "Диагноз выставлен!");
    } else {
        QMessageBox::warning(0, "Постановка диагноза", "Ошибка выставления диагноза!");
    }
}
