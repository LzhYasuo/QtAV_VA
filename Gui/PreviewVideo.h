#ifndef _PERVIEWVIDEO_H_
#define _PERVIEWVIDEO_H_

#include <QWidget>
#include "BaseVideoMain.h"
#include <QtAV>
#include <QtAVWidgets>

class PreViewVideo : public BaseVideoMain
{
    Q_OBJECT
public:
    PreViewVideo(QWidget* parent = nullptr);
    ~PreViewVideo();

    bool Get_Show();
    void Set_PreViewFile(QString);
    void Set_PreViewSeek(int value);
    void Init();
    void AVInit();
private:
    QtAV::VideoOutput* m_IO;
    QtAV::AVPlayer* m_Player;
    QtAV::AudioOutput* audio;
    bool isShow = false;
};


#endif //_PERVIEWVIDEO_H_
