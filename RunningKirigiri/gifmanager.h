#ifndef GIFMANAGER_H
#define GIFMANAGER_H

#include <vector>
#include <QString>
#include <QMovie>
#include <QPixmap>

class GifManager
{
public:
    GifManager(const QString& res_path);
    GifManager(const QString& movie_name,const QString& res_path);
    ~GifManager()
    {
        if(nullptr != movie_)
        {
            delete movie_;
            movie_ = nullptr;
        }
    }

    const std::vector<QPixmap> GetPixVector(){return vec_frame;}

private:
    void InitPixmap();

private:
    std::vector<QPixmap> vec_frame;

    QMovie* movie_;
    //std::map<QString,QMovie*> movie_map_;//资源多了之后考虑用这种办法管理
};

#endif // GIFMANAGER_H
