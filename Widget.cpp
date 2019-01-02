#include "Widget.h"
#include "ui_Widget.h"
#include "ContactItemWidget.h"
#include <QMessageBox>
#include <QThread>
#include <QtDebug>

QList<ChatWindowInfo> Widget::chatWindowInfoList;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    if (!dmsoft.setControl("dm.dmsoft"))
    {
        qDebug() << "Dmsoft initialization failed";
        QMessageBox::critical(this, "错误", "大漠插件初始化失败");
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_refreshButton_clicked()
{
    ui->contactsListWidget->clear();
    chatWindowInfoList.clear();
    EnumWindows(enumWindowsProc, 0);
    for (ChatWindowInfo info : chatWindowInfoList)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 40));
        ui->contactsListWidget->addItem(item);
        ui->contactsListWidget->setItemWidget(item, new ContactItemWidget(info));
    }
}

BOOL CALLBACK Widget::enumWindowsProc(HWND hwnd, LPARAM lParam)
{
    TCHAR buffer[100];
    GetClassName(hwnd, buffer, 100);
    const QString &className = QString::fromWCharArray(buffer);
    if ("ChatWnd" == className)
    {
        GetWindowText(hwnd, buffer, 100);
        const QString &caption = QString::fromWCharArray(buffer);
        chatWindowInfoList.append(ChatWindowInfo("微信", caption, hwnd));
    }
    else if ("TXGuiFoundation" == className)
    {
        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        if (0x960F0000 == style || 0xB60F0000 == style)
        {
            GetWindowText(hwnd, buffer, 100);
            const QString &caption = QString::fromWCharArray(buffer);
            chatWindowInfoList.append(ChatWindowInfo("QQ", caption, hwnd));
        }
    }
    return TRUE;
}

void Widget::on_sendButton_clicked()
{
    const QString &message = ui->messageTextEdit->toPlainText();
    if (!message.isEmpty())
    {
        for (int i = 0; i < ui->contactsListWidget->count(); ++i)
        {
            ContactItemWidget *contactItemWidget = static_cast<ContactItemWidget *>(ui->contactsListWidget->itemWidget(ui->contactsListWidget->item(i)));
            if (contactItemWidget->isChecked())
            {
                HWND hWnd = contactItemWidget->getChatWindowInfo().getHWnd();
//                dmsoft.BindWindowEx(reinterpret_cast<int>(hWnd), "gdi", "windows", "windows", "", 0);  //为何要绑定
                QThread::msleep(50);
                dmsoft.SetWindowState(reinterpret_cast<int>(hWnd), 1);
                //                dmsoft.SetWindowState(reinterpret_cast<int>(hWnd), 8);
                QThread::msleep(50);
                dmsoft.SendString2(reinterpret_cast<int>(hWnd), message);
                QThread::msleep(50);
                dmsoft.KeyDown(13);
                dmsoft.KeyUp(13);
                //                dmsoft.SetWindowState(reinterpret_cast<int>(hWnd), 9);
//                dmsoft.SetWindowState(reinterpret_cast<int>(hWnd), 2);
//                dmsoft.UnBindWindow();
            }
        }
    }
}
