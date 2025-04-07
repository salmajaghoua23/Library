/********************************************************************************
** Form generated from reading UI file 'editBook.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITBOOK_H
#define UI_EDITBOOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_editBook
{
public:
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *ISBN;
    QPushButton *searchBtn;
    QLabel *label_2;
    QLineEdit *name;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *author;
    QPushButton *changeAuthorBtn;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *changeGenreBtn;
    QComboBox *genre;
    QLabel *label_5;
    QSpinBox *quantity;
    QLabel *label_6;
    QLineEdit *publisher;
    QLabel *label_7;
    QLineEdit *price;
    QLabel *label_8;
    QDateEdit *date;
    QPushButton *editBookBtn;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_10;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_11;
    QTextEdit *description;
    QLabel *coverLabel;
    QPushButton *selectImgBtn;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *editBook)
    {
        if (editBook->objectName().isEmpty())
            editBook->setObjectName("editBook");
        editBook->resize(705, 725);
        editBook->setStyleSheet(QString::fromUtf8("background-color:#e9f5db"));
        horizontalLayout_5 = new QHBoxLayout(editBook);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        frame = new QFrame(editBook);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        ISBN = new QLineEdit(frame);
        ISBN->setObjectName("ISBN");
        ISBN->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout_3->addWidget(ISBN);


        verticalLayout->addLayout(horizontalLayout_3);

        searchBtn = new QPushButton(frame);
        searchBtn->setObjectName("searchBtn");
        searchBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"padding : 0 8px;\n"
"background: #90a955;\n"
"border-radius:10px;\n"
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

        verticalLayout->addWidget(searchBtn);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout->addWidget(label_2);

        name = new QLineEdit(frame);
        name->setObjectName("name");
        name->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout->addWidget(name);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout->addWidget(label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        author = new QLineEdit(frame);
        author->setObjectName("author");
        author->setEnabled(false);
        author->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout_4->addWidget(author);


        verticalLayout->addLayout(horizontalLayout_4);

        changeAuthorBtn = new QPushButton(frame);
        changeAuthorBtn->setObjectName("changeAuthorBtn");
        changeAuthorBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"padding : 0 8px;\n"
"background: #90a955;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"\n"
"{\n"
"background:#e9f5db;\n"
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

        verticalLayout->addWidget(changeAuthorBtn);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout->addWidget(label_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        changeGenreBtn = new QPushButton(frame);
        changeGenreBtn->setObjectName("changeGenreBtn");
        changeGenreBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 10pt \"georgia\";\n"
"padding : 0 8px;\n"
"background: #90a955;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"\n"
"{\n"
"background:#e9f5db;\n"
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

        horizontalLayout_6->addWidget(changeGenreBtn);


        verticalLayout->addLayout(horizontalLayout_6);

        genre = new QComboBox(frame);
        genre->setObjectName("genre");
        genre->setEnabled(true);
        genre->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout->addWidget(genre);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout->addWidget(label_5);

        quantity = new QSpinBox(frame);
        quantity->setObjectName("quantity");
        quantity->setStyleSheet(QString::fromUtf8("QSpinBox{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));
        quantity->setMaximum(1000000);
        quantity->setDisplayIntegerBase(10);

        verticalLayout->addWidget(quantity);

        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout->addWidget(label_6);

        publisher = new QLineEdit(frame);
        publisher->setObjectName("publisher");
        publisher->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout->addWidget(publisher);

        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout->addWidget(label_7);

        price = new QLineEdit(frame);
        price->setObjectName("price");
        price->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout->addWidget(price);

        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout->addWidget(label_8);

        date = new QDateEdit(frame);
        date->setObjectName("date");
        date->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));
        date->setCalendarPopup(true);

        verticalLayout->addWidget(date);

        editBookBtn = new QPushButton(frame);
        editBookBtn->setObjectName("editBookBtn");
        editBookBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"color: #ffffff;\n"
"border-radius:10px;\n"
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

        verticalLayout->addWidget(editBookBtn);


        horizontalLayout_5->addWidget(frame);

        frame_2 = new QFrame(editBook);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_2->addWidget(label_10);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("font: 14pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(label_11);

        description = new QTextEdit(frame_2);
        description->setObjectName("description");
        description->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 1px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_3->addWidget(description);

        coverLabel = new QLabel(frame_2);
        coverLabel->setObjectName("coverLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(coverLabel->sizePolicy().hasHeightForWidth());
        coverLabel->setSizePolicy(sizePolicy);
        coverLabel->setFocusPolicy(Qt::StrongFocus);
        coverLabel->setStyleSheet(QString::fromUtf8("background-color: #90a955;\n"
"border-color: rgb(0, 0, 0);"));
        coverLabel->setFrameShape(QFrame::Box);
        coverLabel->setFrameShadow(QFrame::Raised);
        coverLabel->setMidLineWidth(1);

        verticalLayout_3->addWidget(coverLabel);


        verticalLayout_2->addLayout(verticalLayout_3);

        selectImgBtn = new QPushButton(frame_2);
        selectImgBtn->setObjectName("selectImgBtn");
        selectImgBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"border-radius:10px;\n"
"padding : 0 8px;\n"
"background: #90a955;\n"
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

        verticalLayout_2->addWidget(selectImgBtn);

        verticalSpacer = new QSpacerItem(20, 48, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        cancelBtn = new QPushButton(frame_2);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"padding : 0 8px;\n"
"background: #90a955;\n"
"border-radius:10px;\n"
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

        horizontalLayout_2->addWidget(cancelBtn);

        horizontalSpacer_2 = new QSpacerItem(208, 23, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_5->addWidget(frame_2);


        retranslateUi(editBook);

        QMetaObject::connectSlotsByName(editBook);
    } // setupUi

    void retranslateUi(QDialog *editBook)
    {
        editBook->setWindowTitle(QCoreApplication::translate("editBook", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("editBook", "<html><head/><body><p><span style=\" font-weight:700;\">ISBN</span></p></body></html>", nullptr));
        searchBtn->setText(QCoreApplication::translate("editBook", "Search", nullptr));
        label_2->setText(QCoreApplication::translate("editBook", "<html><head/><body><p><span style=\" font-weight:700;\">Name</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("editBook", "<html><head/><body><p><span style=\" font-weight:700;\">Author</span></p></body></html>", nullptr));
        changeAuthorBtn->setText(QCoreApplication::translate("editBook", "Change Author", nullptr));
        label_4->setText(QCoreApplication::translate("editBook", "<html><head/><body><p><span style=\" font-weight:700;\">Genre</span></p></body></html>", nullptr));
        changeGenreBtn->setText(QCoreApplication::translate("editBook", "Change Genre", nullptr));
        label_5->setText(QCoreApplication::translate("editBook", "<html><head/><body><p><span style=\" font-weight:700;\">Quantity</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("editBook", "<html><head/><body><p><span style=\" font-weight:700;\">Pusblisher</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("editBook", "<html><head/><body><p><span style=\" font-weight:700;\">Price</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("editBook", "<html><head/><body><p><span style=\" font-weight:700;\">Date</span></p></body></html>", nullptr));
        editBookBtn->setText(QCoreApplication::translate("editBook", "Edit Book", nullptr));
        label_10->setText(QCoreApplication::translate("editBook", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">Book Description</span></p></body></html>", nullptr));
        label_11->setText(QCoreApplication::translate("editBook", "<html><head/><body><p><span style=\" font-weight:700;\">Book Cover</span></p></body></html>", nullptr));
        coverLabel->setText(QString());
        selectImgBtn->setText(QCoreApplication::translate("editBook", "Select Image", nullptr));
        cancelBtn->setText(QCoreApplication::translate("editBook", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editBook: public Ui_editBook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITBOOK_H
