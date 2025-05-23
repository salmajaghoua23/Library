#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class Login;
}

class QLineEdit;

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void on_loginButton_clicked();
    void on_signUpButton_clicked();
    void on_forgetPasswdBtn_clicked();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    bool m_dragging = false;
    void setValidator();
    QPoint m_lastMousePosition;
private:
    Ui::Login *ui;
};

#endif // LOGIN_H
