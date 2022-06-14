#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QString>

class Config {
  public:
    Config( QString configFileName = "" );
    ~Config();
    void    set( QString beginGroup, QString key, QString value );
    QString get( QString beginGroup, QString key );
    QString getConfigFileName();

  private:
    QString   m_configFileName;
    QSettings m_settings;
};

#endif // CONFIG_H
