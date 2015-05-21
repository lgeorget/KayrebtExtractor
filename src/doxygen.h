#ifndef DOXYGEN_H
#define DOXYGEN_H

#error "This file is not supposed to be included, it is here for documentation purpose only"

/**
 * \mainpage The Kayrebt::Extractor Approximative Manual
 *
 * \section intro_sec Introduction
 *
 * Kayrebt::Extractor is a GCC plugin which extracts activity diagrams out of
 * C functions. It has been designed to analyze the Linux kernel codebase.
 *
 * \section usage_sec Usage
 *
 * \subsection config Configuration
 *
 * Kayrebt:Extractor can be configured through command line arguments and with
 * a YAML configuration file. A typical configuration file looks like the
 * following:
 *
 \code{.yaml}
 general:
   - greedy: 0
   - url:
       - dbfile: my_db.sqlite
       - dbname: symbols
   - categories:
       - 1: 'bgcolor=blue'
       - 2: 'textcolor=red'

 source_file1.c:
   - functions: ['function1','function2']
   - match:
       - '(k|m)alloc.*': 1

 source_file2.c:
   - functions: ['one_more_function','especially_interesting_function']
   - start_match:
       - '.*spin_lock.*': 2
   - end_match: ['spin_unlock']
 \endcode

 * Configuration options:
 * \li \c greedy: Set the greedy mode on (value 1) or off (value 0). If greedy
 * mode is on, Kayrebt::Extractor will output a graph for every function GCC
 * compiles: otherwise only functions explicitly named for will be graphed.
 * \li \c url: Configuration section for the URL fetcher. The URL fetcher is
 * used to resolve a URL for the function symbols from a local SQLITE3 database.
 * This is useful to make hyperlinks between graphs for example.
 * \li \c dbfile: Set the SQLITE3 database file.
 * \li \c dbname: Set the SQLITE3 database name.
 * \li \c categories: Map each category of nodes (a category is represented by
 * a number) with a string defining attributes for the nodes of that category.
 * \li \c functions: Give the list of functions to graph in the compilation unit
 * whose name is the name of the section.
 * \li \c match: Map regular expressions with categories. The nodes whose label
 * matches the regular expression will belong to that category.
 * \li \c start_match: Map regular expressions with categories. From the node
 * matching this regular expression to the first node matching an \c end_match
 * expression, all met nodes will belong to the corresponding category.
 * \li \c end_match: List of category-stopper. When a node matching an \c
 * end_match is met, the nodes no longer belong to the category of the last
 * \c start_match category.
 *
 * It is possible to override categorization defined in the general section
 * by ones in compilation units section. In this case, while compiling the
 * compilation unit, the more specific categorizations will be used. Also,
 * the categorization started by a \c start_match has precedence over
 * standalone categorizations (described \c match). It is not currently
 * possible to nest categorizations.
 *
 * \subsection drawing Drawing an activity diagram
 *
 * To extract an activity diagram from a C function (once the approriate
 * configuration file has been written), it is necessary to call GCC with the
 * plugin as a parameter this way (the exact name of the plugin may vary):
 *
 * <code>gcc -fplugin=kayrebt_extractor file.c -o file.o</code>
 *
 * You may have to give the explicit path to the plugin if it is not installed
 * in GCC default directory (try <code>echo $(gcc -print-file-name=plugin)</code>
 * to find out where the plugins must be installed for GCC to find them
 * automatically).
 *
 * For each source file \c file.c, Kayrebt::Extractor will create a file called
 * \c file.c.dump containing a graph for each function compiled. Of course, only
 * the functions explicitly asked for in the configuration file will be graphed,
 * except if the plugin is running in greedy mode. To actually extract an
 * individual GraphViz file for each graph, the script \c clip.pl is provided.
 * When passed a \c .c.dump file, it will create as many \c function.dot as
 * necessary. GraphViz tools are then necessary to make images out of those
 * graphs files.
 */

#endif
