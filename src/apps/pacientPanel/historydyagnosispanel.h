#ifndef HISTORYDYAGNOSISPANEL_H
#define HISTORYDYAGNOSISPANEL_H

#include <QDialog>

namespace Ui {
class HistoryDyagnosisPanel;
}

class HistoryDyagnosisPanel : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDyagnosisPanel(QVariantList p_listHistoryDyagnosis, QWidget *parent = nullptr);
    ~HistoryDyagnosisPanel();

/*  Функции
 * - createUI - создание таблицы со стилями.
 * - addHistoryItems - заполнение таблицы значениями истории.
*/
public:
    void createUI(const QStringList &headers);
    void addHistoryItems();

/*  Переменные
 * - listHistoryDyagnosis - лист с данными истории диагнозов.
*/
private:
    Ui::HistoryDyagnosisPanel *ui;
    QVariantList listHistoryDyagnosis;
};

#endif // HISTORYDYAGNOSISPANEL_H
