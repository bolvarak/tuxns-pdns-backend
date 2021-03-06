///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef TUXNS_CONFIGURATION_H
#define TUXNS_CONFIGURATION_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QFile"
#include "QtCore/QObject"
#include "QtCore/QSettings"
#include "QtCore/QString"
#include "QtCore/QVariant"
#include "Log.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{
	///////////////////////////////////////////////////////////////////////////
	/// TuxNS::Configuration Class Definition ////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	class Configuration : public QObject
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
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains our settings
			 * @brief TuxNS::Configuration::mSettings
			 * @var QSettings*
			 */
			static QSettings* mSettings;

			/**
			 * @paragraph This property contains the filepath to our store
			 * @brief TuxNS::Configuration::mStore
			 * @var QString
			 */
			static QString mStore;

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method initializes the instance store
			 * @brief TuxNS::Configuration::initialize()
			 * @param QString strFilePath
			 * @return bool
			 */
			static bool initialize(QString strFilePath = NULL);

			///////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method retrieves settings from our store
			 * @brief TuxNS::Configuration::get()
			 * @param QString strProperty
			 * @param QVariant qvDefault [QVariant()]
			 * @return QVariant
			 */
			static QVariant get(QString strProperty, QVariant qvDefault = QVariant());

			///////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method sets a property into our store
			 * @brief TuxNS::Configuration::set()
			 * @param QString strProperty
			 * @param QVariant qvValue
			 * @return bool
			 */
			static bool set(QString strProperty, QVariant qvValue);

			/**
			 * @paragraph This method sets the configuration store file path into the class
			 * @brief TuxNS::Configuration::setStore()
			 * @param QString strFilePath
			 * @return bool
			 */
			static bool setStore(QString strFilePath);

	///////////////////////////////////////////////////////////////////////////
	}; // End TuxNS::Class Definition ////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#endif // End Definitions ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
