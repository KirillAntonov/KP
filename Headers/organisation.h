#ifndef ORGANISATION_H
#define ORGANISATION_H

#include <QMainWindow>
#include <QSqlQuery>
#include "byphone.h"
#include "bykom.h"
#include "byinternet.h"
#include "byfamous.h"

namespace Ui {
class Organisation;
}

class Organisation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Organisation(QWidget *parent = 0);
    void start_organisation(QString id);
    ~Organisation();

signals:
    void mainForm();
    void asb();
    void update(QString id);
    void UPH(QString date, QString Name, QString Type, QString Number, float sum);

private slots:
    void sb();
    void on_backButton_clicked();

    void on_phoneButton_clicked();

    void on_komButton_clicked();

    void on_internetButton_clicked();

    void on_famousButton_clicked();

private:
    Ui::Organisation *ui;
    QString ID;
    QSqlQuery query;
    ByPhone *BP;
    byKom *BK;
    ByInternet *BI;
    ByFamous *BF;
};

#endif // ORGANISATION_H
