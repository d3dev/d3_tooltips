#include "D3_Export.h"
#include <QFile>
#include <QTextStream>
#include <QtSql>
#include "D3_ToolTip.h"

D3_Export::D3_Export(QStandardItemModel *model)
{
    this->model = model;
}

void D3_Export::init(EXPORT_TYPE mode)
{
    this->mode = mode;
}

void D3_Export::run()
{
    switch(mode)
    {
    case EXPORT_XML:
        exportXML();
        break;
    case EXPORT_SQL:
        exportSQL();
        break;
    }
}

void D3_Export::exportXML()
{
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
        emit progress(row);
    }

    out << "</Items>\n";
    file.close();
}

void D3_Export::createDB()
{
    unsigned char e;
    QString req;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("items.db");
    db.open();
    req = "CREATE TABLE d3_tooltips (id INTEGER PRIMARY KEY, ";
    for (e = 0; e < D3_ToolTip::ENUM_END - 1; e++)
        req.append(QString("%1, ").arg(D3_ToolTip::type_string[e]));
    req.append(QString("%1)").arg(D3_ToolTip::type_string[e]));
    db.exec(req);
    req = "CREATE TABLE d3_tooltips_slug (id INTEGER PRIMARY KEY, ";
    for (e = 0; e < D3_ToolTip::ENUM_END - 1; e++)
        req.append(QString("%1, ").arg(D3_ToolTip::type_string[e]));
    req.append(QString("%1)").arg(D3_ToolTip::type_string[e]));
    db.exec(req);
    db.exec("CREATE TABLE d3_custom (id INTEGER PRIMARY KEY, created, last_update, owner, sold)");
    db.close();
}

void D3_Export::exportSQL()
{
    int id = 0;
    unsigned char e;
    QStandardItem *item;
    QString req;
    QFile file("items.db");

    if(! file.exists()) createDB();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("items.db");
    db.open();
    QSqlQuery q(db);

    for(int row = 0; row < model->rowCount(); row++)
    {
        item = model->item(row, 0);
        q.prepare("INSERT INTO d3_custom (created, last_update, owner, sold) VALUES(datetime(), datetime(), :owner, 0)");
        q.bindValue(":owner", item->text());
        q.exec();
        q = db.exec("SELECT last_insert_rowid()");
        q.first();
        id = q.value(0).toInt();
        req = "INSERT INTO d3_tooltips_slug (id, ";
        for (e = 0; e < D3_ToolTip::ENUM_END - 1; e++)
            req.append(QString("%1, ").arg(D3_ToolTip::type_string[e]));
        req.append(QString("%1) VALUES (:id, ").arg(D3_ToolTip::type_string[e]));
        for (e = 0; e < D3_ToolTip::ENUM_END - 1; e++)
            req.append(QString(":%1, ").arg(D3_ToolTip::type_string[e]));
        req.append(QString(":%1)").arg(D3_ToolTip::type_string[e]));
        q.prepare(req);
        q.bindValue(":id", id);
        for (e = 0; e < D3_ToolTip::ENUM_END; e++)
        {
            item = model->item(row, e + 1);
            q.bindValue(QString(":%1").arg(D3_ToolTip::type_string[e]), item->text());
        }
        q.exec();

        req = "INSERT INTO d3_tooltips (id, ";
        for (e = 0; e < D3_ToolTip::ENUM_END - 1; e++)
            req.append(QString("%1, ").arg(D3_ToolTip::type_string[e]));
        req.append(QString("%1) VALUES (:id, ").arg(D3_ToolTip::type_string[e]));
        for (e = 0; e < D3_ToolTip::ENUM_END - 1; e++)
            req.append(QString(":%1, ").arg(D3_ToolTip::type_string[e]));
        req.append(QString(":%1)").arg(D3_ToolTip::type_string[e]));
        q.prepare(req);
        q.bindValue(":id", id);
        for (e = 0; e < D3_ToolTip::ENUM_END; e++)
        {
            item = model->item(row, e + 1);
            q.bindValue(QString(":%1").arg(D3_ToolTip::type_string[e]), item->data(Qt::UserRole).toString());
        }
        q.exec();
        emit progress(row + 1);
    }
    db.close();
}
