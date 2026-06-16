#include "ciphers.h"
#include <algorithm>
#include <stdexcept>

const int SIZE = 256;

bool isCoprime(int x, int y) {
  for (int i = 2; i <= std::min(x, y); i++) {
    if (x % i == 0 and y % i == 0) {
      return false;
    }
  }
  return true;
}

int modInv(int n, int m) {
  for (int i = 0; i < m; i++) {
    if ((n * i) % m == 1) {
      return i;
    }
  }
  return -1;
}

std::vector<int> toBytes(std::string s) {
    std::vector<int> res(s.size());
    for (int i = 0; i < (int)s.size(); i++) {
        res[i] = (int)s[i];
    }
    return res;
}

std::string fromBytes(std::vector<int> v) {
    std::string res(v.size(), ' ');
    for (int i = 0; i < (int)v.size(); i++) {
        res[i] = (char)v[i];
    }
    return res;
}

std::string simple(std::string text, std::string key, bool enc) {
    std::vector<int> data = toBytes(text);
    std::vector<int> k = toBytes(key);

    if (k.size() != SIZE) {
        throw std::invalid_argument("key must be 256 bytes");
    }

    std::vector<int> key_inv(SIZE);
    for (int i = 0; i < SIZE; i++) {
        key_inv[k[i]] = i;
    }

    std::vector<int> res(data.size());

    if (enc) {
        for (int i = 0; i < (int)data.size(); i++) {
            res[i] = k[data[i]];
        }
    } else {
        for (int i = 0; i < (int)data.size(); i++) {
            res[i] = key_inv[data[i]];
        }
    }

    return fromBytes(res);
}

std::string affine(std::string text, int a, int b, bool enc) {
    if (!isCoprime(a, SIZE)) {
        throw std::invalid_argument("a must be coprime with 256");
    }

    std::vector<int> data = toBytes(text);
    std::vector<int> res(data.size());

    if (enc) {
        for (int i = 0; i < (int)data.size(); i++) {
            res[i] = (a * data[i] + b) % SIZE;
        }
    } else {
        int a_inv = modInv(a, SIZE);
        for (int i = 0; i < (int)data.size(); i++) {
            int t = data[i] - b;
            if (t < 0) t += SIZE;
            res[i] = (a_inv * t) % SIZE;
        }
    }

    return fromBytes(res);
}

std::string recurrent(std::string text, int a1, int b1, int a2, int b2, bool enc) {
    if (!isCoprime(a1, SIZE) or !isCoprime(a2, SIZE)) {
        throw std::invalid_argument("a1 and a2 must be coprime with 256");
    }

    std::vector<int> data = toBytes(text);
    if (data.size() < 2) {
        throw std::invalid_argument("text too short");
    }

    std::vector<int> A = {a1, a2};
    std::vector<int> B = {b1, b2};

    for (int i = 2; i < (int)data.size(); i++) {
        A.push_back((A[i - 1] * A[i - 2]) % SIZE);
        B.push_back((B[i - 1] + B[i - 2]) % SIZE);
    }

    std::vector<int> res(data.size());

    if (enc) {
        for (int i = 0; i < (int)data.size(); i++) {
            res[i] = (A[i] * data[i] + B[i]) % SIZE;
        }
    } else {
        for (int i = 0; i < (int)data.size(); i++) {
            int a_inv = modInv(A[i], SIZE);
            int t = data[i] - B[i];
            if (t < 0) t += SIZE;
            res[i] = (a_inv * t) % SIZE;
        }
    }

    return fromBytes(res);
}

std::string vigKey(std::string text, std::string key, bool enc) {
  std::vector<int> data = toBytes(text);
  std::vector<int> k = toBytes(key);

  if (k.empty()) {
    throw std::invalid_argument("key is empty");
  }

  std::vector<int> result(data.size());
  int len = k.size();

  for (int i = 0; i < (int)data.size(); i++) {
    if (enc) {
      result[i] = (data[i] + k[i % len]) % SIZE;
    } else {
      int temp = data[i] - k[i % len];
      if (temp < 0) {
        temp = temp + SIZE;
      }
      result[i] = temp;
    }
  }

  return fromBytes(result);
}

std::vector<int> vigProcess(std::vector<int> data, std::vector<int> key, bool enc, int mode) {
    if (key.empty()) {
        throw std::invalid_argument("key is empty");
    }

    std::vector<int> result(data.size());

    for (int i = 0; i < (int)data.size(); i++) {
        int gamma;

        if (i == 0) {
            gamma = key[0];
        } else {
            if (mode == 0) {  
                if (enc) {
                    gamma = data[i - 1];
                } else {
                    gamma = result[i - 1];
                }
            } else {  
                if (enc) {
                    gamma = result[i - 1];
                } else {
                    gamma = data[i - 1];
                }
            }
        }

        if (enc) {
            result[i] = (data[i] + gamma) % SIZE;
        } else {
            int temp = data[i] - gamma;
            if (temp < 0) {
                temp = temp + SIZE;
            }
            result[i] = temp;
        }
    }

    return result;
}

std::string vigOpen(std::string text, std::string key, bool enc) {
    std::vector<int> result = vigProcess(toBytes(text), toBytes(key), enc, 0);
    return fromBytes(result);
}

std::string vigCipher(std::string text, std::string key, bool enc) {
    std::vector<int> result = vigProcess(toBytes(text), toBytes(key), enc, 1);
    return fromBytes(result);
}