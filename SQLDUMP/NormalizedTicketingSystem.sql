-- MySQL dump 10.13  Distrib 5.5.47, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: TicketingSystem
-- ------------------------------------------------------
-- Server version	5.5.47-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `CommentsTable`
--

DROP TABLE IF EXISTS `CommentsTable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CommentsTable` (
  `TicketID` int(10) DEFAULT NULL,
  `comments` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CommentsTable`
--

LOCK TABLES `CommentsTable` WRITE;
/*!40000 ALTER TABLE `CommentsTable` DISABLE KEYS */;
INSERT INTO `CommentsTable` VALUES (9,'This is a comment'),(9,'This is a second comment');
/*!40000 ALTER TABLE `CommentsTable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tickets`
--

DROP TABLE IF EXISTS `Tickets`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Tickets` (
  `TicketID` int(10) NOT NULL AUTO_INCREMENT,
  `title` varchar(255) DEFAULT NULL,
  `Category` enum('Hardware','Software','Networking') DEFAULT NULL,
  `Severity` enum('1','2','3','4','5') DEFAULT NULL,
  `Createdby` varchar(32) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `status` enum('Open','Closed','Acknowledged','Active','Resolved') DEFAULT NULL,
  `Assignedto` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`TicketID`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tickets`
--

LOCK TABLES `Tickets` WRITE;
/*!40000 ALTER TABLE `Tickets` DISABLE KEYS */;
INSERT INTO `Tickets` VALUES (9,'Office365 issue','Software','4','Paul','I hate office365 issues','Open','smith'),(10,'Computer sucks','Hardware','2','user23','I hate this computer','Closed','Paul'),(13,'Computer sucks','Hardware','2','user23','I hate this computer','Open','smith6'),(14,'Outlook issue','Software','3','Zeus','Outlook is giving me an error','Closed','smith6'),(15,'Skype issue','Software','3','Adonis','Skype is giving me an error','Open','smith5'),(16,'Tikcet123','Hardware','3','joe','This is a test Ticket','Open','smith8'),(17,'Ticket1','Software','4','user5','This is just a test ticket','Open','user5');
/*!40000 ALTER TABLE `Tickets` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `login`
--

DROP TABLE IF EXISTS `login`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `login` (
  `LoginID` int(10) NOT NULL AUTO_INCREMENT,
  `username` varchar(32) DEFAULT NULL,
  `password` varchar(32) DEFAULT NULL,
  `privilegeLevel` enum('admin','manager','user') DEFAULT NULL,
  `reportsto` varchar(30) DEFAULT NULL,
  `AssignedTickets` int(11) NOT NULL,
  PRIMARY KEY (`LoginID`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `login`
--

LOCK TABLES `login` WRITE;
/*!40000 ALTER TABLE `login` DISABLE KEYS */;
INSERT INTO `login` VALUES (1,'Paul','e77722d198f0aea70e70','manager',NULL,2),(2,'Mohmmad','971e25d7fa089f774e0f','manager',NULL,2),(3,'joe','e77722d198f0aea70e70','admin',NULL,0),(4,'john','e77722d198f0aea70e70','user',NULL,0),(5,'admin1','test123','admin','no-one',0),(6,'smith','60ddd7170c7c47a43ecf','user','',1),(7,'smith1','60ddd7170c7c47a43ecf','user','joe',0),(8,'smith2','60ddd7170c7c47a43ecf','manager','joe',0),(9,'smith3','60ddd7170c7c47a43ecf','user','joe',0),(10,'smith4','60ddd7170c7c47a43ecf','user','joe',0),(11,'smith5','60ddd7170c7c47a43ecf','user','Mohmmad',0),(12,'smith6','60ddd7170c7c47a43ecf','user','Mohmmad',0),(13,'smith8','60ddd7170c7c47a43ecf','user','Paul',0),(14,'smith9','60ddd7170c7c47a43ecf','user','Paul',0),(15,'user1','e77722d198f0aea70e70','user','Mohmmad',0),(16,'Dan','60ddd7170c7c47a43ecf','user','joe',0),(17,'Amir','60ddd7170c7c47a43ecf','user','Mohmmad',0),(18,'user23','60ddd7170c7c47a43ecf','user','Mohmmad',0),(19,'testuser123','60ddd7170c7c47a43ecf','manager','Paul',0),(20,'user5','60ddd7170c7c47a43ecf','manager','Paul',0);
/*!40000 ALTER TABLE `login` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-04-25  2:30:01
