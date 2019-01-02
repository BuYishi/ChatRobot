#include "ChatWindowInfo.h"

ChatWindowInfo::ChatWindowInfo(const QString &category, const QString &caption, HWND hWnd) : category(category), caption(caption), hWnd(hWnd) { }

const QString &ChatWindowInfo::getCategory() const
{
    return category;
}

const QString &ChatWindowInfo::getCaption() const
{
    return caption;
}

HWND ChatWindowInfo::getHWnd() const
{
    return hWnd;
}
