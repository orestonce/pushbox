#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include "pbcore.h"
#include "dialog.h"
#include "toast.h"

const int BaseY = 40;
const int BaseX = 30;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage img;
    img.load(QString("://sprites.png"));
    this->img_box = img.copy(32, 0, 32,32);
    this->img_road = img.copy(64, 0, 32,32);
    this->img_tree = img.copy(96, 0, 32,32);
    this->img_goal = img.copy(0, 0, 32,32);

    this->actionMap["U"] = img.copy(0, 96, 32, 32);
    this->actionMap["R"] = img.copy(32, 96, 32, 32);
    this->actionMap["D"] = img.copy(64, 96, 32, 32);
    this->actionMap["L"] = img.copy(96, 96, 32, 32);
    this->setFixedSize(QSize(550, 380));
    this->setStage(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    PushBoxMap data = Go2Cpp_GetDataForQt();
    for (int y=0; y < data.MapMaxY; y++) {
        for (int x=0; x < data.MapMaxX; x++) {
            p.drawImage(BaseX + x*32, BaseY+y*32, this->img_road);
        }
    }
    for (auto one : data.Tree) {
        p.drawImage(BaseX + one.X*32, BaseY+one.Y*32, this->img_tree);
    }
    for (auto one : data.Goal) {
        p.drawImage(BaseX + one.X*32, BaseY+one.Y*32, this->img_goal);
    }
    for (auto one : data.Box) {
        p.drawImage(BaseX + one.X*32, BaseY+one.Y*32, this->img_box);
    }
    p.drawImage(BaseX + data.Boy.X*32, BaseY+data.Boy.Y*32, this->actionMap[data.LastAction]);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    std::string action;

    switch (event->key()) {
    case Qt::Key_Up:
        action = "U";
        break;
    case Qt::Key_Down:
        action = "D";
        break;
    case Qt::Key_Left:
        action = "L";
        break;
    case Qt::Key_Right:
        action = "R";
        break;
    }
    if (!action.empty()) {
        Go2Cpp_DoAction(action);
        if (Go2Cpp_GetIsGamePass()) {
            Toast::Instance()->setSuccess("成功");
            Go2Cpp_SetStage(Go2Cpp_GetDataForQt().Stage+1);
        }
        this->repaint();
    }
}

void MainWindow::setStage(int s)
{
    if (s >= Go2Cpp_GetStageMax()) {
        s = Go2Cpp_GetStageMax();
        ui->pushButton_next->setEnabled(false);
    } else {
        ui->pushButton_next->setEnabled(true);
    }
    if (s <= 1) {
        ui->pushButton_prev->setEnabled(false);
        s = 1;
    } else {
        ui->pushButton_prev->setEnabled(true);
    }
    Go2Cpp_SetStage(s);
    ui->lineEdit->setText(QString::asprintf("%d", Go2Cpp_GetDataForQt().Stage));
    this->repaint();
}

void MainWindow::on_pushButton_next_clicked()
{
    this->setStage(Go2Cpp_GetDataForQt().Stage+1);
}

void MainWindow::on_pushButton_resetStage_clicked()
{
    this->setStage(Go2Cpp_GetDataForQt().Stage);
}

void MainWindow::on_pushButton_setStage_clicked()
{
    Dialog d(this, Go2Cpp_GetDataForQt().Stage);
    int v = d.exec();
    if (v != QDialog::Accepted) {
        return;
    }
    this->setStage(d.GetStage());
}

void MainWindow::on_pushButton_prev_clicked()
{
    this->setStage(Go2Cpp_GetDataForQt().Stage-1);
}
