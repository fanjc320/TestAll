/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50621
Source Host           : localhost:3307
Source Database       : klrz

Target Server Type    : MYSQL
Target Server Version : 50621
File Encoding         : 65001

Date: 2017-03-14 17:02:42
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `test`
-- ----------------------------
DROP TABLE IF EXISTS `test`;
CREATE TABLE `test` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `rq` date NOT NULL,
  `ch` varchar(500) NOT NULL,
  `jql` double DEFAULT NULL,
  `zy` varchar(500) DEFAULT NULL,
  `hsdj` double DEFAULT NULL,
  `hsze` double DEFAULT NULL,
  `dj` double DEFAULT NULL,
  `je` double DEFAULT NULL,
  `se` double DEFAULT NULL,
  `bz` varchar(500) DEFAULT NULL,
  `gys` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of test
-- ----------------------------
