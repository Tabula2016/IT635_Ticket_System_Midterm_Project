USE TicketingSystem;

DROP procedure if exists CreateTicket;

DELIMITER //

create procedure `CreateTicket`(
	IN ID INT,
	IN title varchar(255),
	IN Category enum("Hardware", "Software", "Networking"),
	IN Severity enum("1","2","3","4","5"),
	IN Createdby varchar(32),
	IN description varchar(255),
	IN comments varchar(255),
	IN status enum("Open", "Closed", "Acknowledged", "Active", "Resolved"),
	IN Assignedto varchar(255)
)

BEGIN 

insert into Tickets (
	title,
	Category,
	Severity,
	Createdby,
	description,
	comments,
	status,
	Assignedto)

	values(
		title,
		Category,
		Serverity,
		Createdby,
		description,
		comments,
		status,
		Assignedto);

END //
