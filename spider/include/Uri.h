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
		string protocol;
		string entity;
		string id;
		string uri;
		Uri(string uri);
		string getUri() {
            return this->uri;
		}
		~Uri();
	};
}

#endif // URI_H
