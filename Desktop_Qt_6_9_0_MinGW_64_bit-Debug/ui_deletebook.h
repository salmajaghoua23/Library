/********************************************************************************
** Form generated from reading UI file 'deletebook.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETEBOOK_H
#define UI_DELETEBOOK_H

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

class Ui_deleteBook
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ID;
    QPushButton *deleteBookBtn;

    void setupUi(QDialog *deleteBook)
    {
        if (deleteBook->objectName().isEmpty())
            deleteBook->setObjectName("deleteBook");
        deleteBook->resize(400, 163);
        verticalLayout_2 = new QVBoxLayout(deleteBook);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(deleteBook);
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

        horizontalLayout->addWidget(label);

        ID = new QLineEdit(frame);
        ID->setObjectName("ID");
        ID->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 10px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout->addWidget(ID);

        deleteBookBtn = new QPushButton(frame);
        deleteBookBtn->setObjectName("deleteBookBtn");
        deleteBookBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"color: #ffffff;\n"
"border-radius:8px;\n"
"padding : 0 8px;\n"
"background: #90a955;\n"
"border -radius:10px;\n"
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

        horizontalLayout->addWidget(deleteBookBtn);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(frame);


        retranslateUi(deleteBook);

        QMetaObject::connectSlotsByName(deleteBook);
    } // setupUi

    void retranslateUi(QDialog *deleteBook)
    {
        deleteBook->setWindowTitle(QCoreApplication::translate("deleteBook", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("deleteBook", "<html><head/><body><p><span style=\" font-weight:700;\">Book ID :</span></p></body></html>", nullptr));
        deleteBookBtn->setText(QCoreApplication::translate("deleteBook", "Delete Book", nullptr));
    } // retranslateUi

};

namespace Ui {
    class deleteBook: public Ui_deleteBook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETEBOOK_H
