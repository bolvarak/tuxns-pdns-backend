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
	"Domains"."ID" = :id
		AND "Domains"."Active" = true
		AND "Records"."Active" = true
