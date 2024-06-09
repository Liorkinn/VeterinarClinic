#ifndef TOTALAPPOINTMENTSPANEL_H
#define TOTALAPPOINTMENTSPANEL_H

#include <QDialog>
#include "dbworker.h"

namespace Ui {
class totalAppointmentsPanel;
}

class totalAppointmentsPanel : public QDialog
{
    Q_OBJECT

public:
    explicit totalAppointmentsPanel(Dbworker *p_dbworker, QVariantList p_listAppoint, QWidget *parent = nullptr);
    ~totalAppointmentsPanel();

/*  Функции
 * - createUI - создание таблицы и её стилей.
 * - addAppointItems - добавление итемов в таблицу.
*/
public:
    void createUI(const QStringList &headers);
    void addAppointItems();

private slots:
    void on_button_removeAppointment_clicked();

/*  Переменные
 * - dbworker - объект для работы с БД.
 * - listAppointment - лист с данными о записях.
*/
private:
    Ui::totalAppointmentsPanel *ui;
    Dbworker *dbworker;
    QVariantList listAppointment;
};

#endif // TOTALAPPOINTMENTSPANEL_H
