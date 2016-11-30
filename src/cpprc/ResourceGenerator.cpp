
#include "ResourceGenerator.hpp"

namespace cpprc {
    ResourceGenerator::~ResourceGenerator() {}

    std::string ResourceGenerator::generateData(const char *data, int size) const {
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

}
