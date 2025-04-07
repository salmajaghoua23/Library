/********************************************************************************
** Form generated from reading UI file 'manageBooks.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEBOOKS_H
#define UI_MANAGEBOOKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_manageBooks
{
public:
    QHBoxLayout *horizontalLayout_6;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *ID;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *Name;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *add;
    QPushButton *edit;
    QPushButton *deleteButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QTableView *genreTableView;

    void setupUi(QDialog *manageBooks)
    {
        if (manageBooks->objectName().isEmpty())
            manageBooks->setObjectName("manageBooks");
        manageBooks->resize(802, 510);
        manageBooks->setStyleSheet(QString::fromUtf8("background-color:#e9f5db"));
        horizontalLayout_6 = new QHBoxLayout(manageBooks);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        frame = new QFrame(manageBooks);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_3 = new QSpacerItem(20, 68, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        label = new QLabel(frame);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        ID = new QLineEdit(frame);
        ID->setObjectName("ID");
        ID->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 10px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout_2->addWidget(ID);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 48, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Name = new QLineEdit(frame);
        Name->setObjectName("Name");
        Name->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 10px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout_3->addWidget(Name);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(17, 68, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_3 = new QSpacerItem(78, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        add = new QPushButton(frame);
        add->setObjectName("add");
        add->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{ \n"
"	border-radius:10px;\n"
"	font: 10pt \"georgia\";\n"
"	background-color: #90a955;\n"
"	padding : 0 4px;\n"
"	border-radius:10px;\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"\n"
"QPushButton:hover:!pressed\n"
"\n"
"{\n"
"background:#572b788;\n"
"}\n"
""));

        horizontalLayout->addWidget(add);

        edit = new QPushButton(frame);
        edit->setObjectName("edit");
        edit->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{ \n"
"	border-radius:10px;\n"
"	font: 10pt \"georgia\";\n"
"	background-color: #90a955;\n"
"	padding : 0 10px;\n"
"	border-radius:10px;\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"\n"
"QPushButton:hover:!pressed\n"
"\n"
"{\n"
"background:#572b788;\n"
"}\n"
""));

        horizontalLayout->addWidget(edit);

        deleteButton = new QPushButton(frame);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{ \n"
"	border-radius:10px;\n"
"	font: 10pt \"georgia\";\n"
"	background-color: #90a955;\n"
"	padding : 0 4px;\n"
"	border-radius:10px;\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"\n"
"QPushButton:hover:!pressed\n"
"\n"
"{\n"
"background:#572b788;\n"
"}\n"
""));

        horizontalLayout->addWidget(deleteButton);


        horizontalLayout_7->addLayout(horizontalLayout);

        horizontalSpacer_4 = new QSpacerItem(78, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_4 = new QSpacerItem(17, 88, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        genreTableView = new QTableView(frame);
        genreTableView->setObjectName("genreTableView");
        genreTableView->setStyleSheet(QString::fromUtf8("QHeaderView::section { background-color: #E0777D; font: solid;\n"
"color:white;\n"
"}"));
        genreTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        genreTableView->horizontalHeader()->setDefaultSectionSize(200);
        genreTableView->verticalHeader()->setVisible(false);

        horizontalLayout_4->addWidget(genreTableView);


        horizontalLayout_6->addWidget(frame);


        retranslateUi(manageBooks);

        QMetaObject::connectSlotsByName(manageBooks);
    } // setupUi

    void retranslateUi(QDialog *manageBooks)
    {
        manageBooks->setWindowTitle(QCoreApplication::translate("manageBooks", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("manageBooks", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-family:georgia;font-weight:700; color:#e0777d;\">ID</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("manageBooks", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-family:georgia;font-weight:700; color:#e0777d;\">Name</span></p></body></html>", nullptr));
        add->setText(QCoreApplication::translate("manageBooks", "Add", nullptr));
        edit->setText(QCoreApplication::translate("manageBooks", "Edit", nullptr));
        deleteButton->setText(QCoreApplication::translate("manageBooks", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class manageBooks: public Ui_manageBooks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEBOOKS_H
