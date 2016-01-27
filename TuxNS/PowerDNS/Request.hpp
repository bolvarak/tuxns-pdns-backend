///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef TUXNS_POWERDNS_REQUEST_H
#define TUXNS_POWERDNS_REQUEST_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "iostream"
#include "QtCore/QByteArray"
#include "QtCore/QDebug"
#include "QtCore/QFile"
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
#include "QtNetwork/QHostAddress"
#include "../Log.hpp"
#include "Method.hpp"
#include "Response.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{

	///////////////////////////////////////////////////////////////////////////
	/// TuxNS Namespace //////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	namespace PowerDNS {

		///////////////////////////////////////////////////////////////////////
		/// TuxNS::PowerDNS::Request Class Definition ////////////////////////
		/////////////////////////////////////////////////////////////////////

		class Request : public QObject
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
				 * @paragraph This property contains the decoded requesst
				 * @brief TuxNS::PowerDNS::Request::mRequest
				 * @var QJsonObject
				 */
				QJsonObject mRequest;

				/**
				 * @paragraph This property contains the raw request JSON
				 * @brief TuxNS::PowerDNS::Request::mRequestJSON
				 * @var QByteArray
				 */
				QByteArray mRequestJSON;

				/**
				 * @paragraph This property contains the response to send
				 * @brief TuxNS::PowerDNS::Request::mResponse
				 * @var TuxNS::PowerDNS::Response*
				 */
				TuxNS::PowerDNS::Response* mResponse;

				///////////////////////////////////////////////////////////////
				/// Methods //////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////

			///////////////////////////////////////////////////////////////////
			/// Public Methods & Properties //////////////////////////////////
			/////////////////////////////////////////////////////////////////

			public:

				///////////////////////////////////////////////////////////////
				/// Static Methods ///////////////////////////////////////////
				/////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method creates an instance from the arguments
				 * @brief TuxNS::PowerDNS::Request::fromArg()
				 * @param QByteArray qbaValue
				 * @return TuxNS::PowerDNS::Request*
				 */
				static Request* fromArg(QByteArray qbaValue);

				/**
				 * @paragraph This method creates an instance from raw JSON
				 * @brief TuxNS::PowerDNS::Request::fromJson()
				 * @param QVariant qvJson
				 * @return TuxNS::PowerDNS::Request*
				 */
				static Request* fromJson(QVariant qvJson);

				/**
				 * @paragraph This method creates an instance from STDIN
				 * @brief TuxNS::PowerDNS::Request::fromStdin()
				 * @return TuxNS::PowerDNS::Request*
				 */
				static Request* fromStdin();

				///////////////////////////////////////////////////////////////
				/// Constructors /////////////////////////////////////////////
				/////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method intantiates the class with the request from a QString source
				 * @brief TuxNS::PowerDNS::Request::Request()
				 * @param QString strJSON
				 * @param QObject* objParent [0]
				 */
				explicit Request(QString strJSON, QObject* objParent = 0);

				/**
				 * @paragraph This method intantiates the class with the request from a QByteArray source
				 * @brief TuxNS::PowerDNS::Request::Request()
				 * @param QByteArray qbaJSON
				 * @param QObject* objParent [0]
				 */
				explicit Request(QByteArray qbaJSON, QObject* objParent = 0);

				///////////////////////////////////////////////////////////////
				/// Methods //////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method parses the request from PowerDNS
				 * @brief TuxNS::PowerDNS::Request::parse()
				 * @return TuxNS::PowerDNS::Request* this
				 */
				Request* parse();

				/**
				 * @paragraph This method sends the response directly to STDOUT
				 * @brief TuxNS::PowerDNS::Request::reply()
				 * @param bool blnDirect [false]
				 * @return QByteArray
				 */
				QByteArray reply(bool blnDirect = false);

				///////////////////////////////////////////////////////////////
				/// Getters //////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method returns the response object from the instance
				 * @brief TuxNS::PowerDNS::Request::getResponse()
				 * @return TuxNS::PowerDNS::Response* TuxNS::PowerDNS::Request::mResponse
				 */
				inline Response* &getResponse() { return this->mResponse; }

				///////////////////////////////////////////////////////////////
				/// Setters //////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method sets the response into the instance
				 * @brief TuxNS::PowerDNS::Request::setResponse()
				 * @param TuxNS::PowerDNS::Response* clsResponse
				 * @return TuxNS::PowerDNS::Request* this
				 */
				inline Request* setResponse(TuxNS::PowerDNS::Response* &clsResponse) {
					// Set the response into the instance
					this->mResponse = clsResponse;
					// We're done
					return this;
				}

				/**
				 * @paragraph This method sets the request JSON into the instance
				 * @brief TuxNS::PowerDNS::Request::setRequestJSON()
				 * @param QString strJSON
				 * @return TuxNS::PowerDNS::Request* this
				 */
				inline Request* setRequestJSON(QString strJSON) {
					// We're done
					return this->setRequestJSON(strJSON.toLatin1());
				}

				/**
				 * @paragraph This method sets the request JSON into the instance
				 * @brief TuxNS::PowerDNS::Request::setRequestJSON()
				 * @param QByteArray qbaJSON
				 * @return TuxNS::PowerDNS::Request* this
				 */
				inline Request* setRequestJSON(QByteArray qbaJSON) {
					// Set the raw request into the instance
					this->mRequestJSON = qbaJSON.trimmed();
					// Set the decoded request into the instance
					this->mRequest     = QJsonDocument::fromJson(this->mRequestJSON).object();
					// We're done
					return this;
				}

			///////////////////////////////////////////////////////////////////
			/// Signals //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			signals:

				/**
				 * @paragraph This signal fires when PowerDNS requests a handshake
				 * @brief TuxNS::PowerDNS::Request::initialize()
				 * @param TuxNS::PowerDNS::Response* clsResponse
				 * @param QVariantMap qvmParameters
				 */
				void initialize(PowerDNS::Response* &clsResponse, QVariantMap qvmParameters);

				/**
				 * @paragraph This signal fires when PowerDNS requests a zone listing
				 * @brief TuxNS::PowerDNS::Request::list()
				 * @param TuxNS::PowerDNS::Response* clsResponse
				 * @param QString strZone
				 * @param int  intDomainID [-1]
				 */
				void list(PowerDNS::Response* &clsResponse, QString strZone, int intDomainID = -1);

				/**
				 * @paragraph This signal fires when PowerDNS requests a record lookup
				 * @brief TuxNS::PowerDNS::Request::lookup()
				 * @param TuxNS::PowerDNS::Response* clsResponse
				 * @param QString strQType
				 * @param QString strQName
				 * @param int intZoneID [-1]
				 * @param QHostAddress qhaRemote [QHostAddress("0.0.0.0")]
				 * @param QHostAddress qhaLocal [QHostAddress("0.0.0.0")]
				 * @param QHostAddress qhaRealRemote [QHostAddress("0.0.0.0")]
				 */
				void lookup(PowerDNS::Response* &clsResponse, QString strQType, QString strQName, int intZoneID = -1, QHostAddress qhaRemote = QHostAddress("0.0.0.0"), QHostAddress qhaLocal = QHostAddress("0.0.0.0"), QHostAddress qhaRealRemote = QHostAddress("0.0.0.0"));

		///////////////////////////////////////////////////////////////////////
		}; // End TuxNS::PowerDNS::Request Class Definition //////////////////
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
