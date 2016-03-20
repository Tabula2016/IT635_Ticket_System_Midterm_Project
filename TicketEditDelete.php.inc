<?php
	class TicketEditDelete
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

?>
