///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "Response.hpp"

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
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		Response::Response(QObject* objParent) : QObject(objParent) {

		}

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		void Response::addRecord(int intDomainID, QString strQType, QString strQName, QString strContent, int intTTL, bool blnAuth, int intPriority)
		{
			// Create the JSON object
			QJsonObject qjoRecord;
			// Add the domain ID
			qjoRecord.insert("domain_id", QJsonValue::fromVariant(intDomainID));
			// Add the type
			qjoRecord.insert("qtype",     QJsonValue::fromVariant(strQType));
			// Add the name
			qjoRecord.insert("qname",     QJsonValue::fromVariant(strQName));
			// Add the content
			qjoRecord.insert("content",   QJsonValue::fromVariant(strContent));
			// Add the TTL
			qjoRecord.insert("ttl",       QJsonValue::fromVariant(intTTL));
			// Add the authoritive flag
			qjoRecord.insert("auth",      QJsonValue::fromVariant(blnAuth));
			// Check for a priority
			if ((strQType.toLower() == "mx") || (strQType.toLower() == "srv")) {
				// Add the priority
				qjoRecord.insert("priority", QJsonValue::fromVariant(intPriority));
			}
			// Check for an SOA record
			if (strQType.toLower() == "soa") {
				// Prepend the SOA record
				this->mRecords.prepend(qjoRecord);
			} else {
				// Add the object to the list
				this->mRecords.append(qjoRecord);
			}
		}

		void Response::errorResponse()
		{
			// Add the result
			this->mResponse.insert("result", false);
		}

		void Response::successResponse()
		{
			// Add the result
			this->mResponse.insert("result", true);
		}

		QByteArray Response::write()
		{
			if (this->mRecords.size() > 0) {                  // Record type response
				// Add the result to the object
				this->mResponse.insert("result", this->mRecords);
			} else if (!this->mResponse.contains("result")) { // Predefined Response
				// Set the error response
				this->mResponse.insert("result", false);
			}
			// Send the response
			return QJsonDocument(this->mResponse).toJson(QJsonDocument::Compact);
		}

	///////////////////////////////////////////////////////////////////////////
	} // End TuxNS::PowerDNS Namespace ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////