/********************************************************************************
** Form generated from reading UI file 'genreList.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENRELIST_H
#define UI_GENRELIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_genreList
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_9;
    QLineEdit *value;
    QTableView *TableView;

    void setupUi(QDialog *genreList)
    {
        if (genreList->objectName().isEmpty())
            genreList->setObjectName("genreList");
        genreList->resize(569, 419);
        QFont font;
        font.setPointSize(6);
        genreList->setFont(font);
        genreList->setStyleSheet(QString::fromUtf8("background-color:#e9f5db;"));
        verticalLayout_2 = new QVBoxLayout(genreList);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_9 = new QLabel(genreList);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        horizontalLayout->addWidget(label_9);

        value = new QLineEdit(genreList);
        value->setObjectName("value");
        value->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 15px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout->addWidget(value);


        verticalLayout->addLayout(horizontalLayout);

        TableView = new QTableView(genreList);
        TableView->setObjectName("TableView");
        TableView->setContextMenuPolicy(Qt::PreventContextMenu);
        TableView->setStyleSheet(QString::fromUtf8("QHeaderView::section { background-color: #4f85e2; font: 16 px solid;color:white;}"));
        TableView->setSelectionMode(QAbstractItemView::SingleSelection);
        TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        TableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(TableView);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(genreList);

        QMetaObject::connectSlotsByName(genreList);
    } // setupUi

    void retranslateUi(QDialog *genreList)
    {
        genreList->setWindowTitle(QCoreApplication::translate("genreList", "Dialog", nullptr));
        label_9->setText(QCoreApplication::translate("genreList", "<html><head/><body><p><span style=\" font-weight:700;\">Search Genre</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class genreList: public Ui_genreList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENRELIST_H
