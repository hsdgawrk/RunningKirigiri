#include "contextmenu.h"

ContextMenu::ContextMenu(QWidget* parent)
    :QMenu(parent)
{
    InitContextMenu();
}

void ContextMenu::InitContextMenu()
{
    this->addSeparator();
    QAction* action_about = new QAction(QString("关于"), this);
    addAction(action_about);
    connect(action_about,SIGNAL(triggered()),this,SLOT(slot_show_about_dialog()));

    this->addSeparator();
    QAction* action_quit = new QAction(QString("退出"), this);
    addAction(action_quit);
    connect(action_quit, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void ContextMenu::slot_show_about_dialog()
{
    AboutDialog::Instance()->show();
}
