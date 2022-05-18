#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include "titlebar.h"
#include <QRect>
#include <QWidget>

class BaseWindow : public QWidget {
    Q_OBJECT

  public:
    BaseWindow( QWidget *parent = nullptr );
    ~BaseWindow();
    void showEvent( QShowEvent *event ) override;
    void center();

  private:
    /**
     * @brief initTitleBar 初始化标题栏
     */
    void initTitleBar();
    void paintEvent( QPaintEvent *event );
    void loadStyleSheet( const QString &sheetName );
    void calculateCurrentStrechRect();

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
    TitleBar *m_titleBar;
    QRect     m_leftTopRect;
    QRect     m_leftBottomRect;
    QRect     m_rightTopRect;
    QRect     m_rightBottomRect;
    QRect     m_topBorderRect;
    QRect     m_rightBorderRect;
    QRect     m_bottomBorderRect;
    QRect     m_leftBorderRect;
};

#endif // BASEWINDOW_H
