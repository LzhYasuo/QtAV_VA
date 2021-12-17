#include "Gui/VideoMain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
QApplication a(argc, argv);
VideoMain w;
w.show();

return a.exec();
}
