#ifndef CHECKDYAGNOSISPANEL_H
#define CHECKDYAGNOSISPANEL_H

#include <QDialog>

namespace Ui {
class checkDyagnosisPanel;
}

class checkDyagnosisPanel : public QDialog
{
    Q_OBJECT

public:
    explicit checkDyagnosisPanel(QVariantList p_listDyagnosis, QWidget *parent = nullptr);
    ~checkDyagnosisPanel();

/*  Функции
 * - createUI - создание таблицы и её стилей.
 * - addDyagnosisItems - добавление итемов в таблицу.
*/
public:
    void createUI                   (const QStringList &headers);
    void addDyagnosisItems          ();

/*  Переменные
 * - listDyagnosis - лист с данными диагнозов.
*/
private:
    Ui::checkDyagnosisPanel *ui;
    QVariantList            listDyagnosis;
};

#endif // CHECKDYAGNOSISPANEL_H
