DROP TABLE IF EXISTS `genres`;
CREATE TABLE `genres` (
	`name` VARCHAR[120] PRIMARY KEY
);

DROP TABLE IF EXISTS `themes`;
CREATE TABLE `themes` (
	`name` VARCHAR[120] PRIMARY KEY
);

DROP TABLE IF EXISTS `games`;
CREATE TABLE `games` (
	`title` VARCHAR[120] PRIMARY KEY,
	`year` INT,
	`developer` VARCHAR[120],
	`publisher` VARCHAR[120],
	`manual` VARCHAR[120],
	`boxart` VARCHAR[120],
	`configfile` VARCHAR[120],
	`playtime` INT,
	`completed` BOOLEAN,
	`extras` VARCHAR[120]
);

DROP TABLE IF EXISTS `game_genres`;
CREATE TABLE `game_genres` (
	`game` VARCHAR[120] NOT NULL, 
	`genre` VARCHAR[120] NOT NULL,
	FOREIGN KEY (`game`) REFERENCES `games`(`title`),
	FOREIGN KEY (`genre`) REFERENCES `genres`(`name`),
	CONSTRAINT `con_game_genre_unique` UNIQUE (`game`,`genre`)
);

DROP TABLE IF EXISTS `game_themes`;
CREATE TABLE `game_themes` (
	`game` VARCHAR[120] NOT NULL,
	`theme` VARCHAR[120] NOT NULL,
	FOREIGN KEY (`game`) REFERENCES `games`(`title`),
	FOREIGN KEY (`theme`) REFERENCES `themes`(`name`),
	CONSTRAINT `con_game_theme_unique` UNIQUE (`game`,`theme`)
);
