-- Drop any existing table
DROP TABLE IF EXISTS "public"."Log";
-- Create the new table
CREATE TABLE "public"."Log"
(
	"AccountID" bigint DEFAULT 0,
	"DomainID" bigint DEFAULT 0,
	"RecordID" bigint DEFAULT 0,
	"Source" inet DEFAULT NULL,
	"ListRequest" bool DEFAULT false,
	"Created" timestamp DEFAULT now()
) WITH (OIDS = FALSE);
