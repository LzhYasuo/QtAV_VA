#ifndef VIDEOINFO_H_
#define VIDEOINFO_H_
#include "BaseVideoMain.h"

class VideoInfo : public BaseVideoMain
{
    Q_OBJECT
public:
    VideoInfo(QWidget *parent = nullptr);
    ~VideoInfo();

    void Init();
    QWidget *InitWidget();
public:

};

#endif //VIDEOINFO_H_
