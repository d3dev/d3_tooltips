#ifndef D3_EXPORT_H
#define D3_EXPORT_H

#include <QThread>
#include <QObject>
#include <QStandardItemModel>

class D3_Export : public QThread
{
    Q_OBJECT

public:
    enum EXPORT_TYPE {EXPORT_XML, EXPORT_SQL};
    D3_Export(QStandardItemModel *model);
    void init(EXPORT_TYPE mode);
    void run();
    
signals:
     void progress(int);
    
private:
     QStandardItemModel *model;
     EXPORT_TYPE mode;
     void createDB();
     void exportXML();
     void exportSQL();
    
};

#endif // D3_EXPORT_H
