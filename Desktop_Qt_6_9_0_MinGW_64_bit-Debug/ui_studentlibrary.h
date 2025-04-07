/********************************************************************************
** Form generated from reading UI file 'studentlibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTLIBRARY_H
#define UI_STUDENTLIBRARY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_studentLibrary
{
public:
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QTableView *bookListView;
    QLabel *label;
    QPushButton *addToCartButton;
    QPushButton *borrowButton;
    QLabel *bookDetailsText;

    void setupUi(QWidget *studentLibrary)
    {
        if (studentLibrary->objectName().isEmpty())
            studentLibrary->setObjectName("studentLibrary");
        studentLibrary->resize(698, 575);
        studentLibrary->setStyleSheet(QString::fromUtf8("background-color: #ebf5df"));
        searchLineEdit = new QLineEdit(studentLibrary);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setGeometry(QRect(20, 70, 501, 51));
        searchLineEdit->setStyleSheet(QString::fromUtf8("background:#FF69B4;border-radius:20px;"));
        searchButton = new QPushButton(studentLibrary);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(540, 70, 111, 51));
        searchButton->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background:pink; color:#FF1493; font-size:20px ;font: 63 14pt \"georgia\";"));
        bookListView = new QTableView(studentLibrary);
        bookListView->setObjectName("bookListView");
        bookListView->setGeometry(QRect(10, 140, 631, 371));
        bookListView->setStyleSheet(QString::fromUtf8("background:white;color:balck;font-size:10px;"));
        label = new QLabel(studentLibrary);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 0, 581, 61));
        addToCartButton = new QPushButton(studentLibrary);
        addToCartButton->setObjectName("addToCartButton");
        addToCartButton->setGeometry(QRect(400, 460, 101, 41));
        addToCartButton->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background:pink; color:#3498DB; font-size:20px ;font: 63 14pt \"georgia\";"));
        borrowButton = new QPushButton(studentLibrary);
        borrowButton->setObjectName("borrowButton");
        borrowButton->setGeometry(QRect(530, 460, 101, 41));
        borrowButton->setStyleSheet(QString::fromUtf8("border-radius:20px;\n"
"background:pink; color:#3498DB; font-size:20px ;font: 63 14pt \"georgia\";"));
        bookDetailsText = new QLabel(studentLibrary);
        bookDetailsText->setObjectName("bookDetailsText");
        bookDetailsText->setGeometry(QRect(20, 350, 171, 41));
        bookDetailsText->setStyleSheet(QString::fromUtf8("color:black; background:white;"));

        retranslateUi(studentLibrary);

        QMetaObject::connectSlotsByName(studentLibrary);
    } // setupUi

    void retranslateUi(QWidget *studentLibrary)
    {
        studentLibrary->setWindowTitle(QCoreApplication::translate("studentLibrary", "Form", nullptr));
        searchButton->setText(QCoreApplication::translate("studentLibrary", "Searche", nullptr));
        label->setText(QCoreApplication::translate("studentLibrary", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:#3498db;\">&quot;The user can search for books and view their details.&quot; </span></p></body></html>", nullptr));
        addToCartButton->setText(QCoreApplication::translate("studentLibrary", "Add to cart", nullptr));
        borrowButton->setText(QCoreApplication::translate("studentLibrary", "Emprunter", nullptr));
        bookDetailsText->setText(QCoreApplication::translate("studentLibrary", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700; color:#55007f;\">Label de d\303\251tails ::</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class studentLibrary: public Ui_studentLibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTLIBRARY_H
