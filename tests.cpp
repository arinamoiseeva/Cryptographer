#include "ciphers.h"
#include <gtest/gtest.h>
#include <string>

TEST(AffineTest, Positive) {
  std::string s = "Hello";
  std::string e = affine(s, 3, 5, true);
  std::string d = affine(e, 3, 5, false);
  EXPECT_EQ(s, d);
}

TEST(AffineTest, NegativeNotCoprime) {
  EXPECT_THROW(affine("Hello", 2, 5, true), std::invalid_argument);
}

TEST(RecurrentTest, Positive) {
  std::string s = "Hello";
  std::string e = recurrent(s, 3, 5, 7, 11, true);
  std::string d = recurrent(e, 3, 5, 7, 11, false);
  EXPECT_EQ(s, d);
}

TEST(RecurrentTest, NegativeShortText) {
  EXPECT_THROW(recurrent("A", 3, 5, 7, 11, true), std::invalid_argument);
}

TEST(VigKeyTest, Positive) {
  std::string s = "Hello";
  std::string e = vigKey(s, "key", true);
  std::string d = vigKey(e, "key", false);
  EXPECT_EQ(s, d);
}

TEST(VigKeyTest, NegativeEmptyKey) {
  EXPECT_THROW(vigKey("Hello", "", true), std::invalid_argument);
}

TEST(VigOpenTest, Positive) {
  std::string s = "Hello";
  std::string e = vigOpen(s, "key", true);
  std::string d = vigOpen(e, "key", false);
  EXPECT_EQ(s, d);
}

TEST(VigOpenTest, NegativeEmptyKey) {
  EXPECT_THROW(vigOpen("Hello", "", true), std::invalid_argument);
}

TEST(VigCipherTest, Positive) {
  std::string s = "Hello";
  std::string e = vigCipher(s, "key", true);
  std::string d = vigCipher(e, "key", false);
  EXPECT_EQ(s, d);
}

TEST(VigCipherTest, NegativeEmptyKey) {
  EXPECT_THROW(vigCipher("Hello", "", true), std::invalid_argument);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}