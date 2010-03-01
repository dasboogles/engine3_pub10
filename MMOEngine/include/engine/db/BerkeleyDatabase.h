/*
 * BerkeleyDatabase.h
 *
 *  Created on: 13/02/2010
 *      Author: victor
 */

#ifndef BERKELEYDATABASE_H_
#define BERKELEYDATABASE_H_

#include <db.h>

#include "Database.h"
#include "DatabaseConfig.h"
#include "Transaction.h"
#include "DatabaseEntry.h"
#include "Cursor.h"

namespace engine {
 namespace db {

	 class Environment;
	 class Cursor;

	 class BerkeleyDatabase : public Database {
	 protected:
		 DatabaseConfig databaseConfig;

		 Environment* environment;

		 String filename, databaseName;

		 DB *dbp;           /* DB structure handle */

	 protected:
		BerkeleyDatabase(Environment* env, Transaction* txn, const String& filename, const String& databaseName, const DatabaseConfig& databaseConfig = DatabaseConfig::DEFAULT);

	 public:
		 BerkeleyDatabase(const String& filename, const String& databaseName, const DatabaseConfig& databaseConfig = DatabaseConfig::DEFAULT);
		 ~BerkeleyDatabase();

		 /**
		  * Retrieves the key/data pair with the given key.
		  */
		 int get(Transaction* txn, DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode = LockMode::DEFAULT);

		 /**
		  * Store the key/data pair into the database.
		  */
		 int put(Transaction* txn, DatabaseEntry* key, DatabaseEntry* data);

		 /**
		  * Return a cursor into the database.
		  */
		 Cursor* openCursor(Transaction* txn, const CursorConfig& config = CursorConfig::DEFAULT);

		 /**
		  * Flush any cached information to disk.
		  */
		 void sync();

		 /**
		  * Empty the database, discarding all records it contains.
		  */
		 int truncate(Transaction* txn, bool countRecords);

		 /**
		  * Remove key/data pairs from the database.
		  */
		 int del(Transaction* txn, DatabaseEntry* key);

		 /**
		  * Flush any cached database information to disk and discard the database handle.
		  */
		 void close(bool noSync);


		 inline String& getDatabaseFile() {
			 return filename;
		 }

		 inline String& getDatabaseName() {
			 return databaseName;
		 }

		 inline DatabaseConfig& getDatabaseConfig() {
			 return databaseConfig;
		 }

		 inline Environment* getEnvironment() const {
			 return environment;
		 }

		 friend class Environment;
	 };

 }
}

using namespace engine::db;

#endif /* BERKELEYDATABASE_H_ */