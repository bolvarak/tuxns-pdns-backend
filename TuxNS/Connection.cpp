///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "Connection.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{

	///////////////////////////////////////////////////////////////////////////
	/// Constructors /////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	Connection::Connection(QObject* objParent) : QObject(objParent)
	{
		// Setup the pool
		QThreadPool::globalInstance()->setMaxThreadCount(16);
	}

	///////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	Connection* Connection::setSocket(QLocalSocket* sockClient) {
		// Set the socket into the instance
		this->mSocket = sockClient;
		// Make the slot connections
		this->connect(this->mSocket, SIGNAL(connected()),    this, SLOT(connected()));
		this->connect(this->mSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
		this->connect(this->mSocket, SIGNAL(readyRead()),    this, SLOT(ready()));
		// Send the log message
		Log::debug("Forking Client!");
		// We're done
		return this;
	}

	Connection* Connection::setSocket(int intDescriptor) {
		// Set the socket into the instance
		this->mSocket = new QLocalSocket(this);
		// Make the slot connections
		this->connect(this->mSocket, SIGNAL(connected()),    this, SLOT(connected()));
		this->connect(this->mSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
		this->connect(this->mSocket, SIGNAL(readyRead()),    this, SLOT(ready()));
		// Set the descriptor
		this->mSocket->setSocketDescriptor(intDescriptor);
		// Send the log message
		Log::debug("Forking Descriptor!");
		// We're done
		return this;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Slots /////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void Connection::connected()
	{
		// Send the log message
		Log::notice("Connection Established!");
	}

	void Connection::disconnected()
	{
		// Send the log message
		Log::notice("Connection Closed!");
	}

	void Connection::ready()
	{
		// Send the log message
		Log::notice("Ready for Payloads!");
		// Read the socket data
		QByteArray qbaRequest = this->mSocket->readAll();
		// Send the log message
		Log::notice("Received Payload!");
		// Instantiate the task
		Task* clsTask = new Task();
		// Autoremove this task when it's complete
		clsTask->setAutoDelete(true);
		// Set the source
		clsTask->setSource(qbaRequest);
		// Connect the signal
		this->connect(clsTask, SIGNAL(done(QByteArray)), this, SLOT(reply(QByteArray)), Qt::QueuedConnection);
		// Start the task
		QThreadPool::globalInstance()->start(clsTask);
	}

	void Connection::reply(QByteArray qbaJson)
	{
		// Send the log message
		Log::notice("Sending Payload Response!");
		// Append the newline
		qbaJson.append("\n");
		// Write the reply to the socket
		this->mSocket->write(qbaJson);
	}

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
