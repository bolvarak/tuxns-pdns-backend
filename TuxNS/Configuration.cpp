///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "Configuration.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{
	///////////////////////////////////////////////////////////////////////////
	/// Protected Properties /////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	QSettings* Configuration::mSettings = new QSettings(0);
	QString Configuration::mStore       = QString::null;

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	bool Configuration::initialize(QString strFilePath)
	{
		// Check for a configuration file
		if (mStore.isNull() && strFilePath.isNull()) {
			// Send the log message
			Log::fail("No configuration file provided.");
			// We're done
			return false;
		}
		// Check for a provided file
		if (!strFilePath.isNull()) {
			// Reset the configuration file
			mStore = strFilePath;
		}
		// Create the file
		QFile fleStore(mStore);
		// Make sure the file exists
		if (!fleStore.exists()) {
			// Send the log message
			Log::fail(QString("Configuration file (%1) does not exist.").arg(mStore));
			// We're done
			return false;
		}
		// Try to open the file
		if (!fleStore.open(QFile::ReadWrite) && !fleStore.open(QFile::ReadOnly)) {
			// Send the log message
			Log::fail(QString("Configuration file (%1) could not be opened.").arg(mStore));
			// We're done
			return false;
		}
		// Check for writability
		if (!fleStore.isReadable()) {
			// Send the log message
			Log::fail(QString("Configuration file (%1) could not be read.").arg(mStore));
			// We're done
			return false;
		}
		// Close the file
		fleStore.close();
		// Set the configuration file
		mSettings = new QSettings(mStore, QSettings::IniFormat);
		// Check for writability
		if (!mSettings->isWritable()) {
			// Send the log message
			Log::warn(QString("Configuration file (%1) is not writable.  Configuration::set() will be disabled.").arg(mStore));
		}
		// We're done
		return true;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	QVariant Configuration::get(QString strProperty, QVariant qvDefault)
	{
		// Send the log message
		Log::debug(QString("Retrieving property (%1) with default value (%2) from configuration file (%3)").arg(strProperty, qvDefault.toString(), mStore));
		// Return the setting
		return mSettings->value(strProperty.replace(".", "/"), qvDefault);
	}

	///////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	bool Configuration::set(QString strProperty, QVariant qvValue)
	{
		// Try to set the property
		try {
			// Check for writability
			if (mSettings->isWritable()) {
				// Set the property
				mSettings->setValue(strProperty.replace(".", "/"), qvValue);
				// Send the log message
				Log::debug(QString("Set property (%1) to value (%2) into configuration file (%3)").arg(strProperty, qvValue.toString(), mStore));
			} else {
				// Send the log message
				Log::debug(QString("Configuration file (%1) is not writable.  Ignoring this request.").arg(mStore));
			}
			// We're done
			return true;
		} catch (...) {
			// Send the log message
			Log::fail(QString("Cannot set property (%1) into configuration file (%2)").arg(strProperty, mStore));
			// We're done
			return false;
		}
	}

	bool Configuration::setStore(QString strFilePath)
	{
		// Check for an empty file path
		if (strFilePath.isEmpty()) {
			// Send the log message
			Log::fail("Configuration cannot be empty.");
			// We're done
			return false;
		}
		// Return the initialization status
		return initialize(strFilePath);
	}

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
