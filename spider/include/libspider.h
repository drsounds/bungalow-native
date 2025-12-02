#ifndef H_LIBSPIDER
#define H_LIBSPIDER
#include <map>
#include <string>
#include <vector>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#define DEBUG
#define CONTROL_INPUT 1
#include "SPType.h"
#include "EventArgs.h"
using namespace std;

namespace spider {
	#ifndef MARGIN_STRUCT
	struct margin {
			int left;
			int top;
			int bottom;
			int right;
	};
	#define MARGIN_STRUCT
	#endif
	int htmlToColor(string str);
	struct spider_position {
		int x;
		int y;
	};
	struct rectangle {
		int width;
		int height;
		int x;
		int y;
		int z;
	};

	typedef int(*s_event)(SPType *, EventArgs *);
}
#endif
