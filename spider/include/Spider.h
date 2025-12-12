//
// Created by Alexander Forselius on 2025-12-12.
//

#ifndef SPACIFYCLIENT_SPIDER_H
#define SPACIFYCLIENT_SPIDER_H
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace space {
class SPSpiderElement;
}

namespace spider {
	class Spider {
		space::SPSpiderElement *element;
	public:
		explicit Spider(space::SPSpiderElement *element);
		void serve();
	};
}

#endif //SPACIFYCLIENT_SPIDER_H