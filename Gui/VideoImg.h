#ifndef _VIDEOIMG_H_
#define _VIDEOIMG_H_

#include <VideoOutput.h>
#include <QWidget>
#include <QtAVWidgets/OpenGLWidgetRenderer.h>

using namespace QtAV;

class VideoImg : public OpenGLWidgetRenderer
{
    Q_OBJECT
public:
    VideoImg(QWidget* parent = nullptr);
    ~VideoImg();
signals:
    void SendOneFrameImg(QImage);
protected:
    bool receiveFrame(const VideoFrame& frame);
};

#endif //_VIDEOIMG_H_
