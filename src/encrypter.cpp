#include "encrypter.h"

//#include <openssl/evp.h>
//#include <openssl/hmac.h>
#include "../inc/aes.h"
#include <random>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cstring>
#include <iostream>
#include <filesystem>


void stringToUnsignedChar16(const std::string& str, unsigned char(&output)[16]) {
	if (str.size() > 16) {
		throw std::invalid_argument("String is too long to fit in unsigned char[16]");
	}

	std::memcpy(output, str.data(), str.size());

	// If the string is shorter than 16 characters, pad the rest with zeros
	if (str.size() < 16) {
		std::memset(output + str.size(), 0, 16 - str.size());
	}
}

void reverseChar16(unsigned char(&input)[16], unsigned char(&output)[16])
{
	for (int i = 0; i < 16; ++i) {
		output[i] = input[15 - i];
	}
}


int encryptFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& password) {

    // Шифруем и записываем данные блоками по 4KB
    const size_t bufferSize = 4096;
    std::vector<uint8_t> buffer(bufferSize);

	// Генерируем случайный вектор
	std::vector<uint8_t> randomNumber(AES_BLOCKLEN);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);
	for (auto& byte : randomNumber) {
		byte = static_cast<uint8_t>(dis(gen));
	}

	// Открываем файлы
	std::ifstream inputFile(inputFilePath, std::ios::binary);
	std::ofstream outputFile(outputFilePath, std::ios::binary);
	if (!inputFile.is_open() || !outputFile.is_open()) {
		return 1;
	}

    //inputFile.seekg(0, std::ios_base::end);
    const size_t originSize = std::filesystem::file_size(inputFilePath);//inputFile.tellg();
    //inputFile.seekg(0, std::ios_base::beg);

    // 1. Checksum block
    // 2. Source file size
    outputFile.write(reinterpret_cast<const char*>(randomNumber.data()), randomNumber.size());
    outputFile << originSize;

    size_t blocksToWrite = originSize / bufferSize;
    if (originSize % bufferSize != 0) ++blocksToWrite;

	// Подготавливаем ключ и IV
	uint8_t key[AES_KEYLEN];
	std::memset(key, 0, AES_KEYLEN);
	std::memcpy(key, password.data(), std::min(password.size(), static_cast<size_t>(AES_KEYLEN)));

	uint8_t iv[AES_BLOCKLEN];
	reverseChar16(key, iv);

	// Инициализируем контекст AES
	AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);


	while (blocksToWrite > 1) {
		inputFile.read(reinterpret_cast<char*>(buffer.data()), bufferSize);
		size_t bytesRead = inputFile.gcount();

		if (bytesRead > 0) {
			AES_CBC_encrypt_buffer(&ctx, buffer.data(), buffer.size());
            // buffer.resize(bufferSize);
			outputFile.write(reinterpret_cast<const char*>(buffer.data()), bufferSize);
		}

        --blocksToWrite;
	}
    // Last block
    char buf;
    int count = 0;
    while (inputFile.read(&buf, sizeof(buf)))
    {
        buffer[count] = buf;
        ++count;
    }
    AES_CBC_encrypt_buffer(&ctx, buffer.data(), buffer.size());
    outputFile.write(reinterpret_cast<const char*>(buffer.data()), bufferSize);

	// 7. Добавляем случайный вектор в конец

	std::vector<uint8_t> finalBlock(randomNumber.size());
	std::memcpy(finalBlock.data(), randomNumber.data(), randomNumber.size());

	AES_CBC_encrypt_buffer(&ctx, finalBlock.data(), finalBlock.size());
	outputFile.write(reinterpret_cast<const char*>(finalBlock.data()), finalBlock.size());

    inputFile.close();
    outputFile.close();

	return 0;
}


int decryptFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& password) {

    const size_t bufferSize = 4096;
    std::vector<uint8_t> buffer(bufferSize);

    // 1. Открываем файлы
    std::ifstream inputFile(inputFilePath, std::ios::binary | std::ios::ate);
    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        return 1;
    }

    // 2. Проверяем минимальный размер файла
    const size_t fileSize = inputFile.tellg();
    if (fileSize < 2 * AES_BLOCKLEN + sizeof(size_t)) {
        return 2;
    }
    inputFile.seekg(0);

    // 3. Читаем случайный вектор из начала файла
    std::vector<uint8_t> headerRandomNumber(AES_BLOCKLEN);
    inputFile.read(reinterpret_cast<char*>(headerRandomNumber.data()), 16);

    size_t originSize;
    inputFile >> originSize;

    // Origin file size
    size_t blocksToRead = originSize / bufferSize;
    if (originSize % bufferSize != 0) ++blocksToRead;

    // Подготавливаем ключ и IV
    uint8_t key[AES_KEYLEN];
    std::memset(key, 0, AES_KEYLEN);
    std::memcpy(key, password.data(), std::min(password.size(), static_cast<size_t>(AES_KEYLEN)));

    uint8_t iv[AES_BLOCKLEN];
    reverseChar16(key, iv);

    // Инициализируем контекст AES
    AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);

    // Читаем и расшифровываем данные

    while (blocksToRead > 1) {
        inputFile.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

        // Расшифровываем блок
        AES_CBC_decrypt_buffer(&ctx, buffer.data(), buffer.size());

        outputFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());

        --blocksToRead;
    }

    inputFile.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    AES_CBC_decrypt_buffer(&ctx, buffer.data(), buffer.size());
    outputFile.write(reinterpret_cast<const char*>(buffer.data()), originSize % bufferSize);

    // Получаем randomNumber из конца
    std::vector<uint8_t> footerRandomNumber(AES_BLOCKLEN);
    inputFile.read(reinterpret_cast<char*>(footerRandomNumber.data()), footerRandomNumber.size());
    AES_CBC_decrypt_buffer(&ctx, footerRandomNumber.data(), footerRandomNumber.size());

    // Проверяем совпадение randomNumber из начала и конца
    if (!std::equal(headerRandomNumber.begin(), headerRandomNumber.end(), footerRandomNumber.begin())) {
        return 2; // randomNumber не совпадают
    }

    inputFile.close();
    outputFile.close();

    return 0;
}

