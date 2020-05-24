-- phpMyAdmin SQL Dump
-- version 4.9.0.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 21, 2019 at 06:03 PM
-- Server version: 10.3.16-MariaDB
-- PHP Version: 7.3.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `mediatek`
--

-- --------------------------------------------------------

--
-- Table structure for table `ctrl_gps`
--

CREATE TABLE `ctrl_gps` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Control` varchar(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ctrl_gps`
--

INSERT INTO `ctrl_gps` (`Time`, `Control`) VALUES
('2019-11-19 03:47:01', '0');

-- --------------------------------------------------------

--
-- Table structure for table `ctrl_hum`
--

CREATE TABLE `ctrl_hum` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Control` varchar(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `ctrl_light`
--

CREATE TABLE `ctrl_light` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Control` varchar(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ctrl_light`
--

INSERT INTO `ctrl_light` (`Time`, `Control`) VALUES
('2019-11-16 17:31:08', '1'),
('2019-11-19 03:46:50', '0');

-- --------------------------------------------------------

--
-- Table structure for table `ctrl_temp`
--

CREATE TABLE `ctrl_temp` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Control` varchar(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ctrl_temp`
--

INSERT INTO `ctrl_temp` (`Time`, `Control`) VALUES
('2019-11-16 17:30:05', '1'),
('2019-11-18 07:46:27', '1'),
('2019-11-19 03:36:10', '1'),
('2019-11-19 03:46:44', '0'),
('2019-11-19 03:56:34', '1'),
('2019-11-19 03:57:20', '0'),
('2019-11-19 03:58:38', '1'),
('2019-11-19 03:59:15', '0'),
('2019-11-19 04:01:41', '1');

-- --------------------------------------------------------

--
-- Table structure for table `ctrl_tilt`
--

CREATE TABLE `ctrl_tilt` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Control` varchar(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ctrl_tilt`
--

INSERT INTO `ctrl_tilt` (`Time`, `Control`) VALUES
('2019-11-16 17:32:06', '1'),
('2019-11-19 03:46:57', '0');

-- --------------------------------------------------------

--
-- Table structure for table `gps`
--

CREATE TABLE `gps` (
  `Time` timestamp(6) NOT NULL DEFAULT current_timestamp(6) ON UPDATE current_timestamp(6),
  `Latitude` varchar(10) NOT NULL,
  `Longitude` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gps`
--

INSERT INTO `gps` (`Time`, `Latitude`, `Longitude`) VALUES
('2019-11-18 19:06:17.569431', 'f', 'f'),
('2019-11-19 04:20:03.330068', 'f', 'f');

-- --------------------------------------------------------

--
-- Table structure for table `hup`
--

CREATE TABLE `hup` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `ilow`
--

CREATE TABLE `ilow` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `light`
--

CREATE TABLE `light` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Light` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `light`
--

INSERT INTO `light` (`Time`, `Light`) VALUES
('2019-11-18 19:06:17', 'f'),
('2019-11-19 04:20:03', 'f');

-- --------------------------------------------------------

--
-- Table structure for table `lt`
--

CREATE TABLE `lt` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `lt`
--

INSERT INTO `lt` (`Time`, `Value`) VALUES
('2019-11-16 17:09:44', 0),
('2019-11-16 17:28:30', 0),
('2019-11-18 07:47:04', 0),
('2019-11-19 03:50:44', 0),
('2019-11-19 03:53:34', -10),
('2019-11-19 03:54:36', -100);

-- --------------------------------------------------------

--
-- Table structure for table `mup`
--

CREATE TABLE `mup` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mup`
--

INSERT INTO `mup` (`Time`, `Value`) VALUES
('2019-11-16 17:09:51', 200),
('2019-11-16 17:28:40', 100),
('2019-11-19 03:50:59', 200),
('2019-11-19 03:54:41', 2000);

-- --------------------------------------------------------

--
-- Table structure for table `nlow`
--

CREATE TABLE `nlow` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nlow`
--

INSERT INTO `nlow` (`Time`, `Value`) VALUES
('2019-11-16 17:09:57', -10),
('2019-11-16 17:28:55', -10),
('2019-11-19 03:51:05', -10),
('2019-11-19 03:54:48', -100);

-- --------------------------------------------------------

--
-- Table structure for table `rf`
--

CREATE TABLE `rf` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `rf`
--

INSERT INTO `rf` (`Time`, `Value`) VALUES
('2019-11-16 17:00:47', 10000),
('2019-11-16 17:02:52', 5000),
('2019-11-16 17:03:58', 5000),
('2019-11-16 17:18:16', 5000),
('2019-11-16 17:26:45', 5000);

-- --------------------------------------------------------

--
-- Table structure for table `sensors`
--

CREATE TABLE `sensors` (
  `Time` varchar(50) NOT NULL DEFAULT current_timestamp(),
  `LowerTemp` varchar(30) NOT NULL,
  `Temperature` varchar(50) NOT NULL,
  `UpperTemp` varchar(30) NOT NULL,
  `Latitude` varchar(50) NOT NULL,
  `Longitude` varchar(50) NOT NULL,
  `LowerHumid` varchar(30) NOT NULL,
  `Humidity` varchar(50) NOT NULL,
  `UpperHumid` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='All Sensors';

-- --------------------------------------------------------

--
-- Table structure for table `sf`
--

CREATE TABLE `sf` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sf`
--

INSERT INTO `sf` (`Time`, `Value`) VALUES
('2019-11-16 17:26:55', 10000);

-- --------------------------------------------------------

--
-- Table structure for table `temperature`
--

CREATE TABLE `temperature` (
  `Time` timestamp(6) NOT NULL DEFAULT current_timestamp(6) ON UPDATE current_timestamp(6),
  `Temperature` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `temperature`
--

INSERT INTO `temperature` (`Time`, `Temperature`) VALUES
('2019-11-18 19:06:17.627047', 'f'),
('2019-11-19 04:20:03.317752', '26.00');

-- --------------------------------------------------------

--
-- Table structure for table `tilt`
--

CREATE TABLE `tilt` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Tilt` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `tilt`
--

INSERT INTO `tilt` (`Time`, `Tilt`) VALUES
('2019-11-18 19:06:17', 'f'),
('2019-11-19 04:20:03', 'f');

-- --------------------------------------------------------

--
-- Table structure for table `tup`
--

CREATE TABLE `tup` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `tup`
--

INSERT INTO `tup` (`Time`, `Value`) VALUES
('2019-11-16 17:10:06', 210),
('2019-11-16 17:29:10', 360),
('2019-11-16 17:29:37', 360),
('2019-11-19 03:51:12', 360),
('2019-11-19 03:54:53', 3600),
('2019-11-19 03:55:10', 360);

-- --------------------------------------------------------

--
-- Table structure for table `ulow`
--

CREATE TABLE `ulow` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ulow`
--

INSERT INTO `ulow` (`Time`, `Value`) VALUES
('2019-11-16 17:10:13', 50),
('2019-11-16 17:29:23', 0),
('2019-11-19 03:51:20', 0);

-- --------------------------------------------------------

--
-- Table structure for table `ut`
--

CREATE TABLE `ut` (
  `Time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `Value` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ut`
--

INSERT INTO `ut` (`Time`, `Value`) VALUES
('2019-11-16 17:28:21', 100),
('2019-11-16 17:33:36', 20),
('2019-11-16 17:34:00', 20),
('2019-11-18 07:46:59', 50),
('2019-11-19 03:50:38', 200),
('2019-11-19 03:54:32', 2000);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ctrl_gps`
--
ALTER TABLE `ctrl_gps`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `ctrl_hum`
--
ALTER TABLE `ctrl_hum`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `ctrl_light`
--
ALTER TABLE `ctrl_light`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `ctrl_temp`
--
ALTER TABLE `ctrl_temp`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `ctrl_tilt`
--
ALTER TABLE `ctrl_tilt`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `hup`
--
ALTER TABLE `hup`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `ilow`
--
ALTER TABLE `ilow`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `light`
--
ALTER TABLE `light`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `lt`
--
ALTER TABLE `lt`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `mup`
--
ALTER TABLE `mup`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `nlow`
--
ALTER TABLE `nlow`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `rf`
--
ALTER TABLE `rf`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `sensors`
--
ALTER TABLE `sensors`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `sf`
--
ALTER TABLE `sf`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `temperature`
--
ALTER TABLE `temperature`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `tilt`
--
ALTER TABLE `tilt`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `tup`
--
ALTER TABLE `tup`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `ulow`
--
ALTER TABLE `ulow`
  ADD PRIMARY KEY (`Time`);

--
-- Indexes for table `ut`
--
ALTER TABLE `ut`
  ADD PRIMARY KEY (`Time`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
