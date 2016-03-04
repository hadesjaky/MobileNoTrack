#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegExp>

/*读取本地mobile.db文件，查询dm_mobile表*/

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("MobileNoTrack");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mobile.db");
    bool ok = db.open();
    if (!ok)
    {
        QMessageBox msgBox;
        msgBox.setText("打开mobile.db文件失败");
        msgBox.exec();
        qDebug() << "open db file";
    }
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(searchMobileArea(QString)));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(searchSLOT()));
}

Widget::~Widget()
{
    delete ui;
    db.close();
}
void Widget::searchMobileArea(QString s)
{
    QRegExp reg("^[0-9]{11}$");
    if(!reg.indexIn(s))
    {
        QString headNo = s.left(7);
        QString area;
        this->searchArea(headNo, &area);
        ui->textEdit->append(QString("归属地：%1").arg(area));
    }
}
void Widget::searchSLOT()
{
    QRegExp reg("^[0-9]{11}$");
    if(!reg.indexIn(ui->lineEdit->text()))
    {
        QString area, type, areaCode, postCode;
        if(this->searchAll(ui->lineEdit->text().left(7),&area, &type, &areaCode, &postCode))
        {
            QString s = "区域："+ area+" 卡类型："+type+" 区域码: "+areaCode+" 邮编: "+postCode;
            ui->textEdit->append(s);
        }
        else
            ui->textEdit->append("没有查到该卡号");
    }
    QRegExp regHead("^[0-9]{7}$");
    if(!regHead.indexIn(ui->lineEdit->text()))
    {
        QString area, type, areaCode, postCode;
        if(this->searchAll(ui->lineEdit->text(),&area, &type, &areaCode, &postCode))
        {
            QString s = "区域："+ area+" 卡类型："+type+" 区域码: "+ areaCode+" 邮编: "+postCode;
            ui->textEdit->append(s);
        }
        else
            ui->textEdit->append("没有查到该卡号");
    }
}
bool Widget::searchAll(QString no, QString *Area, QString *Type, QString *AreaCode, QString *PostCode)
{
    QSqlQuery query;
    QString exe = "select MobileArea, MobileType, AreaCode, PostCode from dm_mobile where MobileNumber="+no;
    query.exec(exe);
    while(query.next())
    {
        *Area = query.value(0).toString();
        *Type = query.value(1).toString();
        *AreaCode = query.value(2).toString();
        *PostCode = query.value(3).toString();
        return true;
    }
    return false;
}
bool Widget::searchArea(QString no, QString *Area)
{
    QSqlQuery query;
    QString exe = "select MobileArea from dm_mobile where MobileNumber="+no;
    query.exec(exe);
    while(query.next())
    {
        *Area = query.value(0).toString();
        return true;
    }
    return false;
}
