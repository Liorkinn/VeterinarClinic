#ifndef MYANIMALS_H
#define MYANIMALS_H

#include <QDialog>

namespace Ui {
class MyAnimals;
}

class MyAnimals : public QDialog
{
    Q_OBJECT

public:
    explicit MyAnimals(QVariantList p_listAnimals, QWidget *parent = nullptr);
    ~MyAnimals();

/*  Функции
 * - createUI - создание таблицы со стилями.
 * - setAnimalsItem - заполнение таблицы значениями животных.
*/
    void createUI(const QStringList &headers);
    void setAnimalsItem();

private:
    Ui::MyAnimals *ui;
    QVariantList listAnimals;
};

#endif // MYANIMALS_H
