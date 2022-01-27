-- +----------------------------------------------------------+
-- | libgetter - part of Getter Package Manager               |
-- | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
-- |                                                          |
-- | Copyright (C) 2021-2022 dotandl                          |
-- +----------------------------------------------------------+

BEGIN;
CREATE TABLE IF NOT EXISTS packages (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL UNIQUE,
  full_name TEXT NOT NULL,
  license_name TEXT NOT NULL,
  installed_explicitly INTEGER NOT NULL -- BOOL
);

CREATE TABLE IF NOT EXISTS dependency_types (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  type TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS dependencies (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  package_id INTEGER NOT NULL,
  dependency_id INTEGER NOT NULL,
  dependency_type INTEGER NOT NULL,
  FOREIGN KEY (package_id) REFERENCES packages (id),
  FOREIGN KEY (dependency_id) REFERENCES packages (id),
  FOREIGN KEY (dependency_type) REFERENCES dependency_types (id)
);

INSERT OR IGNORE INTO dependency_types (type)
VALUES
  ('normal'),
  ('optional'),
  ('build'),
  ('replacement'),
  ('conflict');
COMMIT;
