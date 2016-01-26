INSERT INTO "Log" (
	"AccountID",
	"DomainID",
	"RecordID",
	"Source",
	"ListRequest"
) VALUES (
	:account,
	:domain,
	:record,
	:source,
	:listReq
);
