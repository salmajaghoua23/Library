/********************************************************************************
** Form generated from reading UI file 'signUp.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_signUp
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *username;
    QLineEdit *name;
    QLineEdit *password;
    QComboBox *roleComboBox;
    QLabel *label_2;
    QPushButton *backButton;
    QLabel *label_3;
    QPushButton *createButton;
    QLabel *label;
    QLabel *label_4;

    void setupUi(QDialog *signUp)
    {
        if (signUp->objectName().isEmpty())
            signUp->setObjectName("signUp");
        signUp->resize(517, 486);
        signUp->setStyleSheet(QString::fromUtf8("background-color:#E9F5DB;"));
        groupBox = new QGroupBox(signUp);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 511, 461));
        groupBox->setStyleSheet(QString::fromUtf8("font: 18pt \"Georgina\";\n"
"border-color: rgb(196, 178, 255);\n"
"border-color: rgb(170, 0, 255);\n"
"color: pink;\n"
"\n"
""));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        username = new QLineEdit(groupBox);
        username->setObjectName("username");
        username->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        gridLayout->addWidget(username, 0, 1, 1, 2);

        name = new QLineEdit(groupBox);
        name->setObjectName("name");
        name->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        gridLayout->addWidget(name, 1, 1, 1, 2);

        password = new QLineEdit(groupBox);
        password->setObjectName("password");
        password->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));
        password->setInputMethodHints(Qt::InputMethodHint::ImhHiddenText|Qt::InputMethodHint::ImhNoAutoUppercase|Qt::InputMethodHint::ImhNoPredictiveText|Qt::InputMethodHint::ImhSensitiveData);
        password->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(password, 2, 1, 1, 2);

        roleComboBox = new QComboBox(groupBox);
        roleComboBox->setObjectName("roleComboBox");
        roleComboBox->setStyleSheet(QString::fromUtf8("background:white;"));
        roleComboBox->setEditable(true);
        roleComboBox->setMaxVisibleItems(10);

        gridLayout->addWidget(roleComboBox, 3, 1, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\";"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        backButton = new QPushButton(groupBox);
        backButton->setObjectName("backButton");
        backButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-radius:10px;\n"
"padding : 0 4px;\n"
"background: #90A955;\n"
"border -radius:10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 26px\"Georgina\"\n"
"}\n"
"QPushButton:hover{\n"
"background:#572B788;\n"
"}\n"
"QPushButton:pressed\n"
"\n"
"{\n"
"background:#E0777D;\n"
"}\n"
"QToolButton\n"
"{\n"
"\n"
"border-radius:10px;\n"
"bacground:red;\n"
"color:red;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"              font-size: 19px;\n"
"              transition: 0.9s; \n"
"}"));

        gridLayout->addWidget(backButton, 5, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\";"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        createButton = new QPushButton(groupBox);
        createButton->setObjectName("createButton");
        createButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-radius:10px;\n"
"padding : 0 4px;\n"
"background: #90A955;\n"
"border -radius:10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 26px\"Georgina\"\n"
"}\n"
"QPushButton:hover{\n"
"background:#572B788;\n"
"}\n"
"QPushButton:pressed\n"
"\n"
"{\n"
"background:#E0777D;\n"
"}\n"
"QToolButton\n"
"{\n"
"\n"
"border-radius:10px;\n"
"bacground:red;\n"
"color:red;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"              font-size: 19px;\n"
"              transition: 0.9s; \n"
"}"));

        gridLayout->addWidget(createButton, 5, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\";"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font: \"Georgina\";"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);


        retranslateUi(signUp);

        QMetaObject::connectSlotsByName(signUp);
    } // setupUi

    void retranslateUi(QDialog *signUp)
    {
        signUp->setWindowTitle(QCoreApplication::translate("signUp", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("signUp", "   Sign Up", nullptr));
        password->setText(QString());
        label_2->setText(QCoreApplication::translate("signUp", "<html><head/><body><p><span style=\" font-weight:700;\">Name</span></p></body></html>", nullptr));
        backButton->setText(QCoreApplication::translate("signUp", "Back", nullptr));
        label_3->setText(QCoreApplication::translate("signUp", "<html><head/><body><p><span style=\" font-weight:700;\">Password</span></p></body></html>", nullptr));
        createButton->setText(QCoreApplication::translate("signUp", "Create", nullptr));
        label->setText(QCoreApplication::translate("signUp", "<html><head/><body><p><span style=\" font-weight:700;\">Username</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("signUp", "<html><head/><body><p><span style=\" font-weight:700;\">Role</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signUp: public Ui_signUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
