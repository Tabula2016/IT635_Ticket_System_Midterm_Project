<?php

class loginDB
{
	private $db;
	private $ini;

	public function __construct($inifile)
	{
		$this->ini = parse_ini_file($inifile, true);
		$host = $this->ini['loginDB']['host'];
		$user = $this->ini['loginDB']['user'];
		$password = $this->ini['loginDB']['password'];
		$database = $this->ini['loginDB']['database'];
		
		$this->db = new mysqli($host,$user,$password,$database);

		if ($this->db->connect_errno > 0)
		{
			echo __FILE__.":".__LINE__.": failed to connect to database, re: ".$this->db->connect_error.PHP_EOL;
			exit(0);
		}
	}

	public function __destruct()
	{
		$this->db->close();
	}

	public function checkIfUserExists($username)
   	{
		$username = $this->db->real_escape_string($username);
		$query = "select username from login where username = '$username';";
        	$results = $this->db->query($query);
		$row = $results->fetch_assoc();
		
		if ($row['username'] === $username)
        	{
			return true;
		}
        	
		return false;
   	}


	public function validateUser($username, $password)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($this->saltPassword($password));
		$query = "select username, password from login where username = '$username';";
		$results = $this->db->query($query);
		$row = $results->fetch_assoc();

		if ($row['password'] === $password)
		{
			return true;
		}
		
		return false;
	}

 	public function validateAdminPrivilege($username)
   	{
		$username = $this->db->real_escape_string($username);		
		$query = "select privilegeLevel from login where username = '$username';";
        	$results = $this->db->query($query);
		$row = $results->fetch_assoc();
		
		if ($row['privilegeLevel'] === 'admin')
		{
			echo "".PHP_EOL;
			echo "Admin Access granted! Your command has been processed...  ".PHP_EOL;
			echo "".PHP_EOL;
			return true;
		}

		return false;
   	}

	 public function validateManagerPrivilege($username)
        {
                $username = $this->db->real_escape_string($username);
                $query = "select privilegeLevel from login where username = '$username';";
                $results = $this->db->query($query);
                $row = $results->fetch_assoc();

                if ($row['privilegeLevel'] === 'manager')
                {
                        echo "".PHP_EOL;
                        echo "Manager Access granted! Your command has been processed...  ".PHP_EOL;
                        echo "".PHP_EOL;
                        return true;
                }
                
                return false;
        }

	public function validateOwnerPrivilege($username)
	{
		$username = $this->db->real_escape_string($username);
		$query = "select Createdby from Tickets where Createdby = '$username';";
                $results = $this->db->query($query);
                $row = $results->fetch_assoc();

                if ($row['Createdby'] === "$username")
                {
                        echo "".PHP_EOL;
                        echo "Ticket Owner Access granted! Your command has been processed...  ".PHP_EOL;
                        echo "".PHP_EOL;
                        return true;
                }
                echo "false".PHP_EOL;
                return false;
	}

	private function saltPassword($password)
   	{
		$salt = $this->ini['loginDB']['salt'];
		return substr(sha1($password.$salt),10,-10);
   	}	

	public function addNewUser($username, $password, $privilegeLevel, $newusername, $newpassword, $reportsto)
	{
		if ($this->checkIfUserExists($newusername) == true)
		{
			echo "Not able to create new user $newusername, this user already exists in database!".PHP_EOL;
			return;
		}
		
		$username = $this->db->real_escape_string($username);
		$reportsto = $this->db->real_escape_string($reportsto);
		$newpassword = $this->db->real_escape_string($this->saltPassword($newpassword));
		$privilegeLevel = $this->db->real_escape_string($privilegeLevel);
			
		if ($this->db->errno > 0)
        	{
			echo "DB error: ".$this->db->error.PHP_EOL;
			return;
        	}
		
		if(!$this->validateUser($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}
		else if(!$this->validateAdminPrivilege($username))
		{
			echo "User ". $username . "does not have admin access.".PHP_EOL;
			$response = array(
				"message"=>"User" . $username . "does not have admin access",
				"result"=>"false");
			return $response;
		}
		else
		{
			 $query = "insert into login (username,password,privilegeLevel,reportsto) values('$newusername','$newpassword','$privilegeLevel','$reportsto');";
               		 $results = $this->db->query($query);
			 echo $this->ViewLastUserCreated($username).PHP_EOL;
		}
	}

	 public function ViewLastUserCreated($username)
        {
                $username = $this->db->real_escape_string($username);

                        $query = "Select * from login WHERE LoginID =(SELECT MAX(LoginID) from login);";
                        $results = $this->db->query($query);

                        if($results->num_rows > 0)
                        {
                                while($row = $results->fetch_assoc())
                                {
                                        echo " - LoginID: " . $row['LoginID'] . " - Username: " . $row['username'] . " - PrivilegeLevel: " . $row['privilegeLevel'].PHP_EOL;
					echo " - Reportsto: " . $row['reportsto'].PHP_EOL;
                                }

                }
                        else
                        {
                                echo "0 results for specified results...";
                        }




        }
	

	public function ModifyUserRole($username, $password, $targetuser, $privilegeLevel)
	{
		$username = $this->db->real_escape_string($username);
		$privilegeLevel = $this->db->real_escape_string($privilegeLevel);

		 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateAdminPrivilege($username))
                {
                        echo "User ". $username . "does not have admin access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have admin access",
                                "result"=>"false");
                        return $response;
                }
			
		else 
		{
			$query = "UPDATE login SET privilegeLevel = '$privilegeLevel' WHERE username = '$targetuser';";
			$results = $this->db->query($query);
			echo "User " . "$targetuser" . " has been granted " . $privilegeLevel . " access.".PHP_EOL;
		}
	}

	public function ViewTickets($username, $password)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);

		 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateAdminPrivilege($username))
                {
                        echo "User ". $username . "does not have admin access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have admin access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "Select * from Tickets;";
               		$results = $this->db->query($query);

			if($results->num_rows > 0)
                	{
                        	while($row = $results->fetch_assoc())
                        	{	
                                	echo " - ID: " . $row["ID"] . " - title: " . $row["title"] . " - Category: " . $row["Category"] . " - Severity: " . $row["Severity"].PHP_EOL;
                                	echo  " - Created by: " . $row["Createdby"].PHP_EOL;
					echo " - description: " . $row["description"] . " -comments: " . $row["comments"].PHP_EOL;
                                	echo  " - status: " . $row["status"] . " - Assigned to: " . $row["Assignedto"].PHP_EOL;
                                	echo "".PHP_EOL;
                        	}

                }
                	else
                	{
                        	echo "0 results for specified results...";
                	}
	
		}


	}

	public function ViewLastTicket($username)
        {
                $username = $this->db->real_escape_string($username);
                
                        $query = "Select * from Tickets WHERE ID =(SELECT MAX(ID) from Tickets);";
                        $results = $this->db->query($query);

                        if($results->num_rows > 0)
                        {
                                while($row = $results->fetch_assoc())
                                {
                                        echo " - ID: " . $row["ID"] . " - title: " . $row["title"] . " - Category: " . $row["Category"] . " - Severity: " . $row["Severity"].PHP_EOL;
                                        echo  " - Created by: " . $row["Createdby"].PHP_EOL;
                                        echo " - description: " . $row["description"] . " -comments: " . $row["comments"].PHP_EOL;
                                        echo  " - status: " . $row["status"] . " - Assigned to: " . $row["Assignedto"].PHP_EOL;
                                        echo "".PHP_EOL;
                                }

                }
                        else
                        {
                                echo "0 results for specified results...";
                        }

                


        }


	public function DeleteTicket($username, $password, $TicketID)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
		if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateAdminPrivilege($username))
                {
                        echo "User ". $username . "does not have admin access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have admin access",
                                "result"=>"false");
                        return $response;
                }

                else
                {
			$query = "DELETE FROM Tickets WHERE ID = '$TicketID' ;";
                        $results = $this->db->query($query);
			echo $this->ViewTickets($username, $password);
		}
	}

	public function EditTicket($username, $password, $fieldname, $input, $TicketID)
	{
		 $username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);

                 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }

		else if(!$this->validateAdminPrivilege($username))
                {
                        echo "User ". $username . "does not have admin access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have admin access",
                                "result"=>"false");
                        return $response;
                }
		
		else 
		{
			$query = "UPDATE Tickets SET ". $fieldname . " = '$input' where ID = '$TicketID';";
			$results = $this->db->query($query);
			echo "The following changes have been made to: " . $fieldname . "..... information that was entered: " . $input.PHP_EOL;
					
		}

	}

	public function ManagerReportUser($username, $password)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);

		 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateManagerPrivilege($username))
                {
                        echo "User ". $username . "does not have Manager access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have Manager access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "Select username, reportsto from login where reportsto = '$username' ;";
                        $results = $this->db->query($query);

			 if($results->num_rows > 0)
                        {
				echo "Direct Reports: ".PHP_EOL;
                                while($row = $results->fetch_assoc())
                                {
					echo "".PHP_EOL;
					echo " - Username: " . $row["username"] . " - Manager: " . $row["reportsto"].PHP_EOL;
	                                echo "".PHP_EOL;
                                }

                	}
                        else
                        {
                                echo "0 results for specified results...";
                        }

                }
			
	}
	
	public function CreateTicket($username,$title,$category,$severity,$description,$status,$assignedto)
	{
		$username = $this->db->real_escape_string($username);
		$query = "Insert into Tickets (title, category, Severity, Createdby, description, status, Assignedto) values('$title','$category','$severity','$username','$description','$status','$assignedto');";
		$results = $this->db->query($query);
		echo "Ticket has been created!  ".PHP_EOL;
		echo $this->ViewLastTicket($username);

	
	}

	public function AssignTicketToSelf($username, $password, $TicketID)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
		
		 if(!$this->validateUser($username, $password))
                 {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                 }

		 else
                {
                        $query = "update Tickets, login set Tickets.Assignedto = '$username', login.AssignedTickets = login.AssignedTickets+1 where Tickets.ID = '$TicketID' and login.username ='$username';";
                        $results = $this->db->query($query);
                        echo "Ticket ID: " . $TicketID . " has been assigned to " . $username.PHP_EOL;
                }


	}

	public function ManagerAssign($username, $password, $TicketID, $targetuser)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);
		
		 if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
                else if(!$this->validateManagerPrivilege($username))
                {
                        echo "User ". $username . "does not have Manager access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have Manager access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "UPDATE Tickets SET Assignedto = '$targetuser' where ID = '$TicketID' AND Assignedto IN (SELECT username from login WHERE reportsto = '$username');";
			$results = $this->db->query($query);
			echo "Ticket ID: " . $TicketID . " has been assigned to " . $targetuser.PHP_EOL;
		}
		
	}
		
	
	public function ViewOwnedTickets($username, $password)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);

		if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
		
		else
		{
			 $query = "Select * from Tickets where createdby = '$username';";
                        $results = $this->db->query($query);

                        if($results->num_rows > 0)
                        {
                                while($row = $results->fetch_assoc())
                                {
                                        echo " - ID: " . $row["ID"] . " - title: " . $row["title"] . " - Category: " . $row["Category"] . " - Severity: " . $row["Severity"].PHP_EOL;
                                        echo  " - Created by: " . $row["Createdby"].PHP_EOL;
                                        echo " - description: " . $row["description"] . " -comments: " . $row["comments"].PHP_EOL;
                                        echo  " - status: " . $row["status"] . " - Assigned to: " . $row["Assignedto"].PHP_EOL;
                                        echo "".PHP_EOL;
                                }

			}
			else
			{
				echo "0 results found.".PHP_EOL;
			}
		}
	}
	
	public function AddComment($username, $password, $TicketID, $addcomment)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
		if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }
		
		 else if(!$this->validateManagerPrivilege($username) & !$this->validateOwnerPrivilege($username))
                {
                        echo "User ". $username . "does not have proper access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have proper access",
                                "result"=>"false");
                        return $response;
                }

		
		else
		{
			 $query = "Update Tickets SET comments = '$addcomment' where ID = '$TicketID';";
                        $results = $this->db->query($query);
			echo "You have add the following comment: " . $addcomment . " to ticket ID: " . $TicketID.PHP_EOL;
		}
	}

	public function ChangeStatus($username, $password, $status, $TicketID)
	{
		 $username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
                if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }

                 else if(!$this->validateManagerPrivilege($username) & !$this->validateOwnerPrivilege($username))
                {
                        echo "User ". $username . "does not have proper access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have proper access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "Update Tickets SET status = '$status' where ID = '$TicketID';";
                        $results = $this->db->query($query);
			echo "Ticket ID: " . $TicketID . " status has been changed to: " . $status.PHP_EOL;
		}

	}


	public function ManagerTeamReport($username, $password)
	{
		 $username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
                if(!$this->validateUser($username, $password))
                {
                        echo "Incorrect password".PHP_EOL;
                        $response = array(
                                "message"=>"Incorrect",
                                "result"=>"false"
                        );
                        return $response;
                }

                 else if(!$this->validateManagerPrivilege($username) & !$this->validateOwnerPrivilege($username))
                {
                        echo "User ". $username . "does not have proper access.".PHP_EOL;
                        $response = array(
                                "message"=>"User" . $username . "does not have proper access",
                                "result"=>"false");
                        return $response;
                }
		
		else
		{
			$query = "Select * from Tickets WHERE Assignedto IN (Select username from login where reportsto = '$username');";
			$results = $this->db->query($query);
			echo $this->ManagerReportUser($username, $password);

			if($results->num_rows > 0)
                        {
				echo "Tickets that team owns: ".PHP_EOL;
                                while($row = $results->fetch_assoc())
                                {
                                        echo " - ID: " . $row["ID"] . " - title: " . $row["title"] . " - Category: " . $row["Category"] . " - Severity: " . $row["Severity"].PHP_EOL;
                                        echo  " - Created by: " . $row["Createdby"].PHP_EOL;
                                        echo " - description: " . $row["description"] . " -comments: " . $row["comments"].PHP_EOL;
                                        echo  " - status: " . $row["status"] . " - Assigned to: " . $row["Assignedto"].PHP_EOL;
                                        echo "".PHP_EOL;
                                }

                        }
                        else
                        {
                                echo "0 results found.".PHP_EOL;
                        }

		}
	}


}
?>
