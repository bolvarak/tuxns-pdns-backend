QT += core network sql
QT -= gui

CONFIG += c++11

TARGET = tuxns-pdns-backend
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    TuxNS/DNS.cpp \
    TuxNS/PowerDNS/Method.cpp \
    TuxNS/PowerDNS/Response.cpp \
    TuxNS/PowerDNS/Request.cpp \
    TuxNS/Listener.cpp \
    TuxNS/Connection.cpp \
    TuxNS/Task.cpp \
    TuxNS/Log.cpp \
    TuxNS/Bootstrap.cpp

HEADERS += \
    TuxNS/PowerDNS/Request.hpp \
    TuxNS/PowerDNS/Method.hpp \
    TuxNS/PowerDNS/Response.hpp \
    TuxNS/DNS.hpp \
    TuxNS/Listener.hpp \
    TuxNS/Connection.hpp \
    TuxNS/Task.hpp \
    TuxNS/Log.hpp \
    TuxNS/Bootstrap.hpp

DISTFILES += \
	sql/Records.sql \
	sql/Domains.sql \
	sql/Prerequisites.sql \
	sql/Types.sql \
	sql/Log.sql \
	sql/ByID.pg.sql \
	sql/ByName.pg.sql \
	sql/ByType.pg.sql \
	sql/pg/Domains.sql \
	sql/pg/Log.sql \
	sql/pg/Prerequisites.sql \
	sql/pg/Records.sql \
	sql/pg/Types.sql \
	sql/pg/ByID.sql \
	sql/pg/ByName.sql \
	sql/pg/ByType.sql \
	sql/pg/LogEntry.sql \
    sql/pg/ZoneByID.sql \
    sql/pg/ZoneByName.sql \
    sql/pg/Accounts.sql \
    tuxns.conf

RESOURCES += \
	sqlqueries.qrc
