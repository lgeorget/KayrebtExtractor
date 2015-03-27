#ifndef URL_FINDER_H
#define URL_FINDER_H

#include <iostream>
#include <sqlite3.h>

class UrlFinder
{
public:
	UrlFinder();
	void open(const char* filename, const char* dbname);
	std::string operator()(const std::string& function);
	~UrlFinder();
	explicit operator bool() const;

private:
	sqlite3* _db = nullptr;
	sqlite3_stmt* _urlFetcher = nullptr;
	std::string _fetchStmt;
};

#endif
