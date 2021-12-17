#include "QtAVPlayer.h"
#include <QImage>
#include <QHBoxLayout>
#include "VideoImg.h"
#include <QMessageBox>

using namespace QtAV;

QtavPlayer::QtavPlayer(QWidget *parent)
    :QOpenGLWidget (parent)
{
    AVInit();
    this->Init();
}

QtavPlayer::~QtavPlayer()
{

}

void QtavPlayer::Init()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    mLayout->addWidget(ObjImg->widget());

    this->setLayout(mLayout);
}

void QtavPlayer::AVInit()
{
    Widgets::registerRenderers();

    m_Player = new QtAV::AVPlayer(this);
    ObjImg = new VideoImg(this);

    //设置间隔时间(ms单位)
    m_Player->setNotifyInterval(100);
    //设置视频在最后一帧停止
    m_Player->setMediaEndAction(MediaEndAction_Pause);
    //设置跳转帧类型
    m_Player->setSeekType(AccurateSeek);
    //得到音频输出接口
    m_Audio = m_Player->audio();

    m_Player->setRenderer(ObjImg);

    m_Audio->setVolume(0.5);

    this->connect(m_Player,&AVPlayer::positionChanged,this,[=](qint64 value){
        emit UpdateSliderPos(value);
    });
    this->connect(m_Player,&AVPlayer::started,this,[=](){
        mDuration = m_Player->duration();
        emit StartPlayer();
    });
    this->connect(m_Player,&AVPlayer::error,this,[=](const QtAV::AVError& e){
        QMessageBox::warning(nullptr,"",e.ffmpegErrorString());
    });

    m_Player->setVideoDecoderPriority(QStringList() << "FFmpeg");
    connect(ObjImg,&VideoImg::SendOneFrameImg,this,&QtavPlayer::GetOneFrameImg);
}

void QtavPlayer::GetOneFrameImg(QImage img)
{
    if(!isCapture)
    {
        this->img = img;
    }
}

void QtavPlayer::OpenVoiceFile(QString fileName)
{
    m_Player->play(fileName);
    this->fileName = fileName;
    mDuration = m_Player->duration();
}

void QtavPlayer::OpenUrl(QString url)
{
    m_Player->play(url);
    this->fileName = "";
    mDuration = m_Player->duration();
}

qint64 QtavPlayer::duration() const
{
    return mDuration;
}

void QtavPlayer::setDuration(qint64 duration)
{
    mDuration = duration;
}

void QtavPlayer::Seek(int value)
{
    m_Player->seek((qint64)value);
}

void QtavPlayer::SetVolume(float f)
{
    m_Audio->setVolume(f);
}

void QtavPlayer::SetStartStop(bool isPause)
{
    m_Player->pause(isPause);
}

void QtavPlayer::Rotate(int value)
{
    ObjImg->setOrientation(ObjImg->orientation () + value);
}

QImage QtavPlayer::Capture()
{
    qDebug() << img;
    isCapture = true;
    QImage Captrue = img;
    isCapture = false;
    return Captrue;
}

void QtavPlayer::SetSpeed(float f)
{
    m_Player->setSpeed(f);
}

QString QtavPlayer::File()
{
    return fileName;
}

void QtavPlayer::SetLeftFrame(int value)
{
    this->Seek(value - m_Player->notifyInterval());
}

void QtavPlayer::SetRightFrame(int value)
{
    this->Seek(value + m_Player->notifyInterval());
}

void QtavPlayer::SetLeftRefund()
{
    m_Player->seekBackward();
}

void QtavPlayer::SetRightInto()
{
    m_Player->seekForward();
}

