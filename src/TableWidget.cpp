#include "TableWidget.h"
#include <QSignalMapper>

TableWidget::TableWidget(QStandardItemModel *model)
{
    this->model = model;
    exporter = new D3_Export(model);
    pbar.setMinimum(0);
    pbar.setTextVisible(false);
    pbar.setEnabled(false);
    exportSQL.setText("Insert into 'items.db'");
    exportXML.setText("Save as 'export.xml'");
    connect(&exportXML, SIGNAL(clicked()), this, SLOT(on_exportXML()));
    connect(&exportSQL, SIGNAL(clicked()), this, SLOT(on_exportSQL()));
    connect(exporter, SIGNAL(progress(int)), &pbar, SLOT(setValue(int)));
    connect(exporter, SIGNAL(finished()), this, SLOT(on_export_end()));

    tableView.setModel(model);
    tableView.setAlternatingRowColors(true);
    tableView.setSortingEnabled(true);

    hLayout.addWidget(&exportSQL);
    hLayout.addWidget(&exportXML);
    vLayout.addWidget(&tableView);
    vLayout.addWidget(&logMSG);
    vLayout.addWidget(&pbar);
    vLayout.addLayout(&hLayout);
    setLayout(&vLayout);
}

void TableWidget::do_export(D3_Export::EXPORT_TYPE mode)
{
    pbar.setValue(0);
    pbar.setEnabled(true);
    pbar.setMaximum(model->rowCount());
    if (!exporter->isRunning())
    {
        logMSG.setText("Exporting...");
        exporter->init(mode);
        exporter->start();
    }
    else logMSG.setText("Export pending... please wait.");
}

void TableWidget::on_exportXML()
{
    do_export(D3_Export::EXPORT_XML);
}

void TableWidget::on_exportSQL()
{
    do_export(D3_Export::EXPORT_SQL);
}

void TableWidget::on_export_end()
{
    logMSG.setText("Exported.");
    pbar.setValue(0);
    pbar.setEnabled(false);
}

