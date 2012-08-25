#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(QStandardItemModel *model);

public slots:
    void on_exportXML();
    void on_exportSQL();

private:
    QVBoxLayout vLayout;
    QHBoxLayout hLayout;
    QTableView tableView;
    QStandardItemModel *model;
    QModelIndex index;
    QLabel logMSG;
    QPushButton exportSQL, exportXML;

    void createDB();
};

#endif // TABLEWIDGET_H
