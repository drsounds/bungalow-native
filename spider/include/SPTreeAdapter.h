#ifndef TREEADAPTER_H
#define TREEADAPTER_H
#include "libspider.h"
namespace space {
    template <class T>
	class SPTreeAdapter {
	public:
		virtual T getItemAt(int pos);
		virtual int count();
	};
}

#endif // TREEADAPTER_H
