#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    d3_tooltip = new D3_ToolTip();
    for (unsigned char e = 0; e < D3_ToolTip::ENUM_END; e++)
    {
        d3_strings.append(new QLabel("Unknow..."));
        ui->formLayout->addRow(new QLabel(D3_ToolTip::type_string[e]), d3_strings[e]);
    }
    tableView = new TableWidget(d3_tooltip->model);
}

Widget::~Widget()
{
    delete ui;
    delete d3_tooltip;
    delete tableView;
}

void Widget::on_checkBox_1_clicked()
{
    char *res = d3_tooltip->init();
    if (res != NULL)
    {
        ui->checkBox_1->setText(res);
        ui->label_err_1->setText("<span style='font-size:14pt; font-weight:600; color:#aa0000;'>KO</span>");
        ui->checkBox_1->setChecked(false);
    } else {
        ui->label_err_1->setText("<span style='font-size:14pt; font-weight:600; color:#00aa00;'>OK</span>");
        ui->groupBox_2->setEnabled(true);
        ui->checkBox_1->setChecked(true);
    }
}

void Widget::on_checkBox_2_clicked()
{
    if (d3_tooltip->isRunning())
    {
        ui->checkBox_2->setText("Scan pending. Please wait.");
    } else {
        ui->checkBox_2->setText("Please wait while memory is scanned.");
        ui->progressBar->setValue(100663296);
        connect(d3_tooltip, SIGNAL(progress(int)), ui->progressBar, SLOT(setValue(int)));
        connect(d3_tooltip, SIGNAL(finished()), this, SLOT(on_scanCompleted()));
        d3_tooltip->start();
    }
}

void Widget::on_scanCompleted()
{
    //int n = 0;
    QList<QStandardItem *> items;
    ui->progressBar->setValue(805306368);
    if (!d3_tooltip->makeItem(ui->lineEdit->text()))
    {
        ui->label_err_2->setText("<span style='font-size:14pt; font-weight:600; color:#aa0000;'>KO</span>");
        ui->checkBox_2->setChecked(false);
        ui->checkBox_2->setText("Something failed. Investigations needed.");
        return;
    }
    else
    {
        ui->label_err_2->setText("<span style='font-size:14pt; font-weight:600; color:#00aa00;'>OK</span>");
        ui->checkBox_2->setChecked(true);
        ui->checkBox_2->setText("All pointers has been found. Export ready.");
        ui->groupBox_3->setEnabled(true);
        addHotkey();
        items = d3_tooltip->model->takeRow(0);
        for (unsigned char e = 0; e < D3_ToolTip::ENUM_END && e+1 < items.size(); e++)
        {
            d3_strings[e]->setText(items.at(e+1)->data(Qt::UserRole).toString());
        }
    }
}

void Widget::addHotkey()
{
    LPVOID lpMsgBuf;
    DWORD rcode;
    if (RegisterHotKey(winId(), 1, MOD_ALT | MOD_NOREPEAT, 0x42) == 0)
    {
        ui->label_err_3->setText("<span style='font-size:14pt; font-weight:600; color:#aa0000;'>KO</span>");
        //It's possible that the code that sets up a throw calls a Win32 API function inside itself somewhere,
        //that resets the Last-Error value to 0. This may be happening before your call to error_message().
        RegisterHotKey(winId(), 1, MOD_ALT | MOD_NOREPEAT, 0x42);
        rcode = GetLastError();
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, rcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
        ui->checkBox_2->setText(QString("Error %1 : %2").arg(rcode).arg(QString::fromUtf16((LPCTSTR)lpMsgBuf)));
        LocalFree(lpMsgBuf);
    } else {
        ui->label_err_3->setText("<span style='font-size:14pt; font-weight:600; color:#00aa00;'>OK</span>");
    }
}

bool Widget::winEvent(MSG* message, long* result)
{
    if(message->message == WM_HOTKEY)
    {
        d3_tooltip->makeItem(ui->lineEdit->text());
        int n = d3_tooltip->model->rowCount() - 1;
        for (unsigned char e = 0; e < D3_ToolTip::ENUM_END; e++)
        {
            QStandardItem *item = d3_tooltip->model->item(n, (int)e+1);
            if(item) d3_strings[e]->setText(item->data(Qt::UserRole).toString());
        }
        return true;
    }
    return false;
}

void Widget::on_pushButton_clicked()
{
    tableView->show();
}
