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
  std::vector<int> result;
  result.resize(s.size());
  for (int i = 0; i < (int)s.size(); i++) {
    result[i] = (int)s[i];
  }
  return result;
}

std::string fromBytes(std::vector<int> v) {
  std::string result;
  result.resize(v.size());
  for (int i = 0; i < (int)v.size(); i++) {
    result[i] = (char)v[i];
  }
  return result;
}

std::string simple(std::string text, std::string key, bool enc) {
  std::vector<int> data = toBytes(text);
  std::vector<int> k = toBytes(key);

  if (k.size() != SIZE) {
    throw std::invalid_argument("key must be 256 bytes");
  }

  std::vector<int> key_inv;
  key_inv.resize(SIZE);
  for (int i = 0; i < SIZE; i++) {
    key_inv[k[i]] = i;
  }

  std::vector<int> result;
  result.resize(data.size());

  if (enc) {
    for (int i = 0; i < (int)data.size(); i++) {
      result[i] = k[data[i]];
    }
  } else {
    for (int i = 0; i < (int)data.size(); i++) {
      result[i] = key_inv[data[i]];
    }
  }

  return fromBytes(result);
}

std::string affine(std::string text, int a, int b, bool enc) {
  if (isCoprime(a, SIZE) == false) {
    throw std::invalid_argument("a must be coprime with 256");
  }

  std::vector<int> data = toBytes(text);
  std::vector<int> result;
  result.resize(data.size());

  if (enc) {
    for (int i = 0; i < (int)data.size(); i++) {
      int x = data[i];
      int y = (a * x + b) % SIZE;
      result[i] = y;
    }
  } else {
    int a_inv = modInv(a, SIZE);
    if (a_inv == -1) {
      throw std::runtime_error("no inverse for a");
    }
    for (int i = 0; i < (int)data.size(); i++) {
      int y = data[i];
      int step = y - b;
      if (step < 0) {
        step = step + SIZE;
      }
      int x = (a_inv * step) % SIZE;
      result[i] = x;
    }
  }

  return fromBytes(result);
}

std::string recurrent(std::string text, int a1, int b1, int a2, int b2,
                      bool enc) {
  if (isCoprime(a1, SIZE) == false or isCoprime(a2, SIZE) == false) {
    throw std::invalid_argument("a1 and a2 must be coprime");
  }

  std::vector<int> data = toBytes(text);
  if (data.size() < 2) {
    throw std::invalid_argument("text too short");
  }

  std::vector<int> A;
  std::vector<int> B;
  A.push_back(a1);
  A.push_back(a2);
  B.push_back(b1);
  B.push_back(b2);

  for (int i = 2; i < (int)data.size(); i++) {
    int newA = (A[i - 1] * A[i - 2]) % SIZE;
    if (isCoprime(newA, SIZE) == false) {
      throw std::runtime_error("bad coefficient");
    }
    A.push_back(newA);

    int newB = (B[i - 1] + B[i - 2]) % SIZE;
    B.push_back(newB);
  }

  std::vector<int> result;
  result.resize(data.size());

  if (enc) {
    for (int i = 0; i < (int)data.size(); i++) {
      result[i] = (A[i] * data[i] + B[i]) % SIZE;
    }
  } else {
    for (int i = 0; i < (int)data.size(); i++) {
      int a_inv = modInv(A[i], SIZE);
      if (a_inv == -1) {
        throw std::runtime_error("no inverse");
      }
      int step = data[i] - B[i];
      if (step < 0) {
        step = step + SIZE;
      }
      result[i] = (a_inv * step) % SIZE;
    }
  }

  return fromBytes(result);
}

std::string vigKey(std::string text, std::string key, bool enc) {
  std::vector<int> data = toBytes(text);
  std::vector<int> k = toBytes(key);

  if (k.empty()) {
    throw std::invalid_argument("key is empty");
  }

  std::vector<int> result;
  result.resize(data.size());
  int keyLen = k.size();

  for (int i = 0; i < (int)data.size(); i++) {
    if (enc) {
      result[i] = (data[i] + k[i % keyLen]) % SIZE;
    } else {
      int temp = data[i] - k[i % keyLen];
      if (temp < 0) {
        temp = temp + SIZE;
      }
      result[i] = temp;
    }
  }

  return fromBytes(result);
}

std::string vigOpen(std::string text, std::string key, bool enc) {
  std::vector<int> data = toBytes(text);
  std::vector<int> k = toBytes(key);

  if (k.empty()) {
    throw std::invalid_argument("key is empty");
  }

  std::vector<int> result;
  result.resize(data.size());
  std::vector<int> openText;
  openText.resize(data.size());

  for (int i = 0; i < (int)data.size(); i++) {
    int gamma;

    if (i == 0) {
      gamma = k[0];
    } else {
      if (enc) {
        gamma = data[i - 1];
      } else {
        gamma = result[i - 1];
      }
    }

    if (enc) {
      result[i] = (data[i] + gamma) % SIZE;
      openText[i] = data[i];
    } else {
      int temp = data[i] - gamma;
      if (temp < 0) {
        temp = temp + SIZE;
      }
      result[i] = temp;
      openText[i] = result[i];
    }
  }

  return fromBytes(result);
}

std::string vigCipher(std::string text, std::string key, bool enc) {
  std::vector<int> data = toBytes(text);
  std::vector<int> k = toBytes(key);

  if (k.empty()) {
    throw std::invalid_argument("key is empty");
  }

  std::vector<int> result;
  result.resize(data.size());

  for (int i = 0; i < (int)data.size(); i++) {
    int gamma;

    if (i == 0) {
      gamma = k[0];
    } else {
      if (enc) {
        gamma = result[i - 1];
      } else {
        gamma = data[i - 1];
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

  return fromBytes(result);
}