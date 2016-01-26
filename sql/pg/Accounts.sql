-- Drop any existing table
DROP TABLE IF EXISTS "public"."Accounts";
-- Create our table
CREATE TABLE "public"."Accounts"
(
	"ID" bigserial NOT NULL,
	"Username" varchar(125) DEFAULT NULL,
	"Password" text DEFAULT NULL,
	"EmailAddress" varchar(255) DEFAULT NULL,
	"FirstName" varchar(255) DEFAULT NULL,
	"LastName" varchar(255) DEFAULT NULL,
	"Active" bool DEFAULT true,
	"System" bool DEFAULT false,
	"Created" timestamp(6) DEFAULT now(),
	"Updated" timestamp(6),
	CONSTRAINT "tns_accounts_pkey" PRIMARY KEY ("ID"),
	CONSTRAINT "Accounts_Username_key" UNIQUE ("Username")
) WITH (OIDS=FALSE);
