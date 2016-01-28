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
	/// Protected Constants //////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	const int Bootstrap::ActionRestart       = 0x01;
	const int Bootstrap::ActionStart         = 0x02;
	const int Bootstrap::ActionStop          = 0x03;
	const QString Bootstrap::CmdRestart      = "--restart";
	const QString Bootstrap::CmdStart        = "--start";
	const QString Bootstrap::CmdStop         = "--stop";
	const QString Bootstrap::OptConfigFile   = "--config-file";

	///////////////////////////////////////////////////////////////////////////
	/// Protected Static Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	QSettings* Bootstrap::mSettings = new QSettings(0);

	///////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	Bootstrap::Bootstrap(int intArguments, char* chrArguments[]) : QCoreApplication(intArguments, chrArguments)
	{
		// Iterate over the arguments
		for (int intArgument = 0; intArgument < intArguments; ++intArgument) {
			// Add the argument to the instance
			this->mArguments.append(QString::fromLatin1(chrArguments[intArgument]));
		}
		// Set our defaults
		this->mAction        = 0;
		this->mArgumentCount = intArguments;
		this->mConfiguration = QString::null;
		this->mRunning       = false;
		// Setup the application details
		this->setApplicationName   ("TuxNS PowerDNS Remote Backend");
		this->setApplicationVersion("1.0.1");
		this->setOrganizationDomain("tuxns.net");
		this->setOrganizationName  ("TuxNS");
		// Setup our logger
		Log::setLoggingFacility(Log::Standard);
		Log::setLogLevel       (Log::Debug);
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
			if (getSetting(qslDatabaseSettings.value(intKey)).isNull()) {
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
			qsdTuxNS.setDatabaseName(getSetting("db-name").toString());
			qsdTuxNS.setHostName    (getSetting("db-host").toString());
			qsdTuxNS.setPort        (getSetting("db-port").toInt());
			qsdTuxNS.setUserName    (getSetting("db-user").toString());
			qsdTuxNS.setPassword    (getSetting("db-pass").toString());
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
		if (!getSetting("log").isNull()) {
			// Load the file
			QFile fleLog(getSetting("log").toString());
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
					Log::setLogFile(getSetting("log").toString());
					// Reset the logging facility
					Log::setLoggingFacility(Log::File);
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

	bool Bootstrap::processArguments()
	{
		// Iterate over the arguments
		for (int intArgument = 1; intArgument < this->mArgumentCount; ++intArgument) {
			// Determine the command
			if (this->mArguments.value(intArgument).toLower() == CmdRestart) {            // Restart the server
				// Check for an existing action and set it
				this->mAction = ((this->mAction == 0) ? ActionRestart : this->mAction);
			} else if (this->mArguments.value(intArgument).toLower() == CmdStart) {       // Start the server
				// Check for an existing action and set it
				this->mAction = ((this->mAction == 0) ? ActionStart : this->mAction);
			} else if (this->mArguments.value(intArgument).toLower() == CmdStop) {        // Stop the server
				// Check for an existing action and set it
				this->mAction = ((this->mAction == 0) ? ActionStop : this->mAction);
			}  else if (this->mArguments.value(intArgument).toLower() == OptConfigFile) {  // Set Configuration File
				// Create the file
				QFile fleConfig(this->mArguments.value(intArgument + 1));
				// Check the next argument for a file
				if (fleConfig.exists()) {
					// Try to open the file
					if (!fleConfig.open(QFile::ReadWrite) && !fleConfig.open(QFile::ReadOnly)) {
						// Send the log message
						Log::fail(QString("Configuration file (%1) cannot be opened.").arg(this->mArguments.value(intArgument + 1)));
						// We're done
						return false;
					}
					// Check to see if it is readable
					if (!fleConfig.isReadable()) {
						// Send the log message
						Log::fail(QString("Configuration file (%1) is not readable.").arg(this->mArguments.value(intArgument + 1)));
						// We're done
						return false;
					}
					// Check to see if the file is writable
					if (!fleConfig.isWritable()) {
						// Send the log message
						Log::warn(QString("Configuration file (%1) is not writable, setSetting() will not work.").arg(this->mArguments.value(intArgument + 1)));
					}
					// Set the configuration file
					this->mConfiguration = this->mArguments.value(intArgument + 1);
					// Close the file
					fleConfig.close();
					// Increment the iterator
					++intArgument;
				} else {
					// Send the log message
					Log::fail(QString("Configuration file (%1) does not exist.").arg(this->mArguments.value(intArgument + 1)));
					// We're done
					return false;
				}
			} else {

			}
		}
		// We're done
		return true;
	}

	bool Bootstrap::processConfiguration()
	{
		// Set the settings into the instance
		mSettings = new QSettings(this->mConfiguration, QSettings::IniFormat);
		// Gather the log settings
		this->gatherLogSettings();
		// Gather the database settings
		return this->gatherDatabaseSettings();
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	bool Bootstrap::dispatch()
	{
		// Check for arguments
		if (this->mArgumentCount <= 1) {
			// Send the log message
			Log::fail("No arguments provided.  Terminating.");
			// We're done
			return false;
		}
		// Process the arguments
		if (!this->processArguments()) {
			// Send the log message
			Log::fail("Unable to process arguments.  Terminating!");
			// We're done
			return false;
		}

		// Check for an action
		if (this->mAction == 0) {
			// Send the log message
			Log::fail("No action specified.  Terminating.");
			// We're done
			return false;
		}
		// Check for a configuration file
		if (this->mConfiguration.isNull() || this->mConfiguration.isEmpty() || !this->processConfiguration()) {
			// Send the log message
			Log::fail("No configuration provided.  Terminating.");
			// We're done
			return false;
		}
		// Determine the action to take
		if (this->mAction == ActionRestart) {      // Restart
			// Restart the server
			return this->restart();
		} else if (this->mAction == ActionStart) { // Start
			// Start the server
			return this->start();
		} else if (this->mAction == ActionStop) {  // Stop
			// Stop the server
			this->stop(false);
			// We're done
			return false;
		} else {                                   // Not Implemented
			// Send the log message
			Log::fail("An action has been requested.");
			// By default return false
			return false;
		}
	}


	int Bootstrap::eventLoop()
	{
		// Loop infinitely
		while (this->mRunning == true) {
			// Continue
			continue;
		}
		// We're done
		return 0;
	}

	bool Bootstrap::restart()
	{
		// Try to restart the server
		try {
			// Restart the server
			return (this->stop(true) && this->start());
		} catch (...) {
			// Send the log message
			Log::fail("Server failed to restart");
			// We're done
			return false;
		}
	}

	bool Bootstrap::start()
	{
		// Try to start the server
		try {
			// Instantiate our backend
			TuxNS::Listener* tnsSocket = new TuxNS::Listener();
			// Make the connection
			this->connect(tnsSocket, SIGNAL(hasShutdown()), this, SLOT(shutdownReceived()));
			// Await connections
			tnsSocket->await();
			// Reset the running flag
			this->mRunning = true;
			// We're done
			return true;
		} catch (...) {
			// Send the log message
			Log::fail("Server failed to start");
			// We're done
			return false;
		}
	}

	bool Bootstrap::stop(bool blnIsRunning)
	{
		// Try to stop the server
		try {
			// Create the socket
			QLocalSocket* qlsServer = new QLocalSocket();
			// Connect to the local server
			qlsServer->connectToServer(Bootstrap::getSetting("socket", "/tmp/tuxns-pdns.sock").toString());
			// Send the log message
			Log::debug("Establishing server connection.");
			// Try to open the server connection
			if (qlsServer->open(QLocalSocket::ReadWrite) || qlsServer->isOpen()) {
				// Send the log message
				Log::debug("Connection established!  Waiting for ready state.");
				// Send the log message
				Log::debug("Sending shutdown command.");
				// Send the packet
				qlsServer->write(QString("CMD EXEC %1").arg(Bootstrap::getSetting("shutdown-key", "shutdown now").toString()).toLatin1().append("\n"));
				// Send the log message
				Log::debug("Shutdown sent!  Waiting for termination.");
				// Close the connection
				qlsServer->close();
				// Reset the running flag
				this->mRunning = blnIsRunning;
				// Check the running flag
				if (!blnIsRunning) {
					// We're done
					return false;
				} else {
					// We're done
					return true;
				}
			} else {
				// Send the log message
				Log::fail("Could not establish connection to running server.");
				// Reset the running flag
				this->mRunning = blnIsRunning;
				// We're done
				return false;
			}
		} catch (...) {
			// Send the log message
			Log::fail("Server failed to stop");
			// We're done
			return false;
		}
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Slots /////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void Bootstrap::shutdownReceived()
	{
		// Check to see if we need to kill the main event loop
		if (this->mRunning == false) {
			// Send the log message
			Log::warn("Terminating Application Event Loop.");
			// Kill the application
			this->quit();
		}
	}

///////////////////////////////////////////////////////////////////////////////
} //  End TuxNS Namespace ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
