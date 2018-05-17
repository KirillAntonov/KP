#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <fstream>
#include <QDate>

namespace Ui {
class Registration;
class Users;
}

class Registration : public QMainWindow
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = 0);
    ~Registration();

signals:
    void mainWin();
    void asb();

private slots:
    void on_pushButton_clicked();
    void sb();

private:
    Ui::Registration *ui;
    QSqlDatabase db1;
    QSqlQuery query;
    QDate Date;
};



#endif // REGISTRATION_H
