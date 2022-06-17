#ifndef JSBRIDGE_H
#define JSBRIDGE_H

#include "global.h"
#include "widget.h"

#include <QObject>
#include <QWidget>

class JSBridge : public QObject {
    Q_OBJECT;

    Q_PROPERTY( Widget *appWindow READ getCurrent CONSTANT );
    Q_PROPERTY( QString appVersion READ getAppVersion CONSTANT );
    Q_PROPERTY( QString url READ getURL WRITE setURL NOTIFY URLChanged );
    Q_PROPERTY(
        QString server READ getServer WRITE setServer NOTIFY serverChanged );
    Q_PROPERTY( QString websocketURL READ getWebsocketURL WRITE setWebsocketURL
                    NOTIFY websocketURLChanged );

  public:
    JSBridge( Widget *widget );
    ~JSBridge();

  private:
    Widget *m_widget;

  signals:
    void URLChanged();
    void serverChanged();
    void websocketURLChanged();

  public slots:
    /**
     * @brief message 信息框
     * @param title 标题
     * @param text 内容
     */
    void message( const QString &title, const QString &message,
                  bool isModal = false );

    /**
     * @brief question 询问框
     * @param title 标题
     * @param question 内容
     * @return 是或否
     */
    bool ask( const QString &title, const QString &question,
              bool isModal = false );

    /**
     * @brief confirm 确认框
     * @param title 标题
     * @param message 内容
     * @return 是或否
     */
    bool confirm( const QString &title, const QString &message,
                  bool isModal = false );

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
    QWidget *open( QString uniqueLabel, QString options );

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
     * @brief resize 改变窗口大小
     * @param width
     * @param height
     */
    void resize( int width = 0, int height = 0 );

    /**
     * @brief show 显示窗口
     */
    void show();

    void setGeometry( int left, int top, int width, int height );

    /**
     * @brief download 文件下载
     * @param url 文件地址
     */
    void download( QString url );

    /**
     * @brief getCurrent 获取当前窗口
     */
    Widget *getCurrent();

    /**
     * @brief getWindow 根据唯一标识获取窗口
     * @param uniqueLabel 唯一标识
     * @return Widget
     */
    Widget *getWindow( QString uniqueLabel );

    /**
     * @brief getVersion 当前客户端版本号
     * @return 版本号
     */
    QString getAppVersion();

    QString getURL();

    void setURL( QString url );

    void onURLChanged();

    QString getServer();

    void setServer( QString url );

    void onServerChanged();

    QString getWebsocketURL();

    void setWebsocketURL( QString url );

    void onWebsocketURLChanged();

    /**
     * @brief save 打开文件/文件夹保存对话框
     * @return 路径
     */
    QString save( QVariant &options );

    /**
     * @brief downloadDir 返回用户下载目录的路径
     * @return 下载目录
     */
    QString downloadDir();

    void writeBinaryFile( QString path, QVariant &v );
};

#endif // JSBRIDGE_H
