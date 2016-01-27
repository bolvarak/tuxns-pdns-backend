///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "Log.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{

	///////////////////////////////////////////////////////////////////////////
	/// Protected Constants //////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	const QString Log::PrefixDebug  = "[Debug]  ";
	const QString Log::PrefixError  = "[Error]  ";
	const QString Log::PrefixFail   = "[Failure]";
	const QString Log::PrefixNotice = "[Notice] ";
	const QString Log::PrefixWarn   = "[Warning]";

	///////////////////////////////////////////////////////////////////////////
	/// Public Constants /////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	const int Log::Debug    = 1;
	const int Log::Error    = 3;
	const int Log::Fail     = 4;
	const int Log::File     = 0x01;
	const int Log::Notice   = 5;
	const int Log::Standard = 0x02;
	const int Log::Warn     = 2;

	///////////////////////////////////////////////////////////////////////////
	/// Properties ///////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	int Log::mLogFacility   = Log::File;
	QString Log::mLogFile   = NULL;
	int Log::mLogLevel      = Log::Debug;

	///////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	Log::Log() {}

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	QStringList Log::availablePrefixes(int intLogLevel)
	{
		// Create the list to hold our level prefixes
		QStringList qslPrefixes;
		// Check the level
		if (mLogLevel == 5) {
			// Add the notice prefix
			qslPrefixes.append(PrefixNotice);
		} else if (mLogLevel >= 4) {
			// Add the prefixes
			qslPrefixes.append(PrefixNotice);
			qslPrefixes.append(PrefixFail);
		} else if (mLogLevel >= 3) {
			// Add the prefixes
			qslPrefixes.append(PrefixNotice);
			qslPrefixes.append(PrefixFail);
			qslPrefixes.append(PrefixError);
		} else if (mLogLevel >= 2) {
			// Add the prefixes
			qslPrefixes.append(PrefixNotice);
			qslPrefixes.append(PrefixFail);
			qslPrefixes.append(PrefixError);
			qslPrefixes.append(PrefixWarn);
		} else {
			// Add the prefixes
			qslPrefixes.append(PrefixNotice);
			qslPrefixes.append(PrefixFail);
			qslPrefixes.append(PrefixError);
			qslPrefixes.append(PrefixWarn);
			qslPrefixes.append(PrefixDebug);
		}
		// Return the prefixes
		return qslPrefixes;
	}

	void Log::write(QString strMessage, QString strPrefix, int intFacility)
	{
		// Check the prefix
		if (availablePrefixes(mLogLevel).contains(strPrefix, Qt::CaseInsensitive)) {
			// Check the facility
			if (intFacility == Log::File) {
				// Write to the file
				writeToFile(strMessage, strPrefix);
			} else {
				writeToStd(strMessage, strPrefix);
			}
		}
	}

	void Log::writeToFile(QString strMessage, QString strPrefix)
	{
		// Check for a file handle
		if (mLogFile.isNull() || mLogFile.isEmpty()) {
			// Reset the logging facility
			mLogFacility = Standard;
			// Log the warning
			warn("File logging facility chosen, but no file specified.  Falling back to Standard facility.");
			// Log the message
			return write(strMessage, strPrefix, Standard);
		}
		// Create the file handle
		QFile fleLog(mLogFile);
		// Open the file
		if (!fleLog.open(QFile::Append)) {
			// Reset the logging facility
			mLogFacility = Standard;
			// Log the warning
			warn(QString("File logging facility chosen, but file (%1) cannot be opened.  Falling back to Standard facility.").arg(mLogFile));
			// Log the message
			return write(strMessage, strPrefix, Standard);
		}
		// Set the timestamp
		QDateTime qdtNow  = QDateTime::currentDateTime();
		// Create the output string
		QString strOutput = QString("%1[%2]\t%3\n").arg(strPrefix, qdtNow.toString("yyyy-MM-dd HH:mm:ss t"), strMessage);
		// Write the line to the log
		fleLog.write(strOutput.toLatin1());
		// Close the file
		fleLog.close();
	}

	void Log::writeToStd(QString strMessage, QString strPrefix)
	{
		// Set the timestamp
		QDateTime qdtNow  = QDateTime::currentDateTime();
		// Create the output string
		QString strOutput = QString("[TuxNS]%1[%2]\t%3").arg(strPrefix, qdtNow.toString("yyyy-MM-dd HH:mm:ss t"), strMessage);
		// Write the output
		std::cout << strOutput.toLatin1().constData() << std::endl;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void Log::debug(QString strMessage)
	{
		// Send the message
		write(strMessage, Log::PrefixError, mLogFacility);
	}

	void Log::error(QString strMessage)
	{
		// Send the message
		write(strMessage, Log::PrefixError, mLogFacility);
	}

	void Log::fail(QString strMessage)
	{
		// Send the message
		write(strMessage, Log::PrefixFail, mLogFacility);
	}

	void Log::notice(QString strMessage)
	{
		// Send the message
		write(strMessage, Log::PrefixNotice, mLogFacility);
	}

	void Log::warn(QString strMessage)
	{
		// Send the message
		write(strMessage, Log::PrefixWarn, mLogFacility);
	}

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
