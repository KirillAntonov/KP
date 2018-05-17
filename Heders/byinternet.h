#ifndef BYINTERNET_H
#define BYINTERNET_H

#include <QDialog>
#include <QSqlQuery>
#include <QTime>
#include <QDate>

namespace Ui {
class ByInternet;
}

class ByInternet : public QDialog
{
    Q_OBJECT

public:
    explicit ByInternet(QWidget *parent = 0);
    ~ByInternet();

signals:
    void updateHistory(QString date, QString Name, QString Type, QString Number, float sum);

private slots:
    void update(float sum);

    void on_byButton_clicked();

public slots:
    void start_byInternet(QString Name, QString id);

private:
    Ui::ByInternet *ui;
    QSqlQuery query;
    QTime Time;
    QDate Date;
    QString Type;
    QString _Name;
    QString ID;
    QString Number;
    float sum;
};

#endif // BYINTERNET_H
