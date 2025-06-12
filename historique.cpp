#include "historique.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QLabel>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include <algorithm>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

Historique::Historique(int userId, QSqlDatabase database, QWidget *parent)
    : QDialog(parent), currentUserId(userId), db(database)
{
    // Style général rose/violet pastel
    setWindowTitle("📊 Historique & Statistiques");
    setMinimumSize(800, 650);
    resize(900, 800);
    setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #fbeffb, stop:1 #a18cd1);
            border-radius: 12px;
        }
        QLabel {
            color: #a21caf;
            font-size: 16px;
            font-weight: bold;
            background: transparent;
            border: none;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #fbc2eb, stop:1 #a18cd1);
            color: #7c3aed;
            border-radius: 8px;
            padding: 10px 18px;
            font-size: 15px;
            font-weight: bold;
            min-width: 100px;
            border: none;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #a18cd1, stop:1 #fbc2eb);
            color: #a21caf;
        }
        QTabWidget::pane {
            border: none;
            margin-top: 4px;
        }
        QTabBar::tab {
            background: #fbc2eb;
            color: #a21caf;
            padding: 10px 20px;
            border: none;
            border-top-left-radius: 6px;
            border-top-right-radius: 6px;
            margin-right: 4px;
            font-size: 13px;
            font-weight: 500;
        }
        QTabBar::tab:selected {
            background: #fff0f6;
            color: #a18cd1;
            border-bottom: 3px solid #a18cd1;
        }
        QTabBar::tab:hover {
            background: #fbeffb;
        }
        QTableWidget {
            background-color: #fbeffb;
            border: 1px solid #d291bc;
            border-radius: 8px;
            font-size: 14px;
            color: #7c3aed;
            gridline-color: #fbc2eb;
            alternate-background-color: #fbc2eb;
            selection-background-color: #a18cd1;
            selection-color: #a21caf;
        }
        QHeaderView::section {
            background: #a18cd1;
            color: #fff;
            padding: 12px 16px;
            font-weight: 600;
            border: none;
            border-bottom: 2px solid #fbc2eb;
        }
        QTableWidget::item {
            padding: 12px 16px;
            border-bottom: 1px solid #fbc2eb;
            color: #7c3aed;
        }
        QTableWidget::item:selected {
            background: #a18cd1;
            color: #fff0f6;
        }
    )");

    // Effet d'ombre portée pour la fenêtre
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 60));
    shadowEffect->setOffset(0, 4);
    setGraphicsEffect(shadowEffect);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(20);

    // ------------------- WIDGET DE STATISTIQUES -------------------
    QWidget *statsWidget = new QWidget(this);
    statsWidget->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                               "stop:0 #fbc2eb, stop:1 #a18cd1);"
                               "border-radius: 10px;"
                               "padding: 16px;");

    QHBoxLayout *statsLayout = new QHBoxLayout(statsWidget);
    statsLayout->setContentsMargins(0, 0, 0, 0);
    statsLayout->setSpacing(20);

    // Icône décorative
    QLabel *statsIcon = new QLabel(this);
    statsIcon->setPixmap(QPixmap(":/icons/stats.png").scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    statsLayout->addWidget(statsIcon);

    // Label des statistiques
    labelConnexions = new QLabel(this);
    labelConnexions->setFixedHeight(80);
    labelConnexions->setAlignment(Qt::AlignCenter);
    statsLayout->addWidget(labelConnexions);

    mainLayout->addWidget(statsWidget);

    // ------------------- SYSTEME D'ONGLETS MODERNE -------------------
    QTabWidget *tabWidget = new QTabWidget(this);

    // ------------------- ONGLET EMPRUNTS -------------------
    QWidget *empruntsTab = new QWidget();
    empruntsTab->setStyleSheet("background: white; border-radius: 6px;");

    QVBoxLayout *empruntsLayout = new QVBoxLayout(empruntsTab);
    empruntsLayout->setContentsMargins(0, 0, 0, 0);
    empruntsLayout->setSpacing(0);

    // En-tête du tableau
    QLabel *empruntsHeader = new QLabel("📖 Historique des Emprunts");
    empruntsHeader->setStyleSheet(
        "font-size: 16px;"
        "font-weight: bold;"
        "color: #a18cd1;"
        "padding: 12px 16px;"
        "border-bottom: 1px solid #fbc2eb;");
    empruntsLayout->addWidget(empruntsHeader);

    // Tableau
    tableReservations = new QTableWidget(this);
    setupReservationsTable();

    QScrollArea *tableScroll = new QScrollArea();
    tableScroll->setWidget(tableReservations);
    tableScroll->setWidgetResizable(true);
    tableScroll->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    empruntsLayout->addWidget(tableScroll);

    tabWidget->addTab(empruntsTab, "📚 Emprunts");

    // ------------------- ONGLET STATISTIQUES -------------------
    QWidget *statsTab = new QWidget();
    statsTab->setStyleSheet("background: white; border-radius: 6px;");
    QVBoxLayout *statsTabLayout = new QVBoxLayout(statsTab);
    statsTabLayout->setContentsMargins(0, 0, 0, 0);
    statsTabLayout->setSpacing(0);
    // En-tête des statistiques
    QLabel *chartsHeader = new QLabel("📈 Statistiques d'Utilisation");
    chartsHeader->setStyleSheet(
        "font-size: 16px;"
        "font-weight: bold;"
        "color: #a18cd1;"
        "padding: 12px 16px;"
        "border-bottom: 1px solid #fbc2eb;");
    statsTabLayout->addWidget(chartsHeader);
    QScrollArea *chartsScroll = new QScrollArea();
    chartsScroll->setWidgetResizable(true);
    chartsScroll->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    chartsScroll->setFrameShape(QFrame::NoFrame);
    QWidget *chartsContainer = new QWidget();
    QVBoxLayout *chartsLayout = new QVBoxLayout(chartsContainer);
    chartsLayout->setSpacing(25);
    chartsLayout->setContentsMargins(16, 16, 16, 16);

    QChartView *connexionsChart = createConnexionsChart();
    connexionsChart->setMinimumHeight(350);
    connexionsChart->setStyleSheet("background: white; border-radius: 8px;");
    chartsLayout->addWidget(connexionsChart);

    QChartView *empruntsChart = createEmpruntsChart();
    empruntsChart->setMinimumHeight(350);
    empruntsChart->setStyleSheet("background: white; border-radius: 8px;");
    chartsLayout->addWidget(empruntsChart);

    chartsScroll->setWidget(chartsContainer);
    statsTabLayout->addWidget(chartsScroll);
    tabWidget->addTab(statsTab, "📊 Statistiques");

    mainLayout->addWidget(tabWidget);

    // ------------------- BOUTON DE RETOUR -------------------
    btnRetour = new QPushButton("← Retour", this);
    btnRetour->setCursor(Qt::PointingHandCursor);
    connect(btnRetour, &QPushButton::clicked, this, &Historique::retourArriere);
    mainLayout->insertWidget(0, btnRetour, 0, Qt::AlignLeft);

    // Initialisation avec animation
    QTimer::singleShot(100, this, [this]() {
        chargerDonnees();
        appliquerAnimation(this);
    });
}

Historique::~Historique()
{
    // Libération des ressources si nécessaire
}

void Historique::retourArriere()
{
    this->close();
}

void Historique::setupReservationsTable()
{
    tableReservations->setColumnCount(5);
    tableReservations->setHorizontalHeaderLabels(
        QStringList() << "📅 Date emprunt" << "📚 Livre" << "👤 Utilisateur" << "🔄 Date retour" << "✅ Retour effectif");

    tableReservations->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableReservations->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableReservations->setAlternatingRowColors(true);
    tableReservations->setSelectionMode(QAbstractItemView::SingleSelection);
    tableReservations->setSortingEnabled(true);

    // Configuration responsive des colonnes
    tableReservations->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tableReservations->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableReservations->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Interactive);
    tableReservations->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    tableReservations->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    tableReservations->verticalHeader()->setDefaultSectionSize(48);
    tableReservations->verticalHeader()->setVisible(false);
}

void Historique::chargerDonnees()
{
    chargerEmpruntsFromDB();
    chargerStatsConnexions();
    chargerStatsEmprunts();
}

QChartView* Historique::createConnexionsChart()
{
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Connexions");
    set->setColor(QColor("#a18cd1"));

    QMap<QString, int> data = getConnexionsDataLast7Days();
    QStringList categories;

    for (const auto &[date, count] : data.asKeyValueRange()) {
        *set << count;
        categories << QDate::fromString(date, "yyyy-MM-dd").toString("ddd\ndd");
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Connexions des 7 derniers jours");
    chart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setMargins(QMargins(10, 10, 10, 10));

    // Axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsFont(QFont("Arial", 9));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Nombre");
    axisY->setLabelsFont(QFont("Arial", 9));

    int maxValue = 0;
    for (int i = 0; i < set->count(); ++i) {
        if (set->at(i) > maxValue) maxValue = set->at(i);
    }
    axisY->setRange(0, maxValue * 1.2);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    return chartView;
}

QChartView* Historique::createEmpruntsChart()
{
    QBarSeries *series = new QBarSeries();

    QBarSet *empruntsSet = new QBarSet("Emprunts");
    empruntsSet->setColor(QColor("#fbc2eb"));

    QBarSet *retoursSet = new QBarSet("Retours");
    retoursSet->setColor(QColor("#a18cd1"));

    QMap<QString, int> empruntsData = getEmpruntsDataLast7Days();
    QMap<QString, int> retoursData = getRetoursDataLast7Days();
    QStringList categories;

    QDate currentDate = QDate::currentDate();
    for (int i = 6; i >= 0; --i) {
        QDate date = currentDate.addDays(-i);
        QString dateStr = date.toString("yyyy-MM-dd");
        QString dayStr = date.toString("ddd\ndd");

        *empruntsSet << empruntsData[dateStr];
        *retoursSet << retoursData[dateStr];
        categories << dayStr;
    }

    series->append(empruntsSet);
    series->append(retoursSet);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Emprunts et retours des 7 derniers jours");
    chart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setMargins(QMargins(10, 10, 10, 10));

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsFont(QFont("Arial", 9));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Nombre");
    axisY->setLabelsFont(QFont("Arial", 9));

    int maxValue = 0;
    for (int i = 0; i < empruntsSet->count(); ++i) {
        if (empruntsSet->at(i) > maxValue) maxValue = empruntsSet->at(i);
        if (retoursSet->at(i) > maxValue) maxValue = retoursSet->at(i);
    }
    axisY->setRange(0, maxValue * 1.2);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    return chartView;
}

void Historique::chargerEmpruntsFromDB()
{
    tableReservations->clearContents();
    tableReservations->setRowCount(0);

    QSqlQuery query(db);
    if (!db.isOpen()) {
        qDebug() << "La base de données n'est pas ouverte";
        return;
    }
    query.prepare("SELECT e.borrow_date, b.name, a.username, e.return_date, e.actual_return_date "
                  "FROM emprunts e "
                  "JOIN books b ON e.book_id = b.ID "
                  "JOIN accounts a ON e.user_id = a.ID "
                  "WHERE e.user_id = :userId "
                  "ORDER BY e.borrow_date DESC");
    query.bindValue(":userId", currentUserId);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des emprunts:" << query.lastError().text();
        tableReservations->setRowCount(1);
        tableReservations->setItem(0, 0, new QTableWidgetItem("Erreur de chargement des données"));
        return;
    }
    if (!query.next()) {
        tableReservations->setRowCount(1);
        tableReservations->setItem(0, 0, new QTableWidgetItem("Aucun emprunt trouvé"));
        return;
    }
    do {
        int row = tableReservations->rowCount();
        tableReservations->insertRow(row);

        QDate borrowDate = QDate::fromString(query.value(0).toString(), "yyyy-MM-dd");
        QDate returnDate = QDate::fromString(query.value(3).toString(), "yyyy-MM-dd");
        QDate actualReturnDate = query.value(4).isNull() ? QDate() : QDate::fromString(query.value(4).toString(), "yyyy-MM-dd");

        QTableWidgetItem *borrowItem = new QTableWidgetItem(borrowDate.toString("dd/MM/yyyy"));
        QTableWidgetItem *bookItem = new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *userItem = new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *returnItem = new QTableWidgetItem(returnDate.toString("dd/MM/yyyy"));
        QTableWidgetItem *actualReturnItem = new QTableWidgetItem(
            actualReturnDate.isValid() ? actualReturnDate.toString("dd/MM/yyyy") : "Non retourné");

        // Style pour les retards
        if (actualReturnDate.isNull() && QDate::currentDate() > returnDate) {
            returnItem->setBackground(QColor("#fbc2eb"));
            actualReturnItem->setBackground(QColor("#fbc2eb"));
        } else if (actualReturnDate.isValid() && actualReturnDate > returnDate) {
            actualReturnItem->setBackground(QColor("#a18cd1"));
        }

        borrowItem->setTextAlignment(Qt::AlignCenter);
        bookItem->setTextAlignment(Qt::AlignCenter);
        userItem->setTextAlignment(Qt::AlignCenter);
        returnItem->setTextAlignment(Qt::AlignCenter);
        actualReturnItem->setTextAlignment(Qt::AlignCenter);

        tableReservations->setItem(row, 0, borrowItem);
        tableReservations->setItem(row, 1, bookItem);
        tableReservations->setItem(row, 2, userItem);
        tableReservations->setItem(row, 3, returnItem);
        tableReservations->setItem(row, 4, actualReturnItem);
    } while (query.next());
}

QMap<QString, int> Historique::getConnexionsDataLast7Days()
{
    QMap<QString, int> data;
    QDate currentDate = QDate::currentDate();

    for (int i = 0; i < 7; ++i) {
        data[currentDate.addDays(-i).toString("yyyy-MM-dd")] = 0;
    }

    QSqlQuery query(db);
    query.prepare("SELECT DATE(date_connexion), COUNT(*) "
                  "FROM historique_connexions "
                  "WHERE user_id = :userId "
                  "AND DATE(date_connexion) >= DATE('now', '-6 days') "
                  "GROUP BY DATE(date_connexion)");
    query.bindValue(":userId", currentUserId);

    if (query.exec()) {
        while (query.next()) {
            QString dateStr = query.value(0).toString();
            int count = query.value(1).toInt();
            data[dateStr] = count;
        }
    } else {
        qDebug() << "Erreur lors de la récupération des stats connexions:" << query.lastError().text();
    }

    return data;
}

void Historique::enregistrerConnexion(int userId, QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO historique_connexions (user_id, date_connexion) "
                  "VALUES (:userId, datetime('now'))");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'enregistrement de la connexion:" << query.lastError().text();
    }
}

QMap<QString, int> Historique::getEmpruntsDataLast7Days()
{
    QMap<QString, int> data;
    QDate currentDate = QDate::currentDate();

    for (int i = 0; i < 7; ++i) {
        data[currentDate.addDays(-i).toString("yyyy-MM-dd")] = 0;
    }

    QSqlQuery query(db);
    query.prepare("SELECT DATE(borrow_date), COUNT(*) "
                  "FROM emprunts "
                  "WHERE DATE(borrow_date) >= DATE('now', '-6 days') "
                  "AND user_id = :userId "
                  "GROUP BY DATE(borrow_date)");

    query.bindValue(":userId", currentUserId);

    if (query.exec()) {
        while (query.next()) {
            QString dateStr = query.value(0).toString();
            int count = query.value(1).toInt();
            data[dateStr] = count;
        }
    } else {
        qDebug() << "Erreur lors de la récupération des stats emprunts:" << query.lastError().text();
    }

    return data;
}

QMap<QString, int> Historique::getRetoursDataLast7Days()
{
    QMap<QString, int> data;
    QDate currentDate = QDate::currentDate();

    for (int i = 0; i < 7; ++i) {
        data[currentDate.addDays(-i).toString("yyyy-MM-dd")] = 0;
    }

    QSqlQuery query(db);
    query.prepare("SELECT DATE(actual_return_date), COUNT(*) "
                  "FROM emprunts "
                  "WHERE actual_return_date IS NOT NULL "
                  "AND DATE(actual_return_date) >= DATE('now', '-6 days') "
                  "AND user_id = :userId "
                  "GROUP BY DATE(actual_return_date)");

    query.bindValue(":userId", currentUserId);
    if (query.exec()) {
        while (query.next()) {
            QString dateStr = query.value(0).toString();
            int count = query.value(1).toInt();
            data[dateStr] = count;
        }
    } else {
        qDebug() << "Erreur lors de la récupération des stats retours:" << query.lastError().text();
    }

    return data;
}

void Historique::chargerStatsConnexions()
{
    QMap<QString, int> connexionsData = getConnexionsDataLast7Days();
    int totalConnexions = 0;
    int maxConnexions = 0;
    QString jourMax = "Aucune donnée";

    for (auto it = connexionsData.constBegin(); it != connexionsData.constEnd(); ++it) {
        totalConnexions += it.value();
        if (it.value() > maxConnexions) {
            maxConnexions = it.value();
            jourMax = QDate::fromString(it.key(), "yyyy-MM-dd").toString("dddd dd MMMM");
        }
    }

    QString statsText = QString(
                            "<div style='text-align: center;'>"
                            "<div style='font-size: 16px; color: #a18cd1; font-weight: bold; margin-bottom: 8px;'>"
                            "📊 Statistiques de Connexion"
                            "</div>"
                            "<table style='width: 100%; border-collapse: collapse;'>"
                            "<tr>"
                            "<td style='text-align: center; padding: 5px; border-right: 1px solid #eee;'>"
                            "<div style='font-size: 14px;'><b>Aujourd'hui</b></div>"
                            "<div style='font-size: 18px;'>%1</div>"
                            "</td>"
                            "<td style='text-align: center; padding: 5px; border-right: 1px solid #eee;'>"
                            "<div style='font-size: 14px;'><b>Cette semaine</b></div>"
                            "<div style='font-size: 18px;'>%2</div>"
                            "</td>"
                            "<td style='text-align: center; padding: 5px;'>"
                            "<div style='font-size: 14px;'><b>Pic d'activité</b></div>"
                            "<div style='font-size: 16px;'>%3 le<br>%4</div>"
                            "</td>"
                            "</tr>"
                            "</table>"
                            "</div>"
                            ).arg(connexionsData[QDate::currentDate().toString("yyyy-MM-dd")])
                            .arg(totalConnexions)
                            .arg(maxConnexions)
                            .arg(jourMax);

    labelConnexions->setText(statsText);
    labelConnexions->setTextFormat(Qt::RichText);
    appliquerAnimation(labelConnexions);
}

void Historique::chargerStatsEmprunts()
{
    QMap<QString, int> empruntsData = getEmpruntsDataLast7Days();
    QMap<QString, int> retoursData = getRetoursDataLast7Days();

    int totalEmprunts = 0;
    int totalRetours = 0;
    int maxEmprunts = 0;
    QString jourMax;

    for (auto it = empruntsData.constBegin(); it != empruntsData.constEnd(); ++it) {
        totalEmprunts += it.value();
        if (it.value() > maxEmprunts) {
            maxEmprunts = it.value();
            jourMax = QDate::fromString(it.key(), "yyyy-MM-dd").toString("dddd dd MMMM");
        }
    }

    for (auto it = retoursData.constBegin(); it != retoursData.constEnd(); ++it) {
        totalRetours += it.value();
    }

    QString statsText = QString(
                            "<div style='text-align: center;'>"
                            "<div style='font-size: 16px; color: #a18cd1; font-weight: bold; margin-bottom: 8px;'>"
                            "📊 Statistiques des Emprunts"
                            "</div>"
                            "<table style='width: 100%; border-collapse: collapse;'>"
                            "<tr>"
                            "<td style='text-align: center; padding: 5px; border-right: 1px solid #eee;'>"
                            "<div style='font-size: 14px;'><b>Emprunts aujourd'hui</b></div>"
                            "<div style='font-size: 18px;'>%1</div>"
                            "</td>"
                            "<td style='text-align: center; padding: 5px; border-right: 1px solid #eee;'>"
                            "<div style='font-size: 14px;'><b>Emprunts cette semaine</b></div>"
                            "<div style='font-size: 18px;'>%2</div>"
                            "</td>"
                            "<td style='text-align: center; padding: 5px; border-right: 1px solid #eee;'>"
                            "<div style='font-size: 14px;'><b>Retours cette semaine</b></div>"
                            "<div style='font-size: 18px;'>%3</div>"
                            "</td>"
                            "<td style='text-align: center; padding: 5px;'>"
                            "<div style='font-size: 14px;'><b>Pic d'emprunts</b></div>"
                            "<div style='font-size: 16px;'>%4 le<br>%5</div>"
                            "</td>"
                            "</tr>"
                            "</table>"
                            "</div>"
                            ).arg(empruntsData[QDate::currentDate().toString("yyyy-MM-dd")])
                            .arg(totalEmprunts)
                            .arg(totalRetours)
                            .arg(maxEmprunts)
                            .arg(jourMax);

    labelConnexions->setText(statsText);
    labelConnexions->setTextFormat(Qt::RichText);
}

void Historique::appliquerAnimation(QWidget *widget)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);

    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(600);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
