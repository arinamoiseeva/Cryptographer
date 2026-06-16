#ifndef CIPHERS_H
#define CIPHERS_H

#include <string>
#include <vector>

/**
 * @brief Проверяет, являются ли два числа взаимно простыми
 * @param x первое число
 * @param y второе число
 * @return true если взаимно просты, false если есть общий делитель
 */
bool isCoprime(int x, int y);

/**
 * @brief Находит обратный элемент числа по модулю
 * @param n число
 * @param m модуль
 * @return обратный элемент или -1 если не найден
 */
int modInv(int n, int m);

/**
 * @brief Преобразует строку в вектор байтов
 * @param s входная строка
 * @return вектор целых чисел (0-255)
 */
std::vector<int> toBytes(std::string s);

/**
 * @brief Преобразует вектор байтов в строку
 * @param v вектор чисел
 * @return восстановленная строка
 */
std::string fromBytes(std::vector<int> v);

/**
 * @brief Шифр простой замены
 * @param text исходный текст
 * @param key ключ (256 байт, перестановка 0-255)
 * @param enc true - шифрование, false - расшифрование
 * @return результат
 * @throws std::invalid_argument если ключ не равен 256 байтам
 */
std::string simple(std::string text, std::string key, bool enc);

/**
 * @brief Аффинный шифр
 * @param text исходный текст
 * @param a коэффициент умножения (должен быть взаимно прост с 256)
 * @param b коэффициент сдвига
 * @param enc true - шифрование, false - расшифрование
 * @return результат
 * @throws std::invalid_argument если a не взаимно просто с 256
 * @throws std::runtime_error если не найден обратный элемент для a
 */
std::string affine(std::string text, int a, int b, bool enc);

/**
 * @brief Рекуррентный аффинный шифр
 * @param text исходный текст (минимум 2 символа)
 * @param a1 первый коэффициент умножения
 * @param b1 первый коэффициент сдвига
 * @param a2 второй коэффициент умножения
 * @param b2 второй коэффициент сдвига
 * @param enc true - шифрование, false - расшифрование
 * @return результат
 * @throws std::invalid_argument если a1 или a2 не взаимно просты с 256
 * @throws std::invalid_argument если текст короче 2 символов
 * @throws std::runtime_error если сгенерированный коэффициент a[i] не взаимно прост с 256
 * @throws std::runtime_error если не найден обратный элемент для коэффициента a[i]
 */
std::string recurrent(std::string text, int a1, int b1, int a2, int b2,
                      bool enc);

/**
 * @brief Шифр Виженера с повторяющимся ключом
 * @param text исходный текст
 * @param key ключ
 * @param enc true - шифрование, false - расшифрование
 * @return результат
 * @throws std::invalid_argument если ключ пустой
 */
std::string vigKey(std::string text, std::string key, bool enc);

/**
 * @brief Шифр Виженера по открытому тексту
 * @param text исходный текст
 * @param key ключ
 * @param enc true - шифрование, false - расшифрование
 * @return результат
 * @throws std::invalid_argument если ключ пустой
 */
std::string vigOpen(std::string text, std::string key, bool enc);

/**
 * @brief Шифр Виженера по шифртексту
 * @param text исходный текст
 * @param key ключ
 * @param enc true - шифрование, false - расшифрование
 * @return результат
 * @throws std::invalid_argument если ключ пустой
 */
std::string vigCipher(std::string text, std::string key, bool enc);

#endif