#include "sendform.h"
#include "ui_sendform.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

sendForm::sendForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sendForm)
{
    ui->setupUi(this);
    connect(this, &sendForm::asb, this, &sendForm::sb);
    emit asb();
    ui->numEdit->setValidator(new QIntValidator(0, 1000000000, this));

    QDoubleValidator* validator = new QDoubleValidator(0.0, 2000.0, 2, this);
    validator->setLocale(QLocale::English);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->sumEdit->setValidator(validator);

    for(int i = 18; i < 30; ++i)
    {
        ui->YcomboBox->addItem(QString::number(i));
    }
}

void sendForm::sb()
{
    qDebug() << "OK" << endl;
}

sendForm::~sendForm()
{
    delete ui;
}

void sendForm::start_send(QString id)
{
    QSqlQuery query;
    ID = id;
    query.exec("SELECT Balance FROM User WHERE id = "+id+"");
    while(query.next())
    {
        _Balance = query.value(0).toFloat();
    }
}

void sendForm::send(QString id, float Balance, QString ID, float _Balance, float sum)
{
    QSqlQuery query;
    float YouBalance = _Balance + sum;
    sum = (sum + ((sum * 1.5) / 100));
    float MyBalance = Balance - sum;

    if(MyBalance < 0)
    {
        QMessageBox::critical(this, "Перевод средств", "На вашем счету недостаточно средств!");
    }
    else
    {
        qDebug() << MyBalance << endl;
        QMessageBox::information(this, "Перевод средств", "Оплата произведена!");
        query.exec("UPDATE User SET Balance = "+QString::number(MyBalance)+" WHERE id = "+id+"");
        query.exec("UPDATE User SET Balance = "+QString::number(YouBalance)+" WHERE id = "+ID+"");
        emit update(id);
        emit updateHistory(Date.currentDate().toString("dd.MM.yyyy")+" "+Time.currentTime().toString("hh:mm"), Surname+" "+Name+" "+ThirdName+" "+Number, "Перевод средств", Number, sum);
        this->close();
        emit mainForm();
    }
}

void sendForm::on_sendButton_clicked()
{
    QSqlQuery query;
    Number = ui->numEdit->text();
    QString Date = ui->McomboBox->currentText()+"/"+ui->YcomboBox->currentText();
    qDebug() << Date << endl;
    float Balance;
    float sum = ui->sumEdit->text().toFloat();
    query.exec("SELECT id, Balance, Name, Surname, ThirdName FROM User WHERE Number = '"+Number+"' AND Date = '"+Date+"'");
    while(query.next())
    {
        _id = query.value(0).toString();
        Balance = query.value(1).toFloat();
        Name = query.value(2).toString();
        Surname = query.value(3).toString();
        ThirdName = query.value(4).toString();
    }

    if(_id != "")
    {
        send(ID, _Balance, _id, Balance, sum);
    }
    else
    {
        QMessageBox::critical(this, "Перевод средств", "Ошибка ввода данных!");
    }
}

void sendForm::on_backButton_clicked()
{
    this->close();
    emit mainForm();
}
