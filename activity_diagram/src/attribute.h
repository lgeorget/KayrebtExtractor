/**
 * \file attribute.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of structures that foreign code can use to embed extra
 *        attributes in the disgrams
 */
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include "identifier.h"

namespace kayrebt {

	class BaseAttribute
	{
		public:
			BaseAttribute(const std::string& name) : _name(name) {}
			virtual ~BaseAttribute() = default;
			virtual void print(std::ostream& out) const = 0;

		protected:
			std::string _name;
	};

	template<typename T>
	class default_outputter
	{
		public:
			void operator()(std::ostream& out, const T& value) const {
				out << value;
			}
	};

	template<>
	class default_outputter<std::string>
	{
		public:
			void operator()(std::ostream& out, const std::string& value) const;
	};

	template<>
	class default_outputter<const char*>
	{
		public:
			void operator()(std::ostream& out, const char*& value) const;
	};

	template<typename T, typename Outputter = default_outputter<T>>
	class Attribute : public BaseAttribute
	{
		public:
			Attribute(const std::string& name, const T& value, const Outputter& out = Outputter()) : BaseAttribute(name), _value(value), _outputter(out) {}
			virtual void print(std::ostream& out) const {
				out << _name << "=";
				_outputter(out,_value);
			}

		protected:
			T _value;
			Outputter _outputter;
	};
}

std::ostream& operator<<(std::ostream& out, const kayrebt::BaseAttribute& attr);

#endif
