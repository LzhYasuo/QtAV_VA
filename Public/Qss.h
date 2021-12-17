#ifndef QSS_H_
#define QSS_H_
#include <QList>
#include <QVariant>

enum Style_Type
{
    TopMainStyle,
    BottomMainStyle,
    SliderStyle,
    BottomOpenFileButtonStyle,
    BottomReFundButtonStyle,
    BottomStartButtonStyle,
    BottomStopButtonStyle,
    BottomIntoButtonStyle,
    BottomReBackButtonStyle,
    BottomLeftFrameButtonStyle,
    BottomRightFrameButtonStyle,
    BottomVolumeButtonStyle,
    BottomUnVolumeButtonStyle,
    BottomVoiceInfoButtonStyle,
    BottomSetUpButtonStyle,
    BottomBoxStyle,
    BottomCheckStyle,
    TopLabelStyle,

};

struct Style_Css
{
    Style_Type type;
    QList<QVariant> value;
};

class QString;
class Public_Str
{
public:
    static QString Get_Sty(Style_Css);
private:
    Public_Str();
    ~Public_Str();
};

#endif //QSS_H_
