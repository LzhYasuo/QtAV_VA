#ifndef VoiceListView_H_
#define VoiceListView_H_

#include <QWidget>
#include <QTableView>

class VoiceTableModel;
class VoiceTableDelegate;
class VoiceTableView : public QTableView
{
    Q_OBJECT
public:
    VoiceTableView(QWidget* parent = nullptr);
    ~VoiceTableView();

public slots:
    void AllTableSetFalse();
signals:
    void OpenUrl(QString);
private:
    void View_Init();
    //model
    VoiceTableModel* tableModel;
    //delegate
    VoiceTableDelegate* tableDelegate;
};


#endif //_D_TABLE_VIEW_H_
