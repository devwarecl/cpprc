
#ifndef __cpprc_simpleresourcegenerator_hpp__
#define __cpprc_simpleresourcegenerator_hpp__

#include "ResourceGenerator.hpp"

namespace cpprc {
    
    class SimpleResourceGenerator : public ResourceGenerator {
    private:
        std::string templateHpp = "";
        std::string templateCpp = "";
    
        const std::string defineKey = "${DEFINE}";
        const std::string headerKey = "${HEADER}";
        const std::string variableKey = "${VARIABLE}";
        const std::string dataKey = "${DATA}";
        const std::string sizeKey = "${SIZE}";
        
    public:
        SimpleResourceGenerator();

        virtual ~SimpleResourceGenerator();

        virtual CompileUnit generate(const std::string &name_, const Resource &resource) override;
    };
}

#endif
