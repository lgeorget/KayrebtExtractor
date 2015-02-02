#ifndef IDENTIFIER_H
#define IDENTIFIER_H

namespace kayrebt
{
	typedef void* NodeDescriptor;

	class Identifier
	{
		public:
			NodeDescriptor operator*() const { return _n; }
			Identifier(NodeDescriptor n) : _n(n) {}

		private:
			NodeDescriptor _n;
	};
}
#endif
