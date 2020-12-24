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
    //放入布局的导航
    NavToolBtnWidget * nW1 = new NavToolBtnWidget(this);
    nW1->setOrientation(Qt::Vertical);
    ui->verticalLayout->addWidget(nW1);

    for(int i=0; i<2; ++i){
        nW1->addItem(QString(QStringLiteral("水晶之痕[%1]")).arg(i));
    }
    nW1->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    connect(nW1,&NavToolBtnWidget::sigCheckedToolBtn,this,[&](int index){
        ui->stackedWidget->setCurrentIndex(index);
    });

    //使用ui提升的导航
    ui->widget_nav->setOrientation(Qt::Horizontal);
    for(int i=0; i<2; ++i){
        ui->widget_nav->addItem(QString(QStringLiteral("艾欧尼亚[%1]")).arg(i));
    }
    ui->widget_nav->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    connect(ui->widget_nav,&NavToolBtnWidget::sigCheckedToolBtn,this,[&](int index){
        ui->stackedWidget_2->setCurrentIndex(index);
    });

}

//------------------
void Widget::on_pushButton_uploadFile_clicked()
{
    ui->pushButton_uploadFile->blockSignals(true);
    ui->pushButton_uploadFile->setChecked(true);
    ui->pushButton_uploadFile->blockSignals(false);

    ui->pushButton_historicalRecords->blockSignals(true);
    ui->pushButton_historicalRecords->setChecked(false);
    ui->pushButton_historicalRecords->blockSignals(false);
    ui->stackedWidget_3->setCurrentIndex(0);
}

void Widget::on_pushButton_historicalRecords_clicked()
{
    ui->pushButton_historicalRecords->blockSignals(true);
    ui->pushButton_historicalRecords->setChecked(true);
    ui->pushButton_historicalRecords->blockSignals(false);

    ui->pushButton_uploadFile->blockSignals(true);
    ui->pushButton_uploadFile->setChecked(false);
    ui->pushButton_uploadFile->blockSignals(false);
    ui->stackedWidget_3->setCurrentIndex(1);
}
