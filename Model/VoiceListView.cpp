#include "VoiceListView.h"
#include "VoiceModelDelegate.h"
#include <QHeaderView>
#include <QDebug>

VoiceTableView::VoiceTableView(QWidget* parent)
    :QTableView (parent)
{
    // Model
    this->setFixedWidth(200);
    tableModel = new VoiceTableModel();
    this->setModel(tableModel);
    // Delegate
    tableDelegate = new VoiceTableDelegate;
    this->setItemDelegate(tableDelegate);
    tableDelegate->Set_Table(tableModel);

    this->View_Init();
}

VoiceTableView::~VoiceTableView()
{

}

void VoiceTableView::AllTableSetFalse()
{
    for(int i = 0; i < tableModel->Get_List().size(); i++)
    {
        tableModel->Get_List().at(i)->Set_Clicked(false);
    }
}

void VoiceTableView::View_Init()
{
    //显示子网格
    this->setShowGrid(true);
    //取消进度条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setColumnWidth(0,200);
    //禁止拖拽
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    //设置默认高度
    this->verticalHeader()->setDefaultSectionSize(30);
    //设置表头高度
    this->horizontalHeader()->setFixedHeight(30);
    //设置行列表头无法点击
    this->setCornerButtonEnabled(false);
    this->horizontalHeader()->setSectionsClickable(false);
    this->verticalHeader()->setSectionsClickable(false);
    QTableView::horizontalHeader()->hide();
    QTableView::verticalHeader()->hide();

    this->connect(this,&QTableView::doubleClicked,this,[=](const QModelIndex &index){
        for(int i = 0; i < tableModel->Get_List().size(); i++)
            tableModel->Get_List().at(i)->Set_Clicked(false);
        tableModel->Get_List().at(index.row())->Set_Clicked(true);
        qDebug() << tableModel->Get_List().at(index.row())->Get_VoiceUrl();
        emit OpenUrl(tableModel->Get_List().at(index.row())->Get_VoiceUrl());
        tableModel->RefrushModelData();
    });
    //样式表
//    const QString headStyle = Public_Str::Get_Sty(Style_Css{SystemPageTableHead,{}});
//    this->setStyleSheet("border:none;");
//    this->horizontalHeader()->setStyleSheet(headStyle);
//    this->setStyleSheet("background-color:rgb(255,255,255);"
//                        "border:none;");
}
