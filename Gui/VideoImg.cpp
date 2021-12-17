#include "VideoImg.h"
#include <QDebug>

VideoImg::VideoImg(QWidget *parent)
    :OpenGLWidgetRenderer (parent)
{

}

VideoImg::~VideoImg()
{

}

bool VideoImg::receiveFrame(const QtAV::VideoFrame &frame)
{
    //得到每帧的图像
    QImage Image=frame.toImage();
    //将得到的一帧数据传递出去
    emit SendOneFrameImg(Image);

    return OpenGLWidgetRenderer::receiveFrame(frame);
}
