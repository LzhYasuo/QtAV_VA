#include "BaseVideoMain.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QComboBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>

BaseVideoMain::BaseVideoMain(QWidget *parent)
    :QWidget (parent)
{

}

BaseVideoMain::~BaseVideoMain()
{

}

QPushButton *BaseVideoMain::Get_Button(QString btnName, QSize btnSize,QString warnning, QString IconName, QSize IconSize,QString style)
{
    QPushButton* btn = new QPushButton();
    btn->setText(btnName);
    if(!warnning.isEmpty())
        btn->setToolTip(warnning);
    if(btnSize.width() > 0)
        btn->setFixedWidth(btnSize.width());
    if(btnSize.height() > 0)
        btn->setFixedHeight(btnSize.height());
    if(!IconName.isEmpty())
        btn->setIcon(QIcon(IconName));
    if(IconSize.width() > 0 && IconSize.height() > 0)
        btn->setIconSize(IconSize);
    btn->setStyleSheet(style);

    return btn;
}

QLabel *BaseVideoMain::Get_Label(QString lblName, QSize lblSize, QString IconName,bool isPixMapFull,QString style)
{
    QLabel* lbl = new QLabel();
    lbl->setText(lblName);
    if(lblSize.width() > 0)
        lbl->setFixedWidth(lblSize.width());
    if(lblSize.height() > 0)
        lbl->setFixedHeight(lblSize.height());
    if(!IconName.isEmpty())
        lbl->setPixmap(IconName);
    lbl->setScaledContents(isPixMapFull);
    lbl->setStyleSheet(style);

    return lbl;
}

QComboBox *BaseVideoMain::Get_ComboBox(QStringList List,QString Style)
{
    QComboBox* mBox = new QComboBox();
    mBox->addItems(List);

    mBox->setStyleSheet(Style);
    return mBox;
}

QTreeWidgetItem *BaseVideoMain::Get_TreeItem(TreeData DataList, QTreeWidget *parent)
{
    QTreeWidgetItem* Item = new QTreeWidgetItem(parent);

    Item->setText(DataList.Role,DataList.Value.toString());


    return Item;
}

QTreeWidgetItem *BaseVideoMain::Get_TreeItem(TreeData DataList, QTreeWidgetItem *parent)
{
    QTreeWidgetItem* Item = new QTreeWidgetItem(parent);
    Item->setText(DataList.Role,DataList.Value.toString());

    return Item;
}

QHBoxLayout *BaseVideoMain::Get_HLayout()
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    return mLayout;
}

QVBoxLayout *BaseVideoMain::Get_VLayout()
{
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    return mLayout;
}
