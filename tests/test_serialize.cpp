#include <iostream>
#include <fstream>

#include "serializer/serializer.h"

using namespace std;

int main() {
    Serializer serializer;
    string data = serializer.LoadRawData("resources/test_data/sample_data.in");
    Decoder::Node* node = serializer.LoadData(data);
    
    cout << "INCOMPLETE TEST" << endl;
}
