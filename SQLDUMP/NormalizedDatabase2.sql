-- MySQL Script generated by MySQL Workbench
-- 04/28/16 21:15:35
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema TicketingSystem
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema TicketingSystem
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `TicketingSystem` DEFAULT CHARACTER SET utf8 ;
USE `TicketingSystem` ;

-- -----------------------------------------------------
-- Table `TicketingSystem`.`Tickets`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `TicketingSystem`.`Tickets` ;

CREATE TABLE IF NOT EXISTS `TicketingSystem`.`Tickets` (
  `TicketID` INT(10) NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(255) NULL DEFAULT NULL,
  `Category` ENUM('Hardware', 'Software', 'Networking') NULL DEFAULT NULL,
  `Severity` ENUM('1', '2', '3', '4', '5') NULL DEFAULT NULL,
  `Createdby` VARCHAR(32) NULL DEFAULT NULL,
  `description` VARCHAR(255) NULL DEFAULT NULL,
  `status` ENUM('Open', 'Closed', 'Acknowledged', 'Active', 'Resolved') NULL DEFAULT NULL,
  PRIMARY KEY (`TicketID`))
ENGINE = InnoDB
AUTO_INCREMENT = 18
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `TicketingSystem`.`CommentsTable`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `TicketingSystem`.`CommentsTable` ;

CREATE TABLE IF NOT EXISTS `TicketingSystem`.`CommentsTable` (
  `TicketID` INT(10) NULL DEFAULT NULL,
  `comments` VARCHAR(255) NULL DEFAULT NULL,
  INDEX `TicketID_idx` (`TicketID` ASC),
  CONSTRAINT `TicketID`
    FOREIGN KEY (`TicketID`)
    REFERENCES `TicketingSystem`.`Tickets` (`TicketID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `TicketingSystem`.`login`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `TicketingSystem`.`login` ;

CREATE TABLE IF NOT EXISTS `TicketingSystem`.`login` (
  `LoginID` INT(10) NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(32) NULL DEFAULT NULL,
  `password` VARCHAR(32) NULL DEFAULT NULL,
  `privilegeLevel` ENUM('admin', 'manager', 'user') NULL DEFAULT NULL,
  `reportsto` VARCHAR(30) NULL DEFAULT NULL,
  `AssignedTickets` INT(11) NOT NULL,
  PRIMARY KEY (`LoginID`))
ENGINE = InnoDB
AUTO_INCREMENT = 21
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `TicketingSystem`.`Assignment`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `TicketingSystem`.`Assignment` ;

CREATE TABLE IF NOT EXISTS `TicketingSystem`.`Assignment` (
  `TicketID` INT(10) NULL,
  `LoginID` INT(10) NULL,
  `Assignedto` VARCHAR(255) NULL,
  INDEX `TicketID_idx` (`TicketID` ASC),
  INDEX `LoginID_idx` (`LoginID` ASC),
  CONSTRAINT `TicketID`
    FOREIGN KEY (`TicketID`)
    REFERENCES `TicketingSystem`.`Tickets` (`TicketID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `LoginID`
    FOREIGN KEY (`LoginID`)
    REFERENCES `TicketingSystem`.`login` (`LoginID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;