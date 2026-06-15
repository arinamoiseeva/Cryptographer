#ifndef CIPHERS_H
#define CIPHERS_H

#include <string>
#include <vector>

/**
 * @brief Проверяет, являются ли два числа взаимно простыми
 * 
 * @param x первое число
 * @param y второе число
 * @return true если числа взаимно просты
 * @return false если есть общий делитель больше 1
 */
bool isCoprime(int x, int y);

/**
 * @brief Находит обратный элемент числа по модулю
 * 
 * @param num число
 * @param mod модуль
 * @return обратный элемент, или -1 если не найден
 */
int findInverse(int num, int mod);

/**
 * @brief Преобразует строку в вектор байтов
 * 
 * @param text входная строка
 * @return вектор числовых кодов символов
 */
std::vector<int> textToBytes(std::string text);

/**
 * @brief Преобразует вектор байтов обратно в строку
 * 
 * @param bytes вектор числовых кодов
 * @return восстановленная строка
 */
std::string bytesToText(std::vector<int> bytes);

/**
 * @brief Шифрование простой подстановкой
 * 
 * @param text исходный текст
 * @param keyString ключ (256 символов)
 * @return зашифрованный текст, или пустая строка при ошибке
 */
std::string cipherSimpleEncrypt(std::string text, std::string keyString);

/**
 * @brief Расшифрование простой подстановкой
 * 
 * @param text зашифрованный текст
 * @param keyString ключ (256 символов)
 * @return расшифрованный текст, или пустая строка при ошибке
 */
std::string cipherSimpleDecrypt(std::string text, std::string keyString);

/**
 * @brief Аффинное шифрование
 * 
 * Формула: y = (a * x + b) mod 256
 * 
 * @param text исходный текст
 * @param a коэффициент умножения
 * @param b коэффициент сдвига
 * @return зашифрованный текст, или пустая строка при ошибке
 */
std::string cipherAffineEncrypt(std::string text, int a, int b);

/**
 * @brief Аффинное расшифрование
 * 
 * Формула: x = (y - b) * a^(-1) mod 256
 * 
 * @param text зашифрованный текст
 * @param a коэффициент умножения
 * @param b коэффициент сдвига
 * @return расшифрованный текст, или пустая строка при ошибке
 */
std::string cipherAffineDecrypt(std::string text, int a, int b);

/**
 * @brief Рекуррентное аффинное шифрование
 * 
 * @param text исходный текст (минимум 2 символа)
 * @param a1 первый коэффициент умножения
 * @param b1 первый коэффициент сдвига
 * @param a2 второй коэффициент умножения
 * @param b2 второй коэффициент сдвига
 * @return зашифрованный текст, или пустая строка при ошибке
 */
std::string cipherAffineRecurrentEncrypt(std::string text, int a1, int b1, int a2, int b2);

/**
 * @brief Рекуррентное аффинное расшифрование
 * 
 * @param text зашифрованный текст
 * @param a1 первый коэффициент умножения
 * @param b1 первый коэффициент сдвига
 * @param a2 второй коэффициент умножения
 * @param b2 второй коэффициент сдвига
 * @return расшифрованный текст, или пустая строка при ошибке
 */
std::string cipherAffineRecurrentDecrypt(std::string text, int a1, int b1, int a2, int b2);

/**
 * @brief Шифр Виженера с повторяющимся ключом (шифрование)
 * 
 * @param text исходный текст
 * @param keyString ключ
 * @return зашифрованный текст, или пустая строка при ошибке
 */
std::string cipherVigenereKeyEncrypt(std::string text, std::string keyString);

/**
 * @brief Шифр Виженера с повторяющимся ключом (расшифрование)
 * 
 * @param text зашифрованный текст
 * @param keyString ключ
 * @return расшифрованный текст, или пустая строка при ошибке
 */
std::string cipherVigenereKeyDecrypt(std::string text, std::string keyString);

/**
 * @brief Шифр Виженера по открытому тексту (шифрование)
 * 
 * @param text исходный текст
 * @param keyString ключ
 * @return зашифрованный текст, или пустая строка при ошибке
 */
std::string cipherVigenereOpenEncrypt(std::string text, std::string keyString);

/**
 * @brief Шифр Виженера по открытому тексту (расшифрование)
 * 
 * @param text зашифрованный текст
 * @param keyString ключ
 * @return расшифрованный текст, или пустая строка при ошибке
 */
std::string cipherVigenereOpenDecrypt(std::string text, std::string keyString);

/**
 * @brief Шифр Виженера по шифртексту (шифрование)
 * 
 * @param text исходный текст
 * @param keyString ключ
 * @return зашифрованный текст, или пустая строка при ошибке
 */
std::string cipherVigenereCipherEncrypt(std::string text, std::string keyString);

/**
 * @brief Шифр Виженера по шифртексту (расшифрование)
 * 
 * @param text зашифрованный текст
 * @param keyString ключ
 * @return расшифрованный текст, или пустая строка при ошибке
 */
std::string cipherVigenereCipherDecrypt(std::string text, std::string keyString);
   
#endif