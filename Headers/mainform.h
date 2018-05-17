#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <refill.h>
#include <sendform.h>
#include <organisation.h>
#include <QSqlDatabase>
#include <userinformation.h>
#include "historylist.h"
#include "byphone.h"
#include <QKeyEvent>

namespace Ui {
class mainform;
}

class mainform : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainform(QWidget *parent = 0);
    ~mainform();

private slots:
    void out_information(QString Login, QString Pass);

    void keyPressEvent(QKeyEvent *event);

    void on_exit_triggered();

    void on_ChanBalBut_clicked();

    void on_SendButton_clicked();

    void on_OrgButton_clicked();

    void on_myInfo_triggered();

    void on_historyButton_clicked();

    void on_help_triggered();

public slots:
    void start(QString Login, QString Pass);
    void updateInfo(QString id);
    void history(QString date, QString Name, QString Type, QString Number, float sum);
    void course();

private:
    Ui::mainform *ui;
    QSqlQuery query;
    QString Name;
    QString Surname;
    QString ThirdName;
    QString Number;
    QString Date;
    QString Type;
    QString Balance;
    QString password;

    ByPhone *BP;
    QSqlDatabase db;
    refill *ref;
    sendForm *send;
    Organisation *org;
    QString login;
    QString pass;
    QString id;
    UserInformation *UInfo;
    HistoryList * HList;

};

#endif // MAINFORM_H
