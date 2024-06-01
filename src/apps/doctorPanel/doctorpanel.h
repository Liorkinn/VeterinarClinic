#ifndef DOCTORPANEL_H
#define DOCTORPANEL_H

#include <QDialog>

namespace Ui {
class DoctorPanel;
}

class DoctorPanel : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorPanel(QWidget *parent = nullptr);
    ~DoctorPanel();

private:
    Ui::DoctorPanel *ui;
};

#endif // DOCTORPANEL_H
