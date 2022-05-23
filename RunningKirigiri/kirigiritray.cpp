#include "kirigiritray.h"
#include <QToolTip>

#define LOW_PLAY_RATE 200
#define MEDIUM_PLAY_RATE 100
#define HIGH_PLAY_RATE 50

int KirigiriTray::s_frame_count_ = 0;

KirigiriTray::KirigiriTray(QWidget *parent)
    : QMainWindow(parent)
{
    ui_init();
    //此处建立信号槽链接
    ui_creat_connect();
    timer_play_rate_->start(LOW_PLAY_RATE);

    cpu_usage_->start();
    kirigiri_tray_->show();
}

KirigiriTray::~KirigiriTray()
{
    if(nullptr != manager_)
    {
        delete manager_;
        manager_ = nullptr;
    }

    if(nullptr != kirigiri_tray_)
    {
        kirigiri_tray_->hide();
        delete kirigiri_tray_;
        kirigiri_tray_ = nullptr;
    }

    if(nullptr != cpu_usage_)
    {
        if(cpu_usage_->isRunning())
        {
            cpu_usage_->StopThread();
        }

        cpu_usage_->quit();
        delete cpu_usage_;
        cpu_usage_ = nullptr;
    }

    //资源文件反注册
    QResource::unregisterResource("res.rcc");
}

void KirigiriTray::ui_init()
{
    //GIFManager加载资源
    manager_ = new GifManager(QString(":/res/movie/kirigiri_tray.gif"));

    //QTimer初始化
    timer_play_rate_ = new QTimer(this);

    //初始化托盘图标
    kirigiri_tray_ = new QSystemTrayIcon(this);

    //右键菜单
    context_menu_ = new ContextMenu(this);
    kirigiri_tray_->setContextMenu(context_menu_);

    //CPU监视线程
    cpu_usage_ = new ThreadCPUUsage;
}

void KirigiriTray::ui_creat_connect()
{
    connect(timer_play_rate_,SIGNAL(timeout()),this,SLOT(slot_update_tray()));
    connect(cpu_usage_,SIGNAL(sig_cpu_usage(int)),this,SLOT(slot_update_cpu_usage_info(int)));
}

void KirigiriTray::CheckMouseAndShow(const int& cpu_usage)
{
    int xMin = kirigiri_tray_->geometry().x();
    int xMax = kirigiri_tray_->geometry().x()+kirigiri_tray_->geometry().width();

    int yMin = kirigiri_tray_->geometry().y();
    int yMax = kirigiri_tray_->geometry().y()+kirigiri_tray_->geometry().height();

    int x = QCursor::pos().x();
    int y = QCursor::pos().y();

    if(xMin <= x && x <= xMax && \
            yMin <= y && y <= yMax)
    {
        QToolTip::showText(QCursor::pos(),QString("CPU: %1\%").arg(cpu_usage));
    }
    else
    {
        QToolTip::hideText();
    }
}

void KirigiriTray::slot_update_tray()
{
    kirigiri_tray_->setIcon(manager_->GetPixVector()[s_frame_count_]);
    ++s_frame_count_;

    if(int(manager_->GetPixVector().size()) == s_frame_count_)
        s_frame_count_ = 0;
}

void KirigiriTray::slot_update_cpu_usage_info(int cpu_usage)
{
    CheckMouseAndShow(cpu_usage);

    if((0 <= cpu_usage && 40 >= cpu_usage) && \
            (LOW_PLAY_RATE != timer_play_rate_->interval()))
    {
        timer_play_rate_->setInterval(LOW_PLAY_RATE);
    }
    else if((40 < cpu_usage && 70 >= cpu_usage) && \
            (MEDIUM_PLAY_RATE != timer_play_rate_->interval()))
    {
        timer_play_rate_->setInterval(MEDIUM_PLAY_RATE);
    }
    else if((70 < cpu_usage) && \
            (HIGH_PLAY_RATE != timer_play_rate_->interval()))
    {
        timer_play_rate_->setInterval(HIGH_PLAY_RATE);
    }
}

