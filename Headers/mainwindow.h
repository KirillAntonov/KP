#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "registration.h"
#include "mainform.h"
#include "adminwindow.h"
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void keyPressEvent(QKeyEvent *event);

    void on_Info_triggered();

    void on_exit_triggered();

    void on_LoginButton_clicked();

    void on_RegButton_clicked();

private:
    Ui::MainWindow *ui;
    Registration *reg;
    mainform *main;
    AdminWindow *AW;
};

#endif // MAINWINDOW_H
