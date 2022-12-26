#pragma once

#include <string>
#include <iostream>

using namespace std;

// information about the author, category, number of pages and status (on the bookshelf / borrowed). 
struct BookInfo {
    string author;
    string category;
    int numberOfPages;
    bool isBorrowed;
    BookInfo(string author = "-", string category = "-", int numberOfPages = 0, bool isBorrowed = false);
};

BookInfo::BookInfo(string author, string category, int numberOfPages, bool isBorrowed) {
    this->author = author;
    this->category = category;
    this->numberOfPages = numberOfPages;
    this->isBorrowed = isBorrowed;
}

ostream& operator<<(ostream& out, const BookInfo& book) {
	out << "Author: " << book.author << "; Category: " << book.category << "; Number of pages: " << book.numberOfPages << "; Status: ";
    if(book.isBorrowed) {
        out << "borrowed" << endl;
    } else {
        out << "on the bookshlef" << endl;
    }
	return out;
}