#include <iostream>
#include <stdexcept>
#include <sqlite3.h>
#include <functional>
#include "url_finder.h"

UrlFinder::UrlFinder() : _db(nullptr), _urlFetcher(nullptr)
{}

void UrlFinder::open(const char* filename, const char* dbname)
{
	_fetchStmt = "SELECT dir FROM ";
	_fetchStmt += dbname;
	_fetchStmt += " WHERE symbol=?1;";
#ifndef NDEBUG
	std::cerr << "Opening database " << filename << std::endl;
#endif
	if (sqlite3_open(filename, &_db) != SQLITE_OK) {
		throw std::runtime_error(sqlite3_errmsg(_db));
	}

#ifndef NDEBUG
	std::cerr << "Compiling statement" << std::endl;
#endif
	if (sqlite3_prepare_v2(_db, _fetchStmt.c_str(), _fetchStmt.length()+1, &_urlFetcher, nullptr) != SQLITE_OK) {
		throw std::runtime_error(sqlite3_errmsg(_db));
	}
#ifndef NDEBUG
	std::cerr << "Database ready" << std::endl;
	std::cerr << "Stmt: " << _fetchStmt << std::endl;
#endif
}

UrlFinder::~UrlFinder()
{
#ifndef NDEBUG
	std::cerr << "Closing database" << std::endl;
#endif
	if (_urlFetcher)
		sqlite3_finalize(_urlFetcher);
	if (_db)
		sqlite3_close(_db);
}

std::string UrlFinder::operator()(const std::string& function)
{
	if (!_db || !_urlFetcher)
		throw std::bad_function_call();

#ifndef NDEBUG
	std::cerr << "Looking for function " << function << " in the database" << std::endl;
#endif
	sqlite3_bind_text(_urlFetcher, 1, function.c_str(), function.length(), SQLITE_STATIC);
	const char* dir = ".";
	if (sqlite3_step(_urlFetcher) == SQLITE_ROW) {
		sqlite3_column_text(_urlFetcher, 0);
		dir = reinterpret_cast<const char*>(sqlite3_column_blob(_urlFetcher, 0));
	}
	std::string res(dir);
	sqlite3_reset(_urlFetcher);

	return res;
}

UrlFinder::operator bool() const
{
	return _db != nullptr;
}
