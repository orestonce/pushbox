#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent, int stage);
    ~Dialog();
    int GetStage();
private:
    Ui::Dialog *ui;
    int m_stage;
};

#endif // DIALOG_H
