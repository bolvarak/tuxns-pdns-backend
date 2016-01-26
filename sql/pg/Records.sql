-- Drop the table if it exists
DROP TABLE IF EXISTS "public"."Records";
-- Create the new table
CREATE TABLE "public"."Records"
(
	"ID" bigserial NOT NULL,
	"AccountID" bigint DEFAULT 0,
	"DomainID" bigint DEFAULT 0,
	"TypeID" bigint DEFAULT 0,
	"TTL" int4 DEFAULT 600,
	"Priority" int4 DEFAULT -1,
	"Target" varchar(255) DEFAULT NULL,
	"Destination" text DEFAULT NULL,
	"Authoritive" boolean DEFAULT true,
	"Active" boolean DEFAULT true,
	"System" boolean DEFAULT false,
	"Created" timestamp DEFAULT now(),
	"Updated" timestamp DEFAULT NULL,
	-- Set the Primary Key
	CONSTRAINT "tns_records_key" PRIMARY KEY ("ID")
) WITH (OIDS = FALSE);
