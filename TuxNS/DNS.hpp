///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef TUXNS_POWERDNS_H
#define TUXNS_POWERDNS_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "iostream"
#include "QtCore/QCoreApplication"
#include "QtCore/QDateTime"
#include "QtCore/QDebug"
#include "QtCore/QFile"
#include "QtCore/QResource"
#include "QtCore/QTextStream"
#include "QtNetwork/QHostAddress"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlDriver"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlRecord"
#include "Log.hpp"
#include "PowerDNS/Request.hpp"
#include "PowerDNS/Response.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS {

	///////////////////////////////////////////////////////////////////////////
	/// TuxNS::DNS Class Definition //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	class DNS : public QObject
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
			 * @paragraph This property contains the connection to our database
			 * @brief TuxNS::DNS::mDatabase
			 * @var QSqlDatabase
			 */
			QSqlDatabase mDatabase;

			/**
			 * @paragraph This property contains the request object
			 * @brief TuxNS::DNS::mRequest
			 * @var TuxNS::PowerDNS::Request*
			 */
			PowerDNS::Request* mRequest;

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method creates a database log entry for the query
			 * @brief TuxNS::DNS::createLogEntry()
			 * @param QVariant qvAccountID
			 * @param QVariant qvDomainID
			 * @param QVariant qvRecordID
			 * @param QHostAddress qhaSource
			 * @param QVariant qvListRequest
			 */
			void createLogEntry(QVariant qvAccountID, QVariant qvDomainID, QVariant qvRecordID, QHostAddress qhaSource, QVariant qvListRequest);

			/**
			 * @paragraph This method reads a SQL file into a byte array
			 * @brief TuxNS::DNS::readSqlFile()
			 * @param QString strResourcePath
			 * @return QByteArray
			 */
			QByteArray readSqlFile(QString strResourcePath);

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Constants ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constant contains the ANY QType
			 * @brief TuxNS::DNS::Any
			 * @var const QString
			 */
			static const QString Any;

			/**
			 * @paragraph This constant contains the AXFR keyword
			 * @brief TuxNS::DNS::Axfr
			 * @var const QString
			 */
			static const QString Axfr;

			/**
			 * @paragraph This constant contains the DATA keyword
			 * @brief TuxNS::DNS::Data
			 * @var const QString
			 */
			static const QString Data;

			/**
			 * @paragraph This constant contains the END keyword
			 * @brief TuxNS::DNS::End
			 * @var const QString
			 */
			static const QString End;

			/**
			 * @paragraph This constant contains the FAIL keyword
			 * @brief TuxNS::DNS::Fail
			 * @var const QString
			 */
			static const QString Fail;

			/**
			 * @paragraph This constant contains the HELO type keyword
			 * @brief TuxNS::DNS::Helo
			 * @var const QString
			 */
			static const QString Helo;

			/**
			 * @paragraph This constant contains the LOG keyword
			 * @brief TuxNS::DNS::Log
			 * @var const QString
			 */
			static const QString Log;

			/**
			 * @paragraph This constant contains the value for a non-existent ID
			 * @brief TuxNS::DNS::NoID
			 * @var const QString
			 */
			static const QString NoID;

			/**
			 * @paragraph This constant contains the OK keyword
			 * @brief TuxNS::DNS::OK
			 * @var const QString
			 */
			static const QString OK;

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method instantiates the class with defaults
			 * @brief TuxNS::DNS::PowerDNS()
			 * @param QObject* objParent
			 * @return void
			 */
			explicit DNS(QObject* objParent = 0);

			///////////////////////////////////////////////////////////////////
			/// Destructor ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method destroys the instance and cleans up
			 * @brief TuxNS::DNS::~PowerDNS()
			 */
			~DNS();

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method makes the backend ready to receive queries
			 * @brief TuxNS::DNS::process()
			 * @param QString strJSON [NULL]
			 * @param int intLine
			 * @return QByteArray
			 */
			QByteArray process(QString strJSON = NULL);

			/**
			 * @paragraph This method makes the backend ready to receive queries
			 * @brief TuxNS::DNS::process()
			 * @param QByteArray qbaJSON [NULL]
			 * @return QByteArray
			 */
			QByteArray process(QByteArray qbaJSON = NULL);

			///////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method returns the request object from the instance
			 * @brief TuxNS::DNS::getRequest()
			 * @return TuxNS::PowerDNS::Request* TuxNS::DNS::mRequest
			 */
			inline PowerDNS::Request* &getRequest()   { return this->mRequest; }

			/**
			 * @paragraph This method returns the response object from the instance
			 * @brief TuxNS::DNS::getResponse()
			 * @return TuxNS::PowerDNS::Response* TuxNS::DNS::mRequest::mResponse
			 */
			inline PowerDNS::Response* &getResponse() { return this->mRequest->getResponse(); }

			///////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method sets the database connection into the instance
			 * @brief TuxNS::DNS::setDatabase()
			 * @param QSqlDatabase qsdSource
			 * @return TuxNS::DNS* this
			 */
			inline DNS* setDatabase(QSqlDatabase &qsdSource) {
				// Set the database into the instance
				this->mDatabase = qsdSource;
				// We're done
				return this;
			}

			/**
			 * @paragraph This method sets the request object into the instance
			 * @brief TuxNS::DNS::setRequest()
			 * @param TuxNS::DNS::Request* clsRequest
			 * @return TuxNS::DNS* this
			 */
			inline DNS* setRequest(PowerDNS::Request* &clsRequest) {
				// Set the requt into the instance
				this->mRequest = clsRequest;
				// We're done
				return this;
			}

		///////////////////////////////////////////////////////////////////////
		/// Public Slots /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public slots:

			/**
			 * @paragraph This signal fires when PowerDNS requests a handshake
			 * @brief TuxNS::DNS::initialize()
			 * @param TuxNS::PowerDNS::Response* clsResponse
			 * @param QVariantMap qvmParameters
			 */
			void initialize(PowerDNS::Response* &clsResponse, QVariantMap qvmParameters);

			/**
			 * @paragraph This signal fires when PowerDNS requests a zone listing
			 * @brief TuxNS::DNS::list()
			 * @param TuxNS::PowerDNS::Response* clsResponse
			 * @param QString strZone
			 * @param int  intDomainID [-1]
			 */
			void list(PowerDNS::Response* &clsResponse, QString strZone, int intDomainID = -1);

			/**
			 * @paragraph This signal fires when PowerDNS requests a record lookup
			 * @brief TuxNS::DNS::lookup()
			 * @param TuxNS::PowerDNS::Response* clsResponse
			 * @param QString strQType
			 * @param QString strQName
			 * @param int intZoneID [-1]
			 * @param QHostAddress qhaRemote [QHostAddress("0.0.0.0")]
			 * @param QHostAddress qhaLocal [QHostAddress("0.0.0.0")]
			 * @param QHostAddress qhaRealRemote [QHostAddress("0.0.0.0")]
			 */
			void lookup(PowerDNS::Response* &clsResponse, QString strQType, QString strQName, int intZoneID = -1, QHostAddress qhaRemote = QHostAddress("0.0.0.0"), QHostAddress qhaLocal = QHostAddress("0.0.0.0"), QHostAddress qhaRealRemote = QHostAddress("0.0.0.0"));

	///////////////////////////////////////////////////////////////////////////
	}; // End TuxNS::DNS Class Definition ////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#endif // End Definitions ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
