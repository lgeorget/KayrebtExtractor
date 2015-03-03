/**
 * \file identifier.h
 * \brief Definition of a node identifier
 * \author Laurent Georget
 * \date 2015-03-02
 */

#ifndef IDENTIFIER_H
#define IDENTIFIER_H

namespace kayrebt
{
	/**
	 * \brief Node descriptor as given by the Boost Graph Library for the
	 * specific types of graph we use.
	 *
	 * Unfortunately, the typedef has to be hardcoded in order not to
	 * propagate the Boost headers to client code.
	 */
	typedef void* NodeDescriptor;

	/**
	 * \brief Uniquely identify a node in the activity diagram
	 *
	 * \a Identifier is a useful type to represent nodes in the activity
	 * diagram. It can be dereferenced to the inner type, the one produced
	 * by the Boost Graph Library, for use in some algorithms.
	 * Its main use is to provide stronger typing than Boost descriptors for
	 * the different kinds of nodes an activity diagram may contain.
	 */
	class Identifier
	{
		public:
			/**
			 * \brief Dereference the \a Identifier
			 * \return the inner node descriptor handled by the
			 * Boost Graph Library.
			 */
			NodeDescriptor operator*() const { return _n; }

			/**
			 * \brief Construct an \a Identifier from a node
			 * descriptor
			 * \param[in] n the Boost Graph Library node descriptor
			 * to identify
			 */
			Identifier(NodeDescriptor n) : _n(n) {}

		private:
			/**
			 * \brief the Boost Graph Library node descriptor
			 */
			NodeDescriptor _n;
	};
}
#endif
