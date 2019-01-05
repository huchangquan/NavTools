#include "NavToolBtnWidget.h"
#include "ui_NavToolBtnWidget.h"
#include <QTableWidget>

NavToolBtnWidget::NavToolBtnWidget(Qt::Orientation orientation,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavToolBtnWidget)
{
    ui->setupUi(this);
    _orientation = orientation;
    _moveFrame = new QFrame(this);
//    _moveFrame->setStyleSheet("QFrame{background:red;}");
    _moveFrame->setVisible(false);
    _topBottomAnimation = new QPropertyAnimation(this);
    _topBottomAnimation->setPropertyName("pos");
    _topBottomAnimation->setTargetObject(_moveFrame);
    _topBottomAnimation->setDuration(300);
}

NavToolBtnWidget::~NavToolBtnWidget()
{
    removeAll();
    delete _moveFrame;
    delete _topBottomAnimation;
    delete ui;
}

void NavToolBtnWidget::initLeftFrame()
{
    NavToolButton * tBtn = getNavToolButton(0);
    if(tBtn){
        if(_moveFrame->isVisible()) return;
        switch (_orientation) {
        case Qt::Vertical:
            _moveFrame->setFixedWidth(3);
            _moveFrame->setFixedHeight(tBtn->height());
            _moveFrame->move(tBtn->x() - _moveFrame->width()-getMoveFrameSpacing(),tBtn->y());
            break;
        case Qt::Horizontal:
            _moveFrame->setFixedWidth(tBtn->width());
            _moveFrame->setFixedHeight(3);
            _moveFrame->move(tBtn->pos().x(),tBtn->pos().y()+tBtn->height()+getMoveFrameSpacing());
            break;
        default:
            break;
        }
        _moveFrame->setVisible(true);
    }
}
void NavToolBtnWidget::updateLeftFrame()
{
    if(!_moveFrame->isVisible()) return;
    NavToolButton * tBtn = getNavToolButton(_currentIndex);
    if(tBtn){
        switch (_orientation) {
        case Qt::Vertical:
            _moveFrame->setFixedHeight(tBtn->height());
            _moveFrame->move(tBtn->x() - _moveFrame->width()-getMoveFrameSpacing(),tBtn->y());
            break;
        case Qt::Horizontal:
            _moveFrame->setFixedWidth(tBtn->width());
            _moveFrame->move(tBtn->pos().x(),tBtn->pos().y()+tBtn->height()+getMoveFrameSpacing());
            break;
        default:
            break;
        }
    }
}
void NavToolBtnWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateLeftFrame();
}

quint8 NavToolBtnWidget::getMoveFrameSpacing() const
{
    return _moveFrameSpacing;
}

void NavToolBtnWidget::setMoveFrameSpacing(const quint8 &moveFrameSpacing)
{
    _moveFrameSpacing = moveFrameSpacing;
}
void NavToolBtnWidget::setNavToolButtonStyle(Qt::ToolButtonStyle tBtnStyle)
{
    for(int i=0; i<_navToolBtnMap.keys().size(); ++i){
        auto key = _navToolBtnMap.keys().at(i);
        NavToolButton * tBtn = _navToolBtnMap.value(key);
        tBtn->setToolButtonStyle(tBtnStyle);
    }
}
void NavToolBtnWidget::setIconSize(const QSize & size)
{
    for(int i=0; i<_navToolBtnMap.keys().size(); ++i){
        auto key = _navToolBtnMap.keys().at(i);
        NavToolButton * tBtn = _navToolBtnMap.value(key);
        tBtn->setIconSize(size);
    }
}
NavToolButton * NavToolBtnWidget::addItem(const QString & text,
                                          const QString & toolTip,
                                          const QString & iconNormal,
                                          const QString & iconNormalOn)
{
    NavToolButton * tBtn = new NavToolButton(this);
    tBtn->setText(text);
    tBtn->setCheckable(true);
    if(toolTip.isEmpty())
        tBtn->setToolTip(text);
    else
        tBtn->setToolTip(toolTip);
    if(!iconNormal.isEmpty()){
        QIcon icon;
        icon.addPixmap(QPixmap(iconNormal),QIcon::Normal,QIcon::On);
        if(!iconNormalOn.isEmpty())
            icon.addPixmap(QPixmap(iconNormalOn),QIcon::Normal,QIcon::On);
        tBtn->setIcon(icon);
    }
    _navToolBtnMap.insert(_navToolBtnMap.keys().size(),tBtn);
    if(!_boxLayout){
        switch (_orientation) {
        case Qt::Vertical:
            _boxLayout = new QVBoxLayout(this);
            break;
        case Qt::Horizontal:
            _boxLayout = new QHBoxLayout(this);
            break;
        default:
            break;
        }
        this->setLayout(_boxLayout);
    }
    _boxLayout->addWidget(tBtn);
    tBtn->show();
    connect(tBtn,SIGNAL(clicked(bool)),this,SLOT(slotToolBtnClicked(bool)));
    return tBtn;
}

uint NavToolBtnWidget::currentIndex() const
{
    return _currentIndex;
}

void NavToolBtnWidget::moveTopBottomAnimation(int row)
{
    if(_topBottomAnimation->state() == QPropertyAnimation::Running){
        _topBottomAnimation->stop();
    }
    NavToolButton * tBtn = getNavToolButton(row);
    if(!tBtn) return;
    _topBottomAnimation->setStartValue(_moveFrame->pos());
    switch (_orientation) {
    case Qt::Vertical:
        _topBottomAnimation->setEndValue(QPoint(tBtn->pos().x()-_moveFrame->width()-getMoveFrameSpacing(),tBtn->pos().y()));
        break;
    case Qt::Horizontal:
        _topBottomAnimation->setEndValue(QPoint(tBtn->pos().x(),tBtn->pos().y()+tBtn->height()+getMoveFrameSpacing()));
        break;
    default:
        break;
    }
    _topBottomAnimation->start();
}

void NavToolBtnWidget::slotToolBtnClicked(bool checked)
{
    Q_UNUSED(checked)

    NavToolButton * tBtn = qobject_cast<NavToolButton *>(sender());
    int row = _navToolBtnMap.key(tBtn);
    _currentIndex = row;
    if( _preIndex == _currentIndex ){
        tBtn->blockSignals(true);
        tBtn->setChecked(true);
        tBtn->blockSignals(false);
        return;
    }
    initLeftFrame();
    _preIndex = _currentIndex;

    for(int i=0; i<_navToolBtnMap.keys().size(); ++i){
        auto key = _navToolBtnMap.keys().at(i);
        if(row == key) continue;
        NavToolButton * tBtn = _navToolBtnMap.value(key);
        tBtn->blockSignals(true);
        tBtn->setChecked(false);
        tBtn->blockSignals(false);
    }
    moveTopBottomAnimation(_currentIndex);
    emit sigCheckedToolBtn(_currentIndex);
}

void NavToolBtnWidget::setCurrentIndex(const uint &currentIndex)
{
    NavToolButton *tBtn = getNavToolButton(currentIndex);
    if(tBtn){
        tBtn->animateClick();
    }
}

NavToolButton * NavToolBtnWidget::getNavToolButton(int index)
{
    return _navToolBtnMap.value(index);
}

void NavToolBtnWidget::removeAll()
{
    while(!_navToolBtnMap.isEmpty()){
        delete  _navToolBtnMap.take(_navToolBtnMap.firstKey());
    }
}

bool NavToolBtnWidget::removeItem(int index)
{
    if(!_navToolBtnMap.value(index)){
        return false;
    }
    delete  _navToolBtnMap.take(index);
    QList<NavToolButton*>nToolBtnList;
    while(!_navToolBtnMap.isEmpty()){
        nToolBtnList.append(_navToolBtnMap.take(_navToolBtnMap.firstKey()));
    }
    if(nToolBtnList.size()){
        for(int i=0; i<nToolBtnList.size(); ++i){
            _navToolBtnMap.insert(i,nToolBtnList.at(i));
        }
        if(index == currentIndex()){
            setCurrentIndex(0);
        }
    }
    return true;
}
