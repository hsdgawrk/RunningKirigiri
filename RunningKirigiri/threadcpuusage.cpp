#include "threadcpuusage.h"

ThreadCPUUsage::ThreadCPUUsage(QObject* parent)
    :QThread(parent)
{
    m_first_get_CPU_utility_ = true;
    is_stop_ = false;
}

ThreadCPUUsage::~ThreadCPUUsage()
{
    is_stop_ = true;
}

void ThreadCPUUsage::run()
{
    while(!is_stop_)
    {
        GetCpuUsage();
        msleep(1000);
    }
}

void ThreadCPUUsage::GetCpuUsage()
{
    int cpu_usage;
    HQUERY hQuery;
    HCOUNTER hCounter;
    DWORD counterType;
    PDH_RAW_COUNTER rawData;

    PdhOpenQuery(NULL, 0, &hQuery);//开始查询
    const wchar_t* query_str;

    if (QOperatingSystemVersion::current() >= QOperatingSystemVersion::Windows10)
    {
        query_str = L"\\Processor Information(_Total)\\% Processor Utility";
    }
    else
    {
        query_str = L"\\Processor Information(_Total)\\% Processor Time";
    }

    PdhAddCounter(hQuery, query_str, NULL, &hCounter);
    PdhCollectQueryData(hQuery);
    PdhGetRawCounterValue(hCounter, &counterType, &rawData);

    if (m_first_get_CPU_utility_)//需要获得两次数据才能计算CPU使用率
    {
        cpu_usage = 0;
        m_first_get_CPU_utility_ = false;
    }
    else
    {
        PDH_FMT_COUNTERVALUE fmtValue;
        PdhCalculateCounterFromRawValue(hCounter, PDH_FMT_DOUBLE, &rawData, &m_last_rawData_, &fmtValue);//计算使用率
        cpu_usage = fmtValue.doubleValue;//传出数据
        if (cpu_usage > 100)
        {
            cpu_usage = 100;
        }
    }

    m_last_rawData_ = rawData;//保存上一次数据
    PdhCloseQuery(hQuery);//关闭查询

    emit sig_cpu_usage(cpu_usage);
}
