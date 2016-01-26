-- Drop any table with the same name
DROP TABLE IF EXISTS "public"."Types";
-- Create our new table
CREATE TABLE "public"."Types"
(
	"ID" bigserial NOT NULL,
	"Name" varchar(255) NOT NULL,
	"Description" text NULL,
	"Active" boolean DEFAULT true,
	"System" boolean DEFAULT false,
	CONSTRAINT "tns_types_pkey" PRIMARY KEY ("ID"),
	UNIQUE ("Name")
) WITH (OIDS = FALSE);
-- Insert the records
INSERT INTO "public"."Types" VALUES (1, 'NAPTR', 'Naming Authority Pointer', 't', 'f');
INSERT INTO "public"."Types" VALUES (2, 'DNSKEY', 'The DNSKEY DNSSEC record type is for enabeling DNSSEC for domains.', 't', 'f');
INSERT INTO "public"."Types" VALUES (3, 'A', 'The A record contains an IP address. It is stored as a decimal dotted quad string, for example: ''203.0.113.210''.', 't', 'f');
INSERT INTO "public"."Types" VALUES (4, 'TSIG', 'Used for key-exchange and authenticated AXFRs.', 't', 'f');
INSERT INTO "public"."Types" VALUES (5, 'KEY', 'No description', 't', 'f');
INSERT INTO "public"."Types" VALUES (6, 'NSEC', 'No description', 't', 'f');
INSERT INTO "public"."Types" VALUES (7, 'PTR', 'Reverse pointer, used to specify the host name belonging to an IP or IPv6 address.', 't', 'f');
INSERT INTO "public"."Types" VALUES (8, 'AAAA', 'The AAAA record contains an IPv6 address. An example: ''2001:DB8:2000:bf0::1''.', 't', 'f');
INSERT INTO "public"."Types" VALUES (9, 'HINFO', 'Hardware Info record, used to specify CPU and operating system. Stored with a single space separating these two, example: ''i386 Linux''.', 't', 'f');
INSERT INTO "public"."Types" VALUES (10, 'LOC', 'No description', 't', 'f');
INSERT INTO "public"."Types" VALUES (11, 'RP', 'Responsible Person record.  Example: peter.powerdns.com peter.people.powerdns.com, to indicate that peter@powerdns.com is responsible and that more information about peter is available by querying the TXT record of peter.people.powerdns.com.', 't', 'f');
INSERT INTO "public"."Types" VALUES (12, 'OPENPGPKEY', 'The OPENPGPKEY records are used to bind OpenPGP certificates to email addresses.', 't', 'f');
INSERT INTO "public"."Types" VALUES (13, 'SRV', 'SRV records can be used to encode the location and port of services on a domain name.', 't', 'f');
INSERT INTO "public"."Types" VALUES (14, 'SSHFP', 'The SSHFP record type is used for storing Secure Shell (SSH) fingerprints.', 't', 'f');
INSERT INTO "public"."Types" VALUES (15, 'NSEC3', 'No description', 't', 'f');
INSERT INTO "public"."Types" VALUES (16, 'CERT', 'Specialised record type for storing certificates.', 't', 'f');
INSERT INTO "public"."Types" VALUES (17, 'ALIAS', 'The ALIAS pseudo-record type is supported to provide CNAME-like mechanisms on a zone''s apex. ', 't', 'f');
INSERT INTO "public"."Types" VALUES (18, 'AFSDB', 'A specialised record type for the ''Andrew Filesystem''. Stored as: ''#subtype hostname'', where subtype is a number.', 't', 'f');
INSERT INTO "public"."Types" VALUES (19, 'NSEC3PARAM', 'No description', 't', 'f');
INSERT INTO "public"."Types" VALUES (20, 'CNAME', 'The CNAME record specifies the canonical name of a record. It is stored plainly. Like all other records, it is not terminated by a dot. A sample might be ''webserver-01.yourcompany.com''.', 't', 'f');
INSERT INTO "public"."Types" VALUES (21, 'SOA', 'The Start of Authority record is one of the most complex available. It specifies a lot about a domain: the name of the master nameserver (''the primary''), the hostmaster and a set of numbers indicating how the data in this domain expires and how often it needs to be checked. Further more, it contains a serial number which should rise on each change of the domain.', 't', 't');
INSERT INTO "public"."Types" VALUES (22, 'MX', 'The MX record specifies a mail exchanger host for a domain. Each mail exchanger also has a priority or preference. For example 10 mx.example.net.', 't', 'f');
INSERT INTO "public"."Types" VALUES (23, 'DS', 'No description', 't', 'f');
INSERT INTO "public"."Types" VALUES (24, 'RRSIG', 'No description', 't', 'f');
INSERT INTO "public"."Types" VALUES (25, 'DNAME', 'The DNAME record provides redirection for a subtree of the domain name tree in the DNS.', 't', 'f');
INSERT INTO "public"."Types" VALUES (26, 'CDNSKEY', 'No description', 't', 'f');
INSERT INTO "public"."Types" VALUES (27, 'CDS', 'No description', 't', 'f');
INSERT INTO "public"."Types" VALUES (28, 'TLSA', 'TLSA records are used to bind SSL/TLS certificate to named hosts and ports.', 't', 'f');
INSERT INTO "public"."Types" VALUES (29, 'SPF', 'SPF records can be used to store Sender Policy Framework details.', 't', 'f');
INSERT INTO "public"."Types" VALUES (30, 'TKEY', 'Used for key-exchange and authenticated AXFRs.', 't', 'f');
INSERT INTO "public"."Types" VALUES (31, 'NS', 'Nameserver record. Specifies nameservers for a domain.', 't', 'f');
INSERT INTO "public"."Types" VALUES (32, 'TXT', 'The TXT field can be used to attach textual data to a domain.', 't', 'f');
