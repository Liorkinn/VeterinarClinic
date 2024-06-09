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

/*  Функции приёма
 * - createUI - создание и стили таблицы.
 * - addAppointmentItems - заполнение таблицы элементами.
*/
public:
    void createUI                           (const QStringList &headers);
    void addAppointmentItems                ();

private slots:
    void on_button_dyagnosis_clicked        ();

/*  Функция-слот
 * - onDyagnosisSet - обновление данных таблицы.
*/
public slots:
    void onDyagnosisSet                     ();

/*  Переменные
 * - dbworker - объект для работы с БД.
 * - listAppointments - лист с записями на приём.
 * - dyagPanel - объект формы постановки диагноза.
 * - userId - текущий userID пользователя.
*/
private:
    Ui::appointmentsPanel   *ui;
    Dbworker                *dbworker;
    QVariantList             listAppointments;
    dyagnosisPanel          *dyagPanel;
    int userId;
};

#endif // APPOINTMENTSPANEL_H
