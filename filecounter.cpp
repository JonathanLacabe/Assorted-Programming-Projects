#include <string>
#include <iostream>
#include <filesystem>
#include <regex>
using namespace std;

//This program is meant to allow easy file search for numerical filenames,
//finding the number of files before or after a specific number.

int main(){
    int count { };
    int number;
    cout << "Enter filename number: " << endl;
    cin >> number;
    std::filesystem::path p1 { "/* Enter your filepath here! (or uncomment the alt. below)*/" };
    
    //Ossia for those who want to be able to specify the folder filepath in the program:
    /*
    cout << "Enter complete folder filepath: " << endl;
    cin >> p1;
    */
    for (auto& p : std::filesystem::directory_iterator(p1)){
        //Get the filename without extension
        std::string filename = p.path().stem().string();

        //Check if the filename is a number
        if (std::regex_match(filename, std::regex("\\d+"))) {
            //Convert the filename to an integer
            int file_number = std::stoi(filename);

            //Increment count if the filename number is less than or equal to the number submitted by the user.
            if (file_number <= number) {
                ++count;
            }
        }
    }

    std::cout << "# of files in " << p1 << " before " << number << ": " << count << '\n';
}