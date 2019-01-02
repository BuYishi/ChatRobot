#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <windows.h>
#include "ChatWindowInfo.h"
#include "dm.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_refreshButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::Widget *ui;
    Dm::Idmsoft dmsoft;
    static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
    static QList<ChatWindowInfo> chatWindowInfoList;
};

#endif // WIDGET_H
