/**
 * \file url_finder.h
 * \author Laurent Georget
 * \date 2015-05-13
 * \brief Definition of a database querier
 */
#ifndef URL_FINDER_H
#define URL_FINDER_H

#include <iostream>
#include <sqlite3.h>

/**
 * \brief Fetch the location of a function symbol inside a SQLITE3 database
 *
 * The database must have a table with the following structure:
 * ___________________________
 * | symbol  |  file  |  dir |
 * |_________|________|______|
 * | TEXT    |  TEXT  | TEXT |
 * |_________|________|______|
 * The table's name can be configured.
 */
class UrlFinder
{
public:
	/**
	 * \brief Build a UrlFinder object
	 *
	 * This constructor does not initialize the database connection. This is
	 * delayed until a call to UrlFinder::open().
	 *
	 * \param prefix the path leading to the function being dumped (it
	 * corresponds to the file it is defined in)
	 */
	UrlFinder(std::string prefix);
	/**
	 * \brief Open the database connection
	 * \param filename the database file
	 * \param dbname the table's name
	 * \throw std::runtime_error if the database connection could not be
	 * established
	 */
	void open(const char* filename, const char* dbname);
	/**
	 * \brief Fetch the location of a function symbol
	 * \param function the function symbol to look for
	 *
	 * This method actually returns only the 'dir' (third column) or "."
	 * if the function could not be found in the database.
	 */
	std::string operator()(const std::string& function);
	/**
	 * \brief Close the database connection if necessary and destroy the
	 * object
	 */
	~UrlFinder();
	/**
	 * \brief Yield true if the database connection is established
	 */
	explicit operator bool() const;

private:
	sqlite3* _db = nullptr; /*! the database handler */
	sqlite3_stmt* _urlFetcher = nullptr; /*! the prepared statement */
	std::string _fetchStmt; /*! the prepared statement as a string */
	std::string _prefix; /*! the path based on which the UrlFinder will
			       build relative URLs */
};

#endif
