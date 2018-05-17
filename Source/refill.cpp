#include "refill.h"
#include "mainform.h"
#include "ui_refill.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>


refill::refill(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::refill)
{
    ui->setupUi(this);
    connect(this, &refill::asb, this, &refill::sb);
    emit asb();

    QDoubleValidator* validator = new QDoubleValidator(0.0, 2000.0, 2, this);
    validator->setLocale(QLocale::English);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->refillEdit->setValidator(validator);
}

refill::~refill()
{
    delete ui;
}

void refill::sb()
{
    qDebug() << "OK" << endl;
}

void refill::start_refill(QString id)
{
    _id = id;
    QSqlQuery query;
    query.exec("SELECT Balance, Number, Name, Surname, ThirdName FROM User WHERE id = '"+id+"'");
    while(query.next())
    {
        _Balance = query.value(0).toFloat();
        Number = query.value(1).toString();
        Name = query.value(2).toString();
        Surname = query.value(3). toString();
        ThirdName = query.value(4).toString();
    }

    qDebug() << _Balance << endl;
}

void refill::updateBalance(QString ID, float Balance)
{
    QSqlQuery query;
    float result = _Balance + Balance;
    query.exec("UPDATE User SET Balance = "+QString::number(result)+" WHERE id = "+ID+"");
    qDebug() << query.exec() << endl;
    if(query.exec() == true)
    {
        QMessageBox::information(this, "Пополнение счета", "Пополнение произведено успешно!");
        emit update(ID);
        emit updateHistory(Date.currentDate().toString("dd.MM.yyyy")+" "+Time.currentTime().toString("hh:mm"), Surname+" "+Name+" "+ThirdName+ " "+Number, "Пополнение счета", Number, Balance);
        qDebug() << "HIIIFI";
    }
    this->close();
    emit mainForm();
}

void refill::on_refillButton_clicked()
{
    float Balance = ui->refillEdit->text().toFloat();
    qDebug() << Balance << endl;
    updateBalance(_id, Balance);
}

void refill::on_backButton_clicked()
{
    this->close();
    emit mainForm();
}
