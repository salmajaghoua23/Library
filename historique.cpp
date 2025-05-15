#include "historique.h"
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
#include <algorithm>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

Historique::Historique(QWidget *parent) : QDialog(parent)
{
    // Configuration de la fenêtre principale
    setWindowTitle("Historique et Statistiques");
    setMinimumSize(600, 600);  // Taille minimale
    resize(900, 750);         // Taille initiale recommandée
    setStyleSheet("background-color: #f5f7fa;");

    // Layout principal avec marges réduites
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(12);

    // Label des statistiques (taille fixe)
    labelConnexions = new QLabel(this);
    labelConnexions->setFixedHeight(70);
    labelConnexions->setAlignment(Qt::AlignCenter);
    labelConnexions->setStyleSheet(
        "background: white;"
        "border-radius: 8px;"
        "padding: 10px;"
        "border: 1px solid #dfe3e8;"
        "font-size: 14px;"
        );
    mainLayout->addWidget(labelConnexions);

    // Configuration des onglets
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setStyleSheet(
        "QTabBar::tab {"
        "   padding: 8px 12px;"
        "   background: #f0f2f5;"
        "   border: 1px solid #dfe3e8;"
        "   border-bottom: none;"
        "   border-top-left-radius: 4px;"
        "   border-top-right-radius: 4px;"
        "}"
        "QTabBar::tab:selected {"
        "   background: white;"
        "   border-color: #d1d9e6;"
        "}"
        "QTabWidget::pane {"
        "   border: 1px solid #dfe3e8;"
        "   border-top: none;"
        "   border-radius: 0 0 4px 4px;"
        "   background: white;"
        "}"
        );

    /* ------------------- ONGLET RÉSERVATIONS ------------------- */
    QWidget *reservationsTab = new QWidget();
    QVBoxLayout *reservationsLayout = new QVBoxLayout(reservationsTab);
    reservationsLayout->setContentsMargins(0, 0, 0, 0);

    // Configuration du tableau avec scroll area
    tableReservations = new QTableWidget(this);
    setupReservationsTable();

    QScrollArea *tableScroll = new QScrollArea();
    tableScroll->setWidget(tableReservations);
    tableScroll->setWidgetResizable(true);
    tableScroll->setFrameShape(QFrame::NoFrame);
    reservationsLayout->addWidget(tableScroll);

    tabWidget->addTab(reservationsTab, "📚 Réservations");

    /* ------------------- ONGLET STATISTIQUES ------------------- */
    QWidget *statsTab = new QWidget();
    QVBoxLayout *statsLayout = new QVBoxLayout(statsTab);
    statsLayout->setContentsMargins(0, 0, 0, 0);
    statsLayout->setSpacing(15);

    // Conteneur scrollable pour les graphiques
    QScrollArea *chartsScroll = new QScrollArea();
    chartsScroll->setWidgetResizable(true);
    chartsScroll->setFrameShape(QFrame::NoFrame);

    QWidget *chartsContainer = new QWidget();
    QVBoxLayout *chartsLayout = new QVBoxLayout(chartsContainer);
    chartsLayout->setSpacing(20);
    chartsLayout->setContentsMargins(10, 10, 10, 10);

    // Graphique des connexions
    QChartView *connexionsChart = createConnexionsChart();
    connexionsChart->setMinimumHeight(300);
    chartsLayout->addWidget(connexionsChart);

    // Graphique des réservations
    QChartView *reservationsChart = createReservationsChart();
    reservationsChart->setMinimumHeight(300);
    chartsLayout->addWidget(reservationsChart);

    chartsScroll->setWidget(chartsContainer);
    statsLayout->addWidget(chartsScroll);
    tabWidget->addTab(statsTab, "📊 Statistiques");

    mainLayout->addWidget(tabWidget);

    // Initialisation
    initReservationFile();
    chargerDonnees();
}

Historique::~Historique()
{
    // Libération des ressources si nécessaire
}

void Historique::setupReservationsTable()
{
    tableReservations->setColumnCount(3);
    tableReservations->setHorizontalHeaderLabels(
        QStringList() << "Date/Heure" << "Livre" << "Utilisateur");

    // Style optimisé pour le tableau
    tableReservations->setStyleSheet(
        "QTableWidget {"
        "   background-color: white;"
        "   border: none;"
        "   font-size: 12px;"
        "}"
        "QHeaderView::section {"
        "   background-color: #5d6d7e;"
        "   color: white;"
        "   padding: 10px;"
        "   font-weight: bold;"
        "   border: none;"
        "}"
        "QTableWidget::item {"
        "   padding: 8px;"
        "   border-bottom: 1px solid #f0f2f5;"
        "color:black;"
        "}"
        );

    tableReservations->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableReservations->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableReservations->setAlternatingRowColors(true);
    tableReservations->setSelectionMode(QAbstractItemView::SingleSelection);

    // Configuration des colonnes
    tableReservations->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tableReservations->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableReservations->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    tableReservations->verticalHeader()->setDefaultSectionSize(36);
}

void Historique::chargerDonnees()
{ createConnexionsChart();

    chargerReservations();
    chargerStatsConnexions();
    chargerStatsReservations();
}

QChartView* Historique::createConnexionsChart()
{
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Connexions");
    set->setColor(QColor("#4e73df"));

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

    // Configuration des axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsFont(QFont("Arial", 9));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Nombre");
    axisY->setLabelsFont(QFont("Arial", 9));

    // Calcul du maximum avec marge
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

QChartView* Historique::createReservationsChart()
{
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Réservations");
    set->setColor(QColor("#e74c3c"));

    QMap<QString, int> data = getReservationsDataLast7Days();
    QStringList categories;

    for (const auto &[date, count] : data.asKeyValueRange()) {
        *set << count;
        categories << QDate::fromString(date, "yyyy-MM-dd").toString("ddd\ndd");
    }

    // Données de démo si vide
    if (set->count() == 0) {
        *set << 2 << 3 << 1 << 4 << 2 << 0 << 1;
        categories << "Lun" << "Mar" << "Mer" << "Jeu" << "Ven" << "Sam" << "Dim";
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Réservations des 7 derniers jours");
    chart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setMargins(QMargins(10, 10, 10, 10));

    // Configuration des axes
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

void Historique::initReservationFile()
{
    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dirPath);

    QString filePath = dirPath + "/reservations.dat";
    QFile file(filePath);

    if (!file.exists() && file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        QDateTime now = QDateTime::currentDateTime();

        // // Données de démo
        // out << now.toString("yyyy-MM-dd HH:mm:ss") << "|1984|George Orwell\n";
        // out << now.addDays(-1).toString("yyyy-MM-dd HH:mm:ss") << "|Le Petit Prince|Antoine de Saint-Exupéry\n";
        // out << now.addDays(-2).toString("yyyy-MM-dd HH:mm:ss") << "|L'Étranger|Albert Camus\n";

        file.close();
    }
}

void Historique::enregistrerReservation(const QString& livre, const QString& utilisateur)
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/reservations.dat";
    QFile file(filePath);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
            << "|" << livre << "|" << utilisateur << "\n";
        file.close();
    }
}

void Historique::chargerReservations()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/reservations.dat";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        tableReservations->setRowCount(1);
        tableReservations->setItem(0, 0, new QTableWidgetItem("Aucune donnée disponible"));
        return;
    }

    QVector<QStringList> reservations;
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");
        if (parts.size() >= 3) {
            reservations.append(parts);
        }
    }

    // Tri par date décroissante
    std::sort(reservations.begin(), reservations.end(), [](const QStringList &a, const QStringList &b) {
        return QDateTime::fromString(a[0], "yyyy-MM-dd HH:mm:ss") > QDateTime::fromString(b[0], "yyyy-MM-dd HH:mm:ss");
    });

    tableReservations->setRowCount(reservations.size());

    for (int i = 0; i < reservations.size(); ++i) {
        QDateTime dt = QDateTime::fromString(reservations[i][0], "yyyy-MM-dd HH:mm:ss");

        QTableWidgetItem *dateItem = new QTableWidgetItem(dt.toString("dd/MM/yyyy HH:mm"));
        QTableWidgetItem *bookItem = new QTableWidgetItem(reservations[i][1]);
        QTableWidgetItem *userItem = new QTableWidgetItem(reservations[i][2]);

        dateItem->setTextAlignment(Qt::AlignCenter);
        bookItem->setTextAlignment(Qt::AlignCenter);
        userItem->setTextAlignment(Qt::AlignCenter);

        tableReservations->setItem(i, 0, dateItem);
        tableReservations->setItem(i, 1, bookItem);
        tableReservations->setItem(i, 2, userItem);
    }

    file.close();
}

QMap<QString, int> Historique::getConnexionsDataLast7Days()
{
    QMap<QString, int> data;
    QDate currentDate = QDate::currentDate();

    // Initialiser les 7 derniers jours
    for (int i = 0; i < 7; ++i) {
        data[currentDate.addDays(-i).toString("yyyy-MM-dd")] = 0;
    }

    // Remplir avec les données réelles
    QFile file("historique_connexions.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QDateTime dt = QDateTime::fromString(line, "yyyy-MM-dd HH:mm:ss");
            if (dt.isValid() && dt.date() >= currentDate.addDays(-6)) {
                QString dateStr = dt.date().toString("yyyy-MM-dd");
                data[dateStr]++;
            }
        }
        file.close();
    }

    return data;
}

QMap<QString, int> Historique::getReservationsDataLast7Days()
{
    QMap<QString, int> data;
    QDate currentDate = QDate::currentDate();

    // Initialiser les 7 derniers jours
    for (int i = 0; i < 7; ++i) {
        data[currentDate.addDays(-i).toString("yyyy-MM-dd")] = 0;
    }

    // Remplir avec les données réelles
    QFile file(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/reservations.dat");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() >= 1) {
                QDateTime dt = QDateTime::fromString(parts[0], "yyyy-MM-dd HH:mm:ss");
                if (dt.isValid() && dt.date() >= currentDate.addDays(-6)) {
                    QString dateStr = dt.date().toString("yyyy-MM-dd");
                    data[dateStr]++;
                }
            }
        }
        file.close();
    }

    return data;
}

void Historique::chargerStatsConnexions()
{
    QMap<QString, int> connexionsData = getConnexionsDataLast7Days();
    int totalConnexions = 0;
    int maxConnexions = 0;
    QString jourMax;

    for (auto it = connexionsData.constBegin(); it != connexionsData.constEnd(); ++it) {
        totalConnexions += it.value();
        if (it.value() > maxConnexions) {
            maxConnexions = it.value();
            jourMax = QDate::fromString(it.key(), "yyyy-MM-dd").toString("dddd dd MMMM");
        }
    }

    QString statsText = QString(
                            "<div style='text-align: center;'>"
                            "<div style='font-size: 16px; color: #4e73df; font-weight: bold; margin-bottom: 8px;'>"
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

void Historique::chargerStatsReservations()
{
    QMap<QString, int> reservationsData = getReservationsDataLast7Days();
    int totalReservations = 0;
    int maxReservations = 0;
    QString jourMax;

    for (auto it = reservationsData.constBegin(); it != reservationsData.constEnd(); ++it) {
        totalReservations += it.value();
        if (it.value() > maxReservations) {
            maxReservations = it.value();
            jourMax = QDate::fromString(it.key(), "yyyy-MM-dd").toString("dddd dd MMMM");
        }
    }

    qDebug() << "Statistiques des réservations:";
    qDebug() << "Total cette semaine:" << totalReservations;
    qDebug() << "Jour avec le plus de réservations:" << jourMax << "(" << maxReservations << "réservations)";
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
