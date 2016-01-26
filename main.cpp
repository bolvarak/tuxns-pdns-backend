///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QCoreApplication"
#include "QtCore/QDebug"
#include "QtSql/QSqlDatabase"
#include "TuxNS/Log.hpp"
#include "TuxNS/Listener.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Main /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This function wraps our application
 * @brief main()
 * @param int intArguments
 * @param char* chrArguments[]
 * @return int
 */
int main(int intArguments, char* chrArguments[])
{
	// Setup the logger
	TuxNS::Log::setLoggingFacility(TuxNS::Log::Standard);
	TuxNS::Log::setLogLevel       (TuxNS::Log::Debug);
	// Create the application
	QCoreApplication qcaTuxNS(intArguments, chrArguments);
	// Initialize the resource file
	Q_INIT_RESOURCE(sqlqueries);
	// Create the database connection
	QSqlDatabase qsdTuxNS = QSqlDatabase::addDatabase("QPSQL");
	// Setup the connection
	qsdTuxNS.setDatabaseName("databaseName");
	qsdTuxNS.setHostName    ("localhost");
	qsdTuxNS.setPort        (5432);
	qsdTuxNS.setUserName    ("userName");
	qsdTuxNS.setPassword    ("somePasswd");
	// Try to open the database
	if (!qsdTuxNS.open()) {
		// Send the log message
		TuxNS::Log::fail(QString("Database Connection Error! (%1)").arg(qsdTuxNS.lastError().text()));
		// We're done
		return 1;
	}
	// Instantiate our backend
	TuxNS::Listener* clsServer = new TuxNS::Listener();
	// Await connections
	clsServer->await();
	// Return the execution status
	return qcaTuxNS.exec();
}
