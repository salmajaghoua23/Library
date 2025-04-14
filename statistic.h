#ifndef STATISTIC_H
#define STATISTIC_H

#include <QWidget>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPushButton>
#include <QChartView>
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QLabel>

class Statistic : public QWidget
{
    Q_OBJECT

public:
    explicit Statistic(QSqlDatabase db, QWidget *parent = nullptr);
    void loadAndShowStats();
    void updateStats(const QMap<QString, int>& bookPopularity,
                     const QMap<QString, int>& quantityByCategory);
    void createAnotherChart(const QMap<QString, int>& data);
    void createMembersChart(const QMap<QString, int>& data);


private:
    void setupUI();
    void createPopularityChart(const QMap<QString, int>& data);
    void createQuantityChart(const QMap<QString, int>& data);
    void on_statsButton_clicked();
    QWidget *bookStatsWindow;
    QWidget *memberStatsWindow;
    QChartView *membersChartView;
    QSqlDatabase m_db;
    QChartView *popularityChartView;
    QChartView *quantityChartView;
    QPushButton *statButton;
    QWidget *chartWindow;
};

#endif // STATISTIC_H
