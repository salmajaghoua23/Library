/********************************************************************************
** Form generated from reading UI file 'addBook.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDBOOK_H
#define UI_ADDBOOK_H

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

class Ui_addBook
{
public:
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLineEdit *ISBN;
    QLabel *label_2;
    QLineEdit *Name;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *chooseAuthBtn;
    QLineEdit *author;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *chooseGenreBtn;
    QComboBox *Genre;
    QLabel *label_5;
    QSpinBox *quantity;
    QLabel *label_6;
    QLineEdit *publisher;
    QLabel *label_7;
    QLineEdit *price;
    QLabel *label_8;
    QDateEdit *date;
    QHBoxLayout *horizontalLayout;
    QPushButton *addBookBtn;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_9;
    QTextEdit *description;
    QLabel *coverLabel;
    QVBoxLayout *verticalLayout;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *selectImgBtn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cancelBtn;

    void setupUi(QDialog *addBook)
    {
        if (addBook->objectName().isEmpty())
            addBook->setObjectName("addBook");
        addBook->resize(890, 723);
        addBook->setStyleSheet(QString::fromUtf8("background: #e9f5db;\n"
"width:30px;\n"
"hieght:30px;"));
        horizontalLayout_5 = new QHBoxLayout(addBook);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        frame = new QFrame(addBook);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(frame);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(label);

        ISBN = new QLineEdit(frame);
        ISBN->setObjectName("ISBN");
        ISBN->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_3->addWidget(ISBN);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(label_2);

        Name = new QLineEdit(frame);
        Name->setObjectName("Name");
        Name->setEnabled(true);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Georgina")});
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setItalic(false);
        Name->setFont(font1);
        Name->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 20pt\"Georgina\";\n"
"height:30px;\n"
"}"));

        verticalLayout_3->addWidget(Name);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(label_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        chooseAuthBtn = new QPushButton(frame);
        chooseAuthBtn->setObjectName("chooseAuthBtn");
        chooseAuthBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 10pt \"Georgia\";\n"
"border-radius:8px;\n"
"padding : 0 8px;\n"
"background: #90a955;\n"
"border -radius:10px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"\n"
"{\n"
"background:#572B788;\n"
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

        horizontalLayout_3->addWidget(chooseAuthBtn);

        author = new QLineEdit(frame);
        author->setObjectName("author");
        author->setEnabled(false);
        author->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout_3->addWidget(author);


        verticalLayout_3->addLayout(horizontalLayout_3);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(label_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        chooseGenreBtn = new QPushButton(frame);
        chooseGenreBtn->setObjectName("chooseGenreBtn");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Georgia")});
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setItalic(false);
        chooseGenreBtn->setFont(font2);
        chooseGenreBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"\n"
"color: rgb(255, 255, 255);\n"
"font: 10pt \"Georgia\";\n"
"border-radius:8px;\n"
"padding : 0 8px;\n"
"background: #90A955;\n"
"border -radius:15px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"\n"
"{\n"
"background:#572B788;\n"
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

        horizontalLayout_4->addWidget(chooseGenreBtn);

        Genre = new QComboBox(frame);
        Genre->setObjectName("Genre");
        Genre->setEnabled(true);
        Genre->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        horizontalLayout_4->addWidget(Genre);


        verticalLayout_3->addLayout(horizontalLayout_4);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(label_5);

        quantity = new QSpinBox(frame);
        quantity->setObjectName("quantity");
        quantity->setStyleSheet(QString::fromUtf8("QSpinBox{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_3->addWidget(quantity);

        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(label_6);

        publisher = new QLineEdit(frame);
        publisher->setObjectName("publisher");
        publisher->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_3->addWidget(publisher);

        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(label_7);

        price = new QLineEdit(frame);
        price->setObjectName("price");
        price->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"     border-radius: 4px;\n"
"color:balck;\n"
"	font: 24px\n"
"}"));

        verticalLayout_3->addWidget(price);

        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("font: 16pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout_3->addWidget(label_8);

        date = new QDateEdit(frame);
        date->setObjectName("date");
        date->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 2px  solid;\n"
"color:black;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));
        date->setCalendarPopup(true);

        verticalLayout_3->addWidget(date);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addBookBtn = new QPushButton(frame);
        addBookBtn->setObjectName("addBookBtn");
        addBookBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"border-radius:10px;\n"
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

        horizontalLayout->addWidget(addBookBtn);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 48, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_5->addWidget(frame);

        frame_2 = new QFrame(addBook);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_9 = new QLabel(frame_2);
        label_9->setObjectName("label_9");
        label_9->setFont(font);
        label_9->setMouseTracking(true);
        label_9->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_2->addWidget(label_9);

        description = new QTextEdit(frame_2);
        description->setObjectName("description");
        description->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"	background-color: rgb(255, 255, 255);\n"
"	 border: 3px  solid;\n"
"     border-radius: 4px;\n"
"	font: 24px\n"
"}"));

        verticalLayout_2->addWidget(description);

        coverLabel = new QLabel(frame_2);
        coverLabel->setObjectName("coverLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(coverLabel->sizePolicy().hasHeightForWidth());
        coverLabel->setSizePolicy(sizePolicy);
        coverLabel->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        coverLabel->setStyleSheet(QString::fromUtf8("background-color: #90A955;\n"
"border-color: rgb(0, 0, 0);"));
        coverLabel->setFrameShape(QFrame::Shape::Box);
        coverLabel->setFrameShadow(QFrame::Shadow::Raised);
        coverLabel->setMidLineWidth(1);

        verticalLayout_2->addWidget(coverLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("font: 16pt \"georgia\";\n"
"color: #e0777d;"));

        verticalLayout->addWidget(label_11);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_3 = new QSpacerItem(98, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        selectImgBtn = new QPushButton(frame_2);
        selectImgBtn->setObjectName("selectImgBtn");
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(144, 169, 85, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush2);
#endif
        selectImgBtn->setPalette(palette);
        selectImgBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"border-radius:10px;\n"
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

        horizontalLayout_6->addWidget(selectImgBtn);

        horizontalSpacer_4 = new QSpacerItem(88, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 48, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        cancelBtn = new QPushButton(frame_2);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 14pt \"georgia\";\n"
"border-radius:10px;\n"
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


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_5->addWidget(frame_2);


        retranslateUi(addBook);

        QMetaObject::connectSlotsByName(addBook);
    } // setupUi

    void retranslateUi(QDialog *addBook)
    {
        addBook->setWindowTitle(QCoreApplication::translate("addBook", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("addBook", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;font-family:'georgia'; font-weight:700; color:#e0777d;\">ISBN :</span></p></body></html>", nullptr));
        ISBN->setText(QString());
        label_2->setText(QCoreApplication::translate("addBook", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;font-family:'georgia'; font-weight:700; color:#e0777d;\">Name :</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("addBook", "\n"
"<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;font-family:'georgia'; font-weight:700; color:#e0777d;\">Author :</span></p></body></html>", nullptr));
        chooseAuthBtn->setText(QCoreApplication::translate("addBook", "Choose Author", nullptr));
        label_4->setText(QCoreApplication::translate("addBook", "\n"
"<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;font-family:'georgia'; font-weight:700; color:#e0777d;\">Genre :</span></p></body></html>", nullptr));
        chooseGenreBtn->setText(QCoreApplication::translate("addBook", "Choose Genre", nullptr));
        label_5->setText(QCoreApplication::translate("addBook", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;font-family:'georgia'; font-weight:700; color:#e0777d;\">Quantity :</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("addBook", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;font-family:'georgia'; font-weight:700; color:#e0777d;\">Publisher :</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("addBook", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;font-family:'georgia'; font-weight:700; color:#e0777d;\">Price :</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("addBook", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">Date</span></p></body></html>", nullptr));
        addBookBtn->setText(QCoreApplication::translate("addBook", "Add Book", nullptr));
        label_9->setText(QCoreApplication::translate("addBook", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;font-family:'georgia'; font-weight:700; color:#e0777d;\">Book Description :</span></p></body></html>", nullptr));
        coverLabel->setText(QString());
        label_11->setText(QCoreApplication::translate("addBook", "<html><head/><body><p><span style=\" font-weight:700;\">Book Cover</span></p></body></html>", nullptr));
        selectImgBtn->setText(QCoreApplication::translate("addBook", "Select Image", nullptr));
        cancelBtn->setText(QCoreApplication::translate("addBook", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addBook: public Ui_addBook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDBOOK_H
