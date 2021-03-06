///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QByteArray"
#include "QtCore/QDebug"
#include "QtCore/QJsonArray"
#include "QtCore/QJsonDocument"
#include "QtCore/QJsonObject"
#include "QtCore/QJsonParseError"
#include "QtCore/QJsonValue"
#include "QtCore/QObject"
#include "QtCore/QString"
#include "QtCore/QTextStream"
#include "QtCore/QVariant"
#include "QtCore/QVariantList"
#include "QtCore/QVariantMap"
#include "../Log.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{
	///////////////////////////////////////////////////////////////////////////
	/// TuxNS::PowerDNS Namespace ////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	namespace PowerDNS
	{
		///////////////////////////////////////////////////////////////////////
		/// TuxNS::PowerDNS::Response Class Definition ///////////////////////
		/////////////////////////////////////////////////////////////////////

		class Response : public QObject
		{
			///////////////////////////////////////////////////////////////////
			/// QObject Classification ///////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			Q_OBJECT

			///////////////////////////////////////////////////////////////////
			/// Protected Methods & Properties ///////////////////////////////
			/////////////////////////////////////////////////////////////////

			protected:

				///////////////////////////////////////////////////////////////
				/// Properties ///////////////////////////////////////////////
				/////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method contains the records that we'll be returning
				 * @brief TuxNS::PowerDNS::Response::mRecords
				 * @var QJsonArray
				 */
				QJsonArray mRecords;

				/**
				 * @paragraph This property contains the response object
				 * @brief TuxNS::PowerDNS::Response::mResponse
				 * @var QJsonObject
				 */
				QJsonObject mResponse;

			///////////////////////////////////////////////////////////////////
			/// Public Methods & Properties //////////////////////////////////
			/////////////////////////////////////////////////////////////////

			public:

				///////////////////////////////////////////////////////////////
				/// Constructor //////////////////////////////////////////////
				/////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method instantiates the instance with defaults
				 * @brief TuxNS::PowerDNS::Response::Response()
				 * @param QJsonDocument* qjoParent [0]
				 */
				explicit Response(QObject* objParent = 0);

				///////////////////////////////////////////////////////////////
				/// Methods //////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method adds a record to the response
				 * @brief TuxNS::PowerDNS::Response::addRecord()
				 * @param QString strQType
				 * @param QString strQName
				 * @param QString strContent
				 * @param int intTTL
				 * @param bool blnAuth [true]
				 * @param int intPriority [-1]
				 * @return void
				 */
				void addRecord(int intDomainID, QString strQType, QString strQName, QString strContent, int intTTL, bool blnAuth = true, int intPriority = -1);

				/**
				 * @paragraph This method simply returns an error response
				 * @brief TuxNS::PowerDNS::Response::toError()
				 * @return void
				 */
				void errorResponse();

				/**
				 * @paragraph This method simply returns a bare success response
				 * @brief TuxNS::PowerDNS::Response::successResponse()
				 * @return void
				 */
				void successResponse();

				/**
				 * @paragraph This method sends the JSON to STDOUT
				 * @brief TuxNS::PowerDNS::Response::toStdOut()
				 * @return QByteArray
				 */
				QByteArray write();

				///////////////////////////////////////////////////////////////
				/// Getters //////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method returns the array of records from the instance
				 * @brief TuxNS::PowerDNS::Response::getRecords()
				 * @return QJsonArray TuxNS::PowerDNS::Response::mRecords
				 */
				inline QJsonArray getRecords() { return this->mRecords; }

		///////////////////////////////////////////////////////////////////////
		}; // End TuxNS::PowerDNS::Response Class Definition /////////////////
		/////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	} // End TuxNS::PowerDNS Namespace ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#endif // End Definitions ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
