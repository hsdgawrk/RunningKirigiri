#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include "aboutdialog.h"
#include <QMenu>
#include <QObject>
#include <QCoreApplication>

class ContextMenu : public QMenu
{
    Q_OBJECT
public:
    ContextMenu(QWidget* parent = nullptr);

private:
    void InitContextMenu();

private slots:
    void slot_show_about_dialog();
};

#endif // CONTEXTMENU_H
