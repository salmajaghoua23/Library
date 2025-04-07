#ifndef AUTHORSLIST_H
#define AUTHORSLIST_H
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>
#include <QSqlQueryModel>
#include <QObject>

namespace Ui {
class authorsList;
}

class authorsList : public QDialog
{
    Q_OBJECT

public:
    explicit authorsList(QWidget *parent = nullptr);
       ~authorsList();

    QString author;

private slots:
    void showInfo();

    void on_value_textEdited(const QString &arg1);

private:
    Ui::authorsList *ui;
    QSqlQueryModel *model = nullptr;
};

#endif // AUTHORSLIST_H
