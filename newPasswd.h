#ifndef NEWPASSWD_H
#define NEWPASSWD_H

#include <QDialog>
#include <QLineEdit>

class newPasswd : public QDialog
{
    Q_OBJECT

public:
    explicit newPasswd(QWidget *parent = nullptr);

private slots:
    void resetPassword();
    void on_backButton_clicked();

private:
    QLineEdit *usernameEdit;
    QLineEdit *newPassEdit;

};

#endif // NEWPASSWD_H
