DROP TABLE IF EXISTS temperature;
DROP TABLE IF EXISTS humidity;
DROP TABLE IF EXISTS pressure;
DROP TABLE IF EXISTS wind_speed;

CREATE TABLE temperature (
  time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  value FLOAT NOT NULL DEFAULT 0
);

CREATE TABLE humidity (
  time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  value FLOAT NOT NULL DEFAULT 0
);

CREATE TABLE pressure (
  time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  value FLOAT NOT NULL DEFAULT 0
);

CREATE TABLE wind_speed (
  time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  value FLOAT NOT NULL DEFAULT 0
);