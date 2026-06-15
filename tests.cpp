#include "ciphers.h"
#include <iostream>
#include <string>

void test(std::string name, bool ok) {
    if (ok) {
        std::cout << "[PASS] " << name << std::endl;
    } else {
        std::cout << "[FAIL] " << name << std::endl;
    }
}


void test_affine_ok() {
    try {
        std::string text = "Hello";
        int a = 3;
        int b = 5;
        
        std::string enc = cipherAffineEncrypt(text, a, b);
        std::string dec = cipherAffineDecrypt(enc, a, b);
        
        test("Affine encrypt+decrypt", text == dec);
    } catch (std::exception& e) {
        test("Affine encrypt+decrypt", false);
    }
}

void test_affine_bad_a() {
    try {
        std::string text = "Hello";
        int a = 2;
        int b = 5;
        
        std::string enc = cipherAffineEncrypt(text, a, b);
        test("Affine bad a", false);
    } catch (std::invalid_argument& e) {
        test("Affine bad a", true);
    } catch (...) {
        test("Affine bad a", false);
    }
}


void test_recurrent_ok() {
    try {
        std::string text = "Hello";
        int a1 = 3, b1 = 5;
        int a2 = 7, b2 = 11;
        
        std::string enc = cipherAffineRecurrentEncrypt(text, a1, b1, a2, b2);
        std::string dec = cipherAffineRecurrentDecrypt(enc, a1, b1, a2, b2);
        
        test("Recurrent encrypt+decrypt", text == dec);
    } catch (std::exception& e) {
        test("Recurrent encrypt+decrypt", false);
    }
}

void test_recurrent_short() {
    try {
        std::string text = "A";
        
        std::string enc = cipherAffineRecurrentEncrypt(text, 3, 5, 7, 11);
        test("Recurrent short text", false);
    } catch (std::invalid_argument& e) {
        test("Recurrent short text", true);
    } catch (...) {
        test("Recurrent short text", false);
    }
}


void test_vigenere_key_ok() {
    try {
        std::string text = "Hello";
        std::string key = "key";
        
        std::string enc = cipherVigenereKeyEncrypt(text, key);
        std::string dec = cipherVigenereKeyDecrypt(enc, key);
        
        test("VigenereKey encrypt+decrypt", text == dec);
    } catch (std::exception& e) {
        test("VigenereKey encrypt+decrypt", false);
    }
}

void test_vigenere_key_empty() {
    try {
        std::string text = "Hello";
        std::string key = "";
        
        std::string enc = cipherVigenereKeyEncrypt(text, key);
        test("VigenereKey empty key", false);
    } catch (std::invalid_argument& e) {
        test("VigenereKey empty key", true);
    } catch (...) {
        test("VigenereKey empty key", false);
    }
}


void test_vigenere_cipher_ok() {
    try {
        std::string text = "Hello";
        std::string key = "key";
        
        std::string enc = cipherVigenereCipherEncrypt(text, key);
        std::string dec = cipherVigenereCipherDecrypt(enc, key);
        
        test("VigenereCipher encrypt+decrypt", text == dec);
    } catch (std::exception& e) {
        test("VigenereCipher encrypt+decrypt", false);
    }
}

void test_vigenere_cipher_empty() {
    try {
        std::string text = "Hello";
        std::string key = "";
        
        std::string enc = cipherVigenereCipherEncrypt(text, key);
        test("VigenereCipher empty key", false);
    } catch (std::invalid_argument& e) {
        test("VigenereCipher empty key", true);
    } catch (...) {
        test("VigenereCipher empty key", false);
    }
}

int main() {
    
    test_affine_ok();
    test_affine_bad_a();
    
    test_recurrent_ok();
    test_recurrent_short();
    
    test_vigenere_key_ok();
    test_vigenere_key_empty();
    
    test_vigenere_cipher_ok();
    test_vigenere_cipher_empty();
    
    return 0;
}