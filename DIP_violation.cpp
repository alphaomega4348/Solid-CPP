/*
High level Module should not depend on Low level Module. Both should depend on Abstraction.

  Application ---->     SQLDatabase
 (high level)        (low level)

Application:
saveToSqlDatabase():void
saveToMongoDb():void

SqlDatabase:
save():void
MongoDb:
save():void
*/

#include <iostream>
using namespace std;

// Low-level module: SqlDatabase
class SqlDatabase {
public:
    void save() {
        cout << "Data saved to SQL Database" << endl;
    }
};

// Low-level module: MongoDb
class MongoDb {
public:
    void save() {
        cout << "Data saved to MongoDB" << endl;
    }
};

// High-level module: Application
class Application {
public:
    void saveToSqlDatabase() {
        SqlDatabase sqlDb;
        sqlDb.save(); // Direct dependency on SqlDatabase
    }

    void saveToMongoDb() {
        MongoDb mongoDb;
        mongoDb.save(); // Direct dependency on MongoDb
    }
};

int main() {
    Application app;

    // Save data to SQL Database
    app.saveToSqlDatabase();

    // Save data to MongoDB
    app.saveToMongoDb();

    return 0;
}