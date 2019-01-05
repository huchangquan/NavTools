#ifndef NavToolBtnWidget_H
#define NavToolBtnWidget_H

#include <QWidget>
#include "NavToolButton.h"
#include <QFrame>
#include <QPropertyAnimation>
#include <QBoxLayout>

namespace Ui {
class NavToolBtnWidget;
}

class NavToolBtnWidget : public QWidget
{
    Q_OBJECT

public:

    explicit NavToolBtnWidget(Qt::Orientation orientation = Qt::Vertical , QWidget *parent = 0);
    ~NavToolBtnWidget();

    void removeAll();
    bool removeItem(int index);
    NavToolButton *addItem(const QString &text,
                           const QString &toolTip = QString(),
                           const QString &iconNormal = QString(),
                           const QString &iconNormalOn = QString());
    uint currentIndex() const;
    void setCurrentIndex(const uint &currentIndex);
    void setIconSize(const QSize &size);
    void setNavToolButtonStyle(Qt::ToolButtonStyle tBtnStyle);
    NavToolButton *getNavToolButton(int index);
    void moveTopBottomAnimation(int row);
    void updateLeftFrame();
    void initLeftFrame();
    quint8 getMoveFrameSpacing() const;
    void setMoveFrameSpacing(const quint8 &moveFrameSpacing);

public slots:
    void slotToolBtnClicked(bool checked);
signals:
    void sigCheckedToolBtn(int row);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::NavToolBtnWidget *ui;
    QMap<int,NavToolButton*>_navToolBtnMap;
    int _currentIndex = -1;
    QFrame  *_moveFrame = Q_NULLPTR;
    QPropertyAnimation *_topBottomAnimation = Q_NULLPTR;
    int _preIndex = -1;
    Qt::Orientation _orientation = Qt::Vertical;
    QBoxLayout * _boxLayout = Q_NULLPTR;
    quint8 _moveFrameSpacing = 3;//移动模块距离toolButton的间隔
};

#endif // NavToolBtnWidget_H
