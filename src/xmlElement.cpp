#include "xmlElement.hpp"

petscXdmfGenerator::XmlElement::XmlElement(std::string name, std::string preamble, std::string currentPath) : name(name), preamble(preamble), path(currentPath + "/" + name) {}

namespace petscXdmfGenerator {
std::ostream& operator<<(std::ostream& os, const petscXdmfGenerator::XmlElement& object) {
    os << object.preamble;
    os << "<" << object.name;
    for (const auto& attribute : object.attributes) {
        os << " " << attribute.first << "=\"" << attribute.second << "\"";
    }
    os << ">";
    os << object.value;
    for (const auto& element : object.elements) {
        os << *(element);
    }
    os << "</" << object.name << ">";

    return os;
}
}  // namespace petscXdmfGenerator

petscXdmfGenerator::XmlElement& petscXdmfGenerator::XmlElement::operator[](const std::string&& name) {
    elements.push_back(std::make_unique<XmlElement>(name, "", path));
    return *elements[elements.size() - 1];
}

petscXdmfGenerator::XmlElement& petscXdmfGenerator::XmlElement::operator[](const size_t&& index) { return *elements[index]; }

std::string& petscXdmfGenerator::XmlElement::operator()(const std::string&& name) { return attributes[name]; }

std::string& petscXdmfGenerator::XmlElement::operator()() { return value; }

void petscXdmfGenerator::XmlElement::PrettyPrint(std::ostream& stream, size_t depth) {
    const auto t = std::string(2, ' ');
    const auto d = std::string(depth * 2, ' ');

    if (preamble.size() > 0) {
        stream << d << preamble;
    }
    stream << std::endl << d << "<" << name;
    for (const auto& attribute : attributes) {
        stream << " " << attribute.first << "=\"" << attribute.second << "\"";
    }
    stream << ">";

    if (!value.empty()) {
        stream << std::endl << d << t << value;
    }
    for (const auto& element : elements) {
        element->PrettyPrint(stream, depth + 1);
    }

    stream << std::endl << d << "</" << name << ">";
}
