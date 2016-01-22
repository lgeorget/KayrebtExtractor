/**
 * \file url_finder.cpp
 * \author Laurent Georget
 * \date 2015-05-13
 * \brief Implementation of the database querier
 */

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sqlite3.h>
#include <functional>
#include "url_finder.h"

UrlFinder::UrlFinder(std::string prefix) :
	_db(nullptr), _urlFetcher(nullptr), _prefix(prefix)
{}

void UrlFinder::open(const char* filename, const char* dbname)
{
	_fetchStmt = "SELECT dir,file FROM ";
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
	// strip optimizing symbols such as ISRA
	// This should be correct, dots are not allowed in identifiers
	std::string originalSymbol = function.substr(0, function.find('.'));
	sqlite3_bind_text(_urlFetcher, 1, originalSymbol.c_str(), originalSymbol.length(), SQLITE_STATIC);
	std::string res;
	if (sqlite3_step(_urlFetcher) == SQLITE_ROW) {
		sqlite3_column_text(_urlFetcher, 0);
		const char *dir;
		const char *file;
		dir = reinterpret_cast<const char*>(sqlite3_column_blob(_urlFetcher, 0));
		file = reinterpret_cast<const char*>(sqlite3_column_blob(_urlFetcher, 1));
		std::string temp(dir);
		temp += file;
		auto ittemp = temp.begin();
		auto itpref = _prefix.begin();
		auto pos = temp.begin();
		for ( ; ittemp != temp.end() && itpref != _prefix.end() ;
		     ++ittemp, ++itpref) {
			if (*ittemp != *itpref)
				break;
			if (*ittemp == '/') {
				pos = ittemp;
				pos++;
			}
		}
		std::cerr << "temp: " << temp << "\tprefix: " << _prefix << std::endl;

		int count = std::count(itpref, _prefix.end(), '/');
		for (int i = 0 ; i <= count ; i++)
			res += "../";
		std::copy(pos, temp.end(), std::back_inserter(res));
		res += "/" + function;
	} else {
		res = function; // we no longer use the original symbol
				// (== function with optimization suffixes stripped)
				// but the real symbol name
	}

	sqlite3_reset(_urlFetcher);

	return res;
}

UrlFinder::operator bool() const
{
	return _db != nullptr;
}
