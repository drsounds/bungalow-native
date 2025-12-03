#ifndef URI_H
#define URI_H
#include "libspider.h"
#include <string>
#include <vector>

using namespace std;

namespace spider {
    class Uri {
	private:

		vector<string> *fragments;
	public:
    	string uri;
		string protocol;
		string entity;
		string id;
    	string getUri() {
    		return uri;
    	}
		Uri(string uri);
		~Uri();
	};
}

#endif // URI_H
