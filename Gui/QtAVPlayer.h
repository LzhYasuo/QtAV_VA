#ifndef _QTAV_PLAYER_H_
#define _QTAV_PLAYER_H_

#include <QWidget>
#include <QtAV>
#include <QtAVWidgets>
#include <QOpenGLWidget>

class VideoImg;
class QtavPlayer : public QOpenGLWidget
{
    Q_OBJECT
public:
    QtavPlayer(QWidget* parent = nullptr);
    ~QtavPlayer();

    qint64 duration() const;
    void setDuration(qint64 duration);
    void Seek(int value);
    void SetVolume(float);
    void SetStartStop(bool);
    void Rotate(int);
    void SetSpeed(float);
    QString File();
    QImage Capture();

    void SetLeftFrame(int value);
    void SetRightFrame(int value);
    void SetLeftRefund();
    void SetRightInto();

public slots:
    void OpenVoiceFile(QString fileName);
    void OpenUrl(QString url);
signals:
    void UpdateSliderPos(qint64);
    void StartPlayer();
private slots:
    void GetOneFrameImg(QImage);

private:
    void Init();
    void AVInit();
    QtAV::VideoOutput* m_IO;
    QtAV::AVPlayer* m_Player;
    QtAV::AudioOutput* m_Audio;
    VideoImg* ObjImg;
private:
    int TotalPlayTime = 0;
    qint64 mDuration = 0;
    QImage img;
    QString fileName;
    bool isCapture = false;
};

#endif //_QTAV_PLAYER_H_
