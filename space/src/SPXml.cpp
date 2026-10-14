#include "SPXml.h"

#include <expat.h>

#include <algorithm>
#include <fstream>
#include <sstream>

namespace space {
    struct SPXmlBuilder {
        static void addText(SPXmlNode *parent, const std::string &text) {
            auto node = std::make_unique<SPXmlNode>(SPXmlNodeType::Text, "", parent);
            node->m_content = text;
            parent->m_children.push_back(std::move(node));
        }
        static SPXmlNode *addElement(SPXmlNode *parent, std::unique_ptr<SPXmlNode> &root, const char *name, const char **attrs) {
            auto node = std::make_unique<SPXmlNode>(SPXmlNodeType::Element, name, parent);
            for (int i = 0; attrs[i] != nullptr; i += 2) {
                node->m_attributes.emplace_back(attrs[i], attrs[i + 1]);
            }
            SPXmlNode *raw = node.get();
            if (parent == nullptr) {
                root = std::move(node);
            } else {
                parent->m_children.push_back(std::move(node));
            }
            return raw;
        }
        static SPXmlNode *parentOf(SPXmlNode *node) { return node->m_parent; }
    };

    namespace {
        struct ParseState {
            std::unique_ptr<SPXmlNode> root;
            SPXmlNode *current = nullptr;
            std::string text;
        };

        bool isBlank(const std::string &value) {
            return std::all_of(value.begin(), value.end(), [](unsigned char c) {
                return c == ' ' || c == '\t' || c == '\r' || c == '\n';
            });
        }

        void flushText(ParseState *state) {
            if (state->current != nullptr && !isBlank(state->text)) {
                SPXmlBuilder::addText(state->current, state->text);
            }
            state->text.clear();
        }

        void XMLCALL onStart(void *data, const XML_Char *name, const XML_Char **attrs) {
            auto *state = static_cast<ParseState *>(data);
            flushText(state);
            state->current = SPXmlBuilder::addElement(state->current, state->root, name, attrs);
        }

        void XMLCALL onEnd(void *data, const XML_Char *) {
            auto *state = static_cast<ParseState *>(data);
            flushText(state);
            state->current = SPXmlBuilder::parentOf(state->current);
        }

        void XMLCALL onText(void *data, const XML_Char *s, int len) {
            auto *state = static_cast<ParseState *>(data);
            if (state->current != nullptr) {
                state->text.append(s, static_cast<size_t>(len));
            }
        }
    }

    std::string SPXmlNode::getAttribute(const std::string &name, const std::string &fallback) const {
        for (const auto &attribute : m_attributes) {
            if (attribute.first == name) {
                return attribute.second;
            }
        }
        return fallback;
    }

    bool SPXmlDocument::loadFile(const std::string &filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            return false;
        }
        std::ostringstream buffer;
        buffer << file.rdbuf();
        return loadString(buffer.str());
    }

    bool SPXmlDocument::loadString(const std::string &data) {
        m_root.reset();
        ParseState state;
        XML_Parser parser = XML_ParserCreate(nullptr);
        if (parser == nullptr) {
            return false;
        }
        XML_SetUserData(parser, &state);
        XML_SetElementHandler(parser, onStart, onEnd);
        XML_SetCharacterDataHandler(parser, onText);
        bool ok = XML_Parse(parser, data.data(), static_cast<int>(data.size()), 1) != XML_STATUS_ERROR;
        XML_ParserFree(parser);
        if (!ok || state.root == nullptr) {
            return false;
        }
        m_root = std::move(state.root);
        return true;
    }
}
