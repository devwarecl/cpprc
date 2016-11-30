
#pragma once

#ifndef __cpprc_mainresourcegenerator_hpp__
#define __cpprc_mainresourcegenerator_hpp__

#include "ResourceGenerator.hpp"

namespace cpprc {
    /**
     * @brief Generator that takes advante of the cpprc::ResourceManager class.
     */
    class MainResourceGenerator : public ResourceGenerator {
    public:
        MainResourceGenerator();

        virtual ~MainResourceGenerator();
        virtual CompileUnit generate(const std::string &name, const Resource &resource) override;

    private:
        std::string m_headerTemplate;
        std::string m_sourceTemplate;
    };
}

#endif 
