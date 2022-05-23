#ifndef KIRIGIRITRAY_H
#define KIRIGIRITRAY_H

#include "contextmenu.h"
#include "aboutdialog.h"
#include "gifmanager.h"
#include "threadcpuusage.h"
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMovie>
#include <QResource>
#include <QIcon>
#include <QMenu>
#include <QTimer>

class KirigiriTray : public QMainWindow
{
    Q_OBJECT

public:
    KirigiriTray(QWidget *parent = nullptr);
    ~KirigiriTray();

private:
    void ui_init();
    void ui_creat_connect();
    void CheckMouseAndShow(const int& cpu_usage);

private slots:
    void slot_update_tray();
    void slot_update_cpu_usage_info(int);

private:
    QSystemTrayIcon* kirigiri_tray_;
    ContextMenu*     context_menu_;
    GifManager*      manager_;

    QTimer*          timer_play_rate_;
    //QMovie*          kirigiri_gif_;//后期如果资源增多的话考虑采用vector

    static int       s_frame_count_;

    ThreadCPUUsage*  cpu_usage_;
};
#endif // KIRIGIRITRAY_H
