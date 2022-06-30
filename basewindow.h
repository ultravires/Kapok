#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QCloseEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QWidget>

class QCloseEvent;
class QMouseEvent;
class QPaintEvent;

class BaseWindow : public QWidget {
    Q_OBJECT

    Q_PROPERTY( bool resizable READ isResizable WRITE setResizable CONSTANT );

  public:
    BaseWindow( QWidget *parent = nullptr );
    ~BaseWindow();
    void setResizable( bool resizable );
    bool isResizable();

  protected:
    void closeEvent( QCloseEvent *event ) override;
    void resizeEvent( QResizeEvent *event ) override;
    //    void paintEvent( QPaintEvent *event ) override;

  private:
    /**
     * @brief m_resizable 窗口大小是否能被改变
     */
    bool m_resizable = true;
    /**
     * @brief m_movable 窗口位置是否能被移动
     */
    bool m_movable = true;

  public slots:
    void center();
    void setSize( int width, int height );
};

#endif // BASEWINDOW_H
