/********************************************************************************
** Form generated from reading UI file 'newPasswd.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPASSWD_H
#define UI_NEWPASSWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_newPasswd
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *username;
    QLabel *label;
    QLineEdit *name;
    QLabel *label_2;
    QPushButton *backButton;
    QLineEdit *newpass;
    QLabel *label_3;
    QPushButton *submitButton;

    void setupUi(QDialog *newPasswd)
    {
        if (newPasswd->objectName().isEmpty())
            newPasswd->setObjectName("newPasswd");
        newPasswd->resize(502, 589);
        newPasswd->setStyleSheet(QString::fromUtf8("background-color:#e9f5db;"));
        verticalLayout = new QVBoxLayout(newPasswd);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(newPasswd);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("font: 16pt \"Comic Sans MS\" Bold;\n"
"border-color: rgb(196, 178, 255);\n"
"border-color: rgb(170, 0, 255);\n"
"color: #E0777D;"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        username = new QLineEdit(groupBox);
        username->setObjectName("username");
        username->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 10px;\n"
"	font: 24px\n"
"}"));

        gridLayout->addWidget(username, 0, 1, 1, 2);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\" Bold;"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        name = new QLineEdit(groupBox);
        name->setObjectName("name");
        name->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 	10px;\n"
"	font: 24px\n"
"}"));

        gridLayout->addWidget(name, 1, 1, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\" Bold;"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        backButton = new QPushButton(groupBox);
        backButton->setObjectName("backButton");
        backButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-radius:10px;\n"
"padding : 0 4px;\n"
"background: #90a955;\n"
"border -radius:10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 24px\n"
"}\n"
"QPushButton:hover:!pressed\n"
"\n"
"{\n"
"background:#e0777d;\n"
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

        gridLayout->addWidget(backButton, 3, 1, 1, 1);

        newpass = new QLineEdit(groupBox);
        newpass->setObjectName("newpass");
        newpass->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 10px;\n"
"	font: 24px\n"
"}"));
        newpass->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(newpass, 2, 1, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\" Bold;"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        submitButton = new QPushButton(groupBox);
        submitButton->setObjectName("submitButton");
        submitButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-radius:10px;\n"
"padding : 0 4px;\n"
"background: #90A955;\n"
"border -radius:10px;\n"
"color: rgb(255, 255, 255);\n"
"font: 24px\n"
"}\n"
"QPushButton:hover:!pressed\n"
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

        gridLayout->addWidget(submitButton, 3, 2, 1, 1);


        verticalLayout->addWidget(groupBox);


        retranslateUi(newPasswd);

        QMetaObject::connectSlotsByName(newPasswd);
    } // setupUi

    void retranslateUi(QDialog *newPasswd)
    {
        newPasswd->setWindowTitle(QCoreApplication::translate("newPasswd", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("newPasswd", "Forget Password", nullptr));
        label->setText(QCoreApplication::translate("newPasswd", "<html><head/><body><p><span style=\" font-weight:700;\">Username</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("newPasswd", "New Password", nullptr));
        backButton->setText(QCoreApplication::translate("newPasswd", "Back", nullptr));
        label_3->setText(QCoreApplication::translate("newPasswd", "<html><head/><body><p><span style=\" font-weight:700;\">Name</span></p></body></html>", nullptr));
        submitButton->setText(QCoreApplication::translate("newPasswd", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newPasswd: public Ui_newPasswd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPASSWD_H
