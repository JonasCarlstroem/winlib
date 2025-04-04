#include <xercesc/util/PlatformUtils.hpp>
#include <filesystem>
#include "validator.h"
#include "generator.h"

using namespace xercesc;
using namespace std::filesystem;

int main(int argc, const char** argv) {
    try {
        XMLPlatformUtils::Initialize();
        init_strings();
    }
    catch (const XMLException& e) {
        return -1;
    }

    path p = path("../../winlib-schema.xsd");
    validator valid;

    DOMDocument* doc = valid.parse_schema(p.string());
    //auto flags = parse_flags(argc, argv);

    generate_mapping_file("include\\comp", "mappings.txt");
    generate_bindings("mappings.txt");
    return 0;
}