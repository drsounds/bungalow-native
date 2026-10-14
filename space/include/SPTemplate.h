#ifndef SP_TEMPLATE_H
#define SP_TEMPLATE_H

#include <boost/json/object.hpp>
#include <string>

namespace space {
    class SPTemplate {
    public:
        static std::string render(
            const std::string& source,
            const std::string& method,
            const std::string& uri,
            const std::string& action,
            const boost::json::object& data,
            const boost::json::object& model);
        static std::string renderFile(
            const std::string& filename,
            const std::string& method,
            const std::string& uri,
            const std::string& action,
            const boost::json::object& data,
            const boost::json::object& model);
    };
}

#endif
