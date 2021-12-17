#include "VideoMain.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QCheckBox>
#include <QFileDialog>
#include <QApplication>
#include <QClipboard>
#include <QToolTip>
#include <QMimeData>
#include <QDropEvent>

#include "PreviewVideo.h"
#include "VideoInfo.h"
#include "../Public/Qss.h"
#include "QtAVPlayer.h"
#include "../Model/VoiceListView.h"

VideoMain::VideoMain(QWidget *parent)
    : BaseVideoMain(parent),
      NowPlayerTime("00:00:00"),
      LastPlayerTime("00:00:00"),
      mFileName("")
{
    this->setAcceptDrops(true); //启动拖动事件
    mPlayer = new QtavPlayer();
    PerView = new PreViewVideo();
    this->connect(this,&VideoMain::OpenVoiceFile,mPlayer,&QtavPlayer::OpenVoiceFile);
    this->connect(this,&VideoMain::OpenVoiceUrl,mPlayer,&QtavPlayer::OpenUrl);
    mPlayer->installEventFilter(this);
    this->resize(800,700);
    mInfo = new VideoInfo();
    mInfo->hide();
    this->Init();
}

VideoMain::~VideoMain()
{
    PerView->deleteLater();
}

void VideoMain::Init()
{
    QHBoxLayout* mLayout = Get_HLayout();

    QWidget* mWidget = InitWidget();

    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

QWidget *VideoMain::InitTitleTool()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = Get_HLayout();


    QLabel* lbl_logo = Get_Label();
    QLabel* lbl_Title = Get_Label();
    QPushButton* btn_min = Get_Button();
    QPushButton* btn_max = Get_Button();
    QPushButton* btn_exit = Get_Button();

    mLayout->addWidget(lbl_logo);
    mLayout->addWidget(lbl_Title);
    mLayout->addStretch();
    mLayout->addWidget(btn_min);
    mLayout->addWidget(btn_max);
    mLayout->addWidget(btn_exit);

    this->connect(btn_min,&QPushButton::clicked,this,[=]()
                  {
                      this->showMinimized();
                  });
    this->connect(btn_max,&QPushButton::clicked,this,[=]()
                  {
                      this->showMaximized();
                  });
    this->connect(btn_exit,&QPushButton::clicked,this,[=]()
                  {
                      this->close();
                  });

    return mWidget;
}

QWidget *VideoMain::InitWidget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = Get_HLayout();

    QWidget* mLeft = new QWidget();
    QVBoxLayout* mHBox = Get_VLayout();
    //顶部
    QWidget* TopWidget = InitTopWidget();
    //中部
    QWidget* MidWidget = InitMidWidget();
    //底部
    QWidget* BottomWidget = InitBottomWidget();

    mHBox->addWidget(TopWidget);
    mHBox->addWidget(MidWidget);
    mHBox->addWidget(BottomWidget);
    mLeft->setLayout(mHBox);

    QWidget* mRight = new QWidget();
    mRight->setFixedWidth(200);
    QVBoxLayout* mVBox = Get_VLayout();

    QWidget* TableView = InitRightTableViewWidget();
    mVBox->addWidget(TableView);
    mRight->setLayout(mVBox);

    mLayout->addWidget(mLeft);
    mLayout->addWidget(mRight);
    mWidget->setLayout(mLayout);

    this->connect(this,&VideoMain::MenuHide,this,[=](){
        if(TableView->isVisible())
        {
            mRight->setFixedWidth(0);
        }
        else if(!TableView->isVisible())
        {
            mRight->setFixedWidth(200);
        }
        TableView->setVisible(!TableView->isVisible());
    });

    return mWidget;
}

QWidget *VideoMain::InitTopWidget()
{
    QWidget* mWidget = new QWidget();
    mWidget->setStyleSheet(Public_Str::Get_Sty({TopMainStyle,{}}));
    mWidget->setFixedHeight(30);
    QHBoxLayout* mLayout = Get_HLayout();
    mLayout->setContentsMargins(0,0,30,0);

    const QString lblStyle = Public_Str::Get_Sty(Style_Css{TopLabelStyle,{}});

    QLabel* lblFileName = Get_Label(mFileName,QSize(0,0),"",false,lblStyle);
    QLabel* lbl_Time = Get_Label(NowPlayerTime + "/" + LastPlayerTime,QSize(0,0),"",false,lblStyle);

    mLayout->addStretch();
    mLayout->addWidget(lblFileName);
    mLayout->addStretch();
    mLayout->addWidget(lbl_Time);
    mWidget->setLayout(mLayout);

    this->connect(this,&VideoMain::UpdateLabelTime,this,[=](){
        lbl_Time->setText(NowPlayerTime + "/" + LastPlayerTime);
    });

    this->connect(this,&VideoMain::UpdateVoiceFileName,this,[=](){
        lblFileName->setText(mFileName);
    });

    return mWidget;
}

bool VideoMain::eventFilter(QObject *obj, QEvent *event)
{
    QSlider* slider = this->findChild<QSlider*>("mPlayerSlider");
    QSlider* Volume = this->findChild<QSlider*>("mSlider");
    if(obj == slider)
    {
        if(!isUrl)
        {
            if(event->type() == QEvent::MouseButtonPress)
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                int dur = slider->maximum() - slider->minimum();
                int pos = slider->minimum() + dur * ((double)mouseEvent->x() / slider->width());
                if(pos != slider->sliderPosition())
                {
                    slider->setValue(pos);
                }
                mPlayer->Seek(slider->value());
            }
            else if(event->type() == QEvent::HoverEnter)
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                QPoint gpos = mapToGlobal(QPoint(0,this->height() - 260) + QPoint(mouseEvent->pos().x() - 100,mouseEvent->pos().y()));
                int dur = slider->maximum() - slider->minimum();
                int pos = slider->minimum() + dur * ((double)mouseEvent->x() / slider->width());
                PerView->Set_PreViewFile(mPlayer->File());
                PerView->Set_PreViewSeek(pos);
                PerView->setWindowFlags(PerView->windowFlags() |Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
                PerView->move(gpos);

                if(PerView->Get_Show())
                {
                    QToolTip::showText(QPoint(gpos.x() + 100,gpos.y() + 200), QTime(0, 0, 0).addMSecs(pos).toString(QString::fromLatin1("HH:mm:ss")));
                    PerView->show();
                }
            }
            else if(event->type() == QEvent::HoverMove)
            {
                if(PerView->Get_Show())
                {
                    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                    QPoint gpos = mapToGlobal(QPoint(0,this->height() - 260) + QPoint(mouseEvent->pos().x() - 100,mouseEvent->pos().y()));
                    int dur = slider->maximum() - slider->minimum();
                    int pos = slider->minimum() + dur * ((double)mouseEvent->x() / slider->width());
                    PerView->Set_PreViewFile(mPlayer->File());
                    PerView->Set_PreViewSeek(pos);
                    PerView->setWindowFlags(PerView->windowFlags() |Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
                    PerView->move(gpos);

                    if(PerView->Get_Show())
                    {
                        QToolTip::showText(QPoint(gpos.x() + 100,gpos.y() + 200), QTime(0, 0, 0).addMSecs(pos).toString(QString::fromLatin1("HH:mm:ss")));
                        PerView->show();
                    }
                }
            }
            else if(event->type() == QEvent::HoverLeave)
            {
                if(PerView && PerView->isVisible())
                    PerView->hide();
            }
        }
    }
    if(obj == Volume)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            int dur = Volume->maximum() - Volume->minimum();
            int pos = Volume->minimum() + dur * ((double)mouseEvent->x() / Volume->width());
            if(pos != Volume->sliderPosition())
            {
                Volume->setValue(pos);
            }
            if(isVolume)
                mPlayer->SetVolume((float)Volume->value() / 100.0);
        }
    }
    if(obj == mPlayer)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                SetStartStop();
            }
        }
    }
    return QWidget::eventFilter(obj,event);
}

QWidget *VideoMain::InitBottomWidget()
{
    QWidget* mWidget = new QWidget();
    mWidget->setFixedHeight(60);
    mWidget->setStyleSheet(Public_Str::Get_Sty(Style_Css{BottomMainStyle,{}}));
    QVBoxLayout* mLayout = Get_VLayout();

    QSlider* mPlayerSlider = new QSlider(Qt::Horizontal);
    mPlayerSlider->setFixedHeight(15);
    mPlayerSlider->setObjectName("mPlayerSlider");
    mPlayerSlider->installEventFilter(this);
    mPlayerSlider->setStyleSheet(Public_Str::Get_Sty(Style_Css{SliderStyle,{}}));
    QWidget* mBottomButtonWidget = InitBottomButtonWidget();

    mLayout->addWidget(mPlayerSlider);
    mLayout->addWidget(mBottomButtonWidget);
    mWidget->setLayout(mLayout);

    this->connect(mPlayer,&QtavPlayer::StartPlayer,this,[=](){
        //设置进度条总时长的大小
        mPlayerSlider->setRange(0,mPlayer->duration());
        //设置视频文件标题
        emit UpdateVoiceFileName();
    });

    this->connect(mPlayer,&QtavPlayer::UpdateSliderPos,this,[=](qint64 value)
    {
        //更新时间Label
        QTime t(0,0,0);
        t = t.addMSecs(value);
        NowPlayerTime = t.toString("hh:mm:ss");
        t.setHMS(0,0,0);
        t = t.addMSecs(mPlayer->duration());
        LastPlayerTime = t.toString("hh:mm:ss");
        emit UpdateLabelTime();

        //进度条拉进度
        mPlayerSlider->setValue(value);
    });

    this->connect(mPlayerSlider,&QSlider::sliderMoved,this,[=](int value){
        mPlayer->Seek(value);
    });
    return mWidget;
}

QWidget *VideoMain::InitBottomButtonWidget()
{
    QWidget* mWidget = new QWidget();
    mWidget->setStyleSheet(Public_Str::Get_Sty(Style_Css{TopMainStyle,{}}));
    QHBoxLayout* mLayout = Get_HLayout();
    mLayout->setSpacing(15);
    mLayout->setContentsMargins(5,0,5,10);

    const QString OpenStyle = Public_Str::Get_Sty(Style_Css{BottomOpenFileButtonStyle,{}});
    const QString RefundStyle = Public_Str::Get_Sty(Style_Css{BottomReFundButtonStyle,{}});
    const QString Startstyle = Public_Str::Get_Sty(Style_Css{BottomStartButtonStyle,{}});
    const QString StopStyle = Public_Str::Get_Sty(Style_Css{BottomStopButtonStyle,{}});
    const QString IntoStyle = Public_Str::Get_Sty(Style_Css{BottomIntoButtonStyle,{}});
    const QString RebackStyle = Public_Str::Get_Sty(Style_Css{BottomReBackButtonStyle,{}});
    const QString LeftFrameStyle = Public_Str::Get_Sty(Style_Css{BottomLeftFrameButtonStyle,{}});
    const QString RightFrameStyle = Public_Str::Get_Sty(Style_Css{BottomRightFrameButtonStyle,{}});
    const QString VolumeStyle = Public_Str::Get_Sty(Style_Css{BottomVolumeButtonStyle,{}});
    const QString UnVolumeStyle = Public_Str::Get_Sty(Style_Css{BottomUnVolumeButtonStyle,{}});
    const QString VoiceInfoStyle = Public_Str::Get_Sty(Style_Css{BottomVoiceInfoButtonStyle,{}});
    const QString SetUpStyle = Public_Str::Get_Sty(Style_Css{BottomSetUpButtonStyle,{}});
    const QString ComboBoxStyle = Public_Str::Get_Sty(Style_Css{BottomBoxStyle,{}});
    const QString CheckStyle = Public_Str::Get_Sty(Style_Css{BottomCheckStyle,{}});

    QPushButton* btn_Open = Get_Button("",QSize(0,30),"","",QSize(0,0),OpenStyle);
    QPushButton* btn_Refund = Get_Button("",QSize(0,30),"","",QSize(0,0),RefundStyle);
    QPushButton* btn_StartStop = Get_Button("",QSize(0,30),"","",QSize(0,0),Startstyle);
    QPushButton* btn_Into = Get_Button("",QSize(0,30),"","",QSize(0,0),IntoStyle);
    QPushButton* btn_Reback = Get_Button("",QSize(0,30),"","",QSize(0,0),RebackStyle);
    QPushButton* btn_LeftFrame = Get_Button("",QSize(0,30),"","",QSize(0,0),LeftFrameStyle);
    QPushButton* btn_RightFrame = Get_Button("",QSize(0,30),"","",QSize(0,0),RightFrameStyle);
    btn_StartStop->setObjectName("btn_StartStop");

    //音量按钮调整
    QWidget* VoiceWidget = new QWidget();
    VoiceWidget->setFixedHeight(30);
    QHBoxLayout* VoiceLayout = Get_HLayout();
    VoiceLayout->setSpacing(5);
    QPushButton* btn_Volume = Get_Button("",QSize(0,30),"","",QSize(0,0),VolumeStyle);
    QSlider* mSlider = new QSlider(Qt::Horizontal);
    mSlider->setObjectName("mSlider");
    mSlider->installEventFilter(this);
    mSlider->setRange(0,100);
    mSlider->setValue(50);
    mSlider->setStyleSheet(Public_Str::Get_Sty(Style_Css{SliderStyle,{}}));
    VoiceLayout->addWidget(btn_Volume);
    VoiceLayout->addWidget(mSlider);
    VoiceWidget->setLayout(VoiceLayout);

    //速度的下拉框
    QStringList SpeedList;
    SpeedList << "0.1" << "0.5" << "1.0" << "2.0" << "4.0" << "8.0";
    QComboBox* SpeedBox = Get_ComboBox(SpeedList,ComboBoxStyle);
    SpeedBox->setFixedHeight(30);
    SpeedBox->setCurrentIndex(2);

    //旋转的下拉框
    QStringList RotateList;
    RotateList << "0" << "90" << "180" << "270";
    QComboBox* RotateBox = Get_ComboBox(RotateList,ComboBoxStyle);
    RotateBox->setFixedHeight(30);

    //截图的下拉框
    QStringList ScreenShotsList;
    ScreenShotsList << "截图" << "保存在剪切板" << "保存在文件";
    QComboBox* ScreenshotsBox = Get_ComboBox(ScreenShotsList,ComboBoxStyle);
    ScreenshotsBox->setFixedHeight(30);

    //视频信息
    QPushButton* btn_Playinfo = Get_Button("",QSize(0,30),"","",QSize(0,0),VoiceInfoStyle);

    //设置
    QPushButton* btn_SetUp = Get_Button("",QSize(0,30),"","",QSize(0,0),SetUpStyle);

    //Gpu支持
    QCheckBox* UseCpuBox = new QCheckBox();
    UseCpuBox->setFixedHeight(30);
    UseCpuBox->setStyleSheet(CheckStyle);
    UseCpuBox->setText("GPU支持");

    btn_Refund->setEnabled(false);
    btn_Into->setEnabled(false);
    btn_Reback->setEnabled(false);
    btn_LeftFrame->setEnabled(false);
    btn_RightFrame->setEnabled(false);
    SpeedBox->setEnabled(false);
    RotateBox->setEnabled(false);
    ScreenshotsBox->setEnabled(false);

    mLayout->addWidget(btn_Open);
    mLayout->addWidget(btn_Refund);
    mLayout->addWidget(btn_StartStop);
    mLayout->addWidget(btn_Into);
    mLayout->addWidget(btn_Reback);
    mLayout->addWidget(btn_LeftFrame);
    mLayout->addWidget(btn_RightFrame);
    mLayout->addWidget(VoiceWidget);
    mLayout->addStretch();
    mLayout->addWidget(SpeedBox);
    mLayout->addWidget(RotateBox);
    mLayout->addWidget(ScreenshotsBox);
    mLayout->addWidget(btn_Playinfo);
    mLayout->addWidget(btn_SetUp);
    mLayout->addWidget(UseCpuBox);
    mWidget->setLayout(mLayout);

    //打开文件
    this->connect(btn_Open,&QPushButton::clicked,this,[=]()
    {
        QString fileName = QFileDialog::getOpenFileName(this,"打开文件",QDir::currentPath());
        if(fileName.isEmpty())
            return;
        isUrl = false;
        emit EnableButton();
        emit BoolSetAllFalse();

        QFileInfo info(fileName);
        mFileName = info.fileName();
        //打开文件
        emit OpenVoiceFile(fileName);
    });

    //视频信息
    this->connect(btn_Playinfo,&QPushButton::clicked,this,[=]()
    {
        mInfo->show();
    });

    //音量按钮
    this->connect(btn_Volume,&QPushButton::clicked,this,[=](){
        if(isVolume)
        {
            isVolume = false;
            btn_Volume->setStyleSheet(UnVolumeStyle);
            mPlayer->SetVolume(0.0);
        }
        else
        {
            isVolume = true;
            btn_Volume->setStyleSheet(VolumeStyle);
            float f = (float)mSlider->value() / 100.0;
            mPlayer->SetVolume(f);
        }
    });

    //音量进度条
    this->connect(mSlider,&QSlider::sliderMoved,this,[=](int value){
        if(value == mSlider->minimum())
        {
            mPlayer->SetVolume(0.0);
            return;
        }
        if(!isVolume)
            return;
        float f = (float)mSlider->value() / 100.0;
        mPlayer->SetVolume(f);
    });

    //UpdateVoiceFileName 就代表重新打开一个视频
    this->connect(this,&VideoMain::UpdateVoiceFileName,this,[=](){
        isPause = false;
        btn_StartStop->setStyleSheet(StopStyle);
    });

    //暂停开始
    this->connect(btn_StartStop,&QPushButton::clicked,this,[=](){
        SetStartStop();
    });
    this->connect(btn_Refund,&QPushButton::clicked,this,[=](){
        mPlayer->SetLeftRefund();
    });
    this->connect(btn_Into,&QPushButton::clicked,this,[=](){
        mPlayer->SetRightInto();
    });
    this->connect(btn_Reback,&QPushButton::clicked,this,[=](){
//        QSlider* mPlayerSlider = this->findChild<QSlider*>("mPlayerSlider");
//        mPlayerSlider->setValue(0);
        mPlayer->Seek(0.0);
    });
    this->connect(btn_LeftFrame,&QPushButton::clicked,this,[=](){
        QSlider* mPlayerSlider = this->findChild<QSlider*>("mPlayerSlider");
        mPlayer->SetLeftFrame(mPlayerSlider->value());
    });
    this->connect(btn_RightFrame,&QPushButton::clicked,this,[=](){
        QSlider* mPlayerSlider = this->findChild<QSlider*>("mPlayerSlider");
        mPlayer->SetRightFrame(mPlayerSlider->value());
    });
    this->connect(RotateBox,static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::activated),this,[=](const QString& index){
        mPlayer->Rotate(index.toInt());
    });
    this->connect(SpeedBox,static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::activated),this,[=](const QString& index){
        mPlayer->SetSpeed(index.toFloat());
    });
    this->connect(ScreenshotsBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),this,[=](int index){
        if(index == 0)
        {
            return;
        }

        QImage Pic = mPlayer->Capture();
        qDebug() << Pic;
        if(index == 1)
        {
            QApplication::clipboard()->setImage(Pic);
        }
        else if(index == 2)
        {
            QString strFileName = QFileDialog::getSaveFileName(nullptr,"保存图片",QDir::currentPath(),
                                                               "PNG(*.png);;BMP(*.bmp);;JPEG(*.jpg *.jpeg)");
            if(!strFileName.isEmpty())
            {
                QFileInfo info(strFileName);
                qDebug() << info.completeSuffix().toStdString().c_str();
                Pic.save(strFileName,info.completeSuffix().toStdString().c_str(),80);
            }
        }

        ScreenshotsBox->setCurrentIndex(0);
    });
    this->connect(btn_SetUp,&QPushButton::clicked,this,[=](){
        emit MenuHide();
    });
    this->connect(this,&VideoMain::EnableButton,this,[=](){
        btn_Refund->setEnabled(!isUrl);
        btn_Into->setEnabled(!isUrl);
        btn_Reback->setEnabled(!isUrl);
        btn_LeftFrame->setEnabled(!isUrl);
        btn_RightFrame->setEnabled(!isUrl);
        SpeedBox->setEnabled(!isUrl);
        RotateBox->setEnabled(true);
        ScreenshotsBox->setEnabled(true);

    });


    return mWidget;
}

QWidget *VideoMain::InitRightTableViewWidget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = Get_HLayout();

    VoiceTableView* View = new VoiceTableView();
    mLayout->addWidget(View);
    mWidget->setLayout(mLayout);

    this->connect(View,&VoiceTableView::OpenUrl,this,[=](QString url){
        isUrl = true;
        emit EnableButton();
        emit OpenVoiceUrl(url);
        mFileName = "";
        emit UpdateVoiceFileName();
    });
    this->connect(this,&VideoMain::BoolSetAllFalse,View,&VoiceTableView::AllTableSetFalse);
    return mWidget;
}

void VideoMain::SetStartStop()
{
    QPushButton* btn_Start_Stop = this->findChild<QPushButton*>("btn_StartStop");
    const QString Startstyle = Public_Str::Get_Sty(Style_Css{BottomStartButtonStyle,{}});
    const QString StopStyle = Public_Str::Get_Sty(Style_Css{BottomStopButtonStyle,{}});
    isPause = !isPause;
    if(isPause)
    {
        btn_Start_Stop->setStyleSheet(Startstyle);
        mPlayer->SetStartStop(isPause);
    }
    else
    {
        btn_Start_Stop->setStyleSheet(StopStyle);
        mPlayer->SetStartStop(isPause);
    }
}

void VideoMain::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}

void VideoMain::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls())
    {
        QString fileName = url.toLocalFile();
        qDebug() << "拖入的文件名称:" << fileName;
        //加载视频文件
        emit OpenVoiceFile(fileName);
    }
}

QWidget *VideoMain::InitMidWidget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = Get_HLayout();

    mLayout->addWidget(mPlayer);
    mWidget->setLayout(mLayout);

    return mWidget;
}

