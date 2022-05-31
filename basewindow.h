#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QCloseEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QWidget>

class QMouseEvent;

class BaseWindow : public QWidget {
    Q_OBJECT

  public:
    BaseWindow( QWidget *parent = nullptr );
    ~BaseWindow();
    void center();
    void setResizable( bool resizable );
    bool isResizable();

  protected:
    void closeEvent( QCloseEvent *event ) override;
    void resizeEvent( QResizeEvent *event ) override;

  private:
    /**
     * @brief m_resizable 窗口大小是否能被改变
     */
    bool m_resizable = true;
    /**
     * @brief m_movable 窗口位置是否能被移动
     */
    bool m_movable = true;
};

#endif // BASEWINDOW_H
