#ifndef D_MODEL_DELEGATE_H_
#define D_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>
#include <QVariant>

class VoiceModelItem : public QObject
{
    Q_OBJECT
public:
    VoiceModelItem(QObject* parent = nullptr);
    ~VoiceModelItem();

    QString Get_VoiceName();
    void Set_VoiceName(QString);

    QString Get_VoiceUrl();
    void Set_VoiceUrl(QString);

    bool Get_Clicked();
    void Set_Clicked(bool);
private:
    QString VoiceName;
    QString VoiceUrl;
    bool isClicked;
};


class VoiceTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    VoiceTableModel();
    ~VoiceTableModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(VoiceModelItem*);
    void RefrushModelData();

    QList<VoiceModelItem*> Get_List() {return List;}

private:
    QList<VoiceModelItem*> List;
};

class VoiceTableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit VoiceTableDelegate(QObject *parent = nullptr);
    virtual ~VoiceTableDelegate();
    void Set_Table(VoiceTableModel* t) {table = t;};

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    VoiceTableModel* table;
//    virtual bool editorEvent(QEvent *event, VoiceTableModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif //D_MODEL_DELEGATE_H_
