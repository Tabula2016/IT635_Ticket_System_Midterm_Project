Use TicketingSystem;


DROP procedure if exists CreateUser;

DELIMITER //

create procedure `CreateUser`(
	IN LoginID INT,
	IN username varchar(32),
	IN password varchar(32),
	IN PrivilegeLevel enum("manager", "user"),
	IN displayName varchar(32))

BEGIN 

	insert into login (
		login.username,
		login.password,
		login.PrivilegeLevel,
		login.displayName)
	values (
		username,
		password,
		PrivilegeLevel,
		displayName);

END //
