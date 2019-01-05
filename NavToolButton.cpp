#include "NavToolButton.h"

NavToolButton::NavToolButton(QWidget *parent) :
    QToolButton(parent)
{
    setCount(10);
}

NavToolButton::~NavToolButton()
{
}
void NavToolButton::paintEvent(QPaintEvent *e)
{
    QToolButton::paintEvent(e);
    if(0 == _count) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);//平滑直线
    painter.setRenderHint(QPainter::TextAntialiasing, true);//平滑文字

    painter.setPen(Qt::NoPen);
    QBrush decorationBrush(Qt::red);
    QRect decoration;

    decoration.setX( this->rect().topRight().x() - 20);
    decoration.setY( this->rect().topRight().y() + 2);
    decoration.setHeight(18);
    decoration.setWidth(18);

    painter.setBrush(decorationBrush);
    painter.drawEllipse(decoration);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::white,1,Qt::SolidLine));
    QFont normalFont1("Microsoft Yahei", 9);
    normalFont1.setPointSize(9);
    painter.setFont(normalFont1);

    QString decorationText = QString("%1").arg(_count);
    if ( count() > 9){
        decorationText = "9+";
        normalFont1.setPointSize(normalFont1.pointSize()-1);
        painter.setFont(normalFont1);
    }
    painter.drawText(decoration, Qt::AlignHCenter | Qt::AlignVCenter, decorationText);
}

int NavToolButton::count() const
{
    return _count;
}

void NavToolButton::setCount(int count)
{
    _count = count;
}
