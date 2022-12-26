#include "Bookshelf.h"
#include "Map.h"

typedef string Title;
typedef Map<Title, BookInfo> LibraryDatabase;

using namespace std;

void addBooks(LibraryDatabase& database);
void modifyBooks(LibraryDatabase& database);
void testKeyAlreadyExistsException(LibraryDatabase& database);
void testKeyNotFoundException(LibraryDatabase& database);

int main() {
    LibraryDatabase database;
    addBooks(database);
    
    cout << "_______LIBRARY BEFORE CHANGES_______" << endl;
    cout << database;

    modifyBooks(database);
    cout << "_______LIBRARY AFTER CHANGES________" << endl;
    cout << database;

    testKeyNotFoundException(database);
    testKeyAlreadyExistsException(database);
}

void addBooks(LibraryDatabase& database) {
    database.add("Peter Pan", BookInfo("J.M Barrie", "Fantasy", 349));
    database.add("The Fellowship of the Ring", BookInfo("J.R.R Tolkien", "Fantasy", 423));
    database.add("Heart of Darkness", BookInfo("J. Conrad", "Novella", 722));
    database.add("The C++ Programming Language", BookInfo("B. Stroustrup", "Educational", 1376));
    database.add("Quo Vadis", BookInfo("A. Sienkiewicz", "Historical Novel", 589));
}

void modifyBooks(LibraryDatabase& database) {
    database.find("The C++ Programming Language")->isBorrowed = true;
    database.find("Heart of Darkness")->numberOfPages = 72;
    database.find("Quo Vadis")->author = "H. Sienkiewicz";
    database.remove("The Fellowship of the Ring");
    
}

void testKeyAlreadyExistsException(LibraryDatabase& database) {
    cout << "_____KeyAlreadyExistsException______" << endl;
    try {
        database.add("Peter Pan", BookInfo());
    } catch (KeyAlreadyExistsException& e) {
        cout << e.what() << endl;
    }
}

void testKeyNotFoundException(LibraryDatabase& database) {
    cout << "________KeyNotFoundException________" << endl;
    try {
        database.find("Dziady");
    } catch (KeyNotFoundException& e) {
        cout << e.what() << endl;
    }
}