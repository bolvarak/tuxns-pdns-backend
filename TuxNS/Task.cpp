///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "Task.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS {

	///////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	Task::Task()
	{

	}

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void Task::run()
	{
		// Send the log message
		Log::debug("Querying...");
		// Instantiate the DNS handler
		DNS* clsDNS        = new DNS();
		// Process the request
		QByteArray qbaJson = clsDNS->process(this->mSource);
		// Send the log message
		Log::debug("Query Finished!");
		// Emit the signal
		emit this->done(qbaJson);
	}

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
