///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "DNS.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS {

	///////////////////////////////////////////////////////////////////////////
	/// Constants ////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	const QString DNS::Any  = "ANY";
	const QString DNS::Axfr = "AXFR";
	const QString DNS::Data = "DATA";
	const QString DNS::End  = "END";
	const QString DNS::Fail = "FAIL";
	const QString DNS::Helo = "HELO\t1";
	const QString DNS::Log  = "LOG";
	const QString DNS::NoID = "-1";
	const QString DNS::OK   = "OK";

	///////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	DNS::DNS(QObject *objParent) : QObject(objParent)
	{
		// Create the SQL connection
		this->mDatabase = QSqlDatabase::database(QSqlDatabase::defaultConnection, true);
	}

	///////////////////////////////////////////////////////////////////////////
	/// Destructor ///////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	DNS::~DNS()
	{
		// Close the database connection
		// this->mDatabase.close();
	}

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void DNS::createLogEntry(QVariant qvAccountID, QVariant qvDomainID, QVariant qvRecordID, QHostAddress qhaSource, QVariant qvListRequest)
	{
		// Create the query
		QSqlQuery qsqLogEntry(this->mDatabase);
		// Load the SQL file
		qsqLogEntry.prepare(this->readSqlFile(":/sql/pg/LogEntry.sql"));
		// Bind the values
		qsqLogEntry.bindValue(":account", qvAccountID);
		qsqLogEntry.bindValue(":domain",  qvDomainID);
		qsqLogEntry.bindValue(":record",  qvRecordID);
		qsqLogEntry.bindValue(":source",  qhaSource.toString());
		qsqLogEntry.bindValue(":listReq", qvListRequest);
		// Execute the query
		qsqLogEntry.exec();
		// We're done with the query
		qsqLogEntry.finish();
	}

	QByteArray DNS::readSqlFile(QString strResourcePath)
	{
		// Open the SQL file
		QFile fleSQL(strResourcePath);
		// Open the file
		if (!fleSQL.open(QFile::ReadOnly)) {
			// Send the fail
			this->mRequest->getResponse()->errorResponse();
			// We're done
			return this->mRequest->reply();
		}
		// Read the SQL file
		QByteArray qbaSQL = fleSQL.readAll();
		// Close the file
		fleSQL.close();
		// Return the statement
		return qbaSQL;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	QByteArray DNS::process(QString strJSON)
	{
		// Check for provided JSON
		if (!strJSON.isNull()) {
			// Reset the request
			this->mRequest = new PowerDNS::Request(strJSON.trimmed());
		} else {
			// Reset the request
			this->mRequest = PowerDNS::Request::fromStdin();
		}
		// Try to open the database
		if (!this->mDatabase.isOpen()) {
			// Send the log message
			Log::fail(QString("Database Connection Error! (%1)").arg(this->mDatabase.lastError().text()));
			// Send the error response
			this->mRequest->getResponse()->errorResponse();
			// Write the reply
			return this->mRequest->reply();
		}
		// Make the connections
		this->connect(this->mRequest, SIGNAL(initialize(PowerDNS::Response*&,QVariantMap)), this, SLOT(initialize(PowerDNS::Response*&,QVariantMap)));
		this->connect(this->mRequest, SIGNAL(list(PowerDNS::Response*&,QString,int)), this, SLOT(list(PowerDNS::Response*&,QString,int)));
		this->connect(this->mRequest, SIGNAL(lookup(PowerDNS::Response*&,QString,QString,int,QHostAddress,QHostAddress,QHostAddress)), this, SLOT(lookup(PowerDNS::Response*&,QString,QString,int,QHostAddress,QHostAddress,QHostAddress)));
		// Parse the request
		this->mRequest->parse();
		// Send the response
		return this->mRequest->reply();
	}

	QByteArray DNS::process(QByteArray qbaJSON)
	{
		// Check for provided JSON
		if (!qbaJSON.isNull()) {
			// Reset the request
			this->mRequest = new PowerDNS::Request(qbaJSON.trimmed());
		} else {
			// Reset the request
			this->mRequest = PowerDNS::Request::fromStdin();
		}
		// Try to open the database
		if (!this->mDatabase.isOpen()) {
			// Send the log message
			Log::fail(QString("Database Connection Error! (%1)").arg(this->mDatabase.lastError().text()));
			// Send the error response
			this->mRequest->getResponse()->errorResponse();
			// Write the reply
			return this->mRequest->reply();
		}
		// Make the connections
		this->connect(this->mRequest, SIGNAL(initialize(PowerDNS::Response*&,QVariantMap)), this, SLOT(initialize(PowerDNS::Response*&,QVariantMap)));
		this->connect(this->mRequest, SIGNAL(list(PowerDNS::Response*&,QString,int)), this, SLOT(list(PowerDNS::Response*&,QString,int)));
		this->connect(this->mRequest, SIGNAL(lookup(PowerDNS::Response*&,QString,QString,int,QHostAddress,QHostAddress,QHostAddress)), this, SLOT(lookup(PowerDNS::Response*&,QString,QString,int,QHostAddress,QHostAddress,QHostAddress)));
		// Parse the request
		this->mRequest->parse();
		// Send the response
		return this->mRequest->reply();
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Slots /////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void DNS::initialize(PowerDNS::Response *&clsResponse, QVariantMap qvmParameters)
	{
		// For now we don't do anything, so we're all good
		clsResponse->successResponse();
	}


	void DNS::list(PowerDNS::Response *&clsResponse, QString strZone, int intDomainID)
	{
		// Create the SQL query
		QSqlQuery qsqZone(this->mDatabase);
		// Check for an ID
		if (intDomainID > 0) {
			// Prepare the SQL statement
			qsqZone.prepare(this->readSqlFile(":/sql/pg/ZoneByID.sql"));
			// Bind the ID
			qsqZone.bindValue(":id", intDomainID);
		} else {
			// Prepare the SQL statement
			qsqZone.prepare(this->readSqlFile(":/sql/pg/ZoneByName.sql"));
			// Bind the name
			qsqZone.bindValue(":name", strZone);
		}
		// Try to execute the statement
		if (!qsqZone.exec()) {
			// Send the log message
			Log::fail(QString("Zone Query Error Error! (%1)").arg(qsqZone.lastError().text()));
			// Set the error response
			clsResponse->errorResponse();
			// We're done
			return;
		}
		// Iterate over the results
		while (qsqZone.next()) {
			// Localize the record
			QSqlRecord qsrZone = qsqZone.record();
			// Check the type
			if (qsrZone.value("Type").toString().toLower() == "soa") {
				// Add the record to the response
				clsResponse->addRecord(qsrZone.value("DomainID").toInt(), qsrZone.value("Type").toString(), qsrZone.value("Target").toString(), qsrZone.value("SoaRecord").toString(), qsrZone.value("TTL").toInt(), qsrZone.value("Authoritive").toBool(), qsrZone.value("Priority").toInt());
			} else {
				// Add the record to the response
				clsResponse->addRecord(qsrZone.value("DomainID").toInt(), qsrZone.value("Type").toString(), qsrZone.value("Target").toString(), qsrZone.value("Destination").toString(), qsrZone.value("TTL").toInt(), qsrZone.value("Authoritive").toBool(), qsrZone.value("Priority").toInt());
			}
			// Create the log entry
			this->createLogEntry(qsrZone.value("AccountID"), qsrZone.value("DomainID"), qsrZone.value("ID"), QHostAddress("0.0.0.0"), QVariant(true));
		}
		// We're finished with the query
		qsqZone.finish();
	}


	void DNS::lookup(PowerDNS::Response *&clsResponse, QString strQType, QString strQName, int intZoneID, QHostAddress qhaRemote, QHostAddress qhaLocal, QHostAddress qhaRealRemote)
	{
		// Create the query
		QSqlQuery qsqRecords(this->mDatabase);
		// Check for a zone ID
		if ((intZoneID != -1) && (strQType.toUpper() == DNS::Any)) {
			// Prepare the query
			qsqRecords.prepare(this->readSqlFile(":/sql/pg/ZoneByID.sql"));
			// Bind the ID
			qsqRecords.bindValue(":id", intZoneID);
		} else if ((intZoneID != -1) && (strQType.toUpper() != DNS::Any)) {
			// Prepare the query
			qsqRecords.prepare(this->readSqlFile(":/sql/pg/ByID.sql"));
			// Bind the name
			qsqRecords.bindValue(":id",   intZoneID);
			// Bind the type
			qsqRecords.bindValue(":type", strQType);
		} else if ((intZoneID == -1) && (strQType.toUpper() == DNS::Any)) {
			// Prepare the query
			qsqRecords.prepare(this->readSqlFile(":/sql/pg/ByName.sql"));
			// Bind the name
			qsqRecords.bindValue(":name", strQName);
		} else {
			// Prepare the query
			qsqRecords.prepare(this->readSqlFile(":/sql/pg/ByType.sql"));
			// Bind the name
			qsqRecords.bindValue(":name", strQName);
			// Bind the type
			qsqRecords.bindValue(":type", strQType);
		}
		// Try to execute the statement
		if (!qsqRecords.exec()) {
			// Send the log message
			Log::fail(QString("Zone Query Error! (%1)").arg(qsqRecords.lastError().text()));
			// Set the error response
			clsResponse->errorResponse();
			// We're done
			return;
		}
		// Iterate over the results
		while (qsqRecords.next()) {
			// Localize the record
			QSqlRecord qsrRecord = qsqRecords.record();
			// Check the type
			if (qsrRecord.value("Type").toString().toLower() == "soa") {
				// Add the record to the response
				clsResponse->addRecord(qsrRecord.value("DomainID").toInt(), qsrRecord.value("Type").toString(), qsrRecord.value("Target").toString(), qsrRecord.value("SoaRecord").toString(), qsrRecord.value("TTL").toInt(), qsrRecord.value("Authoritive").toBool(), qsrRecord.value("Priority").toInt());
			} else {
				// Add the record to the response
				clsResponse->addRecord(qsrRecord.value("DomainID").toInt(), qsrRecord.value("Type").toString(), qsrRecord.value("Target").toString(), qsrRecord.value("Destination").toString(), qsrRecord.value("TTL").toInt(), qsrRecord.value("Authoritive").toBool(), qsrRecord.value("Priority").toInt());
			}
			// Check for a real remote
			if (qhaRealRemote.toString() != "0.0.0.0") {
				// Create the log entry
				this->createLogEntry(qsrRecord.value("AccountID"), qsrRecord.value("DomainID"), qsrRecord.value("ID"), qhaRealRemote, QVariant(false));
			} else {
				// Create the log entry
				this->createLogEntry(qsrRecord.value("AccountID"), qsrRecord.value("DomainID"), qsrRecord.value("ID"), qhaRemote, QVariant(false));
			}
		}
		// We're finished with the query
		qsqRecords.finish();
	}

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
