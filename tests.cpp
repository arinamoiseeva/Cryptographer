#include "ciphers.h"
#include <gtest/gtest.h>
#include <string>

TEST(SimpleTest, Negative) {
  EXPECT_THROW(simple("Abracadabra", "shortkey", true), std::invalid_argument);
}

TEST(AffineTest, Positive) {
  std::string s = "Hello";
  std::string e = affine(s, 3, 5, true);
  std::string d = affine(e, 3, 5, false);
  EXPECT_EQ(s, d);
}

TEST(AffineTest, Negative) {
  EXPECT_THROW(affine("Hello", 2, 5, true), std::invalid_argument);
}

TEST(RecurrentAffineTest, Positive) {
  std::string s = "Apple";
  std::string e = recurrent(s, 3, 5, 7, 11, true);
  std::string d = recurrent(e, 3, 5, 7, 11, false);
  EXPECT_EQ(s, d);
}

TEST(RecurrentAffineTest, Negative) {
  EXPECT_THROW(recurrent("A", 3, 5, 7, 11, true), std::invalid_argument);
}

TEST(VigKeyTest, Positive) {
  std::string s = "Summer";
  std::string e = vigKey(s, "key", true);
  std::string d = vigKey(e, "key", false);
  EXPECT_EQ(s, d);
}

TEST(VigKeyTest, Negative) {
  EXPECT_THROW(vigKey("Skating", "", true), std::invalid_argument);
}

TEST(VigCipherTest, Positive) {
  std::string s = "Mount Everest";
  std::string e = vigCipher(s, "sea", true);
  std::string d = vigCipher(e, "sea", false);
  EXPECT_EQ(s, d);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}