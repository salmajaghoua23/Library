/********************************************************************************
** Form generated from reading UI file 'stats.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATS_H
#define UI_STATS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stats
{
public:
    QLabel *label;
    QLabel *label_2;
    QWidget *popularityChartContainer;
    QWidget *quantityChartContainer;
    QPushButton *backButton;

    void setupUi(QWidget *stats)
    {
        if (stats->objectName().isEmpty())
            stats->setObjectName("stats");
        stats->resize(529, 353);
        stats->setStyleSheet(QString::fromUtf8("background:beige;"));
        label = new QLabel(stats);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 191, 41));
        label->setStyleSheet(QString::fromUtf8("color:black; font-size:20px;"));
        label_2 = new QLabel(stats);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 20, 221, 41));
        label_2->setStyleSheet(QString::fromUtf8("color:black; font-size:20px;"));
        popularityChartContainer = new QWidget(stats);
        popularityChartContainer->setObjectName("popularityChartContainer");
        popularityChartContainer->setGeometry(QRect(10, 60, 241, 191));
        popularityChartContainer->setStyleSheet(QString::fromUtf8("background:white;"));
        quantityChartContainer = new QWidget(stats);
        quantityChartContainer->setObjectName("quantityChartContainer");
        quantityChartContainer->setGeometry(QRect(260, 60, 241, 191));
        quantityChartContainer->setStyleSheet(QString::fromUtf8("background:white;"));
        backButton = new QPushButton(stats);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(360, 260, 91, 41));
        backButton->setStyleSheet(QString::fromUtf8("border-raidus:20px; color:black;"));

        retranslateUi(stats);

        QMetaObject::connectSlotsByName(stats);
    } // setupUi

    void retranslateUi(QWidget *stats)
    {
        stats->setWindowTitle(QCoreApplication::translate("stats", "Form", nullptr));
        label->setText(QCoreApplication::translate("stats", "Popularit\303\251 des livres", nullptr));
        label_2->setText(QCoreApplication::translate("stats", "Quantit\303\251 par cat\303\251gorie", nullptr));
        backButton->setText(QCoreApplication::translate("stats", "Retourn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stats: public Ui_stats {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATS_H
