#ifndef SPXML_H
#define SPXML_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace space {
    enum class SPXmlNodeType { Element, Text };

    // Minimal backend-neutral XML tree built on top of EXPAT.
    class SPXmlNode {
    public:
        SPXmlNode(SPXmlNodeType type, std::string name = "", SPXmlNode *parent = nullptr)
            : m_type(type), m_name(std::move(name)), m_parent(parent) {}

        SPXmlNodeType getType() const { return m_type; }
        const std::string &getName() const { return m_name; }
        const std::string &getContent() const { return m_content; }
        SPXmlNode *getParent() const { return m_parent; }
        const std::vector<std::pair<std::string, std::string>> &getAttributes() const { return m_attributes; }
        const std::vector<std::unique_ptr<SPXmlNode>> &getChildren() const { return m_children; }
        std::string getAttribute(const std::string &name, const std::string &fallback = "") const;

    private:
        friend class SPXmlDocument;
        friend struct SPXmlBuilder;
        SPXmlNodeType m_type;
        std::string m_name;
        std::string m_content;
        SPXmlNode *m_parent;
        std::vector<std::pair<std::string, std::string>> m_attributes;
        std::vector<std::unique_ptr<SPXmlNode>> m_children;
    };

    class SPXmlDocument {
    public:
        bool loadFile(const std::string &filename);
        bool loadString(const std::string &data);
        const SPXmlNode *getRoot() const { return m_root.get(); }

    private:
        std::unique_ptr<SPXmlNode> m_root;
    };
}

#endif
