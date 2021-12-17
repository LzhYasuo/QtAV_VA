#include "Qss.h"

#define GET_STR(x) #x

QString Public_Str::Get_Sty(Style_Css code)
{
    QString msg = "";
    switch (code.type)
    {
    case TopMainStyle:
    {
        msg = GET_STR
        (
            QWidget
            {
                background-color:rgb(50,50,50);
            }
        );
    }
    break;
    case BottomMainStyle:
    {
        msg = GET_STR
        (
            QWidget
            {
                background-color:rgb(50,50,50);
            }
        );
    }
    break;
    case SliderStyle:
    {
        msg = GET_STR
        (
            QSlider::groove:horizontal
                {
                    border-radius:2px;height:3px;
                }

                QSlider::sub-page:horizontal
                {
                    background:rgb(255, 255, 160);
                }
                QSlider::add-page:horizontal
            {
                background:rgb(200,200,209);
            }

            QSlider::handle:horizontal
            {
                background:rgb(255, 255, 160);
                width:8px;
                border-radius:4px;
                margin:-3px 0px -3px 0px
            }
        );
    }
    break;
    case BottomOpenFileButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/1.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/2.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomReFundButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/3.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/4.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomStartButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/5.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/6.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomStopButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/34.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/35.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomIntoButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/7.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/8.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomReBackButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/9.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/10.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomLeftFrameButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/11.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/12.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomRightFrameButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/13.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/14.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomVolumeButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/30.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/31.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomUnVolumeButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/32.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/33.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomVoiceInfoButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/19.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/20.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomSetUpButtonStyle:
    {
        msg = GET_STR
        (
            QPushButton
            {
                background-image: url(:/Paint/21.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
            QPushButton:hover
            {
                background-image: url(:/Paint/22.png);
                background-repeat:no-repeat;
                background-position:center center;
                border:none;
            }
        );
    }
    break;
    case BottomBoxStyle:
    {
        msg = GET_STR
            (
                QComboBox
                {
                    color:#666666;
                    font-size:14px;
                    padding: 1px 15px 1px 3px;
                    border:1px solid rgba(70,70,70,1);
                    border-radius:5px 5px 0px 0px;
                }
                QComboBox::drop-down
                {
                    subcontrol-origin: padding;
                    subcontrol-position: top right;
                    width: 15px;
                    border:none;
                }
                QComboBox QAbstractItemView
                {
                    background:rgba(255,255,255,1);
                    border:1px solid rgba(70,70,70,1);
                    border-radius:0px 0px 5px 5px;
                    font-size:14px;
                    outline: 0px;  //去虚线
                }
                QComboBox QAbstractItemView::item
                {
                    height:36px;
                    color:#666666;
                    padding-left:9px;
                    background-color:#FFFFFF;
                }
                QComboBox QAbstractItemView::item:hover
                {
                    //悬浮
                    background-color:#409CE1;
                    color:#ffffff;
                }
                QComboBox QAbstractItemView::item:selected
                {
                    //选中
                    background-color:#409CE1;
                    color:#ffffff;
                }
            );
    }
    break;
    case TopLabelStyle:
    {
        msg = GET_STR
        (
            QLabel
            {
                color: rgb(222, 222, 222);
                font: 12pt "黑体";
            }
        );
    }
    break;
    case BottomCheckStyle:
    {
        msg = GET_STR
        (
            QCheckBox
            {
                color : rgb(222,222,222);
                font : 12pt "黑体";
            }
        );
    }
    }

    return msg;
}
