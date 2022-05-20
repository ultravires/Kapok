#ifndef JSBRIDGE_H
#define JSBRIDGE_H

#include <QObject>
#include <QWidget>

class JSBridge : public QObject {
    Q_OBJECT;

  public:
    JSBridge( QWidget *widget );

  private:
    QWidget *widget;
  public slots:
    /**
     * @brief message 信息框
     * @param title 标题
     * @param text 内容
     */
    void message( const QString &title, const QString &message );

    /**
     * @brief question 询问框
     * @param title 标题
     * @param question 内容
     * @return 是或否
     */
    bool ask( QString title, QString question );

    /**
     * @brief confirm 确认框
     * @param title 标题
     * @param message 内容
     * @return 是或否
     */
    bool confirm( QString title, QString message );

    /**
     * @brief warning 警告框
     * @param title 标题
     * @param message 内容
     */
    void warning( QString title, QString message );

    /**
     * @brief setFullScreen 设置窗口是否全屏化
     * @param isFullScreen true 或 false
     */
    void setFullScreen( bool isFullScreen );

    /**
     * @brief maximize 窗口最大化
     */
    void maximize();

    /**
     * @brief minimize 窗口最小化
     */
    void minimize();

    /**
     * @brief normal 窗口正常化
     */
    void normal();

    /**
     * @brief toggleMaximize 窗口最大化或窗口正常化
     */
    void toggleMaximize();

    /**
     * @brief isMaximize 窗口是否是最大化
     * @return true 或 false
     */
    bool isMaximize();

    /**
     * @brief center 窗口居中
     */
    void center();

    /**
     * @brief move 移动窗口
     * @param left 左边距
     * @param top 右边距
     */
    void move( int left, int top );

    /**
     * @brief close 关闭窗口
     */
    void close();

    /**
     * @brief quit 退出程序
     */
    void quit();

    /**
     * @brief open 打开新的窗口
     * @param uniqueLabel 窗口唯一标识
     * @param options JSON 字符串，窗口选项
     */
    void open( QString uniqueLabel, QString options );

    /**
     * @brief setDecorations 设置窗口是否显示边框和栅栏
     * @param decorations true 或 false
     */
    void setDecorations( bool decorations );

    /**
     * @brief isDecorations 是否有窗体装饰
     * @return
     */
    bool isDecorations();

    /**
     * @brief setTitle 设置标题
     * @param title 标题
     */
    void setTitle( QString title );

    /**
     * @brief setResizable 设置是否可改变窗口大小
     * @param resizable 是否可改变
     */
    void setResizable( bool resizable );

    /**
     * @brief resize 改变窗口大小
     * @param width
     * @param height
     */
    void resize( int width = 0, int height = 0 );
};

#endif // JSBRIDGE_H
