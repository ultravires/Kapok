#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "basewindow.h"
#include <QEventLoop>
#include <QMessageBox>
#include <QWidget>

class MessageBox : BaseWindow {
    Q_OBJECT
  public:
    MessageBox( QWidget *parent = nullptr );
    ~MessageBox();

  public:
    static void message( QWidget *parent, const QString &title,
                         const QString &text );
    static bool confirm( QWidget *parent, const QString &title,
                         const QString &text );
    static bool ask( QWidget *parent, const QString &title,
                     const QString &text );

  protected:
    void paintEvent( QPaintEvent *event ) override;
    void closeEvent( QCloseEvent *event ) override;

  private:
    bool        m_chooseResult;
    QEventLoop *m_eventLoop = new QEventLoop( this );

  private slots:
    bool onCancelButtonClick() { return false; };
    bool onConfirmButttonClick() { return true; };
};

#endif // MESSAGEBOX_H
