#include "ciphers.h"
#include <fstream>
#include <iostream>
#include <string>

std::string fixPath(std::string path) {
  for (int i = 0; i < (int)path.size(); i++) {
    if (path[i] == '\\') {
      path[i] = '/';
    }
  }
  return path;
}

std::string read(std::string path) {
  std::ifstream file(path, std::ios::binary);
  if (!file)
    throw std::runtime_error("cannot open: " + path);

  std::string result;
  char ch;
  while (file.get(ch)) {
    result = result + ch;
  }
  return result;
}

void write(std::string path, std::string data) {
  std::ofstream file(path, std::ios::binary);
  if (!file)
    throw std::runtime_error("cannot create: " + path);

  for (int i = 0; i < (int)data.size(); i++) {
    file.put(data[i]);
  }
}

void showMenu() {
  std::cout << "1 - Simple cipher\n";
  std::cout << "2 - Affine cipher\n";
  std::cout << "3 - Recurrent affine cipher\n";
  std::cout << "4 - Key vigenere cipher\n";
  std::cout << "5 - Open vigenere cipher\n";
  std::cout << "6 - Cipher vigenere cipher\n";
  std::cout << "0 - Exit\n";
}

int main() {
  while (true) {
    showMenu();

    int type;
    std::cout << "Choose: ";
    std::cin >> type;

    if (type == 0)
      break;
    if (type < 1 or type > 6) {
      std::cout << "Bad choice\n";
      continue;
    }

    std::string in, out;
    std::cout << "Input file: ";
    std::cin >> in;
    std::cout << "Output file: ";
    std::cin >> out;

    int mode;
    std::cout << "1=encrypt 2=decrypt: ";
    std::cin >> mode;

    bool enc;
    if (mode == 1) {
      enc = true;
    } else {
      enc = false;
    }

    try {
      std::string text = read(in);
      std::string result;

      if (type == 1) {
        std::string keyFile;
        std::cout << "Key file: ";
        std::cin >> keyFile;
        std::string key = read(keyFile);
        result = simple(text, key, enc);
      } else if (type == 2) {
        int a, b;
        std::cout << "a b: ";
        std::cin >> a >> b;
        result = affine(text, a, b, enc);
      } else if (type == 3) {
        int a1, b1, a2, b2;
        std::cout << "a1 b1 a2 b2: ";
        std::cin >> a1 >> b1 >> a2 >> b2;
        result = recurrent(text, a1, b1, a2, b2, enc);
      } else if (type == 4) {
        std::string keyFile;
        std::cout << "Key file: ";
        std::cin >> keyFile;
        std::string key = read(keyFile);
        result = vigKey(text, key, enc);
      } else if (type == 5) {
        std::string keyFile;
        std::cout << "Key file: ";
        std::cin >> keyFile;
        std::string key = read(keyFile);
        result = vigOpen(text, key, enc);
      } else if (type == 6) {
        std::string keyFile;
        std::cout << "Key file: ";
        std::cin >> keyFile;
        std::string key = read(keyFile);
        result = vigCipher(text, key, enc);
      }

      write(out, result);
      std::cout << "Done!\n";

    } catch (std::exception &e) {
      std::cout << "Error: " << e.what() << "\n";
    }
  }
  return 0;
}