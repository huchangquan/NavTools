#include "widget.h"
#include "ui_widget.h"
#include "NavToolBtnWidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::init()
{
    NavToolBtnWidget * nW1 = new NavToolBtnWidget(Qt::Vertical,this);
    NavToolBtnWidget * nW2 = new NavToolBtnWidget(Qt::Horizontal,this);
    ui->verticalLayout->addWidget(nW1);
    ui->verticalLayout->addWidget(nW2);
    for(int i=0; i<3; ++i){
        nW1->addItem(QString(QStringLiteral("水晶之痕[%1]")).arg(i));
        nW2->addItem(QString(QStringLiteral("水晶之痕[%1]")).arg(i));
    }
    nW1->setCurrentIndex(1);
    nW2->setCurrentIndex(2);
}
