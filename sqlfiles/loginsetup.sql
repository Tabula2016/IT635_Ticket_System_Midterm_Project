Use TicketingSystem;

drop table if exists userlogin;

create table login
(
	LoginID int(10) primary key auto_increment,
	username varchar(32),
	password varchar(32),
	privilegeLevel enum("manager","user"),
	displayName varchar(32)
);
