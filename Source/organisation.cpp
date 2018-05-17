#include "organisation.h"
#include "ui_organisation.h"
#include <QDebug>
#include "mainform.h"

Organisation::Organisation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Organisation)
{
    ui->setupUi(this);
    connect(this, &Organisation::asb, this, &Organisation::sb);
    emit asb();
}

Organisation::~Organisation()
{
    delete ui;
}

void Organisation::sb()
{
    qDebug() << "OK" << endl;
}

void Organisation::on_backButton_clicked()
{
    emit update(ID);
    this->close();
    emit mainForm();
}

void Organisation::start_organisation(QString id)
{
    ID = id;
    query.exec("SELECT Название_Организации FROM Organisation WHERE Тип_операции = 'Телефония'");
    while(query.next())
    {
        QString temp = query.value(0).toString();
        ui->phoneBox->addItem(temp);
    }

    query.exec("SELECT Название_Организации FROM Organisation WHERE Тип_операции = 'Коммунальные платежи'");
    while(query.next())
    {
        QString temp = query.value(0).toString();
        ui->komBox->addItem(temp);
    }

    query.exec("SELECT Название_Организации FROM Organisation WHERE Тип_операции = 'Интернет, Телевидение'");
    while(query.next())
    {
        QString temp = query.value(0).toString();
        ui->internetBox->addItem(temp);
    }

    query.exec("SELECT Название_Организации FROM Organisation WHERE Тип_операции = 'Популярные платежи'");
    while(query.next())
    {
        QString temp = query.value(0).toString();
        ui->famousBox->addItem(temp);
    }
}

void Organisation::on_phoneButton_clicked()
{
    BP = new ByPhone();
    connect(BP, &ByPhone::updateHistory, this, &Organisation::UPH);

    BP->show();
    BP->start_byPhone(ui->phoneBox->currentText(), ID);
}

void Organisation::on_komButton_clicked()
{
    BK = new byKom();
    connect(BK, &byKom::updateHistory, this, &Organisation::UPH);

    BK->show();
    BK->start_byKom(ui->komBox->currentText(), ID);
}

void Organisation::on_internetButton_clicked()
{
    BI = new ByInternet();
    connect(BI, &ByInternet::updateHistory, this, &Organisation::UPH);

    BI->show();
    BI->start_byInternet(ui->internetBox->currentText(), ID);
}

void Organisation::on_famousButton_clicked()
{
    BF = new ByFamous();
    connect(BF, &ByFamous::updateHistory, this, &Organisation::UPH);

    BF->show();
    BF->start_byFamous(ui->famousBox->currentText(), ID);
}
