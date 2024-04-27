#include <iostream>
#include "ServiceCenter.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    // Create an instance of the ServiceCenter
    ServiceCenter sc;

    // Process the file to load customers into the system
    sc.processFile(filename);

    
   

    std::cout << "All customers have been processed." << std::endl;

    return 0;
}
