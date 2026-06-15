#include "ciphers.h"
#include <algorithm>
#include <stdexcept>

const int SIZE = 256;

bool isCoprime(int x, int y) {
    for (int i = 2; i < std::min(x, y); i++) {
        if (x % i == 0 and y % i == 0) {
            return false;
        }
    }
    return true;
}

int findInverse(int num, int mod) {
    for (int i = 0; i < mod; i++) {
        if ((num * i) % mod == 1) {
            return i;
        }
    }
    return -1;
}

std::vector<int> textToBytes(std::string text) {
    std::vector<int> bytes;
    bytes.resize(text.size());
    for (int i = 0; i < (int)text.size(); i++) {
        bytes[i] = (int)text[i];
    }
    return bytes;
}

std::string bytesToText(std::vector<int> bytes) {
    std::string result;
    result.resize(bytes.size());
    for (int i = 0; i < (int)bytes.size(); i++) {
        result[i] = (char)bytes[i];
    }
    return result;
}

std::string cipherSimpleEncrypt(std::string text, std::string keyString) {
    std::vector<int> data = textToBytes(text);
    std::vector<int> key = textToBytes(keyString);
    
    if (key.size() != SIZE) {
        throw std::invalid_argument("Key must be exactly 256 characters");
    }
    
    std::vector<int> result;
    result.resize(data.size());
    
    for (int i = 0; i < (int)data.size(); i++) {
        int original = data[i];
        int encrypted = key[original];
        result[i] = encrypted;
    }
    
    return bytesToText(result);
}

std::string cipherSimpleDecrypt(std::string text, std::string keyString) {
    std::vector<int> data = textToBytes(text);
    std::vector<int> key = textToBytes(keyString);
    
    if (key.size() != SIZE) {
        throw std::invalid_argument("Key must be exactly 256 characters");
    }
    
    std::vector<int> reverseKey;
    reverseKey.resize(SIZE);
    
    for (int i = 0; i < SIZE; i++) {
        reverseKey[key[i]] = i;
    }
    
    std::vector<int> result;
    result.resize(data.size());
    
    for (int i = 0; i < (int)data.size(); i++) {
        int encrypted = data[i];
        int original = reverseKey[encrypted];
        result[i] = original;
    }
    
    return bytesToText(result);
}

std::string cipherAffineEncrypt(std::string text, int a, int b) {
    if (isCoprime(a, SIZE) == false) {
        throw std::invalid_argument("Parameter 'a' must be coprime with 256");
    }
    
    std::vector<int> data = textToBytes(text);
    std::vector<int> result;
    result.resize(data.size());
    
    for (int i = 0; i < (int)data.size(); i++) {
        int x = data[i];
        int y = (a * x + b) % SIZE;
        result[i] = y;
    }
    
    return bytesToText(result);
}

std::string cipherAffineDecrypt(std::string text, int a, int b) {
    if (isCoprime(a, SIZE) == false) {
        throw std::invalid_argument("Parameter 'a' must be coprime with 256");
    }
    
    int aInv = findInverse(a, SIZE);
    if (aInv == -1) {
        throw std::runtime_error("Failed to find modular inverse");
    }
    
    std::vector<int> data = textToBytes(text);
    std::vector<int> result;
    result.resize(data.size());
    
    for (int i = 0; i < (int)data.size(); i++) {
        int y = data[i];
        
        int step1 = y - b;
        if (step1 < 0) {
            step1 = step1 + SIZE;
        }
        
        int step2 = aInv * step1;
        int x = step2 % SIZE;
        
        result[i] = x;
    }
    
    return bytesToText(result);
}

std::string cipherAffineRecurrentEncrypt(std::string text, int a1, int b1, int a2, int b2) {
    if (isCoprime(a1, SIZE) == false) {
        throw std::invalid_argument("a1 must be coprime with 256");
    }
    if (isCoprime(a2, SIZE) == false) {
        throw std::invalid_argument("a2 must be coprime with 256");
    }
    
    std::vector<int> data = textToBytes(text);
    if (data.size() < 2) {
        throw std::invalid_argument("Text must be at least 2 characters");
    }
    
    std::vector<int> A;
    std::vector<int> B;
    A.push_back(a1);
    A.push_back(a2);
    B.push_back(b1);
    B.push_back(b2);
    
    std::vector<int> result;
    result.resize(data.size());
    
    int x0 = data[0];
    int y0 = (A[0] * x0 + B[0]) % SIZE;
    result[0] = y0;
    
    int x1 = data[1];
    int y1 = (A[1] * x1 + B[1]) % SIZE;
    result[1] = y1;
    
    for (int i = 2; i < (int)data.size(); i++) {
        int newA = (A[i-1] * A[i-2]) % SIZE;
        
        if (isCoprime(newA, SIZE) == false) {
            throw std::runtime_error("Generated coefficient not coprime");
        }
        
        A.push_back(newA);
        
        int newB = (B[i-1] + B[i-2]) % SIZE;
        B.push_back(newB);
        
        int xi = data[i];
        int yi = (A[i] * xi + B[i]) % SIZE;
        result[i] = yi;
    }
    
    return bytesToText(result);
}

std::string cipherAffineRecurrentDecrypt(std::string text, int a1, int b1, int a2, int b2) {
    if (isCoprime(a1, SIZE) == false) {
        throw std::invalid_argument("a1 must be coprime with 256");
    }
    if (isCoprime(a2, SIZE) == false) {
        throw std::invalid_argument("a2 must be coprime with 256");
    }
    
    std::vector<int> data = textToBytes(text);
    if (data.size() < 2) {
        throw std::invalid_argument("Text must be at least 2 characters");
    }
    
    std::vector<int> A;
    std::vector<int> B;
    A.push_back(a1);
    A.push_back(a2);
    B.push_back(b1);
    B.push_back(b2);
    
    int aInv1 = findInverse(A[0], SIZE);
    int aInv2 = findInverse(A[1], SIZE);
    
    if (aInv1 == -1 or aInv2 == -1) {
        throw std::runtime_error("Failed to find modular inverse");
    }
    
    std::vector<int> result;
    result.resize(data.size());
    
    int y0 = data[0];
    int step0 = y0 - B[0];
    if (step0 < 0) step0 = step0 + SIZE;
    int x0 = (aInv1 * step0) % SIZE;
    result[0] = x0;
    
    int y1 = data[1];
    int step1 = y1 - B[1];
    if (step1 < 0) step1 = step1 + SIZE;
    int x1 = (aInv2 * step1) % SIZE;
    result[1] = x1;
    
    for (int i = 2; i < (int)data.size(); i++) {
        int newA = (A[i-1] * A[i-2]) % SIZE;
        
        if (isCoprime(newA, SIZE) == false) {
            throw std::runtime_error("Generated coefficient not coprime");
        }
        
        A.push_back(newA);
        
        int newB = (B[i-1] + B[i-2]) % SIZE;
        B.push_back(newB);
        
        int aInv = findInverse(A[i], SIZE);
        
        if (aInv == -1) {
            throw std::runtime_error("Failed to find modular inverse");
        }
        
        int yi = data[i];
        int step = yi - B[i];
        if (step < 0) step = step + SIZE;
        int xi = (aInv * step) % SIZE;
        result[i] = xi;
    }
    
    return bytesToText(result);
}

std::string cipherVigenereKeyEncrypt(std::string text, std::string keyString) {
    std::vector<int> data = textToBytes(text);
    std::vector<int> key = textToBytes(keyString);
    
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    std::vector<int> result;
    result.resize(data.size());
    
    int keyLen = key.size();
    
    for (int i = 0; i < (int)data.size(); i++) {
        int d = data[i];
        int k = key[i % keyLen];
        int e = (d + k) % SIZE;
        result[i] = e;
    }
    
    return bytesToText(result);
}

std::string cipherVigenereKeyDecrypt(std::string text, std::string keyString) {
    std::vector<int> data = textToBytes(text);
    std::vector<int> key = textToBytes(keyString);
    
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    std::vector<int> result;
    result.resize(data.size());
    
    int keyLen = key.size();
    
    for (int i = 0; i < (int)data.size(); i++) {
        int e = data[i];
        int k = key[i % keyLen];
        int d = e - k;
        
        if (d < 0) {
            d = d + SIZE;
        }
        
        result[i] = d;
    }
    
    return bytesToText(result);
}

std::string cipherVigenereOpenEncrypt(std::string text, std::string keyString) {
    std::vector<int> data = textToBytes(text);
    std::vector<int> key = textToBytes(keyString);
    
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    std::vector<int> result;
    result.resize(data.size());
    
    for (int i = 0; i < (int)data.size(); i++) {
        int gamma;
        
        if (i == 0) {
            gamma = key[0];
        } else {
            gamma = data[i - 1];
        }
        
        int d = data[i];
        int e = (d + gamma) % SIZE;
        result[i] = e;
    }
    
    return bytesToText(result);
}

std::string cipherVigenereOpenDecrypt(std::string text, std::string keyString) {
    std::vector<int> data = textToBytes(text);
    std::vector<int> key = textToBytes(keyString);
    
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    std::vector<int> result;
    result.resize(data.size());
    
    for (int i = 0; i < (int)data.size(); i++) {
        int gamma;
        
        if (i == 0) {
            gamma = key[0];
        } else {
            gamma = result[i - 1];
        }
        
        int e = data[i];
        int d = e - gamma;
        
        if (d < 0) {
            d = d + SIZE;
        }
        
        result[i] = d;
    }
    
    return bytesToText(result);
}

std::string cipherVigenereCipherEncrypt(std::string text, std::string keyString) {
    std::vector<int> data = textToBytes(text);
    std::vector<int> key = textToBytes(keyString);
    
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    std::vector<int> result;
    result.resize(data.size());
    
    for (int i = 0; i < (int)data.size(); i++) {
        int gamma;
        
        if (i == 0) {
            gamma = key[0];
        } else {
            gamma = result[i - 1];
        }
        
        int d = data[i];
        int e = (d + gamma) % SIZE;
        result[i] = e;
    }
    
    return bytesToText(result);
}

std::string cipherVigenereCipherDecrypt(std::string text, std::string keyString) {
    std::vector<int> data = textToBytes(text);
    std::vector<int> key = textToBytes(keyString);
    
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    std::vector<int> result;
    result.resize(data.size());
    
    for (int i = 0; i < (int)data.size(); i++) {
        int gamma;
        
        if (i == 0) {
            gamma = key[0];
        } else {
            gamma = data[i - 1];
        }
        
        int e = data[i];
        int d = e - gamma;
        
        if (d < 0) {
            d = d + SIZE;
        }
        
        result[i] = d;
    }
    
    return bytesToText(result);
}