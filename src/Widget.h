#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <qt_windows.h>
#include "TableWidget.h"
#include "D3_ToolTip.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void on_scanCompleted();

private slots:
    void on_pushButton_clicked();
    void on_checkBox_1_clicked();
    void on_checkBox_2_clicked();

private:
    Ui::Widget *ui;
    D3_ToolTip *d3_tooltip;
    QList<QLabel *> d3_strings;
    TableWidget *tableView;
    void addHotkey();
    bool winEvent(MSG* message, long* result);
};

#endif // WIDGET_H
