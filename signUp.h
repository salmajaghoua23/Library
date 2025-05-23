#ifndef SIGNUP_H
#define SIGNUP_H
#include <QLabel>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLineEdit>
#include <QComboBox>
class signUp : public QDialog
{
    Q_OBJECT

public:
    explicit signUp(QWidget *parent = nullptr);
    ~signUp();

private slots:
    void on_createButton_clicked();
    void on_backButton_clicked();

private:
    void setValidator();

    // Declare your UI elements
    QLineEdit *nameLineEdit;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QComboBox *roleComboBox;
};

#endif // SIGNUP_H
