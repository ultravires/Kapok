#ifndef JSBRIDGE_H
#define JSBRIDGE_H

#include <QMessageBox>
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
     * @brief showInfoMessageBox 显示信息框
     * @param title 标题
     * @param text 内容
     */
    void showInfoMessageBox( QString title, QString text );

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
};

#endif // JSBRIDGE_H
