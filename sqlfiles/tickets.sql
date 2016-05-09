USE TicketingSystem;

drop table if exists Tickets;

create table Tickets
(
	ID int(10) primary key auto_increment,
	title varchar(255),
	Category enum("Hardware", "Software", "Networking"),
	Severity enum("1", "2", "3", "4", "5"),
	Createdby varchar(32),
	description varchar(255),
	comments varchar(255),
	status enum("Open", "Closed", "Acknowledged", "Active", "Resolved"),
	Assignedto varchar(255)
);
