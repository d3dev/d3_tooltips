#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QWidget>
#include <QTableView>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include "D3_Export.h"

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(QStandardItemModel *model);

public slots:
    void on_export_end();

private slots:
    void on_exportXML();
    void on_exportSQL();

private:
    QVBoxLayout vLayout;
    QHBoxLayout hLayout;
    QTableView tableView;
    QModelIndex index;
    QLabel logMSG;
    QPushButton exportSQL, exportXML;
    QProgressBar pbar;
    QStandardItemModel *model;
    D3_Export *exporter;

    void do_export(D3_Export::EXPORT_TYPE mode);
};

#endif // TABLEWIDGET_H
