
#include "MainResourceGenerator.hpp"

#include <map>
#include <set>
#include <boost/algorithm/string.hpp>

namespace cpprc {
    MainResourceGenerator::MainResourceGenerator() {
        m_sourceTemplate = R"(
#include "${FileName}.hpp"

#include <cpprc/Resource.hpp>
#include <cpprc/ResourceManager.hpp>

using namespace cpprc;

const char s_${Name}_data[] = {${Data}};
const int s_${Name}_size = ${Size};
/*
const bool s_${Name}_temp = ResourceManager::getInstance()->add(
    "${FileName}", 
    std::make_unique<Resource>((const std::uint8_t*)s_${Name}_data, s_${Name}_size)
);
*/
)";

        m_headerTemplate = R"(
#pragma once

#ifndef __${Name}_hpp__
#define __${Name}_hpp__

    extern const char s_${Name}_data[];
    extern const int s_${Name}_size;
    extern const bool s_${Name}_temp;

#endif
)";
    }

    MainResourceGenerator::~MainResourceGenerator() {}

    std::string replaceAll(const std::string &src, std::set<std::string> search, const std::string &value) {
        std::string result = src;

        for (const std::string &key : search) {
            result = boost::replace_all_copy(result, key, value);
        }

        return result;
    }

    CompileUnit MainResourceGenerator::generate(const std::string &name_, const Resource &resource) {
        const std::string fileName = name_;
        const std::string name = replaceAll(name_, {".", "-", "\t", " "}, "_");
        const std::string data = this->generateData(resource.data, (int)resource.size);
        const std::string size = std::to_string(resource.size);

        const std::map<std::string, std::string> properties = {
            {"${FileName}", fileName}, 
            {"${Name}", name}, 
            {"${Data}", data}, 
            {"${Size}", size},
        };

        CompileUnit unit;

        unit.header = m_headerTemplate;
        unit.implementation = m_sourceTemplate;

        for (const auto &pair : properties) {
            boost::replace_all(unit.header, pair.first, pair.second);
            boost::replace_all(unit.implementation, pair.first, pair.second);
        }

        return unit;
    }
}
