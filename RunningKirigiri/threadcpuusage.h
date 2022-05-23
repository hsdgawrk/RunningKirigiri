#ifndef THREADCPUUSAGE_H
#define THREADCPUUSAGE_H

#include <QThread>
#include <QTimer>
#include <QOperatingSystemVersion>

//Windows Cpu Mointer headers
#include <pdh.h>
#include <pdhmsg.h>

class ThreadCPUUsage : public QThread
{
    Q_OBJECT
public:
    ThreadCPUUsage(QObject* parent = nullptr);
    ~ThreadCPUUsage();

    inline void StopThread(){is_stop_ = true;}

private:
    void run() override;
    void GetCpuUsage();

private:
    bool    m_first_get_CPU_utility_;
    bool    is_stop_;
    PDH_RAW_COUNTER m_last_rawData_;//保存计算CPU使用率的上一次数据

signals:
    void sig_cpu_usage(int);
};

#endif // THREADCPUUSAGE_H
