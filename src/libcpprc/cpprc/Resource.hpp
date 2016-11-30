
#pragma once 

#ifndef __cpprc_resource_hpp__
#define __cpprc_resource_hpp__

#include <cstdint>
#include <cstddef>

namespace cpprc {
    class Resource {
    public:
        Resource(const std::uint8_t *data, const std::size_t size);

        const std::uint8_t* getData() const;

        const std::size_t getSize() const;

    private:
        const std::uint8_t *m_data = nullptr;;
        const std::size_t m_size;
    };
}

#endif 
