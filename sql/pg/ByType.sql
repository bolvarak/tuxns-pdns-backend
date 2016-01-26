SELECT
	"Accounts"."EmailAddress" AS "Administrator",
	"Records".*,
	"Types"."Name" AS "Type",
	"Domains"."Nameserver" || ' ' || "Accounts"."EmailAddress" AS "SoaRecord"
FROM
	"Records"
INNER JOIN
	"Accounts"
		ON ("Accounts"."ID" = "Records"."AccountID")
INNER JOIN
	"Types"
		ON ("Types"."ID" = "Records"."TypeID")
INNER JOIN
	"Domains"
		ON ("Domains"."ID" = "Records"."DomainID")
WHERE
	lower("Records"."Target") = lower(:name)
		AND lower("Types"."Name") = lower(:type)
		AND "Records"."Active" = true
		AND "Types"."Active"   = true
		AND "Domains"."Active" = true
