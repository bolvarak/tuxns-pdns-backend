///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef TUXNS_BOOTSTRAP_H
#define TUXNS_BOOTSTRAP_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QCoreApplication"
#include "QtCore/QObject"
#include "QtCore/QSettings"
#include "QtCore/QString"
#include "QtCore/QStringList"
#include "QtNetwork/QLocalSocket"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "Log.hpp"
#include "Listener.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{
	///////////////////////////////////////////////////////////////////////////
	/// TuxNS::Bootstrap Class Definition ////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	class Bootstrap : public QCoreApplication
	{
		///////////////////////////////////////////////////////////////////////
		/// QObject Classification ///////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		Q_OBJECT

		///////////////////////////////////////////////////////////////////////
		/// Protected Methods & Properties ///////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		protected:

			///////////////////////////////////////////////////////////////////
			/// Constants ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constant contains the identifier for a restart action
			 * @brief TuxNS::Bootstrap::ActionRestart
			 * @var int
			 */
			static const int ActionRestart;

			/**
			 * @paragraph This constant contains the identifier for a start action
			 * @brief TuxNS::Bootstrap::ActionStart
			 * @var int
			 */
			static const int ActionStart;

			/**
			 * @paragraph This constant contains the identifier for a stop action
			 * @brief TuxNS::Bootstrap::ActionStop
			 * @var int
			 */
			static const int ActionStop;

			/**
			 * @paragraph This constant contains the command for restarting the service
			 * @brief TuxNS::Bootstrap::CmdRestart
			 * @var QString
			 */
			static const QString CmdRestart;

			/**
			 * @paragraph This constant contains the command for starting the server
			 * @brief TuxNS::Bootstrap::CmdStart
			 * @var QString
			 */
			static const QString CmdStart;

			/**
			 * @paragraph This constant contains the command for stopping the service
			 * @brief TuxNS::Bootstrap::CmdStop
			 * @var QString
			 */
			static const QString CmdStop;

			/**
			 * @paragraph This constant contains the optional configuration file path
			 * @brief TuxNS::Bootstrap::OptConfigFile
			 * @var QString
			 */
			static const QString OptConfigFile;

			///////////////////////////////////////////////////////////////////
			/// Static Properties ////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains our settings
			 * @brief TuxNS::Bootstrap::mSettings
			 * @var QSettings*
			 */
			static QSettings* mSettings;

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property tells the system which action to take after preload
			 * @brief TuxNS::Bootstrap::mAction
			 * @var int
			 */
			int mAction;

			/**
			 * @paragraph This property contains the arguments passed from STDIN
			 * @brief TuxNS::Bootstrap::mArguments
			 * @var QStringList
			 */
			QStringList mArguments;

			/**
			 * @paragraph This property contains the number of arguments passed from STDIN
			 * @brief TuxNS::Bootstrap::mArgumentCount
			 * @var int
			 */
			int mArgumentCount;

			/**
			 * @paragraph This property contains the path to the configuration file
			 * @brief TuxNS::Bootstrap::mConfiguration
			 * @var QString
			 */
			QString mConfiguration;

			/**
			 * @paragraph This property tells the system whether it is running or not
			 * @brief TuxNS::Bootstrap::mRunning
			 * @var bool
			 */
			bool mRunning;

			///////////////////////////////////////////////////////////////////
			/// Protected Methods ////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method processes the log settings into the service
			 * @brief TuxNS::Bootstrap::gatherLogSettings()
			 * @return bool
			 */
			bool gatherLogSettings();

			/**
			 * @paragraph This method processes the database settings into the service
			 * @brief TuxNS::Bootstrap::gatherDatabaseSettings()
			 * @return bool
			 */
			bool gatherDatabaseSettings();

			/**
			 * @paragraph This method processes the command line arguments to the instance
			 * @brief TuxNS::Bootstrap::processArguments()
			 * @return bool
			 */
			bool processArguments();

			/**
			 * @paragraph This method processes the configuration file for the application
			 * @brief TuxNS::Bootstrap::processConfiguration()
			 * @return bool
			 */
			bool processConfiguration();

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method instantiates the object with defaults
			 * @brief TuxNS::Bootstrap::Bootstrap()
			 * @param int intArguments
			 * @param char* chrArguments[]
			 */
			explicit Bootstrap(int intArguments, char* chrArguments[]);

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method dispatches the service
			 * @brief TuxNS::Bootstrap::dispatch()
			 * @return bool
			 */
			bool dispatch();

			/**
			 * @paragraph This method loops until the application is closed
			 * @brief TuxNS::Bootstrap::eventLoop()
			 * @return int
			 */
			int eventLoop();

			/**
			 * @paragraph This method restarts the server
			 * @brief TuxNS::Bootstrap::restart()
			 * @return void
			 */
			bool restart();

			/**
			 * @paragraph This method starts the server
			 * @brief TuxNS::Bootstrap::start()
			 * @return void
			 */
			bool start();

			/**
			 * @paragraph This method stops the server
			 * @brief TuxNS::Bootstrap::stop()
			 * @param bool blnIsRunning [false]
			 * @return void
			 */
			bool stop(bool blnIsRunning = false);

			///////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method returns a setting from the configuration file
			 * @brief TuxNS::Bootstrap::getSetting()
			 * @param QString strPath
			 * @param QVariant qvDefault [QVariant()]
			 * @return QVariant
			 */
			inline static QVariant getSetting(QString strPath, QVariant qvDefault = QVariant()) {
				// Return the setting
				return mSettings->value(strPath.replace(".", "/"), qvDefault);
			}

			///////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method writes or overwrites a setting in the configuration file
			 * @brief TuxNS::Bootstrap::setSetting()
			 * @param QString strPath
			 * @param QVariant qvValue
			 * @return bool
			 */
			inline static bool setSetting(QString strPath, QVariant qvValue) {
				// Check to see if the settings are writable
				if (mSettings->isWritable()) {
					// Write the new value
					mSettings->setValue(strPath, qvValue);
					// We're done
					return true;
				}
				// We're done
				return false;
			}

		///////////////////////////////////////////////////////////////////////
		/// Public Slots /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public slots:

			/**
			 * @paragraph This slot gets executed when a shutdown request is received
			 * @brief TuxNS::Bootstrap::shutdownReceived()
			 * @return void
			 */
			void shutdownReceived();

	///////////////////////////////////////////////////////////////////////////
	}; // End TuxNS::Bootstrap Class Definition //////////////////////////////
	/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#endif // End Definitions ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
