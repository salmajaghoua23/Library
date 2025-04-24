#ifndef DELETEMEMBER_H
#define DELETEMEMBER_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class deleteMember;
}

class deleteMember : public QDialog
{
    Q_OBJECT

public:
    explicit deleteMember(QWidget *parent = nullptr);
    ~deleteMember();

private slots:
    void on_deleteMemberBtn_clicked();
    void on_returnBtn_clicked();
private:
    Ui::deleteMember *ui;
    QSqlTableModel *model;
    void loadMembers();

};

#endif // DELETEMEMBER_H
