#include "VoiceModelDelegate.h"
#include <QTextOption>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <QByteArray>
#include <QEvent>
#include <QMouseEvent>
#include <QCoreApplication>

VoiceModelItem::VoiceModelItem(QObject *parent)
    :QObject (parent)
{

}

VoiceModelItem::~VoiceModelItem()
{

}

QString VoiceModelItem::Get_VoiceName()
{
    return VoiceName;
}

void VoiceModelItem::Set_VoiceName(QString msg)
{
    VoiceName = msg;
}

QString VoiceModelItem::Get_VoiceUrl()
{
    return VoiceUrl;
}

void VoiceModelItem::Set_VoiceUrl(QString t)
{
    VoiceUrl = t;
}

bool VoiceModelItem::Get_Clicked()
{
    return isClicked;
}

void VoiceModelItem::Set_Clicked(bool C)
{
    isClicked = C;
}

VoiceTableModel::VoiceTableModel()
{
    QString msg = QCoreApplication::applicationDirPath() + "\\TVInfoList.txt";
    QFile mFile(msg);
    QTextCodec *code=QTextCodec::codecForName("utf8");
    if(!mFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&mFile);
    in.setCodec(code );
    while(!in.atEnd())
    {
        VoiceModelItem* item = new VoiceModelItem();
        QString msg = in.readLine();
        QStringList StrList;
        StrList = msg.split(":");
        QString Name = StrList.at(0);
        QString Url = msg.mid(StrList.at(0).length() + 1,-1);
        item->Set_VoiceUrl(Url);
        item->Set_VoiceName(Name);
        item->Set_Clicked(false);

        List.push_back(item);
    }
    mFile.close();

}

VoiceTableModel::~VoiceTableModel()
{

}

Qt::ItemFlags VoiceTableModel::flags(const QModelIndex &index) const
{
    //所有的都是双击然后触发换Url 所以不限死
//    return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
    if(index.column() == 0)
        return QAbstractTableModel::flags(index);
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
}

int VoiceTableModel::rowCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return List.size();
}

int VoiceTableModel::columnCount(const QModelIndex &index) const
{
    if(index.isValid())
        return 0;
    return 1;
}

QVariant VoiceTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || List.size() < 1)
        return QVariant();
    //居中
    if(role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(index.column() == 0)
        {
            return List.at(index.row())->Get_VoiceName();
        }
    }
    return QVariant();
}

QVariant VoiceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::EditRole || role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            return "";
        }
        else if(orientation == Qt::Vertical)
        {
            return "";
        }
    }
    return QVariant();
}

bool VoiceTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || List.size() < 1)
        return false;
    if(role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    if(role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return true;
    }
    return false;
}

void VoiceTableModel::RefrushModel(VoiceModelItem *item)
{
    const int count = List.size();
    beginInsertRows(QModelIndex(), count, count);
    List.push_back(item);
    endInsertRows();
}

void VoiceTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}



VoiceTableDelegate::VoiceTableDelegate(QObject *parent)
    :QItemDelegate(parent)
{

}

VoiceTableDelegate::~VoiceTableDelegate()
{

}

void VoiceTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.model()->data(index,Qt::DisplayRole).toString() == "")
        return;
    if(index.column() == 0)
    {
        painter->save();
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        bool str = table->Get_List().at(index.row())->Get_Clicked();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        if(str)
        {
            painter->setPen(QPen(QColor(0,0,0)));
            painter->fillRect(option.rect,QBrush(QColor(255,255,255)));
        }
        else
        {
            painter->fillRect(option.rect,QBrush(QColor(50,50,50)));
            painter->setPen(QPen(QColor(255,255,255)));
        }
        painter->drawText(option.rect,mos,o);
        painter->restore();
    }
}

//bool VoiceTableDelegate::editorEvent(QEvent *event,
//                                        VoiceTableModel *model,
//                                        const QStyleOptionViewItem &option,
//                                        const QModelIndex &index)
//{
//    qDebug() << "0";
//    if(index.column() == 0)
//    {
//        qDebug() << "1";
//        if((event->type() == QEvent::MouseButtonRelease) ||
//            (event->type() == QEvent::MouseButtonDblClick))
//        {
//            qDebug() << "2";
//            QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
//            if(mouse_event->button() != Qt::LeftButton )
//            {
//                return false;
//            }

//            if(event->type() == QEvent::MouseButtonDblClick)
//            {
//                for(int i = 0; i < model->Get_List().size(); i++)
//                {
//                    model->Get_List().at(i)->Set_Clicked(false);
//                }
//                model->Get_List().at(index.row())->Set_Clicked(!model->Get_List().at(index.row())->Get_Clicked());
//                qDebug() << index.row();
//            }
//        }
//        return QItemDelegate::editorEvent(event, model, option, index);
//    }
//    else
//        return QItemDelegate::editorEvent(event, model, option, index);
//}
