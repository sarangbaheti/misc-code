-- - InstSamp.SQL   09/18/1996
GO

---------------------------------------------------------------
-- Create Database
---------------------------------------------------------------
-- Set switches for creating database
set nocount on
set dateformat mdy

-- Initially point to the master database
USE master

GO

-- Drop the VCEESamples database if it initially exists
declare @dttm varchar(55)
select @dttm=convert(varchar,getdate(),113)
raiserror('Beginning InstSamp.SQL at %s ....',1,1,@dttm) with nowait

if exists (select * from sysdatabases where name='VCEESamples')
	DROP database VCEESamples

GO

-- Check for completion.  (Make sure the db is completely dropped before creating another.)
CHECKPOINT

GO

-- Create the VCEESamples database using 3 MB of space in master.
CREATE DATABASE VCEESamples
	on master = 3

GO

-- Check for completion.  (Make sure the db is completely created before proceeding.)
CHECKPOINT

GO

-- Switch to the VCEESamples database.
USE VCEESamples

GO

-- Verify the existence of VCEESamples.
if db_name() = 'VCEESamples'
	raiserror ('''VCEESamples'' database created, and context now in use.', 1, 1)
else
	raiserror ('Error in InstSamp.SQL, ''USE VCEESamples'' failed!  Killing the SPID now.',
			22, 127) with log

GO

-- Clear the log.
execute sp_dboption 'VCEESamples', 'trunc. log on chkpt.' , 'true'

GO

---------------------------------------------------------------
-- Create Tables
---------------------------------------------------------------

-- Echo to console that we are creating tables.
raiserror('Now at the create table section ....',1,1)

GO

---------------------------------------------------------------
-- Tables for Orders Samples

-- OrdersAccount
CREATE TABLE OrdersAccount
(
	AccountID       int     NOT NULL    CONSTRAINT UPKCL_ccountind PRIMARY KEY CLUSTERED,
	Balance     money   NOT NULL,
	PIN     varchar(4)  NOT NULL
)

GO

-- OrdersInventory
CREATE TABLE OrdersInventory
(
	PartID      int     NOT NULL    CONSTRAINT UPKCL_partidind PRIMARY KEY CLUSTERED,
	InStock     int     NOT NULL,
	Description varchar(128)    NULL,
	Price       money   NOT NULL
)

GO

-- OrdersShipping
CREATE TABLE OrdersShipping
(
	OrderID     int     NOT NULL    CONSTRAINT UPKCL_orderidind PRIMARY KEY CLUSTERED,
	AccountID   int     NOT NULL,
	PartID      int     NOT NULL,
	Quantity    int     NOT NULL,
	State       int     NOT NULL
)

GO

---------------------------------------------------------------
-- Tables for Stocks Samples

-- StocksAccount
CREATE TABLE StocksAccount
(
	AccountID   int     NOT NULL    CONSTRAINT UPKCL_accountidind PRIMARY KEY CLUSTERED,
	Balance     money   NOT NULL,
	PIN     varchar(4)  NOT NULL
)

GO

-- StocksShares and additional index
CREATE TABLE StocksShares
(
	AccountID   int     NOT NULL,
	Stock       varchar(10) NOT NULL,
	Shares      int     NOT NULL
)

GO

CREATE INDEX UPKCL_stockind ON StocksShares(Stock)

GO

-- StocksTrades
CREATE TABLE StocksTrades
(
	AccountID   int     NOT NULL,
	Stock       varchar(10) NOT NULL,
	Action      int     NOT NULL,
	Shares      int     NOT NULL,
	Price       float   NOT NULL
)

GO

---------------------------------------------------------------
-- Populate tables with data
---------------------------------------------------------------

GO

---------------------------------------------------------------
-- Tables for Orders Samples

-- OrdersAccount
raiserror('Now at the inserts to OrdersAccount ....',1,1)

insert OrdersAccount VALUES(1, 1000.00, 'xxxx')
insert OrdersAccount VALUES(2, 1000.00, 'xxxx')
insert OrdersAccount VALUES(3, 1000.00, 'xxxx')
insert OrdersAccount VALUES(4, 1000.00, 'xxxx')
insert OrdersAccount VALUES(5, 1000.00, 'xxxx')
insert OrdersAccount VALUES(6, 1000.00, 'xxxx')

GO

-- OrdersInventory
raiserror('Now at the inserts to OrdersInventory ....',1,1)

GO

insert OrdersInventory VALUES(1, 1000, 'Widgets', 5.25)
insert OrdersInventory VALUES(2, 1500, 'Nuts', 0.05)
insert OrdersInventory VALUES(3, 200, 'Bolts', 0.25)
insert OrdersInventory VALUES(4, 2000, 'Hammers', 15.75)

GO

---------------------------------------------------------------
-- Tables for Stocks Samples

-- StocksAccount
raiserror('Now at the inserts to StocksAccount ....',1,1)

GO

insert StocksAccount VALUES(1, 100000.00, 'xxxx')
insert StocksAccount VALUES(2, 25.00, 'xxxx')
insert StocksAccount VALUES(3, 5000.00, 'xxxx')
insert StocksAccount VALUES(4, 5.00, 'xxxx')
insert StocksAccount VALUES(5, -20.00, 'xxxx')
insert StocksAccount VALUES(6, 0.00, 'xxxx')
insert StocksAccount VALUES(7, 3000.00, 'xxxx')
insert StocksAccount VALUES(8, 400000.00, 'xxxx')
insert StocksAccount VALUES(9, 6795.23, 'xxxx')
insert StocksAccount VALUES(10, 600.00, 'xxxx')
insert StocksAccount VALUES(11, 50.00, 'xxxx')
insert StocksAccount VALUES(12, 1000000.00, 'xxxx')

GO

-- StocksTrades
raiserror('Now at the inserts to StocksTrades ....',1,1)

GO

insert StocksTrades VALUES(1, 'FOO', 1, 100, 25.25)
insert StocksTrades VALUES(2, 'BAR', 0, 200, 20.00)
insert StocksTrades VALUES(3, 'FOO', 1, 1000, 25.375)
insert StocksTrades VALUES(4, 'BAR', 0, 300, 20.25)

GO

-- StocksShares
raiserror('Now at the inserts to StocksShares ....',1,1)

GO
insert StocksShares VALUES(1, 'FOO', 1000)
insert StocksShares VALUES(2, 'BAR', 200)
insert StocksShares VALUES(1, 'BAR', 300)
insert StocksShares VALUES(2, 'BAZ', 500)
insert StocksShares VALUES(4, 'FOO', 2000)
insert StocksShares VALUES(5, 'BAR', 500)

GO

-- Create sp to validate account used by MTO's.
raiserror('Now creating sp_validaccount ....',1,1)

GO

CREATE PROCEDURE sp_validaccount @acct int
AS
declare @cnt int
select @cnt=count(*) from StocksAccount where StocksAccount.AccountID = @acct
if @cnt=0
begin
	raiserror ('Invalid Account', 16, -1)
end
RETURN

---------------------------------------------------------------
-- Grant permissions to db objects
---------------------------------------------------------------

GO

-- SP Valid Account
raiserror('Now granting permissions for stored procedures ....',1,1)

GO

GRANT execute ON sp_validaccount TO public
GRANT CREATE PROCEDURE TO public

GO

GRANT ALL ON OrdersAccount TO public
GRANT ALL ON OrdersInventory TO public
GRANT ALL ON OrdersShipping TO public
GRANT ALL ON StocksAccount TO public
GRANT ALL ON StocksShares TO public
GRANT ALL ON StocksTrades TO public

GRANT CREATE TABLE TO public
GRANT CREATE VIEW TO public
GRANT CREATE RULE TO public
GRANT CREATE DEFAULT TO public
GRANT CREATE PROCEDURE TO public

GO

-- Refresh the database to update permissions.
UPDATE STATISTICS OrdersAccount
UPDATE STATISTICS OrdersShipping
UPDATE STATISTICS OrdersInventory
UPDATE STATISTICS StocksAccount
UPDATE STATISTICS StocksShares
UPDATE STATISTICS StocksTrades

GO

-- Ensure permissions are granted before proceeding.
CHECKPOINT

GO

---------------------------------------------------------------
-- End the script.
---------------------------------------------------------------

-- Return to the master database.
USE master

GO

-- Ensure we are in the master database before proceeding.
CHECKPOINT

GO

-- Send date and time that script completed.
declare @dttm varchar(55)
select @dttm=convert(varchar,getdate(),113)
raiserror('Ending InstSamp.SQL at %s ....',1,1,@dttm) with nowait

GO
-- -
