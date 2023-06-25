#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <array>

int SPEED = INT8_MAX*4; // up to INT32_MAX

void readLetters(std::ifstream& f, std::unordered_map<char, std::array<std::string, 11>>& alphabet, int iter, char offset){
    for(int i = 0; i < iter; ++i){
        std::array<std::string, 11> letter;
        for(int j = 0; j < 11; ++j)
            std::getline(f, letter[j], '\n');
        alphabet[i+offset] = letter;
    }
}

void print(std::array<std::string, 11>& result, int offset){
    for(int i = 0; i < result[0].size()+4; ++i)
        std::cout << "#";
    std::cout << std::endl;

    for(int i = 0; i < 11; ++i)
        std::cout << "# " << result[i].substr(offset, result[i].size() - offset) << result[i].substr(0, offset) << " #" << std::endl;

    for(int i = 0; i < result[0].size()+4; ++i)
        std::cout << "#";
    offset = (offset + 1)%result[0].size();
}

int main(){
    std::ifstream f("letters.txt");
    std::unordered_map<char, std::array<std::string, 11>> alphabet;

    readLetters(f, alphabet, 26, 'a');
    readLetters(f, alphabet, 10, '0');
    readLetters(f, alphabet, 1, ' ');

    std::string input;
    std::cout << "Enter your text: ";
    std::getline (std::cin, input);
    input += "  ";

    std::array<std::string, 11> result;
    for(int i = 0; i < 11; ++i){
        for(char& c: input){
            if (c > 'A' and c < 'Z') 
                c += 'a' - 'A';
            if(alphabet.find(c) == alphabet.end()){
                std::cout << "Input contains forbidden characters";
                exit(1);
            }
            result[i] += alphabet[c][i];
        }
    }

    int iterations = 0;
    int offset = 0;
    while(1){
        if(iterations < INT32_MAX/SPEED){
            iterations++;
            continue;
        }

        iterations = 0;
        system("cls");
        print(result, offset);
        offset = (offset + 1)%result[0].size();
    }
}