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
     * @brief m_resizable 是否能被改变窗口大小
     */
    bool m_resizable = false;
};

#endif // BASEWINDOW_H
