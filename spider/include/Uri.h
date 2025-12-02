#ifndef URI_H
#define URI_H
#include "libspider.h"
#include <string>
#include <vector>

using namespace std;

namespace spider {
	class Uri;
	#ifndef URI_CLASS
    class Uri : public string {
	private:

		vector<string> *fragments;
	public:
		string protocol;
		string entity;
		string id;
		Uri(string uri);
		~Uri();
	};
	#define URI_CLASS;
	#endif
}

#endif // URI_H
