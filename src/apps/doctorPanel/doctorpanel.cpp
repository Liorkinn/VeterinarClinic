#include "doctorpanel.h"
#include "ui_doctorpanel.h"

DoctorPanel::DoctorPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoctorPanel)
{
    ui->setupUi(this);
}

DoctorPanel::~DoctorPanel()
{
    delete ui;
}
