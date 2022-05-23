#include "gifmanager.h"

GifManager::GifManager(const QString &res_path)
{
    vec_frame.clear();

    //装载gif资源
    movie_ = new QMovie(res_path, "gif");
    InitPixmap();
}

void GifManager::InitPixmap()
{
    for(int i = 0;i < movie_->frameCount(); ++i)
    {
        movie_->jumpToFrame(i);
        vec_frame.push_back(movie_->currentPixmap());
    }
}
