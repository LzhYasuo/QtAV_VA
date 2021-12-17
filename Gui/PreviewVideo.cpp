#include "PreviewVideo.h"
#include <QHBoxLayout>

using namespace QtAV;

PreViewVideo::PreViewVideo(QWidget *parent)
    :BaseVideoMain(parent)
{
    this->AVInit();
    this->Init();
}

PreViewVideo::~PreViewVideo()
{

}

bool PreViewVideo::Get_Show()
{
    return isShow;
}

void PreViewVideo::Set_PreViewFile(QString msg)
{
    isShow = false;
    if(!msg.isEmpty())
    {
        isShow = true;
        m_Player->play(msg);
        m_Player->pause(true);
    }
}

void PreViewVideo::Set_PreViewSeek(int value)
{
    m_Player->seek((qint64)value);
}

void PreViewVideo::Init()
{
    this->resize(200,200);
    QHBoxLayout* mLayout = Get_HLayout();
    mLayout->addWidget(m_IO->widget());
    this->setLayout(mLayout);
}

void PreViewVideo::AVInit()
{
    //初始化
    QtAV::Widgets::registerRenderers();

    m_Player = new AVPlayer(this);
    m_IO = new VideoOutput(this);

    m_Player->setSeekType(AccurateSeek);
    m_Player->setNotifyInterval(100);
    Widgets::registerRenderers();

    m_Player->setRenderer(m_IO);
}
