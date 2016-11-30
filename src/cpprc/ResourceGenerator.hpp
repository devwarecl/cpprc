
#ifndef __cpprc_resourcegenerator_hpp__
#define __cpprc_resourcegenerator_hpp__

#include <string>

namespace cpprc {
    struct Resource {
        char* data = nullptr;
        size_t size = 0;

        Resource() {}
        Resource(char* data_, size_t size_) : data(data_), size(size_) {}
    };

    struct CompileUnit {
        std::string header;
        std::string implementation;

        CompileUnit() {}
        CompileUnit(const std::string &header_, const std::string &implementation_)
            : header(header_), implementation(implementation_) {}
    };

    class ResourceGenerator {
    public:
        virtual ~ResourceGenerator();
        virtual CompileUnit generate(const std::string &name, const Resource &resource) = 0;

    protected:
        std::string generateData(const char *data, int size) const;
    };
}

#endif
