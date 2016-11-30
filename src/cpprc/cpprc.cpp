
/**
 * @file file2cpp
 * @author Felipe Apablaza
 *
 * Generate a compilation unit with the binary data of the specified file. 
 * Allows the embedding of any file (binary or text) inside a C++ program.
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "SimpleResourceGenerator.hpp"
#include "MainResourceGenerator.hpp"

int main(int argc, char **argv) 
{
    namespace fs = boost::filesystem;
    namespace po = boost::program_options;

    try {
        po::options_description desc("Allowed options");

        // Program options
        po::positional_options_description positional;
        positional.add("input", -1);

        desc.add_options()
            ("help,h", "Produce help message")
            ("input", po::value<fs::path>()->required(),  "Input ASCII or binary file")
            ("output-path,o", po::value<fs::path>(),  "Output path (defaults to current path)")
            ("style,s", po::value<std::string>(), "Generator style (raw[default], cpprc)");
            
        po::variables_map vm;

        try {
            // Parse command line
            po::store(po::command_line_parser(argc, argv).options(desc).positional(positional).run(), vm);
            po::notify(vm);

            // Handle help display
            if (vm.count("help")) {
                std::cout << desc << std::endl;
                return 1;
            }

            // Further parameter validation
            fs::path inputFile = vm["input"].as<fs::path>();
            if (!fs::exists(inputFile)) {
                throw std::runtime_error("The file '" + inputFile.string() + "' doesn't exist.");
            }

            if (fs::is_directory(inputFile)) {
                throw std::runtime_error("'" + inputFile.string() + "' must be a file, not a directory.");
            }

            // Process output directory parameter
            fs::path outputPath;
            if (vm.count("output-path")) {
                outputPath =  vm["output-path"].as<fs::path>();
            } else {
                outputPath = fs::current_path();
            }

            // Output parameter validation
            if (!fs::exists(outputPath) || fs::is_regular_file(outputPath)) {
                throw std::runtime_error("The output path '" + outputPath.parent_path().string() + "' is invalid.");
            }

            // Process style resource compile unit generator
            std::unique_ptr<cpprc::ResourceGenerator> generator;

            std::string style = vm["style"].as<std::string>();

            if (style == "") {
                style = "raw";
            }

            if (style!="raw" && style!="cpprc") {
                throw std::runtime_error("The specified generator style '" + style + "' isn't valid.");
            }

            if (style == "raw") {
                generator = std::make_unique<cpprc::SimpleResourceGenerator>();
            } else if (style == "cpprc") {
                generator = std::make_unique<cpprc::MainResourceGenerator>();
            }

            // Open the file an try to get its data
            std::fstream fileHandle;
            fileHandle.open(inputFile.string().c_str(), std::ios_base::in | std::ios_base::binary);
            if (!fileHandle.is_open()) {
                throw std::runtime_error("The file '" + inputFile.string() + "' couldn't be opened.");
            }
            
            // Load the file data
            std::vector<char> fileData;
            fileData.resize(static_cast<unsigned int>(fs::file_size(inputFile)));
            fileHandle.read(fileData.data(), fileData.size());

            // Generate the compile unit
            std::string name = inputFile.filename().string();
            cpprc::Resource resource(fileData.data(), fileData.size());

            cpprc::CompileUnit unit = generator->generate(name, resource);

            // Finally, store the data
            fs::path parentPath = outputPath;
            fs::path headerFile = parentPath / (name + ".hpp");
            fs::path implFile = parentPath / (name + ".cpp");

            std::fstream headerHandle;
            headerHandle.open(headerFile.string(), std::ios_base::out);
            if (!headerHandle.is_open()) {
                throw std::runtime_error("The header file '" + headerFile.string() + "' couldn't be opened for write access");
            }

            headerHandle << unit.header;
            headerHandle.flush();

            std::fstream implHandle;
            implHandle.open(implFile.string(), std::ios_base::out);
            if (!implHandle.is_open()) {
                throw std::runtime_error("The source file '" + implFile.string() + "' couldn't be opened for write access");
            }

            implHandle << unit.implementation;
            implHandle.flush();

            return 0;
        } catch (po::error &exp) {
            std::cout << "Error: " << exp.what() << std::endl;
            std::cout << desc << std::endl;

            return 1;
        } catch (std::runtime_error &exp) {
            std::cout << "Runtime Error: " << exp.what() << std::endl;

            return 2;
        }
    } catch (std::exception &exp) {
        std::cout << "Application unhandled exception: " << std::endl;
        std::cout << exp.what() << std::endl;

        return -1;
    }
}
