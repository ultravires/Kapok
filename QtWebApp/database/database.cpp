#include "database.h"

#include <QCoreApplication>
#include <QSqlQuery>

Database::Database( QString connectionName, QObject *parent )
    : QObject( parent ) {
    if ( QSqlDatabase::contains( connectionName ) ) {
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

Database::~Database() {}
