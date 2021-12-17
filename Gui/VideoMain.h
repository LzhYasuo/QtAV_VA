#ifndef VIDEOMAIN_H
#define VIDEOMAIN_H

#include "BaseVideoMain.h"

class VideoInfo;
class QtavPlayer;
class PreViewVideo;
class VideoMain : public BaseVideoMain
{
Q_OBJECT

public:
    VideoMain(QWidget *parent = 0);
    ~VideoMain();

signals:
    void OpenVoiceFile(QString);
    void OpenVoiceUrl(QString);
    void UpdateLabelTime();
    void UpdateVoiceFileName();
    void MenuHide();
    void EnableButton();
    void BoolSetAllFalse();

private:
    //初始化
    void Init();
    //初始化标题栏
    QWidget* InitTitleTool();
    //初始化界面
    QWidget* InitWidget();
    //初始化上界面
    QWidget* InitTopWidget();
    //初始化下界面
    QWidget* InitBottomWidget();
    //初始化中间界面
    QWidget* InitMidWidget();
    //初始化下界面的按钮
    QWidget* InitBottomButtonWidget();
    //初始化TableView
    QWidget* InitRightTableViewWidget();
    //
    void SetStartStop();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);

private:
    QString NowPlayerTime;
    QString LastPlayerTime;
    QString mFileName;

    VideoInfo* mInfo;
    QtavPlayer* mPlayer;
    PreViewVideo* PerView;

    bool isVolume = true;
    bool isPause = false;
    bool isUrl = false;
//    int VoiceValue = 50;
};

#endif // VIDEOMAIN_H
