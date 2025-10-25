/*
rather than that this should happen-

   Application ---------->    Interface---------->     SQLDatabase
   (high level)                                        (low level)

Application:
Database d;
d.save()

<<abstract>> 
Database:
save():void

SqlDatabase: (is a relationship with Database)
save():void
MongoDb:     (is a relationship with Database)
save():void
*/

#include <iostream>
using namespace std;

// Abstract interface: Database
class Database {
public:
    virtual void save() = 0; // Pure virtual function
    virtual ~Database() {}
};

// Low-level module: SqlDatabase
class SqlDatabase : public Database {
public:
    void save() override {
        cout << "Data saved to SQL Database" << endl;
    }
};

// Low-level module: MongoDb
class MongoDb : public Database {
public:
    void save() override {
        cout << "Data saved to MongoDB" << endl;
    }
};

// High-level module: Application
class Application {
private:
    Database* database; // Dependency on abstraction
public:
    Application(Database* db) {
        // Inject dependency via constructor
        database = db;
    } 

    void saveData() {
        database->save(); // Call save on the abstraction
    }
};

int main() {
    // Use SQL Database
    SqlDatabase sqlDb;
    Application app1(&sqlDb);
    app1.saveData();

    // Use MongoDB
    MongoDb mongoDb;
    Application app2(&mongoDb);
    app2.saveData();

    return 0;
}