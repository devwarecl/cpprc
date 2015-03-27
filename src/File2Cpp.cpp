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
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

struct Resource {
	char* data = nullptr;
	int size = 0;

	Resource() {}
	Resource(char* data_, int size_) : data(data_), size(size_) {}
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
	virtual ~ResourceGenerator() {}
	virtual CompileUnit generate(const std::string &name, const Resource &resource) = 0;
};

class SimpleResourceGenerator : public ResourceGenerator {
private:
	std::string templateHpp = "";
	std::string templateCpp = "";
	
	const std::string defineKey = "${DEFINE}";
	const std::string headerKey = "${HEADER}";
	const std::string variableKey = "${VARIABLE}";
	const std::string dataKey = "${DATA}";
	const std::string sizeKey = "${SIZE}";
	
private:
	std::string generateData(const char *data, int size) const {
		std::string dataStr;
		dataStr.reserve(size + 1);
		
		for (int i=0; i<size; ++i) {
			if (i%512 == 0) {
				dataStr += "\n";
			}

			dataStr += std::to_string(static_cast<int>(data[i]));
			dataStr += ", "; 
		}

		return dataStr;
	}

public:
	SimpleResourceGenerator() {
		this->templateHpp += "#ifndef __" + defineKey + "_HPP__\n";
		this->templateHpp += "#define __" + defineKey + "_HPP__\n";
		this->templateHpp += "extern const char " + variableKey + "_data[];\n";
		this->templateHpp += "extern const int " + variableKey + "_size;\n";
		this->templateHpp += "#endif\n";

		this->templateCpp += "#include \"" + headerKey + ".hpp\"\n";
		this->templateCpp += "const char " + variableKey + "_data[] = {" + dataKey + "};\n";
		this->templateCpp += "const int " + variableKey + "_size = " + sizeKey + ";\n";
	}

	virtual ~SimpleResourceGenerator() {}

	virtual CompileUnit generate(const std::string &name, const Resource &resource) override {
		std::string hpp = this->templateHpp;
		std::string cpp = this->templateCpp;
		
		// generate header
		boost::replace_all(hpp, defineKey, boost::to_upper_copy(name));
		boost::replace_all(hpp, variableKey, boost::to_lower_copy(name));
			
		// generate impl
		boost::replace_all(cpp, headerKey, name);
		boost::replace_all(cpp, variableKey, boost::to_lower_copy(name));
		boost::replace_all(cpp, dataKey, this->generateData(resource.data, resource.size));
		boost::replace_all(cpp, sizeKey, std::to_string(resource.size));

		return CompileUnit(hpp, cpp);
	}
};

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
			("output-path,o", po::value<fs::path>(),  "Output path (defaults to current path)");
			
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
			std::string name = inputFile.stem().string();
			Resource resource(fileData.data(), fileData.size());
			SimpleResourceGenerator generator;

			CompileUnit unit = generator.generate(name, resource);

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
