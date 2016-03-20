<?php


class LoginAI 

{


private $db;
private $ini;
 
function __construct($inifile)
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







function read_input()
{
	echo "Enter Username and Password for Admin access:  ".PHP_EOL;
	$usernameInput = fopen("php://stdin", "r");
	$input1 = fgets($usernameInput, 32);
	$input1= rtrim($input1);
	fclose($usernameInput);

	$passwordInput = fopen("php://stdin", "r");
	$input2 = fgets($passwordInput, 32);
	$input2 =rtrim($input2);
	fclose($passwordInput);

	$query = "Select username, password, privielgeLevel from login where username = '$input1';";
	$results =$this->db->query($query);
	$row = $results->fetch_assoc();
	
	if($row['password'] === $input2 && $row['privilegeLevel'] === "Admin")
	{
		echo "Logged in as Admin:  '$input1'";
		return true;
	}
	
	return false;
}


}

$read_input = new LoginAI();

$read_input->read_input();

?>
