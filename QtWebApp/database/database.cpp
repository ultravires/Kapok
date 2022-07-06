#include "database.h"

#include <QCoreApplication>
#include <QSqlQuery>

Database::Database( QString connectionName, QObject *parent )
    : QObject( parent ) {
    if ( QSqlDatabase::contains( connectionName ) ) {
        m_database = QSqlDatabase::database( connectionName );
    } else {
        m_database = QSqlDatabase::addDatabase( "QSQLITE" );
        m_database.setDatabaseName( QCoreApplication::applicationDirPath() +
                                    "//" + connectionName + ".db" );
    }
}

bool Database::exec( const QString &queryString ) {
    if ( !m_database.open() ) {
        return false;
    }

    QSqlQuery query( m_database );
    return query.exec( queryString );
}

bool Database::existTable( const QString &tableName ) {
    if ( !m_database.open() ) {
        return false;
    }

    QSqlQuery query( m_database );
    query.exec( QStringLiteral( "SELECT count(*) FROM sqlite_master WHERE "
                                "type='table' AND name='%1'" )
                    .arg( tableName ) );
    if ( query.next() ) {
        if ( query.value( 0 ).toInt() > 0 ) {
            return true;
        }
    }
    return false;
}

Database::~Database() {}
