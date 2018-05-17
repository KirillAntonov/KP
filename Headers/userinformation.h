#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QMainWindow>
#include <QSqlQuery>

namespace Ui {
class UserInformation;
}

class UserInformation : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserInformation(QWidget *parent = 0);
    ~UserInformation();

signals:
    void mainForm();
    void asb();

public slots:
    void start_userInformation(QString id);

private slots:
    void on_BackButton_clicked();
    void sb();
    void update_password(QString Pass);
    void output_information(QString id);

    void on_changepassButton_clicked();

private:
    Ui::UserInformation *ui;
    QSqlQuery query;
    QString _id;
    QString Name;
    QString Surname;
    QString ThirdName;
    QString Sex;
    QString Birthday;
    QString MobilePhone;
    QString Pass;
    QString _Pass;
};

#endif // USERINFORMATION_H
