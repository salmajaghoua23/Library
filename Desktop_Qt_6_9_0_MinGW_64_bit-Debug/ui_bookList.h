/********************************************************************************
** Form generated from reading UI file 'bookList.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKLIST_H
#define UI_BOOKLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_bookList
{
public:
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *value;
    QTableView *tableView;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *coverLabel;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *ISBN;
    QLabel *name;
    QLabel *author;
    QLabel *genre;
    QLabel *publisher;
    QLabel *price;
    QLabel *quantity;
    QLabel *date;
    QLabel *desc;

    void setupUi(QDialog *bookList)
    {
        if (bookList->objectName().isEmpty())
            bookList->setObjectName("bookList");
        bookList->resize(948, 505);
        frame = new QFrame(bookList);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 581, 481));
        frame->setStyleSheet(QString::fromUtf8("background-color:#e9f5db"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(frame);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        value = new QLineEdit(frame);
        value->setObjectName("value");
        value->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout->addWidget(value);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(frame);
        tableView->setObjectName("tableView");
        tableView->setStyleSheet(QString::fromUtf8("QHeaderView::section { background-color: #e0777d; font: solid}"));
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setHighlightSections(true);
        tableView->verticalHeader()->setVisible(false);
        tableView->verticalHeader()->setHighlightSections(false);

        verticalLayout->addWidget(tableView);


        verticalLayout_2->addLayout(verticalLayout);

        frame_2 = new QFrame(bookList);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(590, 10, 351, 481));
        frame_2->setStyleSheet(QString::fromUtf8("background-color:#e9f5db"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        coverLabel = new QLabel(frame_2);
        coverLabel->setObjectName("coverLabel");
        coverLabel->setFocusPolicy(Qt::StrongFocus);
        coverLabel->setStyleSheet(QString::fromUtf8("background-color: #84A9FF;\n"
"border-color: rgb(0, 0, 0);"));
        coverLabel->setFrameShape(QFrame::Box);
        coverLabel->setFrameShadow(QFrame::Raised);
        coverLabel->setMidLineWidth(1);

        horizontalLayout_2->addWidget(coverLabel);

        horizontalSpacer = new QSpacerItem(138, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        ISBN = new QLabel(frame_2);
        ISBN->setObjectName("ISBN");
        sizePolicy.setHeightForWidth(ISBN->sizePolicy().hasHeightForWidth());
        ISBN->setSizePolicy(sizePolicy);
        ISBN->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(ISBN);

        name = new QLabel(frame_2);
        name->setObjectName("name");
        sizePolicy.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
        name->setSizePolicy(sizePolicy);
        name->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(name);

        author = new QLabel(frame_2);
        author->setObjectName("author");
        sizePolicy.setHeightForWidth(author->sizePolicy().hasHeightForWidth());
        author->setSizePolicy(sizePolicy);
        author->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(author);

        genre = new QLabel(frame_2);
        genre->setObjectName("genre");
        sizePolicy.setHeightForWidth(genre->sizePolicy().hasHeightForWidth());
        genre->setSizePolicy(sizePolicy);
        genre->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(genre);

        publisher = new QLabel(frame_2);
        publisher->setObjectName("publisher");
        sizePolicy.setHeightForWidth(publisher->sizePolicy().hasHeightForWidth());
        publisher->setSizePolicy(sizePolicy);
        publisher->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(publisher);

        price = new QLabel(frame_2);
        price->setObjectName("price");
        sizePolicy.setHeightForWidth(price->sizePolicy().hasHeightForWidth());
        price->setSizePolicy(sizePolicy);
        price->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(price);

        quantity = new QLabel(frame_2);
        quantity->setObjectName("quantity");
        sizePolicy.setHeightForWidth(quantity->sizePolicy().hasHeightForWidth());
        quantity->setSizePolicy(sizePolicy);
        quantity->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(quantity);

        date = new QLabel(frame_2);
        date->setObjectName("date");
        sizePolicy.setHeightForWidth(date->sizePolicy().hasHeightForWidth());
        date->setSizePolicy(sizePolicy);
        date->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(date);

        desc = new QLabel(frame_2);
        desc->setObjectName("desc");
        sizePolicy.setHeightForWidth(desc->sizePolicy().hasHeightForWidth());
        desc->setSizePolicy(sizePolicy);
        desc->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(desc);


        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(bookList);

        QMetaObject::connectSlotsByName(bookList);
    } // setupUi

    void retranslateUi(QDialog *bookList)
    {
        bookList->setWindowTitle(QCoreApplication::translate("bookList", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("bookList", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">Value to search :</span></p></body></html>", nullptr));
        coverLabel->setText(QString());
        ISBN->setText(QCoreApplication::translate("bookList", "<html><head/><body><p><span style=\" font-weight:700;\">ISBN :</span></p></body></html>", nullptr));
        name->setText(QCoreApplication::translate("bookList", "<html><head/><body><p><span style=\" font-weight:700;\">Name :</span></p></body></html>", nullptr));
        author->setText(QCoreApplication::translate("bookList", "<html><head/><body><p><span style=\" font-weight:700;\">Author :</span></p></body></html>", nullptr));
        genre->setText(QCoreApplication::translate("bookList", "<html><head/><body><p><span style=\" font-weight:700;\">Genre :</span></p></body></html>", nullptr));
        publisher->setText(QCoreApplication::translate("bookList", "<html><head/><body><p><span style=\" font-weight:700;\">Publisher :</span></p></body></html>", nullptr));
        price->setText(QCoreApplication::translate("bookList", "<html><head/><body><p><span style=\" font-weight:700;\">Price :</span></p></body></html>", nullptr));
        quantity->setText(QCoreApplication::translate("bookList", "<html><head/><body><p><span style=\" font-weight:700;\">Quantity :</span></p></body></html>", nullptr));
        date->setText(QCoreApplication::translate("bookList", "<html><head/><body><p><span style=\" font-weight:700;\">Date Received :</span></p></body></html>", nullptr));
        desc->setText(QCoreApplication::translate("bookList", "<html><head/><body><p><span style=\" font-weight:700;\">Description :</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bookList: public Ui_bookList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKLIST_H
