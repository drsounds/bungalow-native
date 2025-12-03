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
#define SP_EVENT_MOUSE_DOWN 1
#define SP_EVENT_MOUSE_UP 2
#define SP_EVENT_MOUSE_MOVE 3
#define SP_EVENT_NAVIGATE 4

#include "SPType.h"
#include "EventArgs.h"
using namespace std;


namespace spider {
	class SPEvent
	{
	public:
		string type;
		EventArgs *args;
		SPType *sender;
		SPEvent(const string& type, EventArgs *args, SPType *sender) {
			this->type = type;
			this->args = args;
			this->sender = sender;
		}
	};
	class SPMessage
	{
	public:
		string type;
		string subject_uri;
		string predicate;
		string object_uri;
	};
	struct margin {
		int left;
		int top;
		int bottom;
		int right;
	};
	int htmlToColor(string str);
	struct position {
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

	typedef int(*sp_callback)(const string& action, SPType *, EventArgs *);
}
#endif
