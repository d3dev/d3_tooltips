#include "TableWidget.h"
#include "D3_ToolTip.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QtSql>

TableWidget::TableWidget(QStandardItemModel *model)
{
    this->model = model;
    exportSQL.setText("Insert into 'items.db'");
    exportXML.setText("Save as 'export.xml'");
    connect(&exportXML, SIGNAL(clicked()), this, SLOT(on_exportXML()));
    connect(&exportSQL, SIGNAL(clicked()), this, SLOT(on_exportSQL()));

    tableView.setModel(model);
    tableView.setAlternatingRowColors(true);
    tableView.setSortingEnabled(true);

    hLayout.addWidget(&exportSQL);
    hLayout.addWidget(&exportXML);
    vLayout.addWidget(&tableView);
    vLayout.addWidget(&logMSG);
    vLayout.addLayout(&hLayout);
    setLayout(&vLayout);
}

void TableWidget::on_exportXML()
{
    logMSG.setText("Exporting...");
    QStandardItem *item;
    QFile file("export.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
    out << "<Items>\n";

    for(int row = 0; row < model->rowCount(); row++)
    {
        out << "\t<Item>\n";

        item = model->item(row, 0);
        out << "\t\t<CUSTOM>" << item->text() << "</CUSTOM>\n";
        for(int col = 0; col < D3_ToolTip::ENUM_END; col++)
        {
            item = model->item(row, col+1);
            out << "\t\t<" << D3_ToolTip::type_string[col] << ">";
            //if(item) out << item->data(Qt::UserRole).toString();
            if(item) out << item->text();
            out << "</" << D3_ToolTip::type_string[col] << ">\n";
        }
        out << "\t</Item>\n";
    }

    out << "</Items>\n";
    file.close();
    logMSG.setText("Exported.");
}

void TableWidget::createDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("items.db");
    db.open();
    db.exec("CREATE TABLE d3_tooltips (id INTEGER PRIMARY KEY, name, type, slot, rating, rating_label, special_stats, stats, required_level, cost, durability, required_class)");
    db.exec("CREATE TABLE d3_tooltips_slug (id INTEGER PRIMARY KEY, name, type, slot, rating, rating_label, special_stats, stats, required_level, cost, durability, required_class)");
    db.exec("CREATE TABLE d3_custom (id INTEGER PRIMARY KEY, date, owner, sold)");
    db.commit();
    db.close();
}

void TableWidget::on_exportSQL()
{
    int id = 0;
    QStandardItem *item;
    QFile file("items.db");

    logMSG.setText("Inserting...");
    if(! file.exists()) createDB();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("items.db");
    db.open();
    QSqlQuery q(db);

    for(int row = 0; row < model->rowCount(); row++)
    {
        item = model->item(row, 0);
        q.prepare("INSERT INTO d3_custom (date, owner, sold) VALUES(datetime(), :owner, 0)");
        q.bindValue(":owner", item->text());
        q.exec();
        q = db.exec("SELECT last_insert_rowid()");
        q.first();
        id = q.value(0).toInt();

        q.prepare("INSERT INTO d3_tooltips_slug (id , name, type, slot, rating, rating_label, special_stats, stats, required_level, cost, durability, required_class) "
                  "VALUES (:id , :name, :type, :slot, :rating, :rating_label, :special_stats, :stats, :required_level, :cost, :durability, :required_class)");
        q.bindValue(":id", id);
        item = model->item(row, 1);
        q.bindValue(":name", item->text());
        item = model->item(row, 2);
        q.bindValue(":type", item->text());
        item = model->item(row, 3);
        q.bindValue(":slot", item->text());
        item = model->item(row, 4);
        q.bindValue(":rating", item->text());
        item = model->item(row, 5);
        q.bindValue(":rating_label", item->text());
        item = model->item(row, 6);
        q.bindValue(":special_stats", item->text());
        item = model->item(row, 7);
        q.bindValue(":stats", item->text());
        item = model->item(row, 8);
        q.bindValue(":required_level", item->text());
        item = model->item(row, 9);
        q.bindValue(":cost", item->text());
        item = model->item(row, 10);
        q.bindValue(":durability", item->text());
        item = model->item(row, 11);
        q.bindValue(":required_class", item->text());
        q.exec();

        q.prepare("INSERT INTO d3_tooltips (id , name, type, slot, rating, rating_label, special_stats, stats, required_level, cost, durability, required_class) "
                  "VALUES (:id , :name, :type, :slot, :rating, :rating_label, :special_stats, :stats, :required_level, :cost, :durability, :required_class)");
        q.bindValue(":id", id);
        item = model->item(row, 1);
        q.bindValue(":name", item->data(Qt::UserRole).toString());
        item = model->item(row, 2);
        q.bindValue(":type", item->data(Qt::UserRole).toString());
        item = model->item(row, 3);
        q.bindValue(":slot", item->data(Qt::UserRole).toString());
        item = model->item(row, 4);
        q.bindValue(":rating", item->data(Qt::UserRole).toString());
        item = model->item(row, 5);
        q.bindValue(":rating_label", item->data(Qt::UserRole).toString());
        item = model->item(row, 6);
        q.bindValue(":special_stats", item->data(Qt::UserRole).toString());
        item = model->item(row, 7);
        q.bindValue(":stats", item->data(Qt::UserRole).toString());
        item = model->item(row, 8);
        q.bindValue(":required_level", item->data(Qt::UserRole).toString());
        item = model->item(row, 9);
        q.bindValue(":cost", item->data(Qt::UserRole).toString());
        item = model->item(row, 10);
        q.bindValue(":durability", item->data(Qt::UserRole).toString());
        item = model->item(row, 11);
        q.bindValue(":required_class", item->data(Qt::UserRole).toString());
        q.exec();
    }

    db.close();
    logMSG.setText("Inserted.");
}
