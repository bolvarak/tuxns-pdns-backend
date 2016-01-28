///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QCoreApplication"
#include "QtCore/QDebug"
#include "QtSql/QSqlDatabase"
#include "TuxNS/Log.hpp"
#include "TuxNS/Bootstrap.hpp"
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
	// Initialize our SQL templates
	Q_INIT_RESOURCE(sqlqueries);
	// Create the application
	TuxNS::Bootstrap* tnsServer = new TuxNS::Bootstrap(intArguments, chrArguments);
	// Dispatch the server
	if (tnsServer->dispatch()) {
		// Return the main event loop
		return tnsServer->eventLoop();
	} else {
		// We're done
		return 1;
	}
}
