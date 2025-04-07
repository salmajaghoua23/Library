#ifndef MEMBERSLIST_H
#define MEMBERSLIST_H
#include <QObject>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>

namespace Ui {
class membersList;
}

class membersList : public QDialog
{
  //  Q_OBJECT

public:
    explicit membersList(QWidget *parent = nullptr);
    ~membersList();

private slots:

    void on_value_textEdited(const QString &arg1);

private:
    Ui::membersList *ui;
};

#endif // MEMBERSLIST_H
