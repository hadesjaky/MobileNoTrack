#include "widget.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file;
    bool ok = file.exists("mobile.db");
    if(!ok)
    {
        QMessageBox msgBox;
        msgBox.setText("mobile.db文件放到可执行文件同级目录");
        msgBox.exec();
        return 0;
    }
    Widget w;
    w.show();

    return a.exec();
}
