///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "Request.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{
	///////////////////////////////////////////////////////////////////////////
	/// TuxNS Namespace //////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	namespace PowerDNS
	{
		///////////////////////////////////////////////////////////////////////
		/// Static Methods ///////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		Request* Request::fromArg(QByteArray qbaValue)
		{
			// Return the new instance
			return new Request(qbaValue);
		}

		Request* Request::fromJson(QVariant qvJson)
		{
			// Return the new instance
			return new Request(qvJson.toByteArray());
		}

		Request* Request::fromStdin()
		{
			// Create the stream
			QTextStream qtsInput(stdin);
			// Return the new instance
			return new Request(qtsInput.readAll().trimmed().toLatin1());
		}

		///////////////////////////////////////////////////////////////////////
		/// Constructors /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		Request::Request(QString strJSON, QObject* objParent) : QObject(objParent)
		{
			// Set the raw request into the instance
			this->mRequestJSON = strJSON.toLatin1();
			// Set the decoded request into the instance
			this->mRequest     = QJsonDocument::fromJson(this->mRequestJSON).object();
			// Initialize the response
			this->mResponse = new Response();
		}

		Request::Request(QByteArray qbaJSON, QObject* objParent) : QObject(objParent)
		{
			// Set the raw request into the instance
			this->mRequestJSON = qbaJSON;
			// Set the decoded request into the instance
			this->mRequest     = QJsonDocument::fromJson(this->mRequestJSON).object();
			// Initialize the response
			this->mResponse = new Response();
		}

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		Request* Request::parse()
		{
			// Localize the method
			QString strMethod         = this->mRequest.value("method").toString().toLower();
			// Localize the parameters
			QJsonObject qjoParameters = this->mRequest.value("parameters").toObject();
			// Check the method
			if (strMethod == Method::Initialize) {    // Handshake
				// Initialize the handshake
				emit this->initialize(this->mResponse, qjoParameters.toVariantMap());
			} else if (strMethod == Method::List) {   // List a zone
				// List the zone
				emit this->list(this->mResponse, qjoParameters.value("zonename").toString(), qjoParameters.value("domain_id").toInt(-1));
			} else if (strMethod == Method::Lookup) { // Lookup a record
				// Lookup the record
				emit this->lookup(
					this->mResponse,
					qjoParameters.value("qtype").toString(),
					qjoParameters.value("qname").toString(),
					qjoParameters.value("zone-id").toInt(-1),
					QHostAddress(qjoParameters.value("remote").toString("0.0.0.0")),
					QHostAddress(qjoParameters.value("local").toString("0.0.0.0")),
					QHostAddress(qjoParameters.value("real-remote").toString("0.0.0.0"))
				);
			} else {                                  // Not implemented
				// Set the response
				this->mResponse->errorResponse();
			}
			// We're done
			return this;
		}

		QByteArray Request::reply(bool blnDirect)
		{
			// Grab the response
			QByteArray qbaJson = this->mResponse->write();
			// Check for direct output
			if (blnDirect == true) {
				// Send the output
				std::cout << qbaJson.constData() << std::endl;
			}
			// We're done
			return qbaJson;
		}

	///////////////////////////////////////////////////////////////////////////
	} // End TuxNS::PowerDNS Namespace ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
