///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef TUXNS_CONNECTION_H
#define TUXNS_CONNECTION_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QDebug"
#include "QtCore/QObject"
#include "QtCore/QThreadPool"
#include "QtNetwork/QLocalSocket"
#include "Log.hpp"
#include "Task.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS
{

	///////////////////////////////////////////////////////////////////////////
	/// TuxNS::Connection Class Definition ///////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	class Connection : public QObject
	{
		///////////////////////////////////////////////////////////////////////
		/// QObject Classification ///////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		Q_OBJECT

		///////////////////////////////////////////////////////////////////////
		/// Private Methods & Properties /////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		private:

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the instance of our socket
			 * @brief TuxNS::Connection::mSocket
			 * @var QLocalSocket*
			 */
			QLocalSocket* mSocket;

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constructor instantiates the class with defaults
			 * @brief TuxNS::Connection::Connection()
			 * @param QObject* objParent [0]
			 */
			explicit Connection(QObject* objParent = 0);

			///////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method returns the socket from the instance
			 * @brief TuxNS::Connection::getSocket()
			 * @return QLocalSocket* TuxNS::Connection::mSocket
			 */
			inline QLocalSocket* &getSocket() { return this->mSocket; }

			///////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method sets the socket into the instance
			 * @brief TuxNS::Connection::setSocket()
			 * @param QLocalSocket* sockClient
			 * @return
			 */
			Connection* setSocket(QLocalSocket* sockClient);

			/**
			 * @paragraph This method sets the socket into the instance via a descriptor
			 * @brief TuxNS::Connection::setSocket()
			 * @param int intDescriptor
			 * @return TuxNS::Connection* this
			 */
			Connection* setSocket(int intDescriptor);

		///////////////////////////////////////////////////////////////////////
		/// Public Slots /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public slots:

			/**
			 * @paragraph This slot gets called when a connection is established
			 * @brief TuxNS::Connection::connected()
			 * @return void
			 */
			void connected();

			/**
			 * @paragraph This slot gets called when a connection is closed
			 * @brief TuxNS::Connection::disconnected()
			 * @return void
			 */
			void disconnected();

			/**
			 * @paragraph This slot gets called when the current connection is ready to be read
			 * @brief TuxNS::Connection::ready()
			 * @return void
			 */
			void ready();

			/**
			 * @paragraph This slot gets called when the response is ready for the current connection
			 * @brief TuxNS::Connection::reply()
			 * @param QByteArray qbaJson
			 * @return void
			 */
			void reply(QByteArray qbaJson);

	///////////////////////////////////////////////////////////////////////////
	}; // End TuxNS::Connection Class Definition /////////////////////////////
	/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#endif // End Definitions ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
