# tuxns-pdns-backend
This is the Remote PowerDNS backend that TuxNS uses.  It creates a UNIX socket that PowerDNS will forward requests to that queries a PostgreSQL database for records.

# Supported Methods
```
initialize
list
lookup
```

## TODO
- Add in support for the remaining methods, however that is not within the scope of TuxNS

# Prerequisites
- PowerDNS compiled with remote backend
- Qt 5.5+ with SQL plugins
- PostgreSQL 9.4+

# Database
All of the SQL files are in ```sql/pg/```

# Configuration
Make sure to update your database and logging information in ```main.cpp```.  Also if you wish to change the socket path, it is in ```TuxNS/Listener.cpp```

# Compiling
```
cd /path/to/repo
qmake && make
./tuxns-pdns-backend
```

# PowerDNS Configuration
```
allow-recursion=127.0.0.1
cache-ttl=6
config-dir=/etc
daemon=yes
distributor-threads=3
guardian=yes
local-port=53
loglevel=3
module-dir=/usr/local/lib/pdns ## Could also be /lib/powerdns or /usr/lib/powerdns
negquery-cache-ttl=60
setgid=root
setuid=root
socket-dir=/var/run
webserver=no
launch=remote
remote-connection-string=unix:path=/tmp/tuxns-pdns.sock,timeout=30000
```

# Testing the Socket
Visit https://doc.powerdns.com/md/authoritative/backend-remote/ for query examples and use the following command to connect.
```
socat - unix-connect:/tmp/tuxns-pdns.sock
```
