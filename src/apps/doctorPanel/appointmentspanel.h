#ifndef APPOINTMENTSPANEL_H
#define APPOINTMENTSPANEL_H

#include <QDialog>
#include <QMessageBox>

#include "dbworker.h"
#include "dyagnosispanel.h"

namespace Ui {
class appointmentsPanel;
}

class appointmentsPanel : public QDialog
{
    Q_OBJECT

public:
    explicit appointmentsPanel(int p_user_id, Dbworker *p_dbworker, QVariantList p_listAppointments, QWidget *parent = nullptr);
    ~appointmentsPanel();

    void createUI(const QStringList &headers);
    void addAppointmentItems();

private slots:
    void on_button_dyagnosis_clicked();

public slots:
    void onDyagnosisSet();

private:
    Ui::appointmentsPanel *ui;
    Dbworker *dbworker;
    QVariantList listAppointments;
    dyagnosisPanel *dyagPanel;
    int userId;
};

#endif // APPOINTMENTSPANEL_H
