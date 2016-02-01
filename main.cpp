///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QCoreApplication"
#include "QtCore/QDebug"
#include "QtSql/QSqlDatabase"
#include "TuxNS/Log.hpp"
#include "TuxNS/Configuration.hpp"
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
	// Default the log settings
	TuxNS::Log::setLogLevel(TuxNS::Log::Error);
	// Initialize our SQL templates
	Q_INIT_RESOURCE(sqlqueries);
	// Instantiate our application
	TuxNS::Bootstrap* tnsService = new TuxNS::Bootstrap(intArguments, chrArguments);
	// Prepare the service and return
	return (tnsService->prepare() ? tnsService->getApplication().exec() : 0);
}
