#ifndef HISTORYLIST_H
#define HISTORYLIST_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QSqlTableModel>

namespace Ui {
class HistoryList;
}

class HistoryList : public QMainWindow
{
    Q_OBJECT

public slots:
    void start_history(QString ID);

public:
    explicit HistoryList(QWidget *parent = 0);
    ~HistoryList();

signals:
    void mainForm();
    void asb();

private slots:
    void sb();

    void on_backButton_clicked();

    void on_export_into_triggered();

private:
    Ui::HistoryList *ui;
    QString id;
    QSqlQuery query;
    QString _Name;
    QString _Surname;
    QString _ThirdName;
    QSqlTableModel *model;
};

#endif // HISTORYLIST_H
