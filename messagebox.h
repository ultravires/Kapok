#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "basewindow.h"
#include <QEventLoop>
#include <QMessageBox>
#include <QWidget>

enum MessageBoxType {
    NoType = 0,      // 没有类型
    TypeInformation, // 信息框
    TypeWarning,     // 警告框
    TypeQuestion,    // 询问框
    TypePrompt       // 提示输入框
};

enum MessageBoxButton {
    ButtonCancel = 0, // 取消
    ButtonConfirm,    // 确定
};

class MessageBox : QDialog {
    Q_OBJECT
  public:
    MessageBox( QWidget *parent = nullptr );
    ~MessageBox();

  public:
    static void message( QWidget *parent, const QString &title,
                         const QString &text, bool isModal = false );
    static bool confirm( QWidget *parent, const QString &title,
                         const QString &text, bool isModal = false );
    static bool ask( QWidget *parent, const QString &title, const QString &text,
                     bool isModal = false );
    static int  showMessageBox( QWidget *parent, const QString &title,
                                const QString &text, MessageBoxType type,
                                MessageBoxButton buttons, bool isModal = false );

  protected:
    void paintEvent( QPaintEvent *event ) override;
    void closeEvent( QCloseEvent *event ) override;

  private:
    bool        m_chooseResult;
    QEventLoop *m_eventLoop = new QEventLoop( this );

  private slots:
    void onCancelButtonClicked();
    void onConfirmButtonClicked();
};

#endif // MESSAGEBOX_H
