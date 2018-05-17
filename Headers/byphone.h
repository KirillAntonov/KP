#ifndef BYPHONE_H
#define BYPHONE_H

#include <QDialog>
#include <QSqlQuery>
#include <QTime>
#include <QDate>

namespace Ui {
class ByPhone;
}

class ByPhone : public QDialog
{
    Q_OBJECT

public:
    explicit ByPhone(QWidget *parent = 0);
    ~ByPhone();

public slots:
    void start_byPhone(QString Name, QString id);

signals:
    void updateHistory(QString date, QString Name, QString Type, QString Number, float sum);

private slots:
    void on_byButton_clicked();
    void update(float sum);

private:
    Ui::ByPhone *ui;
    QString ID;
    QSqlQuery query;
    QString _Name;
    QString Number;
    QString Type;
    QTime Time;
    QDate Date;
    float sum;
};

#endif // BYPHONE_H
