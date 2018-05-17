#ifndef SENDFORM_H
#define SENDFORM_H

#include <QDialog>
#include <QTime>
#include <QDate>

namespace Ui {
class sendForm;
}

class sendForm : public QDialog
{
    Q_OBJECT

public:
    explicit sendForm(QWidget *parent = 0);
    ~sendForm();

signals:
    void mainForm();
    void asb();
    void update(QString id);
    void updateHistory(QString date, QString Name, QString Type, QString Number, float sum);

private slots:
    void send(QString id, float Balance, QString ID, float _Balance, float sum);
    void sb();
    void on_sendButton_clicked();

    void on_backButton_clicked();

public slots:
    void start_send(QString id);

private:
    Ui::sendForm *ui;
    QString _Date;
    QString _id;
    QString ID;
    float _Balance;
    QTime Time;
    QDate Date;
    QString Number;
    QString Name;
    QString Surname;
    QString ThirdName;
};

#endif // SENDFORM_H
