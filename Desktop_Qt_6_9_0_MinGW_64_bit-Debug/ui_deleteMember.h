/********************************************************************************
** Form generated from reading UI file 'deleteMember.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETEMEMBER_H
#define UI_DELETEMEMBER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_deleteMember
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ID;
    QPushButton *deleteMemberBtn;

    void setupUi(QDialog *deleteMember)
    {
        if (deleteMember->objectName().isEmpty())
            deleteMember->setObjectName("deleteMember");
        deleteMember->resize(658, 152);
        verticalLayout_2 = new QVBoxLayout(deleteMember);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(deleteMember);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("background-color:#e9f5db"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        horizontalLayout->addWidget(label, 0, Qt::AlignLeft);

        ID = new QLineEdit(frame);
        ID->setObjectName("ID");
        ID->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout->addWidget(ID);

        deleteMemberBtn = new QPushButton(frame);
        deleteMemberBtn->setObjectName("deleteMemberBtn");
        deleteMemberBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"border-radius:8px;\n"
"padding : 0 8px;\n"
"background: #90a955;\n"
"border -radius:10px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"\n"
"{\n"
"background:#572b788;\n"
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

        horizontalLayout->addWidget(deleteMemberBtn);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(frame);


        retranslateUi(deleteMember);

        QMetaObject::connectSlotsByName(deleteMember);
    } // setupUi

    void retranslateUi(QDialog *deleteMember)
    {
        deleteMember->setWindowTitle(QCoreApplication::translate("deleteMember", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("deleteMember", "Member ID ", nullptr));
        deleteMemberBtn->setText(QCoreApplication::translate("deleteMember", "Delete Member", nullptr));
    } // retranslateUi

};

namespace Ui {
    class deleteMember: public Ui_deleteMember {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETEMEMBER_H
