///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef TUXNS_TASK_H
#define TUXNS_TASK_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QDebug"
#include "QtCore/QObject"
#include "QtCore/QRunnable"
#include "Log.hpp"
#include "DNS.hpp"

///////////////////////////////////////////////////////////////////////////////
/// TuxNS Namespace //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace TuxNS {

	///////////////////////////////////////////////////////////////////////////
	/// TuxNS::Task Class Definition /////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	class Task : public QObject, public QRunnable
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
			 * @paragraph This property contains the request JSON
			 * @brief TuxNS::Task::mSource
			 * @var QByteArray
			 */
			QByteArray mSource;

			///////////////////////////////////////////////////////////////////
			/// Overloaded Methods ///////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method executes the task
			 * @brief TuxNS::Task::run()
			 * @return void
			 */
			void run();

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method does nothing, it is simply a placeholder
			 * @brief TuxNS::Task::Task()
			 */
			explicit Task();

			///////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method returns the source JSON from the instance
			 * @brief TuxNS::Task::getSource()
			 * @return QByteArray TuxNS::Task::mSource
			 */
			inline QByteArray getSource() { return this->mSource; }

			///////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method sets the request JSON into the instance
			 * @brief TuxNS::Task::setSource()
			 * @param QByteArray qbaJson
			 * @return TuxNS::Task* this
			 */
			inline Task* setSource(QByteArray qbaJson) {
				// Set the request JSON into the instance
				this->mSource = qbaJson;
				// We're done
				return this;
			}

		///////////////////////////////////////////////////////////////////////
		/// Signals //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		signals:

			/**
			 * @paragraph This signal fires when this task has finished
			 * @brief TuxNS::Task::done()
			 * @param QByteArray qbaJson
			 * @return void
			 */
			void done(QByteArray qbaJson);

	///////////////////////////////////////////////////////////////////////////
	}; // End TuxNS::Task Class Definition ///////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
} // End TuxNS Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#endif // End Definitions ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////