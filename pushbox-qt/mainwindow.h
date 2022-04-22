#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual void paintEvent(QPaintEvent *event) override final;
    virtual void keyPressEvent(QKeyEvent *event) override final;
private slots:
    void on_pushButton_next_clicked();

    void on_pushButton_resetStage_clicked();

    void on_pushButton_setStage_clicked();

    void on_pushButton_prev_clicked();

private:
    void setStage(int s);
private:
    Ui::MainWindow *ui;
    QImage img_road, img_box, img_tree, img_goal;
    std::map<std::string, QImage> actionMap;
};

#endif // MAINWINDOW_H
