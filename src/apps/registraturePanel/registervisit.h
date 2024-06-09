#ifndef REGISTERVISIT_H
#define REGISTERVISIT_H

#include <QDialog>
#include <QMessageBox>
#include "dbworker.h"

namespace Ui {
class RegisterVisit;
}

class RegisterVisit : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterVisit(Dbworker *p_dbworker, QVariantList p_listDoctors, QVariantList p_listAnimals, QWidget *parent = nullptr);
    ~RegisterVisit();

/*  Функции
 * - createUIAnimals - создание таблицы животных и её стилей.
 * - createUIDoctors - создание таблицы докторов и её стилей.
 * - addItemDoctors - добавление итемов в таблицу.
 * - addItemAnimals - добавление итемов в таблицу.
*/
public:
    void createUIAnimals(const QStringList &headers);
    void createUIDoctors(const QStringList &headers);
    void addItemDoctors();
    void addItemAnimals();

private slots:
    void on_button_registerVisit_clicked();

private slots:
    void checkEvenTime(const QDateTime &newDateTime);


/*  Переменные
 * - dbworker - объект для работы с БД.
 * - listDoctors - лист с данными о докторах.
 * - listAnimals - лист с данными о животных.
*/
private:
    Ui::RegisterVisit *ui;
    Dbworker *dbworker;
    QVariantList listDoctors;
    QVariantList listAnimals;
};

#endif // REGISTERVISIT_H
