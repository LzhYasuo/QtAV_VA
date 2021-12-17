#ifndef BASE_VIDEO_MAIN_H_
#define BASE_VIDEO_MAIN_H_

#include <QWidget>
#include <QVariant>
#include <QList>

struct TreeData
{
    int Role;
    QVariant Value;
};

class QTreeWidget;
class QTreeWidgetItem;
class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QComboBox;
class BaseVideoMain : public QWidget
{
    Q_OBJECT
public:
    BaseVideoMain(QWidget* parent = nullptr);
    ~BaseVideoMain();

protected:
    QPushButton* Get_Button(QString btnName = "",QSize btnSize = QSize(0,0),
                            QString IconName = "",QString warnning = "",
                            QSize IconSize = QSize(0,0),QString style = "");
    QLabel* Get_Label(QString lblName = "",QSize lblSize = QSize(0,0),
                      QString IconName = "",bool isPixMapFull = false,
                      QString style = "");
    QComboBox* Get_ComboBox(QStringList List = QStringList(),QString Style = "");
    QTreeWidgetItem* Get_TreeItem(TreeData DataList,QTreeWidget* parent = nullptr);
    QTreeWidgetItem* Get_TreeItem(TreeData DataList,QTreeWidgetItem* parent = nullptr);
    QHBoxLayout* Get_HLayout();
    QVBoxLayout* Get_VLayout();

protected:
};

#endif //BASE_VIDEO_MAIN_H_
