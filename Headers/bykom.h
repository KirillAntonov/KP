#ifndef BYKOM_H
#define BYKOM_H

#include <QDialog>
#include <QSqlQuery>
#include <QTime>
#include <QDate>

namespace Ui {
class byKom;
}

class byKom : public QDialog
{
    Q_OBJECT

public:
    explicit byKom(QWidget *parent = 0);
    ~byKom();

signals:
    void updateHistory(QString date, QString Name, QString Type, QString Number, float sum);

public slots:
    void start_byKom(QString Name, QString id);

private slots:
    void on_byButton_clicked();
    void update(float sum);

private:
    Ui::byKom *ui;
    QSqlQuery query;
    QTime Time;
    QDate Date;
    QString Type;
    QString ID;
    QString _Name;
    QString Number;
    float sum;
};

#endif // BYKOM_H
