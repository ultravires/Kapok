#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

class Database : public QObject {
    Q_OBJECT

  public:
    Database( QString name, QObject *parent = nullptr );
    ~Database();
    bool exec( const QString &queryString );
    bool existTable( const QString &tableName );

  private:
    QSqlDatabase m_database;
};

#endif // DATABASE_H
