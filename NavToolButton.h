#ifndef NavToolButton_H
#define NavToolButton_H

#include <QToolButton>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

class NavToolButton : public QToolButton
{
    Q_OBJECT

public:
    explicit NavToolButton(QWidget *parent = Q_NULLPTR);
    ~NavToolButton();

    int count() const;
    void setCount(int count);

protected:
    void paintEvent(QPaintEvent *e) override;
private:
    int _count = 0;
};

#endif // NavToolButton_H
