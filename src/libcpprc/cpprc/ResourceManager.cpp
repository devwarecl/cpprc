
#include "ResourceManager.hpp"
#include "Resource.hpp"

#include <map>
#include <memory>
#include <cstring>

#if defined(_DEBUG)
#include <iostream>
#endif 

namespace cpprc {

    class ResourceManagerImpl : public ResourceManager {
    public:
        ResourceManagerImpl() {
#if defined(_DEBUG)
            std::cout << "ResourceManagerImpl::ResourceManagerImpl();" << std::endl;
#endif
        }

        virtual ~ResourceManagerImpl() {}

        virtual Resource* get(const std::string &name) override {
            auto pos = m_resources.find(name);

            if (pos == m_resources.end()) {
                return nullptr;
            } else {
                return pos->second.get();
            }
        }

        virtual std::string getString(const std::string &name) override {
            Resource *resource = this->get(name);

            std::string result;
            result.resize((resource->getSize() + 1));

            std::memcpy((void*)result.c_str(), resource->getData(), result.size());

            result[result.size()] = '\0';

            return result;
        }

        virtual bool add(const std::string &name, std::unique_ptr<Resource> resource)  override {
#if defined(_DEBUG)
            std::cout << "ResourceManagerImpl::add(\"" << name << "\");" << std::endl;
#endif

            m_resources[name] = std::move(resource);

            return true;
        }
        
        virtual std::unique_ptr<Resource> remove(const std::string &name)  override {
            auto resource = std::move(m_resources[name]);

            m_resources.erase(name);

            return resource;
        }
        
        virtual void erase(const std::string &name)  override {
            m_resources.erase(name);
        }    

    private:
        std::map<std::string, std::unique_ptr<Resource>> m_resources;
    };

    ResourceManager* ResourceManager::getInstance() {
        static ResourceManagerImpl manager;

        return &manager;
    }
}
