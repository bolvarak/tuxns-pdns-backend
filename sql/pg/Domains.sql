-- Drop any existing tables with this name
DROP TABLE IF EXISTS "public"."Domains";
-- Create the Domains table
CREATE TABLE "public"."Domains"
(
	"ID" bigserial NOT NULL,
	"AccountID" bigint DEFAULT 0,
	"TTL" int4 DEFAULT 0,
	"Serial" int4 DEFAULT 0,
	"Nameserver" varchar(255) DEFAULT 'ns1.tuxns.net',
	"Name" varchar(255) NOT NULL,
	"Active" boolean DEFAULT true,
	"System" boolean DEFAULT false,
	"Created" timestamp DEFAULT now(),
	"Updated" timestamp DEFAULT NULL,
	-- Set our primary key
	CONSTRAINT "tns_domains_pkey" PRIMARY KEY ("ID"),
	-- Make sure the domain name is unique
	UNIQUE ("Name")
) WITH (OIDS = FALSE);
