#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFileInfo>
#include <QGridLayout>
#include <QMainWindow>
#include <QMouseEvent>
#include <QWebChannel>
#include <QWebEngineView>

class QMouseEvent;

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();
};
#endif // MAINWINDOW_H
