#include "VideoInfo.h"
#include <QTreeWidget>
#include <QHBoxLayout>

VideoInfo::VideoInfo(QWidget *parent)
    :BaseVideoMain (parent)
{
    this->Init();
}

VideoInfo::~VideoInfo()
{

}

void VideoInfo::Init()
{
    QHBoxLayout* mLayout = Get_HLayout();

    QWidget* mWidget = InitWidget();
    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

QWidget *VideoInfo::InitWidget()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = new QHBoxLayout();

    QTreeWidget* TreeWidget = new QTreeWidget();
    TreeWidget->setColumnCount(2);
    QStringList HeadLabels;
    HeadLabels << "字段" << "值";
    TreeWidget->setHeaderLabels(HeadLabels);

    TreeData Data{0,"视频文件"};
    QTreeWidgetItem* VoideFileItem = Get_TreeItem(Data,TreeWidget);
    Data = TreeData{0,"格式"};
    QTreeWidgetItem* FormatItem = Get_TreeItem(Data,TreeWidget);
    Data = TreeData{0,"码率"};
    QTreeWidgetItem* BitRateItem = Get_TreeItem(Data,TreeWidget);
    Data = TreeData{0,"起始时间"};
    QTreeWidgetItem* StartTimeItem = Get_TreeItem(Data,TreeWidget);
    Data = TreeData{0,"时长"};
    QTreeWidgetItem* TimeLengthItem = Get_TreeItem(Data,TreeWidget);
    Data = TreeData{0,"元数据"};
    QTreeWidgetItem* MetadataItem = Get_TreeItem(Data,TreeWidget);
    Data = TreeData{0,"Compaitible_brands"};
    QTreeWidgetItem* Compaitible_brandsItem = Get_TreeItem(Data,MetadataItem);
    Data = TreeData{0,"Major_brand"};
    QTreeWidgetItem* Major_brandItem = Get_TreeItem(Data,MetadataItem);
    Data = TreeData{0,"CreateTion_Time"};
    QTreeWidgetItem* CreateTion_TimeItem = Get_TreeItem(Data,MetadataItem);
    Data = TreeData{0,"Minor_Version"};
    QTreeWidgetItem* Minor_VersionItem = Get_TreeItem(Data,MetadataItem);
    Data = TreeData{0,"视频"};
    QTreeWidgetItem* VoiceItem = Get_TreeItem(Data,TreeWidget);
    Data = TreeData{0,"可用"};
    QTreeWidgetItem* Available = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"解码"};
    QTreeWidgetItem* DecodingItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"解码器"};
    QTreeWidgetItem* DecoderItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"解码详细"};
    QTreeWidgetItem* DecoderInfoItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"时长"};
    QTreeWidgetItem* VoidePlayerTimeItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"起始时间"};
    QTreeWidgetItem* VoiceStartimeItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"码率"};
    QTreeWidgetItem* VoideBitRateItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"帧数"};
    QTreeWidgetItem* VoiceFramesItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"FPS"};
    QTreeWidgetItem* VoiceFPSFramesItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"当前FPS"};
    QTreeWidgetItem* VoiceNowFpsFramesItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"像素格式"};
    QTreeWidgetItem* VoicePixel_FormatItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"尺寸"};
    QTreeWidgetItem* VoiceSizeItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"编码尺寸"};
    QTreeWidgetItem* VoiceCode_sizeItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"GOP大小"};
    QTreeWidgetItem* VoiceGopSizeItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"元数据"};
    QTreeWidgetItem* VoicePixelFormatItem = Get_TreeItem(Data,VoiceItem);
    Data = TreeData{0,"encoder"};
    QTreeWidgetItem* VoicEencoderItem = Get_TreeItem(Data,VoicePixelFormatItem);
    Data = TreeData{0,"Creation_time"};
    QTreeWidgetItem* VoiceCreateTimeItem = Get_TreeItem(Data,VoicePixelFormatItem);
    Data = TreeData{0,"language"};
    QTreeWidgetItem* VoiceLanguageItem = Get_TreeItem(Data,VoicePixelFormatItem);
    Data = TreeData{0,"音频"};
    QTreeWidgetItem* AudioItem = Get_TreeItem(Data,TreeWidget);
    Data = TreeData{0,"可用"};
    QTreeWidgetItem* AudioAvailable = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"解码"};
    QTreeWidgetItem* AudioDecodingItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"解码器"};
    QTreeWidgetItem* AudioDecoderItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"解码详细"};
    QTreeWidgetItem* AudioDecoderInfoItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"时长"};
    QTreeWidgetItem* AudioTimeLengthItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"起始时间"};
    QTreeWidgetItem* AudioStartTimeItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"码率"};
    QTreeWidgetItem* AudioBitRateItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"帧数"};
    QTreeWidgetItem* AudioFramesItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"FPS"};
    QTreeWidgetItem* AudioFpsItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"采样格式"};
    QTreeWidgetItem* AudioSamplingFormatItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"采样率"};
    QTreeWidgetItem* AudioSamplingRateItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"声道数"};
    QTreeWidgetItem* AudioTrackNumItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"声道布局"};
    QTreeWidgetItem* AudioTrackLayoutItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"Frame size"};
    QTreeWidgetItem* AudioFrameSize = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"元数据"};
    QTreeWidgetItem* AudioMetadataItem = Get_TreeItem(Data,AudioItem);
    Data = TreeData{0,"Creation_time"};
    QTreeWidgetItem* AudioCreationTimeItem = Get_TreeItem(Data,AudioMetadataItem);
    Data = TreeData{0,"language"};
    QTreeWidgetItem* AudioLanguage = Get_TreeItem(Data,AudioMetadataItem);
    Data = TreeData{0,"handler_name"};
    QTreeWidgetItem* AudioHandlerName = Get_TreeItem(Data,AudioMetadataItem);

    mLayout->addWidget(TreeWidget);
    mWidget->setLayout(mLayout);

    return mWidget;
}
