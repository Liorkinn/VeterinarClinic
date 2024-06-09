#ifndef DYAGNOSISPANEL_H
#define DYAGNOSISPANEL_H

#include <QDialog>
#include <QMessageBox>

#include "dbworker.h"

namespace Ui {
class dyagnosisPanel;
}

class dyagnosisPanel : public QDialog
{
    Q_OBJECT

public:
    explicit dyagnosisPanel(int p_appointment_id, Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~dyagnosisPanel();

private slots:
    void on_button_setDyagnosis_clicked();

signals:
    void dyagnosisSet();

private:
    Ui::dyagnosisPanel *ui;
    Dbworker           *dbworker;
    int                 appointmentID;
};

#endif // DYAGNOSISPANEL_H
