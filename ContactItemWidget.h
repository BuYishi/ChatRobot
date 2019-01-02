#ifndef CONTACTITEMWIDGET_H
#define CONTACTITEMWIDGET_H

#include <QWidget>
#include "ChatWindowInfo.h"

namespace Ui {
class ContactItemWidget;
}

class ContactItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContactItemWidget(const ChatWindowInfo &chatWindowInfo, QWidget *parent = 0);
    ~ContactItemWidget();
    bool isChecked();
    const ChatWindowInfo &getChatWindowInfo() const;

private slots:
    void on_contactCheckBox_toggled(bool checked);

private:
    Ui::ContactItemWidget *ui;
    ChatWindowInfo chatWindowInfo;
    bool checked = false;
};

#endif // CONTACTITEMWIDGET_H
