#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include "titlebar.h"
#include <QMouseEvent>
#include <QRect>
#include <QWidget>

// 定义当前鼠标所处状态;
enum WindowStretchRectState {
    NO_SELECT = 0,     // 鼠标未进入下方矩形区域;
    LEFT_TOP_RECT,     // 鼠标在左上角区域;
    TOP_BORDER,        // 鼠标在上边框区域;
    RIGHT_TOP_RECT,    // 鼠标在右上角区域;
    RIGHT_BORDER,      // 鼠标在右边框区域;
    RIGHT_BOTTOM_RECT, // 鼠标在右下角区域;
    BOTTOM_BORDER,     // 鼠标在下边框区域;
    LEFT_BOTTOM_RECT,  // 鼠标在左下角区域;
    LEFT_BORDER        // 鼠标在左边框区域;
};

class QMouseEvent;

class BaseWindow : public QWidget {
    Q_OBJECT

  public:
    BaseWindow( QWidget *parent = nullptr );
    ~BaseWindow();
    void showEvent( QShowEvent *event ) override;
    void center();
    void setSupportStretch( bool isSupportStretch );
    bool getSupportStretch();

  private:
    /**
     * @brief initTitleBar 初始化标题栏
     */
    void                   initTitleBar();
    void                   paintEvent( QPaintEvent *event );
    void                   loadStyleSheet( const QString &sheetName );
    void                   calculateCurrentStrechRect();
    WindowStretchRectState getCurrentStretchState( QPoint cursorPos );
    void updateMouseStyle( WindowStretchRectState stretchState );
    void updateWindowSize();
    void mousePressEvent( QMouseEvent *event ) override;
    void mouseMoveEvent( QMouseEvent *event ) override;
    void mouseReleaseEvent( QMouseEvent *event ) override;
    bool event( QEvent *event ) override;

  private slots:
    /**
     * @brief onButtonMinClicked 最小化按钮点击事件
     */
    void onButtonMinClicked();
    /**
     * @brief onButtonRestoreClicked 正常化按钮点击事件
     */
    void onButtonRestoreClicked();
    /**
     * @brief onButtonMaxClicked 最大化按钮点击事件
     */
    void onButtonMaxClicked();
    /**
     * @brief onButtonCloseClicked 关闭按钮点击事件
     */
    void onButtonCloseClicked();

  protected:
    TitleBar              *m_titleBar;
    QRect                  m_leftTopRect;
    QRect                  m_leftBottomRect;
    QRect                  m_rightTopRect;
    QRect                  m_rightBottomRect;
    QRect                  m_topBorderRect;
    QRect                  m_rightBorderRect;
    QRect                  m_bottomBorderRect;
    QRect                  m_leftBorderRect;
    bool                   m_isMousePressed = false;
    WindowStretchRectState m_stretchRectState;
    QPoint                 m_endPoint;
    QPoint                 m_startPoint;
    QRect                  m_windowRectBeforeStretch;
    int                    m_windowMinWidth  = 0;
    int                    m_windowMinHeight = 0;
    bool                   m_isSupportStretch;
};

#endif // BASEWINDOW_H
