#ifndef CHATWINDOWINFO_H
#define CHATWINDOWINFO_H

#include <QString>
#include <windows.h>
class ChatWindowInfo
{
public:
    ChatWindowInfo(const QString &category, const QString &caption, HWND hWnd);
    const QString &getCategory() const;
    const QString &getCaption() const;
    HWND getHWnd() const;
private:
    QString category;
    QString caption;
    HWND hWnd;
};

#endif // CHATWINDOWINFO_H
