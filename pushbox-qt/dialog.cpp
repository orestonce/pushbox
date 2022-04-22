#include "dialog.h"
#include "ui_dialog.h"
#include <QIntValidator>
#include "pbcore.h"

Dialog::Dialog(QWidget *parent, int stage) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText(QString().sprintf("设置关卡[1, %d]", Go2Cpp_GetStageMax()));
    ui->lineEdit->setValidator(new QIntValidator(1, Go2Cpp_GetStageMax(), this));
    ui->lineEdit->setText(QString().sprintf("%d", stage));
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::GetStage()
{
    int s = atoi(ui->lineEdit->text().toStdString().c_str());
    return s;
}
