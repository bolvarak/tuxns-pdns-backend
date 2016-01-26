///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef TUXNS_LOG_H
#define TUXNS_LOG_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "iostream"
#include "QtCore/QByteArray"
#include "QtCore/QDateTime"
#include "QtCore/QDebug"
#include "QtCore/QFile"
#include "QtCore/QObject"
#include "QtCore/QString"
#include "QtCore/QStringList"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS {

	///////////////////////////////////////////////////////////////////////////
	/// TuxNS::Log Class Definition //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	class Log
	{
		///////////////////////////////////////////////////////////////////////
		/// Protected Methods & Properties ///////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		protected:

			///////////////////////////////////////////////////////////////////
			/// Constants ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constant contains the debug prefix
			 * @brief TuxNS::Log::PrefixDebug
			 * @var QString
			 */
			static const QString PrefixDebug;

			/**
			 * @paragraph This constant contains the error prefix
			 * @brief TuxNS::Log::PrefixError
			 * @var QString
			 */
			static const QString PrefixError;

			/**
			 * @paragraph This constant contains the fail prefix
			 * @brief TuxNS::Log::PrefixFail
			 * @var QString
			 */
			static const QString PrefixFail;

			/**
			 * @paragraph This constant contains the notice prefix
			 * @brief TuxNS::Log::PrefixNotice
			 * @var QString
			 */
			static const QString PrefixNotice;

			/**
			 * @paragraph This constant contains the warn prefix
			 * @brief TuxNS::Log::PrefixWarn
			 * @var QString
			 */
			static const QString PrefixWarn;

			///////////////////////////////////////////////////////////////////
			/// Static Properties ////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the logging facility in use
			 * @brief TuxNS::Log::mLogFacility
			 * @var int
			 */
			static int mLogFacility;

			/**
			 * @paragraph This property contains the path to the log file in use
			 * @brief TusNS::Log::mLogFile
			 * @var QString
			 */
			static QString mLogFile;

			/**
			 * @paragraph This property contains the level of logging to provide
			 * @brief TuxNS::Log::mLogLevel
			 * @var int
			 */
			static int mLogLevel;

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method determines the avaialable prefixes for the current log level
			 * @brief TuxNS::Log::availablePrefixes()
			 * @param int intLogLevel
			 * @return QStringList
			 */
			static QStringList availablePrefixes(int intLogLevel);

			/**
			 * @paragraph This method writes the message to the log
			 * @brief TuxNS::Log::write()
			 * @param QString strMessage
			 * @param QString strPrefix [TuxNS::Log::Debug]
			 * @param int intFacility [TuxNS::Log::Standard]
			 * @return void
			 */
			static void write(QString strMessage, QString strPrefix = PrefixDebug, int intFacility = Standard);

			/**
			 * @paragraph This method does the actual writing to the log file
			 * @brief TuxNS::Log::writeToFile()
			 * @param QString strMessage
			 * @param QString strPrefix
			 * @return void
			 */
			static void writeToFile(QString strMessage, QString strPrefix);

			/**
			 * @paragraph This method does the actual writing to standard out
			 * @brief TuxNS::Log::writeToStd()
			 * @param QString strMessage
			 * @param QString strPrefix
			 * @return void
			 */
			static void writeToStd(QString strMessage, QString strPrefix);

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Constants ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constant defines the Debug log level
			 * @brief TuxNS::Log::Debug
			 * @var int
			 */
			static const int Debug;

			/**
			 * @paragraph This constant defines the Error log level
			 * @brief TuxNS::Log::Error
			 * @var int
			 */
			static const int Error;

			/**
			 * @paragraph This constant defines the Fail log level
			 * @brief TuxNS::Log::Fail
			 * @var int
			 */
			static const int Fail;

			/**
			 * @paragraph This constant defines the file logging facility
			 * @brief TuxNS::Log::File
			 * @var int
			 */
			static const int File;

			/**
			 * @paragraph This constant defines the notice log level
			 * @brief TuxNS::Log::Notice
			 * @var int
			 */
			static const int Notice;

			/**
			 * @paragraph This constant defines the stdout logging facility
			 * @brief TuxNS::Log::Standard
			 * @var int
			 */
			static const int Standard;

			/**
			 * @paragraph This constatn defines the Warn log level
			 * @brief TuxNS::Log::Warn
			 * @var int
			 */
			static const int Warn;

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This is just a placeholder since this is a static class
			 * @brief TuxNS::Log::Log
			 */
			Log();

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method logs a debug message
			 * @brief TuxNS::Log::debug()
			 * @param QString strMessage
			 * @return void
			 */
			static void debug(QString strMessage);

			/**
			 * @paragraph This method logs an error message
			 * @brief TuxNS::Log::error()
			 * @param QString strMessage
			 * @return void
			 */
			static void error(QString strMessage);

			/**
			 * @paragraph This method logs a fail message
			 * @brief TuxNS::Log::fail()
			 * @param QString strMessage
			 * @return void
			 */
			static void fail(QString strMessage);

			/**
			 * @paragraph This method logs a notice message
			 * @brief TuxNS::Log::notice()
			 * @param QString strMessage
			 * @return void
			 */
			static void notice(QString strMessage);

			/**
			 * @paragraph This method logs a warning message
			 * @brief TuxNS::Log::warn()
			 * @param QString strMessage
			 * @return void
			 */
			static void warn(QString strMessage);

			///////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method sets the logging facility into the instance
			 * @brief TuxNS::Log::setLoggingFacility()
			 * @param int intFacility
			 * @return void
			 */
			inline static void setLoggingFacility(int intFacility) {
				// Set the logging facility
				mLogFacility = intFacility;
			}

			/**
			 * @paragraph This method sets the log file into the instance
			 * @brief TuxNS::Log::setLogFile()
			 * @param QByteArray qbaPath
			 * @return void
			 */
			inline static void setLogFile(QByteArray qbaPath) {
				// Set the log file
				mLogFile = QString::fromLatin1(qbaPath);
			}

			/**
			 * @paragraph This method sets the log file into the instance
			 * @brief TuxNS::Log::setLogFile()
			 * @param QString strPath
			 * @return void
			 */
			inline static void setLogFile(QString strPath) {
				// Set the log file
				mLogFile = strPath;
			}

			/**
			 * @paragraph This method sets the log level into the instance
			 * @brief TuxNS::Log::setLogLevel()
			 * @param int intLevel
			 * @return void
			 */
			inline static void setLogLevel(int intLevel) {
				// Set the log level
				mLogLevel = intLevel;
			}

	///////////////////////////////////////////////////////////////////////////
	}; // End TuxNS::Log Class Definition ////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#endif // End Definitions ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
