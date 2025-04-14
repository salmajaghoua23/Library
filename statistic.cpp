#include "statistic.h"
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Statistic::Statistic(QSqlDatabase db, QWidget *parent) : QWidget(parent),
    m_db(db),
    popularityChartView(new QChartView),
    quantityChartView(new QChartView),
    statButton(new QPushButton("Afficher les statistiques")),
    bookStatsWindow(nullptr),membersChartView(new QChartView),
    memberStatsWindow(nullptr)
{
    membersChartView = new QChartView(this);
    membersChartView->setRenderHint(QPainter::Antialiasing);

    setupUI();
    connect(statButton, &QPushButton::clicked, this, &Statistic::on_statsButton_clicked);
}


void Statistic::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Cliquez pour voir les statistiques :");
    mainLayout->addWidget(label);
    mainLayout->addWidget(statButton);
    setLayout(mainLayout);
}

void Statistic::updateStats(const QMap<QString, int>& bookPopularity,
                            const QMap<QString, int>& quantityByCategory)
{
    createPopularityChart(bookPopularity);
    createQuantityChart(quantityByCategory);
}


void Statistic::on_statsButton_clicked()
{
    if (!chartWindow) {
        chartWindow = new QWidget();
        chartWindow->setWindowTitle("Fenêtre de statistiques");
        chartWindow->resize(800, 600);
        QVBoxLayout *layout = new QVBoxLayout(chartWindow);
        layout->addWidget(popularityChartView);
        layout->addWidget(quantityChartView);
        chartWindow->setLayout(layout);
    }

    chartWindow->show();
}
void Statistic::loadAndShowStats() {
    if (!m_db.isOpen()) {
        if (!m_db.open()) {
            qDebug() << "❌ Erreur de connexion DB:" << m_db.lastError();
            return;
        }
    }

    QMap<QString, int> bookPopularity;
    QMap<QString, int> quantityByCategory;
    QMap<QString, int> membersByType;

    QSqlQuery query(m_db);


    // 1️⃣ Statistiques membres
    query.prepare("SELECT type, COUNT(*) FROM membres GROUP BY type");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête membres:" << query.lastError();
    } else {
        while (query.next()) {
            QString type = query.value(0).toString();
            int count = query.value(1).toInt();
            membersByType[type] = count;
        }
    }

    // 2️⃣ Popularité des livres
    query.prepare("SELECT l.titre, COUNT(e.id) AS emprunts "
                  "FROM livres l LEFT JOIN emprunts e ON l.id = e.livre_id "
                  "GROUP BY l.titre ORDER BY emprunts DESC LIMIT 5");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête popularité:" << query.lastError();
    } else {
        while (query.next()) {
            bookPopularity[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    // 3️⃣ Quantité par catégorie
    query.prepare("SELECT categorie, COUNT(*) AS count FROM livres GROUP BY categorie");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête catégories:" << query.lastError();
    } else {
        while (query.next()) {
            quantityByCategory[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    // 🧠 Création des charts
    createPopularityChart(bookPopularity);
    createQuantityChart(quantityByCategory);
    createMembersChart(membersByType);

    // 📚 Fenêtre des livres
    if (!bookStatsWindow) {
        bookStatsWindow = new QWidget();
        bookStatsWindow->setWindowTitle("📚 Statistiques des livres");
        QVBoxLayout *layout = new QVBoxLayout(bookStatsWindow);
        layout->addWidget(popularityChartView);
        layout->addWidget(quantityChartView);
    }

    // 👥 Fenêtre des membres
    if (!memberStatsWindow) {
        memberStatsWindow = new QWidget();
        memberStatsWindow->setWindowTitle("👥 Statistiques des membres");
        QVBoxLayout *layout = new QVBoxLayout(memberStatsWindow);
        layout->addWidget(membersChartView);
    }

    bookStatsWindow->show();
    bookStatsWindow->raise();

    memberStatsWindow->show();
    memberStatsWindow->raise();
}

void Statistic::createPopularityChart(const QMap<QString, int>& data) {
    QPieSeries *series = new QPieSeries();
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());
        slice->setBrush(QColor("#FFD700"));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Popularité des livres");
    chart->setTitleBrush(QBrush(QColor("#7A288A")));
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(16); // Taille du titre
    chart->setTitleFont(titleFont);

    popularityChartView->setChart(chart);
}


void Statistic::createQuantityChart(const QMap<QString, int>& data) {
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Quantité");
    set->setColor(QColor("#FFD700"));

    QStringList categories;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        *set << it.value();
        categories << it.key();
    }
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Quantité par catégorie");
    chart->setTitleBrush(QBrush(QColor("#7A288A")));
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(16); // Taille du titre
    chart->setTitleFont(titleFont);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    QFont labelsFont;
    labelsFont.setPointSize(12); // Taille des étiquettes
    axisX->setLabelsFont(labelsFont);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsFont(labelsFont); // Taille des nombres sur l'axe Y
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    quantityChartView->setChart(chart);
}
void Statistic::createMembersChart(const QMap<QString, int>& data) {
    if (data.isEmpty()) {
        qDebug() << "Aucune donnée disponible pour les membres.";
        return; // Arrêter si les données sont vides
    }

    QPieSeries *series = new QPieSeries();
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());
        slice->setLabelVisible(true);
        slice->setBrush(QColor::fromHsv(rand() % 360, 255, 200)); // Couleurs aléatoires
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des membres par type");
    chart->setTitleBrush(QBrush(QColor("#7A288A")));

    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(16); // Ajuste la taille du titre
    chart->setTitleFont(titleFont);

    // Assurer que le membersChartView est bien attaché
    membersChartView->setChart(chart);
    membersChartView->setRenderHint(QPainter::Antialiasing);

    // Vérifier que la fenêtre d'affichage est bien configurée et montrée
    if (!chartWindow) {
        chartWindow = new QWidget();
        chartWindow->setWindowTitle("📊 Statistiques des membres");
        // chartWindow->resize(800, 600);
        QVBoxLayout *layout = new QVBoxLayout(chartWindow);
        layout->addWidget(membersChartView);
        chartWindow->setLayout(layout);
    }
    chartWindow->show();
}



void Statistic::createAnotherChart(const QMap<QString, int>& data) {
    QPieSeries *series = new QPieSeries();
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());
        slice->setBrush(QColor("#FFD700"));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Autre statistique");
    chart->setTitleBrush(QBrush(QColor("#7A288A")));

QFont titleFont = chart->titleFont();
titleFont.setPointSize(16);
chart->setTitleFont(titleFont);

QChartView *chartView = new QChartView(chart);
chartView->setRenderHint(QPainter::Antialiasing);

// Ajoutez chartView à votre layout

if (!chartWindow) {
    chartWindow = new QWidget();
    chartWindow->setWindowTitle("Fenêtre de statistiques");
    QVBoxLayout *layout = new QVBoxLayout(chartWindow);
    layout->addWidget(popularityChartView);
    layout->addWidget(quantityChartView);
    layout->addWidget(chartView); // Ajoutez le nouveau chartView
    chartWindow->setLayout(layout);
} else {
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(chartWindow->layout());
    if (layout) {
        layout->addWidget(chartView); // Ajoutez le nouveau chartView
    }
}
}
