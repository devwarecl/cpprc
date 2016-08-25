
#include "SimpleResourceGenerator.hpp"

#include <boost/algorithm/string.hpp>

namespace cpprc {
    std::string SimpleResourceGenerator::generateData(const char *data, int size) const {
        std::string dataStr;
        dataStr.reserve(size + 1);
        
        for (int i=0; i<size; ++i) {
            if (i%512 == 0) {
                dataStr += "\n";
            }

            dataStr += std::to_string(static_cast<int>(data[i]));
            dataStr += ", "; 
        }

        return dataStr;
    }

    SimpleResourceGenerator::SimpleResourceGenerator() {
        this->templateHpp += "#ifndef __" + defineKey + "_HPP__\n";
        this->templateHpp += "#define __" + defineKey + "_HPP__\n";
        this->templateHpp += "extern const char " + variableKey + "_data[];\n";
        this->templateHpp += "extern const int " + variableKey + "_size;\n";
        this->templateHpp += "#endif\n";

        this->templateCpp += "#include \"" + headerKey + ".hpp\"\n";
        this->templateCpp += "const char " + variableKey + "_data[] = {" + dataKey + "};\n";
        this->templateCpp += "const int " + variableKey + "_size = " + sizeKey + ";\n";
    }

    SimpleResourceGenerator::~SimpleResourceGenerator() {}

    CompileUnit SimpleResourceGenerator::generate(const std::string &name_, const Resource &resource) {
        std::string name = name_;
        std::string identifierName = name_;
        std::string hpp = this->templateHpp;
        std::string cpp = this->templateCpp;
        
        boost::replace_all(identifierName, ".", "_");

        // generate header
        boost::replace_all(hpp, defineKey, boost::to_upper_copy(identifierName));
        boost::replace_all(hpp, variableKey, boost::to_lower_copy(identifierName));
        
        // generate impl
        boost::replace_all(cpp, headerKey, name);
        boost::replace_all(cpp, variableKey, boost::to_lower_copy(identifierName));
        boost::replace_all(cpp, dataKey, this->generateData(resource.data, resource.size));
        boost::replace_all(cpp, sizeKey, std::to_string(resource.size));

        return CompileUnit(hpp, cpp);
    }
}
