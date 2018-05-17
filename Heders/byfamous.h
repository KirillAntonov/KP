#ifndef BYFAMOUS_H
#define BYFAMOUS_H

#include <QDialog>
#include <QSqlQuery>
#include <QTime>
#include <QDate>

namespace Ui {
class ByFamous;
}

class ByFamous : public QDialog
{
    Q_OBJECT

signals:
    void updateHistory(QString date, QString Name, QString Type, QString Number, float sum);

public slots:
    void start_byFamous(QString Name, QString id);

public:
    explicit ByFamous(QWidget *parent = 0);
    ~ByFamous();

private slots:
    void on_byButton_clicked();
    void update(float sum);

private:
    Ui::ByFamous *ui;
    QSqlQuery query;
    QTime Time;
    QDate Date;
    QString Type;
    QString ID;
    QString _Name;
    QString Number;
    float sum;
};

#endif // BYFAMOUS_H
