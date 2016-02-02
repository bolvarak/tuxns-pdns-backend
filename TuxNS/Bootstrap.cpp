///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "Bootstrap.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{
	///////////////////////////////////////////////////////////////////////////
	/// Protected Static Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	Bootstrap::Bootstrap(int intArguments, char* chrArguments[], QObject* objParent) : QObject(objParent), mApplication(intArguments, chrArguments)
	{
		// Setup the application
		this->mApplication.setApplicationName   ("TuxNS PowerDNS Remote Backend");
		this->mApplication.setApplicationVersion("1.0.1");
		this->mApplication.setOrganizationDomain("tuxns.in");
		this->mApplication.setOrganizationName  ("TuxNS");
		// Instantiate the CLI parser
		this->mInput = new QCommandLineParser();
	}

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	bool Bootstrap::gatherDatabaseSettings()
	{
		// Create a list for the database options
		QStringList qslDatabaseSettings;
		// Create an okay flag for the database
		bool blnDBOK = true;
		// Add the database options
		qslDatabaseSettings.append("db-name");
		qslDatabaseSettings.append("db-host");
		qslDatabaseSettings.append("db-port");
		qslDatabaseSettings.append("db-user");
		qslDatabaseSettings.append("db-pass");
		// Iterate over the keys
		for (int intKey = 0; intKey < qslDatabaseSettings.size(); ++intKey) {
			// Check the key
			if (Configuration::get(qslDatabaseSettings.value(intKey)).isNull()) {
				// Send the log message
				Log::fail(QString("Missing database configuration key (%1).").arg(qslDatabaseSettings.value(intKey)));
				// Reset the flag
				blnDBOK = false;
			}
		}
		// Check the flag
		if (blnDBOK == true) {
			// Create the database connection
			QSqlDatabase qsdTuxNS = QSqlDatabase::addDatabase("QPSQL");
			// Setup the connection
			qsdTuxNS.setDatabaseName(Configuration::get("db-name").toString());
			qsdTuxNS.setHostName    (Configuration::get("db-host").toString());
			qsdTuxNS.setPort        (Configuration::get("db-port").toInt());
			qsdTuxNS.setUserName    (Configuration::get("db-user").toString());
			qsdTuxNS.setPassword    (Configuration::get("db-pass").toString());
			// Try to open the connection
			if (!qsdTuxNS.open()) {
				// Send the log message
				Log::fail(QString("No database connection can be established:  %1").arg(qsdTuxNS.lastError().driverText()));
				Log::fail("Terminating!");
				// We're done
				return false;
			}
		} else {
			// Send the log message
			Log::fail("No database connection can be established.  Terminating!");
			// We're done
			return false;
		}
		// We're done
		return true;
	}

	bool Bootstrap::gatherLogSettings()
	{
		// Check for a log file path
		if (!Configuration::get("log").isNull()) {
			// Load the file
			QFile fleLog(Configuration::get("log").toString());
			// Check the file
			if (!fleLog.exists()) {            // Doesn't exist
				// Send the log message
				Log::warn(QString("Log file (%1) does not exist.  Falling back to STDERR logging.").arg(fleLog.fileName()));
			} else {
				// Try to open the log file
				if (!fleLog.open(QFile::ReadWrite)) {
					// Send the log message
					Log::warn(QString("Log file (%1) cannot be opened.  Falling back to STDERR logging.").arg(fleLog.fileName()));
				} else if (!fleLog.isReadable()) { // Isn't readable
					// Send the log message
					Log::warn(QString("Log file (%1) is not readable.  Falling back to STDERR logging.").arg(fleLog.fileName()));
				} else if (!fleLog.isWritable()) { // Isn't writable
					// Send the log message
					Log::warn(QString("Log file (%1) is not writable.  Falling back to STDERR logging.").arg(fleLog.fileName()));
				} else {                           // Log file is good
					// Set the logfile
					Log::setLogFile        (Configuration::get("log",          "/tmp/tuxns-pdns-backend.log").toString());
					// Reset the logging facility
					Log::setLoggingFacility(Configuration::get("log-facility", 2).toInt());
					// Reset the logging level
					Log::setLogLevel       (Configuration::get("log-level",    3).toInt());
				}
			}
			// We're done
			return true;
		} else {
			// Send the log message
			Log::warn("Log file not set.  Falling back to STDERR logging.");
			// We're done
			return false;
		}
	}

	bool Bootstrap::processConfiguration()
	{
		// Gather the log settings
		this->gatherLogSettings();
		// Gather the database settings
		return this->gatherDatabaseSettings();
	}

	void Bootstrap::setupCLI()
	{
		// Setup the parser
		this->mInput->addHelpOption();
		this->mInput->addVersionOption();
		// Add the configuration file option
		this->mInput->addOption(QCommandLineOption(
			QStringList() << "c" << "config-file",
			QCoreApplication::translate("main", "The path that the configuration file will be located."),
			QCoreApplication::translate("main", "path")
		));
		// Add the control options
		this->mInput->addOption(QCommandLineOption(
			QStringList() << "d" << "daemon",
			QCoreApplication::translate("main", "This service will be run as a daemon")
		));
		// Add the pipe option
		this->mInput->addOption(QCommandLineOption(
			QStringList() << "p" << "pipe",
			QCoreApplication::translate("main", "This service will be a one-off with the query piped through STDIN")
		));
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	bool Bootstrap::daemon()
	{
		// Try to start the server
		try {
			// Instantiate our listener
			this->mListener = new Listener();
			// Await connections
			this->mListener->await();
			// We're done
			return true;
		} catch (...) {
			// Send the log message
			Log::fail("Server failed to start");
			// We're done
			return false;
		}
	}

	bool Bootstrap::prepare()
	{
		// Send the log message
		Log::debug(QString("Application Starting Up:  %1").arg(QString(this->mApplication.startingUp())));
		// Process the input
		this->setupCLI();
		// Process the arguments
		this->mInput->process(this->mApplication);
		// Check for a config file
		if (!this->mInput->isSet("config-file")) {
			// Send the log message
			Log::fail("Configuration file not specified.");
			// We're done
			return false;
		}
		// Load the configuration
		if (!Configuration::initialize(this->mInput->value("config-file"))) {
			// We're done
			return false;
		}
		// Process the configuration
		if (!this->processConfiguration()) {
			// We're done
			return false;
		}
		// Check for a startup command
		if (this->mInput->isSet("daemon")) {
			// Return the start status
			return this->daemon();
		} else {
			// Send the log message
			Log::fail("No valid control command provided.");
			// We're done
			return false;
		}

	}


	///////////////////////////////////////////////////////////////////////////
	/// Public Slots /////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
} //  End TuxNS Namespace ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
