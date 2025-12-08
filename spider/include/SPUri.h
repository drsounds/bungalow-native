#ifndef URI_H
#define URI_H
#include "libspider.h"
#include <string>
#include <vector>

using namespace std;

namespace space {
    class SPUri {
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
		SPUri(string uri);
		~SPUri();
	};
}

#endif // URI_H
