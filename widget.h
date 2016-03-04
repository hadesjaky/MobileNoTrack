#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void searchMobileArea(QString s);
    void searchSLOT();
private:
    Ui::Widget *ui;
    QSqlDatabase db;
    //根据号码查找，返回区域名，卡类型，区域码，邮编
    bool searchAll(QString no, QString *Area, QString *Type, QString *AreaCode, QString *PostCode);
    bool searchArea(QString no, QString *Area);

};

#endif // WIDGET_H
