#ifndef ADVANCEDTOOLBOX_H
#define ADVANCEDTOOLBOX_H

#include <QFrame>
#include <QWidget>
#include <QIcon>
#include <QApplication>
#include <QDrag>
#include <QEvent>
#include <QLayoutItem>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QAbstractButton>
#include <QRubberBand>
#include <QStyleOption>
#include <QtMath>
#include <functional>

class AdvancedToolBoxPrivate;
class ToolBoxTitle;
class ToolBoxSplitterHandle;

class AdvancedToolBox : public QWidget
{
    Q_OBJECT
public:
    explicit AdvancedToolBox(QWidget* parent = nullptr);
    ~AdvancedToolBox();

    int getitemscount();
    void adjustsize();

    void addWidget(QWidget* widget,const QString& label, const QIcon& icon = QIcon());
    int indexOf(QWidget* widget);
    QWidget* takeIndex(int index);
    QWidget* widget(int index);
    void clear();

    void setItemExpand(int index,bool expand = true);
    void setItemVisible(int index,bool visible = true);

    void setItemText(int index,const QString& text);
    void setItemIcon(int index,const QIcon& icon);
    QString itemText(int index);
    QIcon itemIcon(int index);

    int textIndentation();
    void resetTextIndentation(int indent = -1);

protected:
    bool event(QEvent* e);
    void paintEvent(QPaintEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void startDrag(int index,const QPoint& gpos);

private:
    Q_DECLARE_PRIVATE(AdvancedToolBox)
    Q_DISABLE_COPY(AdvancedToolBox)
    QScopedPointer<AdvancedToolBoxPrivate> d_ptr;

private:
    friend class ToolBoxTitle;
    friend class ToolBoxSplitterHandle;
};

class ToolBoxSplitterHandle : public QWidget
{
public:
    ToolBoxSplitterHandle(AdvancedToolBox* parent);
    void setIndex(int index);
    int index();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    int _index = -1;
    bool pressed = false;
    QPoint moveStart;
};

class ToolBoxPageContainer : public QWidget
{
public:
    using QWidget::QWidget;
    bool event(QEvent* e){
        if(e->type() == QEvent::LayoutRequest)
            updateGeometry();
        return QWidget::event(e);
    }
};

class ToolBoxTitle : public QAbstractButton
{
    Q_OBJECT

signals:
    void titleClicked(int index);
    void titleContextMenuRequest(int index,const QPoint &pos);

public:
    explicit ToolBoxTitle(const QString& label, const QIcon& icon, AdvancedToolBox* parent) : QAbstractButton(parent)
    {
        setText(label);
        setIcon(icon);
        setIconSize(QSize(16,16));
        connect(this,&ToolBoxTitle::clicked,this,[this](){emit titleClicked(tabIndex);});
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this,&ToolBoxTitle::customContextMenuRequested,this,[this](const QPoint& pos){emit titleContextMenuRequest(tabIndex,this->mapToGlobal(pos));});
        setAttribute(Qt::WA_Hover);
    }

    void setIndex(int index)
    {
        tabIndex = index;
    }
    QSize sizeHint() const
    {
        if(_sizeHint.isValid())
            return _sizeHint;

        ensurePolished();
        QStyleOptionTab opt;
        opt.initFrom(this);
        if(this->expanded)
            opt.state |= QStyle::State_On;
        if(this->underMouse())
            opt.state |= QStyle::State_MouseOver;

        QWidget* parent = parentWidget();
        int w = style()->pixelMetric(QStyle::PM_TabBarTabHSpace,&opt,parent);
        int h = style()->pixelMetric(QStyle::PM_TabBarTabHSpace,&opt,parent);

        bool nullicon = this->icon().isNull();
        QSize icon_size = nullicon ? QSize(0,0) : this->iconSize();
        w += icon_size.width();
        w += nullicon ? 0 : 4;

        const QFontMetrics fm = fontMetrics();
        w += fm.size(0,this->text()).width();
        h += qMax(fm.height(),icon_size.height());
        _sizeHint = style()->sizeFromContents(QStyle::CT_TabBarTab,&opt,QSize(w,h),parent);
        return _sizeHint;
    }
    QSize minimumSizeHint() const
    {
        return sizeHint();
    }
    void setExpanded(bool expanded)
    {
        if(this->expanded != expanded)
        {
            this->expanded = expanded;
            update();
        }
    }

protected:
    bool event(QEvent* e)
    {
        switch (e->type()) {
        case QEvent::HoverMove:
        case QEvent::HoverEnter:
        {
            int indent = static_cast<AdvancedToolBox*>(parentWidget())->textIndentation();
            QHoverEvent* he = static_cast<QHoverEvent*>(e);
            QRect rect = this->rect();
            rect.setRight(rect.left() + indent);
            bool test = rect.contains(he->pos());
            if (hoverBranch != test)
            {
                hoverBranch = test;
                update();
            }
        }
            break;
        case QEvent::HoverLeave:
            hoverBranch = false;
            break;
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* me = static_cast<QMouseEvent*>(e);
            if(me->buttons() == Qt::LeftButton)
            {
                pressed = true;
                pressedPos = me->globalPos();
            }
        }
            break;
        case QEvent::MouseMove:
            if(pressed)
            {
                QMouseEvent* me = static_cast<QMouseEvent*>(e);
                if((me->globalPos() - pressedPos).manhattanLength() > QApplication::startDragDistance())
                {
                    setDown(false);
                    qobject_cast<AdvancedToolBox*>(parentWidget())->startDrag(tabIndex,pressedPos);
                    return true;
                }
            }
            break;
        case QEvent::MouseButtonRelease:
            if(static_cast<QMouseEvent*>(e)->button() == Qt::LeftButton)
                pressed = false;
            break;
        default:
            break;
        };
        return QAbstractButton::event(e);
    }
    void initStyleOption(QStyleOptionToolBox* option) const
    {
        if(!option)
            return;
        option->initFrom(this);

        option->text = text();
        option->icon = icon();
        if(isDown())
            option->state |= QStyle::State_Sunken;
        if(this->expanded)
            option->state |= QStyle::State_Open;
    }
    void paintEvent(QPaintEvent*)
    {
        QWidget* parent = parentWidget();

        QStyleOptionToolBox tabopt;
        initStyleOption(&tabopt);

        QPainter painter(this);
        style()->drawControl(QStyle::CE_ToolBoxTabShape, &tabopt, &painter, parent);

        int indent = static_cast<AdvancedToolBox*>(parentWidget())->textIndentation();

        if(indent > 0)
        {
            QStyleOptionViewItem branchopt;
            branchopt.rect = tabopt.rect;
            branchopt.state = tabopt.state;
            branchopt.state &= ~QStyle::State_MouseOver;
            branchopt.state |= hoverBranch ? QStyle::State_MouseOver : QStyle::State_None;
            branchopt.state |= QStyle::State_Children;
            branchopt.rect.setRight(tabopt.rect.left() + indent);
            style()->drawPrimitive(QStyle::PE_IndicatorBranch, &branchopt,&painter,parent);
        }
        tabopt.rect.setLeft(tabopt.rect.left() + indent);

        bool null_icon = this->icon().isNull();
        int icon_width = this->iconSize().width();
        if(!null_icon)
        {
            QRect cr = style()->subElementRect(QStyle::SE_ToolBoxTabContents, &tabopt,parent);
            cr.setWidth(icon_width + 2);
            cr.moveLeft(cr.left() + 2);
            QIcon::Mode mode = tabopt.state & QStyle::State_Enabled ? QIcon::Normal : QIcon::Disabled;
            if(mode == QIcon::Normal && tabopt.state & QStyle::State_HasFocus)
                mode = QIcon::Active;
            QIcon::State state = tabopt.state & QStyle::State_Open ? QIcon::On : QIcon::Off;
            this->icon().paint(&painter, cr, Qt::AlignCenter, mode, state);
            tabopt.rect.adjust(icon_width + 4, 0, 0, 0);
        }

        if(!tabopt.text.isEmpty())
        {
            tabopt.icon = QIcon();
            style()->drawControl(QStyle::CE_ToolBoxTabLabel, &tabopt, &painter, parent);
        }
    }
    void changeEvent(QEvent* e)
    {
        _sizeHint = QSize();
        updateGeometry();
        QWidget::changeEvent(e);
    }
private:
    QPoint pressedPos;
    bool pressed = false;
    bool expanded = true;
    mutable QSize _sizeHint;
    bool hoverBranch = false;
    int tabIndex = -1;
};

class AdvancedToolBoxPrivate : public QObject
{
    Q_DECLARE_PUBLIC(AdvancedToolBox)
public:
    class ToolBoxItem;
public:
    AdvancedToolBoxPrivate(AdvancedToolBox* p)
        : QObject()
        , q_ptr(p)
    {
        QStyle* style = q_ptr->style();
        handleWidth = style->pixelMetric(QStyle::PM_DockWidgetSeparatorExtent, nullptr, p);
        indent = style->pixelMetric(QStyle::PM_TreeViewIndentation, nullptr, p);
    }
    ~AdvancedToolBoxPrivate()
    {
        qDeleteAll(items);
    }

    inline int getitemscount(){return items.count();}

    QWidget* takeIndex(int index);
    QWidget* widget(int index);
    void clear();

    void setIndexExpand(int index,bool expand = true);
    void setIndexVisible(int index,bool visible = true);

    void styleChangedEvent();

    void setIndentation(int i);

    void insertWidgetToList(int index, QWidget* widget, const QString& label ,const QIcon& icon = QIcon());
    void doLayout();

    void expandStateChanged(int index, bool expand);
    void moveHandle(int index,int distance);
    void updateGeometries(bool animate = false);

    void resetPages();
    ToolBoxSplitterHandle* createHandle();
    ToolBoxTitle* createTitle(const QString& label, const QIcon& icon);
    void showTitleMenu(int index, const QPoint& pos);

    void setDragRubberVisible(bool visible, const QRect& rect = QRect());
    void updateTitleIndent();
    void resetManualSize();
    void widgetDestroyed(QObject* o);

protected:
    int indent = 10;
    int handleWidth = 5;
    QSize contentsSize;
    int boxSpacing = 0;
    QList<ToolBoxItem*> items;

    QRubberBand* dragRubber = nullptr;

    bool isAnimationState = false;
    bool nextIsAnimation = false;

    AdvancedToolBox* q_ptr = nullptr;
//    friend class AdvancedToolBox;
    friend class ToolBoxSplitterHandle;
};

class AdvancedToolBoxPrivate::ToolBoxItem
{
    QWidget* widget = nullptr;
    ToolBoxSplitterHandle* handle = nullptr;
    ToolBoxTitle* tabTitle = nullptr;
    QWidget* tabContainer = nullptr;

    int layoutSize = 0;
    int sizeHint = 0;
    int minSize = 0;
    int maxSize = QWIDGETSIZE_MAX;
    int manualSize = 0;

    bool freezeTarget = false;
    bool isExpanded = true;
    inline bool expanded() {return isExpanded;}

    void calItemSize()
    {
        QWidgetItem wi(widget);
        sizeHint = wi.sizeHint().height();
        if(sizeHint <= 0)
            sizeHint = 100;
        int m = wi.minimumSize().height();
        minSize = m <= 0 ? 50 : m;
        maxSize = wi.maximumSize().height();
    }

    int preferSize()
    {
        int prefer = 0;
        if(manualSize > 0)
            prefer = manualSize;
        else if(sizeHint > 0)
            prefer = sizeHint;
        else
            prefer = 100;
        return qMin(qMax(minSize,prefer),maxSize);
    }

    inline bool canResize() const
    {
        return !widget->isHidden() && isExpanded;
    }

    inline bool isHidden() const
    {
        return widget->isHidden();
    }

    inline QString title() const
    {
        return tabTitle->text();
    }
    friend class AdvancedToolBox;
    friend class AdvancedToolBoxPrivate;
};

#endif // ADVANCEDTOOLBOX_H
