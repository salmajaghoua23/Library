/********************************************************************************
** Form generated from reading UI file 'digitalLibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIGITALLIBRARY_H
#define UI_DIGITALLIBRARY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_digitalLibrary
{
public:
    QVBoxLayout *verticalLayout_10;
    QFrame *frame_4;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_23;
    QHBoxLayout *horizontalLayout_22;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLabel *username;
    QHBoxLayout *horizontalLayout_21;
    QFrame *frame_9;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_24;
    QLabel *bookNum;
    QSpacerItem *horizontalSpacer_19;
    QFrame *frame_8;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_20;
    QLabel *memberNum;
    QSpacerItem *horizontalSpacer_21;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_20;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_13;
    QLabel *authorNum;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *manageGenre;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_18;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *manageAuthorButton;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_16;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *addMemberBtn;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *editMemberBtn;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *deleteMemberBtn;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *membersListBtn;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *addBookBtn;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *editBookBtn;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *deleteBookBtn;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *booksListBtn;
    QFrame *frame_5;
    QPushButton *statsButton;
    QFrame *frame_7;
    QPushButton *statsButton_2;
    QFrame *frame_10;
    QPushButton *testDataButton;
    QFrame *frame_11;
    QPushButton *statsButton_4;

    void setupUi(QDialog *digitalLibrary)
    {
        if (digitalLibrary->objectName().isEmpty())
            digitalLibrary->setObjectName("digitalLibrary");
        digitalLibrary->resize(850, 825);
        verticalLayout_10 = new QVBoxLayout(digitalLibrary);
        verticalLayout_10->setObjectName("verticalLayout_10");
        frame_4 = new QFrame(digitalLibrary);
        frame_4->setObjectName("frame_4");
        frame_4->setStyleSheet(QString::fromUtf8("background-color: #ebf5df"));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        frame_3 = new QFrame(frame_4);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(238, 13, 577, 631));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: #ebf5df;\n"
""));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName("horizontalLayout_22");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8(""));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));

        horizontalLayout->addWidget(label_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        frame_2 = new QFrame(frame_3);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #e9f5db;\n"
"border-radius: 10px;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_15 = new QVBoxLayout(frame_2);
        verticalLayout_15->setObjectName("verticalLayout_15");

        verticalLayout_2->addWidget(frame_2);

        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font: 63 18pt \"Comic Sans MS\";\n"
"color: rgb(255, 255, 255);\n"
"font-weight: bold;"));

        verticalLayout_2->addWidget(label_4);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_22->addLayout(horizontalLayout);

        label = new QLabel(frame_3);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 10pt \"georgia\";"));

        horizontalLayout_22->addWidget(label);

        username = new QLabel(frame_3);
        username->setObjectName("username");
        username->setStyleSheet(QString::fromUtf8("color: #90a955;\n"
"font: 20pt \"georgia\";"));

        horizontalLayout_22->addWidget(username);


        horizontalLayout_23->addLayout(horizontalLayout_22);


        verticalLayout_3->addLayout(horizontalLayout_23);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        frame_9 = new QFrame(frame_3);
        frame_9->setObjectName("frame_9");
        frame_9->setStyleSheet(QString::fromUtf8("background-color: #e0777d;\n"
"border-radius: 10px;"));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_12 = new QVBoxLayout(frame_9);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName("verticalLayout_13");
        label_24 = new QLabel(frame_9);
        label_24->setObjectName("label_24");
        label_24->setStyleSheet(QString::fromUtf8("font: 63 18pt \"georgia\";\n"
"color: rgb(255, 255, 255);\n"
"font-weight: bold;"));
        label_24->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_13->addWidget(label_24);

        bookNum = new QLabel(frame_9);
        bookNum->setObjectName("bookNum");
        bookNum->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 63 24pt \"georgia\";\n"
""));
        bookNum->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_13->addWidget(bookNum);


        verticalLayout_12->addLayout(verticalLayout_13);


        horizontalLayout_21->addWidget(frame_9);

        horizontalSpacer_19 = new QSpacerItem(13, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_19);

        frame_8 = new QFrame(frame_3);
        frame_8->setObjectName("frame_8");
        frame_8->setStyleSheet(QString::fromUtf8("background-color: #e0777d;\n"
"border-radius: 8px;"));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_8);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_20 = new QLabel(frame_8);
        label_20->setObjectName("label_20");
        label_20->setStyleSheet(QString::fromUtf8("font: 63 18pt \"georgia\";\n"
"color: rgb(255, 255, 255);\n"
"font-weight: bold;"));
        label_20->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_8->addWidget(label_20);

        memberNum = new QLabel(frame_8);
        memberNum->setObjectName("memberNum");
        memberNum->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 63 24pt \"georgia\";\n"
""));
        memberNum->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_8->addWidget(memberNum);


        verticalLayout_9->addLayout(verticalLayout_8);


        horizontalLayout_21->addWidget(frame_8);

        horizontalSpacer_21 = new QSpacerItem(13, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_21);

        frame_6 = new QFrame(frame_3);
        frame_6->setObjectName("frame_6");
        frame_6->setStyleSheet(QString::fromUtf8("background-color: #e0777d;\n"
"border-radius: 8px;"));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_20 = new QHBoxLayout(frame_6);
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_13 = new QLabel(frame_6);
        label_13->setObjectName("label_13");
        label_13->setStyleSheet(QString::fromUtf8("font: 63 18pt \"georgia\";\n"
"color: rgb(255, 255, 255);\n"
"font-weight: bold;"));
        label_13->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(label_13);

        authorNum = new QLabel(frame_6);
        authorNum->setObjectName("authorNum");
        authorNum->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 63 24pt \"georgia\";\n"
""));
        authorNum->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(authorNum);


        horizontalLayout_20->addLayout(verticalLayout_7);


        horizontalLayout_21->addWidget(frame_6);


        verticalLayout_3->addLayout(horizontalLayout_21);

        frame = new QFrame(frame_4);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 0, 221, 581));
        frame->setStyleSheet(QString::fromUtf8("background-color: #c1fba4;\n"
"border-radius:8px"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("font: 63 20 pt \"georgia\";\n"
"color:#bc4749;"));

        horizontalLayout_3->addWidget(label_5);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        manageGenre = new QPushButton(frame);
        manageGenre->setObjectName("manageGenre");
        manageGenre->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        manageGenre->setAutoDefault(false);
        manageGenre->setFlat(true);

        horizontalLayout_5->addWidget(manageGenre);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_18 = new QSpacerItem(18, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_18);

        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("font: 63 14pt \"georgia\";\n"
"color: #e0777d;"));

        horizontalLayout_4->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_4 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        manageAuthorButton = new QPushButton(frame);
        manageAuthorButton->setObjectName("manageAuthorButton");
        manageAuthorButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        manageAuthorButton->setAutoDefault(false);
        manageAuthorButton->setFlat(true);

        horizontalLayout_6->addWidget(manageAuthorButton);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        horizontalSpacer_16 = new QSpacerItem(18, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_16);

        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("font: 63 12pt \"georgia\";\n"
"color: #e0777d;"));

        horizontalLayout_17->addWidget(label_7);


        verticalLayout->addLayout(horizontalLayout_17);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_5 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        addMemberBtn = new QPushButton(frame);
        addMemberBtn->setObjectName("addMemberBtn");
        addMemberBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        addMemberBtn->setAutoDefault(false);
        addMemberBtn->setFlat(true);

        horizontalLayout_7->addWidget(addMemberBtn);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_6 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_6);

        editMemberBtn = new QPushButton(frame);
        editMemberBtn->setObjectName("editMemberBtn");
        editMemberBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        editMemberBtn->setAutoDefault(false);
        editMemberBtn->setFlat(true);

        horizontalLayout_8->addWidget(editMemberBtn);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer_7 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);

        deleteMemberBtn = new QPushButton(frame);
        deleteMemberBtn->setObjectName("deleteMemberBtn");
        deleteMemberBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        deleteMemberBtn->setAutoDefault(false);
        deleteMemberBtn->setFlat(true);

        horizontalLayout_9->addWidget(deleteMemberBtn);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer_8 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_8);

        membersListBtn = new QPushButton(frame);
        membersListBtn->setObjectName("membersListBtn");
        membersListBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        membersListBtn->setAutoDefault(false);
        membersListBtn->setFlat(true);

        horizontalLayout_10->addWidget(membersListBtn);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        horizontalSpacer_11 = new QSpacerItem(18, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_11);

        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("font: 63 12pt \"georgia\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_18->addWidget(label_8);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalSpacer_9 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_9);

        addBookBtn = new QPushButton(frame);
        addBookBtn->setObjectName("addBookBtn");
        addBookBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        addBookBtn->setAutoDefault(false);
        addBookBtn->setFlat(true);

        horizontalLayout_11->addWidget(addBookBtn);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalSpacer_10 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_10);

        editBookBtn = new QPushButton(frame);
        editBookBtn->setObjectName("editBookBtn");
        editBookBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        editBookBtn->setAutoDefault(false);
        editBookBtn->setFlat(true);

        horizontalLayout_12->addWidget(editBookBtn);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalSpacer_12 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        deleteBookBtn = new QPushButton(frame);
        deleteBookBtn->setObjectName("deleteBookBtn");
        deleteBookBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        deleteBookBtn->setAutoDefault(false);
        deleteBookBtn->setFlat(true);

        horizontalLayout_13->addWidget(deleteBookBtn);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        horizontalSpacer_13 = new QSpacerItem(28, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_13);

        booksListBtn = new QPushButton(frame);
        booksListBtn->setObjectName("booksListBtn");
        booksListBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        booksListBtn->setAutoDefault(false);
        booksListBtn->setFlat(true);

        horizontalLayout_14->addWidget(booksListBtn);


        verticalLayout->addLayout(horizontalLayout_14);

        frame_5 = new QFrame(frame_4);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 580, 221, 31));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: #c1fba4;\n"
"border-radius:8px"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        statsButton = new QPushButton(frame_5);
        statsButton->setObjectName("statsButton");
        statsButton->setGeometry(QRect(30, 10, 175, 16));
        statsButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        statsButton->setAutoDefault(false);
        statsButton->setFlat(true);
        frame_7 = new QFrame(frame_5);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(10, 30, 221, 41));
        frame_7->setStyleSheet(QString::fromUtf8("background-color: #c1fba4;\n"
"border-radius:8px"));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        statsButton_2 = new QPushButton(frame_7);
        statsButton_2->setObjectName("statsButton_2");
        statsButton_2->setGeometry(QRect(30, 10, 175, 16));
        statsButton_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        statsButton_2->setAutoDefault(false);
        statsButton_2->setFlat(true);
        frame_10 = new QFrame(frame_4);
        frame_10->setObjectName("frame_10");
        frame_10->setGeometry(QRect(10, 610, 221, 31));
        frame_10->setStyleSheet(QString::fromUtf8("background-color: #c1fba4;\n"
"border-radius:8px"));
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        testDataButton = new QPushButton(frame_10);
        testDataButton->setObjectName("testDataButton");
        testDataButton->setGeometry(QRect(30, 6, 181, 20));
        testDataButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        testDataButton->setAutoDefault(false);
        testDataButton->setFlat(true);
        frame_11 = new QFrame(frame_10);
        frame_11->setObjectName("frame_11");
        frame_11->setGeometry(QRect(10, 30, 221, 41));
        frame_11->setStyleSheet(QString::fromUtf8("background-color: #c1fba4;\n"
"border-radius:8px"));
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        statsButton_4 = new QPushButton(frame_11);
        statsButton_4->setObjectName("statsButton_4");
        statsButton_4->setGeometry(QRect(30, 10, 175, 16));
        statsButton_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font: 63 14pt \"georgia\";\n"
"color: #e0777d;\n"
"padding : 0 8px;\n"
"\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background:#036666;\n"
"border-radius:5px;\n"
"}"));
        statsButton_4->setAutoDefault(false);
        statsButton_4->setFlat(true);

        verticalLayout_10->addWidget(frame_4);


        retranslateUi(digitalLibrary);

        manageGenre->setDefault(false);
        manageAuthorButton->setDefault(false);
        addMemberBtn->setDefault(false);
        editMemberBtn->setDefault(false);
        deleteMemberBtn->setDefault(false);
        membersListBtn->setDefault(false);
        addBookBtn->setDefault(false);
        editBookBtn->setDefault(false);
        deleteBookBtn->setDefault(false);
        booksListBtn->setDefault(false);
        statsButton->setDefault(false);
        statsButton_2->setDefault(false);
        testDataButton->setDefault(false);
        statsButton_4->setDefault(false);


        QMetaObject::connectSlotsByName(digitalLibrary);
    } // setupUi

    void retranslateUi(QDialog *digitalLibrary)
    {
        digitalLibrary->setWindowTitle(QCoreApplication::translate("digitalLibrary", "Dialog", nullptr));
        label_3->setText(QString());
        label_4->setText(QCoreApplication::translate("digitalLibrary", "<html><head/><body><p><span style=\" color:#e0777d;font-family:georgia;\">Froggy</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("digitalLibrary", "<html><head/><body><p align=\"right\"><span style=\" font-size:16pt; font-weight:700;\">                                                Welcome Back</span></p></body></html>", nullptr));
        username->setText(QCoreApplication::translate("digitalLibrary", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:700; font-style:italic; color:#bc4749;\">[+username]</span></p></body></html>", nullptr));
        label_24->setText(QCoreApplication::translate("digitalLibrary", "Books", nullptr));
        bookNum->setText(QCoreApplication::translate("digitalLibrary", "50", nullptr));
        label_20->setText(QCoreApplication::translate("digitalLibrary", "Members", nullptr));
        memberNum->setText(QCoreApplication::translate("digitalLibrary", "22", nullptr));
        label_13->setText(QCoreApplication::translate("digitalLibrary", "Authors", nullptr));
        authorNum->setText(QCoreApplication::translate("digitalLibrary", "7", nullptr));
        label_5->setText(QCoreApplication::translate("digitalLibrary", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:700; font-style:italic; color:#bc4749;\">Genres</span></p></body></html>", nullptr));
        manageGenre->setText(QCoreApplication::translate("digitalLibrary", "Manage Genres", nullptr));
        label_6->setText(QCoreApplication::translate("digitalLibrary", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:700; font-style:italic; color:#bc4749;\">Authors</span></p></body></html>", nullptr));
        manageAuthorButton->setText(QCoreApplication::translate("digitalLibrary", "Manage Authors", nullptr));
        label_7->setText(QCoreApplication::translate("digitalLibrary", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:700; font-style:italic; color:#bc4749;\">Members</span></p></body></html>", nullptr));
        addMemberBtn->setText(QCoreApplication::translate("digitalLibrary", "Add Member", nullptr));
        editMemberBtn->setText(QCoreApplication::translate("digitalLibrary", "Edit Member", nullptr));
        deleteMemberBtn->setText(QCoreApplication::translate("digitalLibrary", "Delete Member", nullptr));
        membersListBtn->setText(QCoreApplication::translate("digitalLibrary", "Members List", nullptr));
        label_8->setText(QCoreApplication::translate("digitalLibrary", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:700; font-style:italic; color:#bc4749;\">Books</span></p></body></html>", nullptr));
        addBookBtn->setText(QCoreApplication::translate("digitalLibrary", "Add Book", nullptr));
        editBookBtn->setText(QCoreApplication::translate("digitalLibrary", "Edit Book", nullptr));
        deleteBookBtn->setText(QCoreApplication::translate("digitalLibrary", "Delete Book", nullptr));
        booksListBtn->setText(QCoreApplication::translate("digitalLibrary", "Books List", nullptr));
        statsButton->setText(QCoreApplication::translate("digitalLibrary", "Statistic", nullptr));
        statsButton_2->setText(QCoreApplication::translate("digitalLibrary", "Statistic", nullptr));
        testDataButton->setText(QCoreApplication::translate("digitalLibrary", "test", nullptr));
        statsButton_4->setText(QCoreApplication::translate("digitalLibrary", "Statistic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class digitalLibrary: public Ui_digitalLibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIGITALLIBRARY_H
