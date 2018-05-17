#include "historylist.h"
#include "ui_historylist.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>
#include <QFileDialog>


HistoryList::HistoryList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HistoryList)
{
    ui->setupUi(this);
    connect(this, &HistoryList::asb, this, &HistoryList::sb);
    emit asb();
    update();
}

HistoryList::~HistoryList()
{
    delete ui;
}

void HistoryList::start_history(QString ID)
{
    id = ID;

    query.exec("SELECT Name, Surname, ThirdName FROM User WHERE id = '"+id+"'");
    while(query.next())
    {
        _Name = query.value(0).toString();
        _Surname = query.value(1).toString();
        _ThirdName = query.value(2).toString();
    }

    model = new QSqlTableModel(this);
    model->setTable("History");
    model->setFilter("id = '"+id+"'");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
}

void HistoryList::sb()
{
    qDebug() << "OK" << endl;
}

void HistoryList::on_backButton_clicked()
{
    this->close();
    emit mainForm();
}

void HistoryList::on_export_into_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this, "Выбрать папку", "C:/");
    qDebug() << path << endl;
    QDateTime DT;
    QFile file(path+"/Выписка на имя "+_Surname+" "+_Name+" "+_ThirdName+".doc");
    QTextStream out(&file);
    QString temp;
    QString head;
    QString Name;
    QString Type;
    QString Date;
    QString Number;
    float sum;
    QString Number_check;

    if(file.open(QIODevice::WriteOnly))
    {
        head = "Выписка сформирована на имя "+_Surname+" "+_Name+" "+_ThirdName+".\nДата формирование выписки: "+DT.currentDateTime().toString("dd.MM.yyyy hh:mm")+"";
        out << head << "\n" << "\n";
        query.exec("SELECT * FROM History WHERE id = '"+id+"'");
        while(query.next())
        {
            Name = query.value(1).toString();
            Type = query.value(2).toString();
            Date = query.value(3).toString();
            Number = query.value(4).toString();
            sum = query.value(5).toFloat();
            Number_check = query.value(6).toString();

            temp = "Получатель: ";
            out << temp << Name << "\n";
            temp = "Тип операции: ";
            out << temp << Type << "\n";
            out << Date << "\n";
            temp = "Номер (счета, телефона, договора): ";
            out << temp << Number << "\n";
            temp = "Сумма: ";
            out << temp << QString::number(sum) << " BYN" << "\n";
            temp = "Номер чека: ";
            out << temp << Number_check << "\n" << "\n" << "\n";
        }
    }
    if(path != "")
    {
        QMessageBox::information(this, "История платежей", "Выписка сформирована успешно!\nВыписка находится по пути: "+path+"");
    }
    else
    {
        QMessageBox::critical(this, "История платежей", "Ошибка! Путь не выбран!");
    }
    file.close();
}
