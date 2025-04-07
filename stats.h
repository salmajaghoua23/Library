#ifndef STATS_H
#define STATS_H

#include <QDialog>
#include <QtCharts>
#include <QSqlDatabase>
#include <QWidget>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QPieSeries>
// QT_CHARTS_USE_NAMESPACE

    class Stats : public QDialog {
    Q_OBJECT
    public:
        explicit Stats(QSqlDatabase db, QWidget *parent = nullptr);
        void loadAndShowStats();

    private:
        void setupUI();
        void loadData();
        void createCharts();

        QSqlDatabase m_db;
        QChartView *m_popularityChart;
        QChartView *m_quantityChart;
        QMap<QString, int> m_bookPopularity;
        QMap<QString, int> m_quantityByCategory;
    };

#endif // STATS_H
