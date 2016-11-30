
#include "ResourceManager.hpp"
#include "Resource.hpp"

#include <map>
#include <memory>

namespace cpprc {

    class ResourceManagerImpl : public ResourceManager {
    public:
        virtual ~ResourceManagerImpl() {}

        virtual Resource* get(const std::string &name) override {
            auto pos = m_resources.find(name);

            if (pos == m_resources.end()) {
                return nullptr;
            } else {
                return pos->second.get();
            }
        }

        virtual void add(const std::string &name, std::unique_ptr<Resource> resource)  override {
            m_resources[name] = std::move(resource);
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
