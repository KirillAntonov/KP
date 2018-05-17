#include "byinternet.h"
#include "ui_byinternet.h"
#include <QMessageBox>
#include <QDebug>

ByInternet::ByInternet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByInternet)
{
    ui->setupUi(this);
    QDoubleValidator* validator = new QDoubleValidator(0.0, 2000.0, 2, this);
    validator->setLocale(QLocale::English);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->sumEdit->setValidator(validator);
}

ByInternet::~ByInternet()
{
    delete ui;
}

void ByInternet::start_byInternet(QString Name, QString id)
{
    _Name = Name;
    ID = id;
    ui->label_3->setText("Получатель: " +_Name);
}

void ByInternet::on_byButton_clicked()
{
    Number = ui->numberEdit->text();
    sum = ui->sumEdit->text().toFloat();

    update(sum);
}

void ByInternet::update(float sum)
{
    float MyBalance;
    float OrgBalance;

    query.exec("SELECT Balance FROM User WHERE id = '"+ID+"'");
    while(query.next())
    {
        MyBalance = query.value(0).toFloat();
    }
    MyBalance = MyBalance - sum;

    if(MyBalance < 0)
    {
        QMessageBox::critical(this, "Оплата услуг", "Недостаточно средств!");
    }
    else
    {
        query.exec("UPDATE User SET Balance = '"+QString::number(MyBalance)+"' WHERE id = '"+ID+"'");

        query.exec("SELECT Баланс, Тип_операции FROM Organisation WHERE Название_Организации = '"+_Name+"'");
        while(query.next())
        {
            OrgBalance = query.value(0).toFloat();
            Type = query.value(1).toString();
        }
        OrgBalance = OrgBalance + sum;

        query.exec("UPDATE Organisation SET Баланс = '"+QString::number(OrgBalance)+"' WHERE Название_Организации = '"+_Name+"'");
        if(query.exec() == true)
        {
            QMessageBox::information(this, "Оплата услуг", "Оплата успешно произведена!");
            emit updateHistory(Date.currentDate().toString("dd.MM.yyyy")+" "+Time.currentTime().toString("hh:mm"), _Name, Type, Number, sum);
            this->close();
        }
        else
        {
            QMessageBox::critical(this, "Оплата услуг", "Ошибка базы данных!");
        }
    }
}
