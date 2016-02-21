#!/usr/bin/perl -w
## Strict Syntax
use strict;
## Database Interface
use DBI;
## PostgreSQL
use DBD::Pg;
## INI configuration
use Config::Simple;
## Configuration file path
my $configPath = "/tmp/tuxns.ini";
## Turn off buffering
$|=1;
## Read input from STDIN
my $strLine    = <>;
## Clean the input
chomp($strLine);
## Make sure we have a valid HELO
unless($strLine eq "HELO\t1") {
	## Send the FAIL command
	print "FAIL\n";
	## Send the error
	print STDERR "Received '", $strLine, "'\n";
	## Clear the buffer
	<>;
	## We're done
	exit;
}
## Send the OK response to PowerDNS
print "OK\tTuxNS Initialized\n";
## Iterate over STDIN
while(<>) {
	## Clean the input
	chomp($_);
	## Grab the data
	my @arrParts = split(/\t|\s{2,}/, $_);
	## Make sure we have the correct number of parts to the query
	if (scalar(@arrParts) < 6) {
		## Send the log message
		print "LOG\tPowerDNS sent a bad query.\n";
		## Send the fail message
		print "END\n";
		## Next line
		next;
	}
	## Process the query
	queryTuxNS($arrParts[0], $arrParts[1], $arrParts[2], $arrParts[3], $arrParts[4], $arrParts[5]);
	## We're done
	print "END\n";
}
## Result processor
sub processRecord {
	## Grab our record
	my $hshRecord = shift;
	## Set the data placeholder
	my $strData;
	## Determine the record type
	if (uc $hshRecord->{"Type"} eq "SOA") {
		## Send the data
		$strData = $hshRecord->{"Target"}."\tIN\t".$hshRecord->{"Type"}."\t".$hshRecord->{"TTL"}."\t".$hshRecord->{"DomainID"}."\t".$hshRecord->{"SoaRecord"};
	} elsif (uc $hshRecord->{"Type"} eq "MX") {
		## Send the data
		$strData = $hshRecord->{"Target"}."\tIN\t".$hshRecord->{"Type"}."\t".$hshRecord->{"TTL"}."\t".$hshRecord->{"DomainID"}."\t".$hshRecord->{"Priority"}." ".$hshRecord->{"Destination"};
	} elsif (uc $hshRecord->{"Type"} eq "SRV") {
		## Send the data
		$strData = $hshRecord->{"Target"}."\tIN\t".$hshRecord->{"Type"}."\t".$hshRecord->{"TTL"}."\t".$hshRecord->{"DomainID"}."\t".$hshRecord->{"Priority"}." ".$hshRecord->{"Destination"};
	} else {
		## Send the data
		$strData = $hshRecord->{"Target"}."\tIN\t".$hshRecord->{"Type"}."\t".$hshRecord->{"TTL"}."\t".$hshRecord->{"DomainID"}."\t".$hshRecord->{"Destination"};
	}
	## Send the data
	print "DATA\t${strData}\n";
}
## Define our query subroutine
sub queryTuxNS {
	## Localize the configuration path
	glob $configPath;
	## Define our arguments
	my $strType       = shift;
	my $strQueryName  = shift;
	my $strQueryClass = shift;
	my $strQueryType  = shift;
	my $mixID         = shift;
	my $strIpAddress  = shift;
	## Open the configuration file
	my $clsConfig     = new Config::Simple($configPath);
	## Define our connection settings
	my $strDatabase   = $clsConfig->param('db-name');
	my $strHostName   = $clsConfig->param('db-host');
	my $intPort       = $clsConfig->param('db-port');
	## Open the database connection
	my $dbConn        = DBI->connect("DBI:Pg:dbname=$strDatabase;host=$strHostName;port=$intPort", $clsConfig->param("db-user"), $clsConfig->param("db-pass"), {
		RaiseError => 1
	}) or die "LOG\t".$DBI::errstr."\nFAIL\n";
	## Define the statement
	my $sthQuery;
	## Check for a zone ID and the query type
	if (($mixID ne "-1") && (uc $strQueryType eq "ANY")) {
		## Prepare the statement
		$sthQuery = $dbConn->prepare(sqlStatement("zoneById"))
			or die "LOG\t".$dbConn->errstr."\nFAIL\n";
		## Bind the values
		$sthQuery->bind_param(1, $mixID);
	} elsif (($mixID ne "-1") && (uc $strQueryType ne "ANY")) {
		## Prepare the statement
		$sthQuery = $dbConn->prepare(sqlStatement("byId"))
			or die "LOG\t".$dbConn->errstr."\nFAIL\n";
		## Bind the values
		$sthQuery->bind_param(1, $mixID);
		$sthQuery->bind_param(2, $strQueryType);
	} elsif (($mixID eq "-1") && (uc $strQueryType eq "ANY")) {
		## Prepare the statement
		$sthQuery = $dbConn->prepare(sqlStatement("byName"))
			or die "LOG\t".$dbConn->errstr."\nFAIL\n";
		## Bind the values
		$sthQuery->bind_param(1, $strQueryName);
	} else {
		## Prepare the statement
		$sthQuery = $dbConn->prepare(sqlStatement("byType"))
			or die "LOG\t".$dbConn->errstr."\nFAIL\n";
		## Bind the values
		$sthQuery->bind_param(1, $strQueryName);
		$sthQuery->bind_param(2, $strQueryType);
	}
	## Execute the query
	$sthQuery->execute()
		or die "LOG\t".$sthQuery->errstr."\nFAIL\n";
	## Check for rows
	if ($sthQuery->rows == 0) {
		## Send the log
		print "LOG\tNo results found.\n";
	} else {
		## Iterate over the records
		while (my $hshRecord = $sthQuery->fetchrow_hashref()) {
			## Process the record
			processRecord($hshRecord);
		}
	}
	## Close the database
	$dbConn->disconnect();
}
## Query preparation
sub sqlStatement {
	## Grab our arguments
	my $strName    = shift;
	## Create the SQL hash
	my %hshQueries = (
		byId     => "SELECT \"Accounts\".\"EmailAddress\" AS \"Administrator\", \"Records\".*, \"Types\".\"Name\" AS \"Type\", \"Domains\".\"Nameserver\" || ' ' || \"Accounts\".\"EmailAddress\" AS \"SoaRecord\" FROM \"Records\" INNER JOIN \"Accounts\" ON (\"Accounts\".\"ID\" = \"Records\".\"AccountID\") INNER JOIN \"Types\" ON (\"Types\".\"ID\" = \"Records\".\"TypeID\") INNER JOIN \"Domains\" ON (\"Domains\".\"ID\" = \"Records\".\"DomainID\") WHERE \"Domains\".\"ID\" = ? AND \"Records\".\"Active\" = true AND \"Domains\".\"Active\" = true AND lower(\"Types\".\"Name\") = lower(?)",
		byName   => "SELECT \"Accounts\".\"EmailAddress\" AS \"Administrator\", \"Records\".*, \"Types\".\"Name\" AS \"Type\", \"Domains\".\"Nameserver\" || ' ' || \"Accounts\".\"EmailAddress\" AS \"SoaRecord\" FROM \"Records\" INNER JOIN \"Accounts\" ON (\"Accounts\".\"ID\" = \"Records\".\"AccountID\") INNER JOIN \"Types\" ON (\"Types\".\"ID\" = \"Records\".\"TypeID\") INNER JOIN \"Domains\" ON (\"Domains\".\"ID\" = \"Records\".\"DomainID\") WHERE lower(\"Records\".\"Target\") = lower(?) AND \"Records\".\"Active\" = true AND \"Domains\".\"Active\" = true",
		byType   => "SELECT \"Accounts\".\"EmailAddress\" AS \"Administrator\", \"Records\".*, \"Types\".\"Name\" AS \"Type\", \"Domains\".\"Nameserver\" || ' ' || \"Accounts\".\"EmailAddress\" AS \"SoaRecord\" FROM \"Records\" INNER JOIN \"Accounts\" ON (\"Accounts\".\"ID\" = \"Records\".\"AccountID\") INNER JOIN \"Types\" ON (\"Types\".\"ID\" = \"Records\".\"TypeID\") INNER JOIN \"Domains\" ON (\"Domains\".\"ID\" = \"Records\".\"DomainID\") WHERE lower(\"Records\".\"Target\") = lower(?) AND lower(\"Types\".\"Name\") = lower(?) AND \"Records\".\"Active\" = true AND \"Types\".\"Active\" = true AND \"Domains\".\"Active\" = true",
		zoneById => "SELECT \"Accounts\".\"EmailAddress\" AS \"Administrator\", \"Records\".*, \"Types\".\"Name\" AS \"Type\", \"Domains\".\"Nameserver\" || ' ' || \"Accounts\".\"EmailAddress\" AS \"SoaRecord\" FROM \"Records\" INNER JOIN \"Accounts\" ON (\"Accounts\".\"ID\" = \"Records\".\"AccountID\") INNER JOIN \"Types\" ON (\"Types\".\"ID\" = \"Records\".\"TypeID\") INNER JOIN \"Domains\" ON (\"Domains\".\"ID\" = \"Records\".\"DomainID\") WHERE \"Domains\".\"ID\" = ? AND \"Domains\".\"Active\" = true AND \"Records\".\"Active\" = true"
	);
	## Return the SQL query
	return $hshQueries{$strName};
}
