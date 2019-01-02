#include "ContactItemWidget.h"
#include "ui_ContactItemWidget.h"

ContactItemWidget::ContactItemWidget(const ChatWindowInfo &chatWindowInfo, QWidget *parent) :
    QWidget(parent),
    chatWindowInfo(chatWindowInfo),
    ui(new Ui::ContactItemWidget)
{
    ui->setupUi(this);
    ui->categoryLabel->setText(chatWindowInfo.getCategory());
    ui->contactCheckBox->setText(chatWindowInfo.getCaption());
}

ContactItemWidget::~ContactItemWidget()
{
    delete ui;
}

bool ContactItemWidget::isChecked()
{
    return checked;
}

const ChatWindowInfo &ContactItemWidget::getChatWindowInfo() const
{
    return chatWindowInfo;
}

void ContactItemWidget::on_contactCheckBox_toggled(bool checked)
{
    this->checked = checked;
}
