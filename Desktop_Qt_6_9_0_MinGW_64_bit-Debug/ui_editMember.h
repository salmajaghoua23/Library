/********************************************************************************
** Form generated from reading UI file 'editMember.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMEMBER_H
#define UI_EDITMEMBER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_editMember
{
public:
    QFrame *frame;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_11;
    QLineEdit *ID;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QPushButton *searchMemberBtn;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QLineEdit *firstName;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_10;
    QLineEdit *lastName;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QLineEdit *phone;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_8;
    QLineEdit *mail;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_9;
    QComboBox *gender;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *editMemberBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *editMember)
    {
        if (editMember->objectName().isEmpty())
            editMember->setObjectName("editMember");
        editMember->resize(376, 507);
        editMember->setStyleSheet(QString::fromUtf8("background-color:#E9F5DB;"));
        frame = new QFrame(editMember);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(11, 11, 358, 490));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\";\n"
"color: #E0777D;"));

        verticalLayout_2->addWidget(label_11);

        ID = new QLineEdit(frame);
        ID->setObjectName("ID");
        ID->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_2->addWidget(ID);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        searchMemberBtn = new QPushButton(frame);
        searchMemberBtn->setObjectName("searchMemberBtn");
        searchMemberBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 10pt \"Georgina\";\n"
"border-radius:4px;\n"
"padding : 0 8px;\n"
"background: #90A955;\n"
"border -radius:10px;\n"
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

        verticalLayout_3->addWidget(searchMemberBtn);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\";\n"
"color: #E0777D;\n"
""));

        verticalLayout->addWidget(label_6);

        firstName = new QLineEdit(frame);
        firstName->setObjectName("firstName");
        firstName->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout->addWidget(firstName);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\";\n"
"color: #E0777D;"));

        verticalLayout_10->addWidget(label_10);

        lastName = new QLineEdit(frame);
        lastName->setObjectName("lastName");
        lastName->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_10->addWidget(lastName);


        verticalLayout_4->addLayout(verticalLayout_10);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\";\n"
"color: #E0777D;"));

        verticalLayout_7->addWidget(label_7);

        phone = new QLineEdit(frame);
        phone->setObjectName("phone");
        phone->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_7->addWidget(phone);


        verticalLayout_4->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\";\n"
"color:#E0777D;"));

        verticalLayout_8->addWidget(label_8);

        mail = new QLineEdit(frame);
        mail->setObjectName("mail");
        mail->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(250, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_8->addWidget(mail);


        verticalLayout_4->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("font: 14pt \"Georgina\";\n"
"color: #E0777D;"));

        verticalLayout_9->addWidget(label_9);

        gender = new QComboBox(frame);
        gender->addItem(QString());
        gender->addItem(QString());
        gender->setObjectName("gender");
        gender->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_9->addWidget(gender);


        verticalLayout_4->addLayout(verticalLayout_9);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(78, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        editMemberBtn = new QPushButton(frame);
        editMemberBtn->setObjectName("editMemberBtn");
        editMemberBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"Georgina\";\n"
"border-radius:8px;\n"
"padding : 0 10px;\n"
"background: #90A955;\n"
"border -radius:10px;\n"
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

        horizontalLayout_2->addWidget(editMemberBtn);

        horizontalSpacer_2 = new QSpacerItem(78, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_2);


        retranslateUi(editMember);

        QMetaObject::connectSlotsByName(editMember);
    } // setupUi

    void retranslateUi(QDialog *editMember)
    {
        editMember->setWindowTitle(QCoreApplication::translate("editMember", "Dialog", nullptr));
        label_11->setText(QCoreApplication::translate("editMember", "<html><head/><body><p><span style=\" font-weight:700;\">Member ID</span></p></body></html>", nullptr));
        searchMemberBtn->setText(QCoreApplication::translate("editMember", "Search", nullptr));
        label_6->setText(QCoreApplication::translate("editMember", "<html><head/><body><p><span style=\" font-weight:700;\">First Name</span></p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("editMember", "<html><head/><body><p><span style=\" font-weight:700;\">Last Name </span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("editMember", "<html><head/><body><p><span style=\" font-weight:700;\">Phone Number</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("editMember", "<html><head/><body><p><span style=\" font-weight:700;\">Email </span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("editMember", "<html><head/><body><p><span style=\" font-weight:700;\">Gender</span></p></body></html>", nullptr));
        gender->setItemText(0, QCoreApplication::translate("editMember", "Male", nullptr));
        gender->setItemText(1, QCoreApplication::translate("editMember", "Female", nullptr));

        editMemberBtn->setText(QCoreApplication::translate("editMember", "Edit Member Info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editMember: public Ui_editMember {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMEMBER_H
