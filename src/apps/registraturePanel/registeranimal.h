#ifndef REGISTERANIMAL_H
#define REGISTERANIMAL_H

#include <QDialog>
#include <QMessageBox>

#include "dbworker.h"

namespace Ui {
class registerAnimal;
}

class registerAnimal : public QDialog
{
    Q_OBJECT

public:
    explicit registerAnimal(QVariantList p_listUsers, Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~registerAnimal();


/*  Функции
 * - createUI - создание таблицы и её стилей.
 * - setItemTableUsers - добавление итемов в таблицу.
 * - setItemComboBoxAnimals - добавление данных животных в выпадающий список.
*/
public:
    void createUI(const QStringList &headers);
    void setItemTableUsers();
    void setItemComboBoxAnimals();

private slots:
    void on_button_registrationAnimal_clicked();


/*  Переменные
 * - listUsers - лист с данными пользователей.
 * - dbworker - объект для работы с БД.
*/
private:
    Ui::registerAnimal *ui;
    QVariantList listUsers;
    Dbworker *dbworker;

    QMap<int, QString> animalTypes;
};

#endif // REGISTERANIMAL_H
