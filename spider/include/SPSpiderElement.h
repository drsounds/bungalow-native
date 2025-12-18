//
// Created by Alexander Forselius on 2025-12-12.
//

#ifndef SPACIFYCLIENT_PYSPELEMENT_H
#define SPACIFYCLIENT_PYSPELEMENT_H
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "SPTabBarViewElement.h"


class Spider {

};

namespace space
{
	class SPElement;
	class SPSpiderElement : public SPTabBarViewElement {
		public:
			explicit SPSpiderElement(SPElement *parent);
			void start();
	};
}


#endif //SPACIFYCLIENT_PYSPELEMENT_H