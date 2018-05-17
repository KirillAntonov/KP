#ifndef REFILL_H
#define REFILL_H

#include <QDialog>
#include <QTime>
#include <QDate>

namespace Ui {
class refill;
}

class refill : public QDialog
{
    Q_OBJECT

public:
    explicit refill(QWidget *parent = 0);
    ~refill();

signals:
    void mainForm();
    void asb();
    void update(QString id);
    void updateHistory(QString date, QString Name, QString Type, QString Number, float sum);

private slots:
    void updateBalance(QString ID, float Balance);
    void on_refillButton_clicked();
    void sb();

    void on_backButton_clicked();

public slots:
    void start_refill(QString id);

private:
    Ui::refill *ui;
    QString _id;
    QString Number;
    float _Balance;
    QTime Time;
    QDate Date;
    QString Name;
    QString Surname;
    QString ThirdName;

};

#endif // REFILL_H
