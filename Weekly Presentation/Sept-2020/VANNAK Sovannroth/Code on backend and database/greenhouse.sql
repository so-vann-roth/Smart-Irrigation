-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Oct 01, 2020 at 04:51 AM
-- Server version: 5.7.26
-- PHP Version: 7.2.18

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `greenhouse`
--

-- --------------------------------------------------------

--
-- Table structure for table `abouts`
--

DROP TABLE IF EXISTS `abouts`;
CREATE TABLE IF NOT EXISTS `abouts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(200) DEFAULT NULL,
  `description` text,
  `icon` varchar(100) DEFAULT NULL,
  `photo` varchar(200) DEFAULT NULL,
  `sequence` tinyint(4) NOT NULL,
  `url` varchar(250) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `abouts`
--

INSERT INTO `abouts` (`id`, `title`, `description`, `icon`, `photo`, `sequence`, `url`, `active`, `create_at`) VALUES
(1, 'test', NULL, 'test', 'uploads/abouts/g2P3M3vFGYr5mFaEKhbk7GLRax8Mf4Enb59stgl9.jpeg', 1, '#', 0, '2020-09-06 07:51:04'),
(2, 'test', 'Laudem latine persequeris id sed, ex fabulas delectus quo. No vel partiendo abhorreant vituperatoribus, ad pro quaestio laboramus. Ei ubique vivendum pro. At ius nisl accusam lorenta zanos paradigno tridexa panatarel.', 'sdg', 'uploads/abouts/CNRpo0NE0TqtROp2aAEkM4OnEGVYeNnkyjZfOUbG.jpeg', 1, '#', 1, '2020-09-06 08:13:44'),
(3, 'book', '123', 't', 'uploads/abouts/mSorQWxrRR8XO8QB4U773dIIVGcmQLxywvLBvTax.jpeg', 1, '#', 1, '2020-09-06 10:28:41'),
(4, 'car', 'ewewqewgertheth', 'e', 'uploads/abouts/ru0AuJYwAuOsPlpDYRliHKuvIkpI6OXAofr5a3c9.jpeg', 1, '#', 1, '2020-09-06 10:29:01'),
(5, 'dfds', 'dfafa', 'w', 'uploads/abouts/VVwwNraoFnSHulJ80fQQyOAYoPW5BKQUTz2mASph.jpeg', 1, '#', 1, '2020-09-06 10:29:15');

-- --------------------------------------------------------

--
-- Table structure for table `categories`
--

DROP TABLE IF EXISTS `categories`;
CREATE TABLE IF NOT EXISTS `categories` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(200) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `categories`
--

INSERT INTO `categories` (`id`, `name`, `active`, `create_at`) VALUES
(1, 'Web development', 1, '2020-09-04 09:30:11'),
(2, 'Web', 0, '2020-09-04 09:34:40'),
(3, 'ITC Green House', 1, '2020-09-05 16:00:48'),
(4, 'Facebook', 0, '2020-09-06 10:27:04'),
(5, 'Telegram', 1, '2020-09-06 10:27:14'),
(6, 'Facebook', 1, '2020-09-21 08:52:44');

-- --------------------------------------------------------

--
-- Table structure for table `charts`
--

DROP TABLE IF EXISTS `charts`;
CREATE TABLE IF NOT EXISTS `charts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(200) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `clients`
--

DROP TABLE IF EXISTS `clients`;
CREATE TABLE IF NOT EXISTS `clients` (
  `id` int(11) NOT NULL,
  `name` varchar(200) DEFAULT NULL,
  `logo` varchar(200) DEFAULT NULL,
  `url` varchar(200) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `companies`
--

DROP TABLE IF EXISTS `companies`;
CREATE TABLE IF NOT EXISTS `companies` (
  `id` tinyint(4) NOT NULL AUTO_INCREMENT,
  `name` varchar(200) DEFAULT NULL,
  `logo` varchar(200) DEFAULT NULL,
  `description` text,
  `phone` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `address` text NOT NULL,
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `companies`
--

INSERT INTO `companies` (`id`, `name`, `logo`, `description`, `phone`, `email`, `address`, `create_at`) VALUES
(1, 'LBE Labratory', 'uploads/companies/s5kLmkuECxXFN0fpwzpumEtUWz7eXJHDzt5VTzUO.jpeg', 'Tamen quem nulla quae legam multos aute sint culpa legam noster magna veniam enim veniam illum dolore legam minim quorum culpa amet magna export quem marada parida nodela caramase seza.', '0123456789', 'info@itc.com', 'Institute of Technology of Cambodia', '2020-09-03 13:53:31');

-- --------------------------------------------------------

--
-- Table structure for table `features`
--

DROP TABLE IF EXISTS `features`;
CREATE TABLE IF NOT EXISTS `features` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(200) DEFAULT NULL,
  `description` text,
  `icon` varchar(200) DEFAULT NULL,
  `url` varchar(250) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `features`
--

INSERT INTO `features` (`id`, `title`, `description`, `icon`, `url`, `active`, `create_at`) VALUES
(1, 'test', 'test', 'test', '#', 0, '2020-09-05 16:03:22'),
(2, 'slideshow1', 'sfdwfew', 'test', '#', 1, '2020-09-05 16:55:10'),
(3, 'fdg', NULL, 'sdg', '#', 0, '2020-09-05 16:55:18'),
(4, 'slideshowew', NULL, 'test', '#', 0, '2020-09-06 04:46:13'),
(5, 'Our Mission', NULL, 'eefw', '#', 1, '2020-09-07 08:26:44');

-- --------------------------------------------------------

--
-- Table structure for table `itc`
--

DROP TABLE IF EXISTS `itc`;
CREATE TABLE IF NOT EXISTS `itc` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `temp1` float NOT NULL,
  `temp2` float NOT NULL,
  `hum1` float NOT NULL,
  `hum2` float NOT NULL,
  `mois1` float NOT NULL,
  `mois2` float NOT NULL,
  `radiation` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `itcs`
--

DROP TABLE IF EXISTS `itcs`;
CREATE TABLE IF NOT EXISTS `itcs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Temp1` float NOT NULL,
  `Temp2` float NOT NULL,
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `migrations`
--

DROP TABLE IF EXISTS `migrations`;
CREATE TABLE IF NOT EXISTS `migrations` (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `migration` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `batch` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `pages`
--

DROP TABLE IF EXISTS `pages`;
CREATE TABLE IF NOT EXISTS `pages` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(250) DEFAULT NULL,
  `description` text,
  `slug` varchar(100) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pages`
--

INSERT INTO `pages` (`id`, `title`, `description`, `slug`, `active`, `create_at`) VALUES
(1, 'ABOUT US', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.', 'about', 1, '2020-09-06 03:43:26'),
(2, 'SERVICES', 'Laudem latine persequeris id sed, ex fabulas delectus quo. No vel partiendo abhorreant vituperatoribus, ad pro quaestio laboramus. Ei ubique vivendum pro. At ius nisl accusam lorenta zanos paradigno tridexa panatarel.', 'service', 1, '2020-09-06 03:45:29'),
(3, 'TEAM', 'Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque', 'team', 1, '2020-09-06 03:46:57'),
(4, 'CONTACT US', 'Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque', 'contact', 1, '2020-09-06 03:48:04');

-- --------------------------------------------------------

--
-- Table structure for table `portfolios`
--

DROP TABLE IF EXISTS `portfolios`;
CREATE TABLE IF NOT EXISTS `portfolios` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(200) DEFAULT NULL,
  `description` text,
  `photo` varchar(200) DEFAULT NULL,
  `category_id` int(11) DEFAULT NULL,
  `url` varchar(200) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `projects`
--

DROP TABLE IF EXISTS `projects`;
CREATE TABLE IF NOT EXISTS `projects` (
  `id` tinyint(4) NOT NULL AUTO_INCREMENT,
  `title` varchar(200) DEFAULT NULL,
  `logo` varchar(200) DEFAULT NULL,
  `description` text,
  `address` text NOT NULL,
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `projects`
--

INSERT INTO `projects` (`id`, `title`, `logo`, `description`, `address`, `create_at`) VALUES
(1, 'Smart Irrigation (IoT and AI)', 'uploads/projects/EH2z4UIfryMHylIpl4HurvCKsQGTMwnj00OORX6J.png', 'Tamen quem nulla quae legam multos aute sint culpa legam noster magna veniam enim veniam illum dolore legam minim quorum culpa amet magna export quem marada parida nodela caramase seza.', 'Institute of Technology of Cambodia', '2020-09-03 13:53:31');

-- --------------------------------------------------------

--
-- Table structure for table `services`
--

DROP TABLE IF EXISTS `services`;
CREATE TABLE IF NOT EXISTS `services` (
  `id` int(11) NOT NULL,
  `title` varchar(200) NOT NULL,
  `description` text NOT NULL,
  `icon` varchar(100) NOT NULL,
  `sequence` tinyint(4) NOT NULL DEFAULT '1',
  `url` varchar(250) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `slides`
--

DROP TABLE IF EXISTS `slides`;
CREATE TABLE IF NOT EXISTS `slides` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(250) DEFAULT NULL,
  `description` text,
  `photo` varchar(200) DEFAULT NULL,
  `sequence` tinyint(4) NOT NULL DEFAULT '1',
  `url` varchar(200) DEFAULT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=15 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `slides`
--

INSERT INTO `slides` (`id`, `title`, `description`, `photo`, `sequence`, `url`, `active`, `create_at`) VALUES
(13, 'test', 'slide', 'uploads/slides/XOkzK5vxVQDdXN6uGN1fVcuencJvn16XMsIv9IZn.jpeg', 1, '#', 1, '2020-09-05 06:43:00'),
(12, 'slideshow', 'slide', 'uploads/slides/d6bBINyFoSxRhjid1CPGO9PMHZHjXF4IPlCi9jWv.jpeg', 1, '#', 0, '2020-09-05 06:42:47'),
(11, 'slideshow', 'slide', 'uploads/slides/gGIGvN19e2Ovm3AOYyXdV7MiDnb992PUpaQemWr8.jpeg', 1, '#', 0, '2020-09-05 06:39:12'),
(9, 'slideshow', 'slide', 'uploads/slides/yotlpH3gV05iH26bFfovWUzF6C5w6ZG8mRSZICnY.jpeg', 1, '#', 0, '2020-09-05 06:36:52'),
(10, 'slideshow', 'slide', 'uploads/slides/x8jaqpNHynfLTEbJa7DQ4BFgMopFR0hAVl8cv1BL.png', 1, '#', 0, '2020-09-05 06:37:03'),
(14, 'test', 'slide', 'uploads/slides/5ca3bbd7edc1f4ff862e4d0ed2b145ce.jpg', 1, '#', 1, '2020-09-05 14:53:28');

-- --------------------------------------------------------

--
-- Table structure for table `socials`
--

DROP TABLE IF EXISTS `socials`;
CREATE TABLE IF NOT EXISTS `socials` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `icon` varchar(200) NOT NULL,
  `url` varchar(200) NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `socials`
--

INSERT INTO `socials` (`id`, `name`, `icon`, `url`, `active`, `create_at`) VALUES
(1, 'Facebook', 'Facebook', 'https://facebook.com', 1, '2020-09-04 13:35:23');

-- --------------------------------------------------------

--
-- Table structure for table `teams`
--

DROP TABLE IF EXISTS `teams`;
CREATE TABLE IF NOT EXISTS `teams` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `position` varchar(100) NOT NULL,
  `photo` varchar(200) NOT NULL,
  `description` text,
  `facebook` varchar(200) NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `teams`
--

INSERT INTO `teams` (`id`, `name`, `position`, `photo`, `description`, `facebook`, `active`, `create_at`) VALUES
(1, 'Vannak Sovannroth', 'Third year', 'uploads/teams/aX6RL3hZBmxOXfmiAdD1L06F4b88zBS2QDYleryh.png', 'Frontend, Backend, and App', 'Sovannroth Vannak', 0, '2020-09-30 13:41:48'),
(2, 'GTR', 'Student', 'uploads/teams/KlAXZHwXjFLSX3gzQOPzTJeYSuobQjD3v8kvMFA8.png', 'wefwe', 'Sovannroth Vannak', 0, '2020-09-30 13:57:53'),
(3, 'Hel Chanthan', 'Teacher', 'uploads/teams/GjIQjre2n8k9APwk7DdzZDneTySwjIW9dBwH1kIt.jpeg', 'Advisor', 'Chanthan Hel', 1, '2020-10-01 02:47:22'),
(4, 'Vannak Sovannroth', 'Student', 'uploads/teams/KFlvtkuysG6smzriFMqWhXN2PXzG8MeukUZlMmmG.jpeg', 'Frontend, Backend, and Mobile App', 'Sovannroth Vannak', 1, '2020-10-01 02:49:07'),
(5, 'Nhim Chann Rengsey', 'Student', 'uploads/teams/pEGbjSKlurjeMsqMKit6CgS48DZ6uD9Hm1s61a0f.jpeg', 'PH sensor, PCB, and Hardware', 'Nhim Chann Rengsey', 1, '2020-10-01 02:51:20'),
(6, 'Proeung Bunrong', 'Student', 'uploads/teams/ZpBV80f2uB40VfU8lSOYOZ576SuCTtO7TCfX2d7j.jpeg', 'Thingspeak fetch data from Green House', 'Bunrong Proeung', 1, '2020-10-01 02:58:35'),
(7, 'Chek Nita', 'Student', 'uploads/teams/MCPYh0bXhhgx5LG3GoqlfkGXvXPSgdYQGftUfAmn.jpeg', 'Learning Machine Learning and AI', 'Nita Chek', 1, '2020-10-01 02:59:59');

-- --------------------------------------------------------

--
-- Table structure for table `testimonials`
--

DROP TABLE IF EXISTS `testimonials`;
CREATE TABLE IF NOT EXISTS `testimonials` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(200) DEFAULT NULL,
  `position` varchar(100) DEFAULT NULL,
  `photo` varchar(200) DEFAULT NULL,
  `description` text,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `create_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE IF NOT EXISTS `users` (
  `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email_verified_at` timestamp NULL DEFAULT NULL,
  `password` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `remember_token` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `photo` varchar(250) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=21 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `name`, `email`, `email_verified_at`, `password`, `remember_token`, `photo`, `created_at`, `updated_at`) VALUES
(1, 'Admin', 'admin@gmail.com', NULL, '$2y$10$HrSpWs0ldzR7mpAp6et42OzOjExwFooR7vIxKVehOfGeEoznWVB52', NULL, 'uploads/users/WlpOHH33QAjPiT7k4Wt96L9OzVyF9UGJLt1Sm9SB.png', '2020-08-25 22:20:12', '2020-08-25 22:20:12'),
(2, 'GTR', 'gtr@gmail.com', NULL, '$2y$10$E0GKBK0CeFOdW4gP7UoC.exuFmNNFWtMNJ8wwuFbajO3A9hAxuZ8a', NULL, 'uploads/users/SrvsTXGemKZVaUpV0VGrXT3PIZh6yor9ENvbGr7D.jpeg', NULL, NULL),
(4, 'LBE', 'lbe@gmaill.com', NULL, '$2y$10$uE3g8O5qxn.B6G9Q6ObVkOXblru335hPPgM61yqo1cqjaj3MEjFc.', NULL, 'uploads/users/V71cW6B7qzYMryqWcpmv03wAQLamSYwVqzZARhRI.jpeg', NULL, NULL),
(9, 'Sovannroth', 'sovannroth@gmail.com', NULL, '$2y$10$y33K6iLviDkx.c9GBzSZsewXQht1UvLyuWcMQsNDqTjGBM1N0Dnw.', NULL, 'uploads/users/XcIeraMODAbnuFdfu4rydZbx2bs9cCkNezzcRgwj.jpeg', NULL, NULL),
(10, 'Nita', 'nita@gmail.com', NULL, '$2y$10$to09LD8/O/8dANcbo0kMXOHafb780Y2zVJr9RXNOTlvGeAymcNNhS', NULL, 'uploads/users/rkkZ6KxrqpFwbqbaokODSiF3AzmlHWckz9ms3KWL.png', NULL, NULL),
(8, 'ITC', 'itc@gmail.com', NULL, '$2y$10$nH3oYSuu3pq03XvKBjNd9OP3xesGCR0iBTgOpVqfbPV4nOTXoo1hm', NULL, 'uploads/users/hjB3BBRou9Mz4eZrBre2RMpLT16HDopXf8Huup1W.png', NULL, NULL),
(11, 'Rengsey', 'rengsey@gmail.com', NULL, '$2y$10$Fs5oF4A94XweX6.kAQIW5.iQQMgnskwff2B9wZ8FEH2c90ueNCFFC', NULL, 'uploads/users/n2qLLWSFls3tWCBn5FoG7duaOlz4kHtmcx297RQa.png', NULL, NULL),
(12, 'Rotanak', 'rotanak@gmail.com', NULL, '$2y$10$XISLocVh7kxqCVHdVfNFeukb6okQiMIFRktPkiAoSABuW8ddxf7k.', NULL, 'uploads/users/J0I8hD5EjYNgXcr8Sw6fVcRLPOLmbH1xHHK4asoL.png', NULL, NULL),
(13, 'Bonrong', 'bonrong@gmail.com', NULL, '$2y$10$86Z5q4xBHqZiEB/Lk.qZiOvLXkPmEYIuSQGlewtbpSZdwbft4r/UG', NULL, 'uploads/users/HOaPcUK6UWGgHGQkVZTesfBoNwtz4au81mUCnY9E.jpeg', NULL, NULL),
(14, 'Mary', 'mary@gmail.com', NULL, '$2y$10$to8O./pD/LEiY9WvEt8rgO2uJGi3vYZhHG97ThuBbLdXlVi7lcb3O', NULL, 'uploads/users/ITi4dMIumcH4obKHFdF2Hkwip9sWaYtCsVFPQfMJ.jpeg', NULL, NULL),
(15, 'Chettra', 'chettra@gmail.com', NULL, '$2y$10$5x7EQU4npCr0K2GAaYyxEeAjYtnGTFIt4jrhqtDK1BIae/2qdaoW2', NULL, 'uploads/users/avIqEF8i22es2rHODS2qaivbVzvcA3oqJjnh74CI.jpeg', NULL, NULL),
(16, 'Chivan', 'chivan@gmail.com', NULL, '$2y$10$fu/HgFFhiDB0uA0ED84JpOtNxNEiHX3BIyDbXzsdc38cAMCUJ9iMW', NULL, 'uploads/users/kdMknO3I5nmwJDce1kfJTBCQDfWVEYLmD9rT1ZIr.jpeg', NULL, NULL),
(17, 'Borey', 'borey@gmail.com', NULL, '$2y$10$sWczjjvpptkDOfQkVUmoyu1u87YjwnXg/pt.rX3ik4h2ktHlYvLBi', NULL, 'uploads/users/0KihtGvlAcwqIwLwAC4SXUFnJkef9hZZIMhLvWAq.jpeg', NULL, NULL),
(18, 'Soknim', 'soknim@gmail.com', NULL, '$2y$10$Fd.58Ff2PD2GT/n1.ngVaecDBJK.T.g2kT0IwuU58d6brMfpIFCYu', NULL, 'uploads/users/eEgOMi8eg84JcVQfC6Fa2eqeEX9fxPqzdEbozeSo.jpeg', NULL, NULL),
(19, 'Sokheng', 'sokheng@gmail.com', NULL, '$2y$10$VmV7lUQMrKnLGF.C5uuiUOoLpl.zle/2g92qwZY9.ydg3X6pgGB8e', NULL, 'uploads/users/tuk7J9dP8ruSzsRmLMFwCopmC57QZGQXWOd12f1Z.jpeg', NULL, NULL),
(20, 'RUA', 'rua@gmail.com', NULL, '$2y$10$fSyVjkFCG8Rjtvinu65oj.wHx.nNZqT8PngMYSFl8j6GBVEA/ncD6', NULL, 'uploads/users/VdSvhhoaHDunJjIHznk3YuLK4Ew6bfy1ylYx97yy.jpeg', NULL, NULL);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
