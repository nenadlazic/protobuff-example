//protobuf_sample.cc
#include <iostream>
#include <fstream>
#include <iomanip>

#include "projectmanagement.pb.h"

using namespace std;

/**
 * Prints the given byte array as hexadecimal values.
*/
void printByteArray(const uint8_t* data, int size) {
    for (int i = 0; i < size; ++i) {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(data[i]) << " ";
    }
    cout << endl;
}

/**
 * Writes the serialized data to a binary file.
*/
void writeSerializedDataToFile(const uint8_t* serialized_data, int serialized_size) {
    // Open a file for writing in binary mode
    ofstream outFile("serialized_data.bin", ios::binary);
    if (!outFile.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return;
    }

    // Write the serialized data to the file
    outFile.write(reinterpret_cast<const char*>(serialized_data), serialized_size);

    // Close the file
    outFile.close();
}

/**
* Reads the content of a binary file into a dynamically allocated byte array.
*/
std::size_t readFileToByteArray(const std::string& filename, uint8_t** byteArray) {
    std::ifstream inFile(filename, std::ios::binary | std::ios::ate);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return 0;
    }
    
    std::size_t fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    *byteArray = new uint8_t[fileSize];
    inFile.read(reinterpret_cast<char*>(*byteArray), fileSize);
    inFile.close();

    return fileSize;
}

void printProjectInfo(const projectmanagement::Project& project) {
    cout << "Project: " << project.title() << endl;
    cout << "URL: " << project.url() << endl;
    
    cout << "Developers:" << endl;
    for (int i = 0; i < project.developer_size(); ++i) {
        const projectmanagement::Developer& developer = project.developer(i);
        cout << "Developer " << i + 1 << ":" << endl;
        cout << "  First name: " << developer.first_name() << endl;
        cout << "  Last name: " << developer.last_name() << endl;
        cout << "  Email: " << developer.email() << endl;
    }
}

int main()
{
    // Use protobuff msg object to set data
    projectmanagement::Project project;
    project.set_title("Sample");
    project.set_url("http://www.sample.com");
 
    projectmanagement::Developer *developer1 = project.add_developer();
    developer1->set_first_name("ABC");
    developer1->set_last_name("XYZ");
    developer1->set_email("abc.xyz@example.com");

    projectmanagement::Developer *developer2 = project.add_developer();
    developer2->set_first_name("DEF");
    developer2->set_last_name("GHI");
    developer2->set_email("def.ghi@example.com");

    // Print msg data before serialization
    cout << "############################ Before serialization ##############################"<<endl;
    printProjectInfo(project);
    cout << "################################################################################"<<endl << endl;

    // Serialize the project message to a byte array
    int serialized_size = project.ByteSizeLong();
    uint8_t serialized_data[serialized_size];
    project.SerializeToArray(serialized_data, serialized_size);


    // Print serialized values
    cout << "########################## Serialized Data (Hex) - write #######################"<<endl;
    printByteArray(serialized_data, serialized_size);
    cout << "################################################################################"<<endl << endl;

    // Open a file for writing in binary mode
    writeSerializedDataToFile(serialized_data, serialized_size);

    //Read from file
    uint8_t* serialized_data_read = nullptr;
    std::size_t serialized_size_read = readFileToByteArray("serialized_data.bin", &serialized_data_read);

    // Print serialized values from file
    cout << "######################### Serialized Data (Hex) - read ########################"<<endl;
    printByteArray(serialized_data_read, serialized_size_read);
    cout << "###############################################################################"<<endl << endl;


    projectmanagement::Project project_deserialization;
    // Deserialize the data from the byte array into the Person message
    if (!project_deserialization.ParseFromArray(serialized_data_read, serialized_size_read)) {
        std::cerr << "Failed to parse data into Project message." << std::endl;
        return 1;
    }

    // Print msg data after deserialization
    cout << "######################### After deserialization ################################"<<endl;
    printProjectInfo(project_deserialization);
    cout << "################################################################################"<<endl;

    return 0;
}
