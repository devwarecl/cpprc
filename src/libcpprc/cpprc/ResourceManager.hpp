
#pragma once 

#ifndef __cpprc_resourcemanager_hpp__
#define __cpprc_resourcemanager_hpp__

#include <string>
#include <memory>

namespace cpprc {
    class Resource;

    class ResourceManager {
    public:
        virtual ~ResourceManager() {}

        virtual Resource* get(const std::string &name) = 0;

        virtual std::string getString(const std::string &name) = 0;

        virtual bool add(const std::string &name, std::unique_ptr<Resource> resource) = 0;
        
        virtual std::unique_ptr<Resource> remove(const std::string &name) = 0;
        
        virtual void erase(const std::string &name) = 0;

    public:
        static cpprc::ResourceManager* getInstance();
    };
}

#endif 
