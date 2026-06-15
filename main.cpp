#include "ciphers.h"
#include <iostream>
#include <string>

void showMenu() {
    std::cout << "1 - Simple substitution cipher\n";
    std::cout << "2 - Affine cipher\n";
    std::cout << "3 - Affine recurrent cipher\n";
    std::cout << "4 - Vigenere cipher (key mode)\n";
    std::cout << "5 - Vigenere cipher (open text mode)\n";
    std::cout << "6 - Vigenere cipher (cipher text mode)\n";
    std::cout << "0 - Exit\n";
    std::cout << "Choose cipher: ";
}

int main() {
    system("chcp 65001 > nul");  
    std::string line;
    
    while (true) {
        showMenu();
        
        std::getline(std::cin, line);
        int choice = std::stoi(line);
        
        if (choice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }
        
        std::cout << "Enter text: ";
        std::getline(std::cin, line);
        std::string text = line;
        
        std::string result;
        
        if (choice == 1) {
            std::cout << "Enter key (256 characters): ";
            std::getline(std::cin, line);
            std::string key = line;
            
            std::cout << "1 - encrypt, 2 - decrypt: ";
            std::getline(std::cin, line);
            int mode = std::stoi(line);
            
            if (mode == 1) {
                result = cipherSimpleEncrypt(text, key);
            } else {
                result = cipherSimpleDecrypt(text, key);
            }
        }
        else if (choice == 2) {
            std::cout << "Enter a: ";
            std::getline(std::cin, line);
            int a = std::stoi(line);
            
            std::cout << "Enter b: ";
            std::getline(std::cin, line);
            int b = std::stoi(line);
            
            std::cout << "1 - encrypt, 2 - decrypt: ";
            std::getline(std::cin, line);
            int mode = std::stoi(line);
            
            if (mode == 1) {
                result = cipherAffineEncrypt(text, a, b);
            } else {
                result = cipherAffineDecrypt(text, a, b);
            }
        }
        else if (choice == 3) {
            std::cout << "Enter a1: ";
            std::getline(std::cin, line);
            int a1 = std::stoi(line);
            
            std::cout << "Enter b1: ";
            std::getline(std::cin, line);
            int b1 = std::stoi(line);
            
            std::cout << "Enter a2: ";
            std::getline(std::cin, line);
            int a2 = std::stoi(line);
            
            std::cout << "Enter b2: ";
            std::getline(std::cin, line);
            int b2 = std::stoi(line);
            
            std::cout << "1 - encrypt, 2 - decrypt: ";
            std::getline(std::cin, line);
            int mode = std::stoi(line);
            
            if (mode == 1) {
                result = cipherAffineRecurrentEncrypt(text, a1, b1, a2, b2);
            } else {
                result = cipherAffineRecurrentDecrypt(text, a1, b1, a2, b2);
            }
        }
        else if (choice == 4) {
            std::cout << "Enter key: ";
            std::getline(std::cin, line);
            std::string key = line;
            
            std::cout << "1 - encrypt, 2 - decrypt: ";
            std::getline(std::cin, line);
            int mode = std::stoi(line);
            
            if (mode == 1) {
                result = cipherVigenereKeyEncrypt(text, key);
            } else {
                result = cipherVigenereKeyDecrypt(text, key);
            }
        }
        else if (choice == 5) {
            std::cout << "Enter key: ";
            std::getline(std::cin, line);
            std::string key = line;
            
            std::cout << "1 - encrypt, 2 - decrypt: ";
            std::getline(std::cin, line);
            int mode = std::stoi(line);
            
            if (mode == 1) {
                result = cipherVigenereOpenEncrypt(text, key);
            } else {
                result = cipherVigenereOpenDecrypt(text, key);
            }
        }
        else if (choice == 6) {
            std::cout << "Enter key: ";
            std::getline(std::cin, line);
            std::string key = line;
            
            std::cout << "1 - encrypt, 2 - decrypt: ";
            std::getline(std::cin, line);
            int mode = std::stoi(line);
            
            if (mode == 1) {
                result = cipherVigenereCipherEncrypt(text, key);
            } else {
                result = cipherVigenereCipherDecrypt(text, key);
            }
        }
        else {
            std::cout << "Error: invalid choice!\n";
            continue;
        }
        
        if (result.empty()) {
            std::cout << "Error: invalid parameters or key!\n";
        } else {
            std::cout << "\nResult: " << result << "\n";
        }
        
        std::cout << "\n";
    }
    
    return 0;
}