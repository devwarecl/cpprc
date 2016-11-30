
#include "Resource.hpp"

namespace cpprc {

    Resource::Resource(const std::uint8_t *data, const std::size_t size)
        : m_data(data), m_size(size) {
    }

    const std::uint8_t* Resource::getData() const {
        return m_data;
    }

    const std::size_t Resource::getSize() const {
        return m_size;
    }
}
