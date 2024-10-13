#pragma once
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace Sha
{
    inline std::string to_hex_string(const unsigned char* input, size_t length) {
        std::stringstream hex_stream;
        hex_stream << std::hex << std::setfill('0');
        for (size_t i = 0; i < length; i++) {
            hex_stream << std::setw(2) << static_cast<int>(input[i]);
        }
        return hex_stream.str();
    }

    inline std::string sha256(const std::string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data.c_str(), data.size());
        SHA256_Final(hash, &sha256);
        return to_hex_string(hash, SHA256_DIGEST_LENGTH);
    }

    inline std::string getFirst16Chars(const std::string& input) {
        if (input.length() >= 16) {
            return input.substr(0, 16);
        }
        else {
            return input;
        }
    }

    inline std::string getFirst32Chars(const std::string& input) {
        if (input.length() >= 32) {
            return input.substr(0, 32);
        }
        else {
            return input;
        }
    }

    std::string decryptAES256CBC(const std::string& ciphertext, const std::string& key, const std::string& iv) {
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        std::vector<unsigned char> plaintext(ciphertext.size());

        int len;
        int plaintext_len;
        int retval;

        // 初始化解密操作
        if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()))) {
            EVP_CIPHER_CTX_free(ctx);
            return "";
            throw std::runtime_error("DecryptInit failed");
        }

        // 提供密文进行解密
        if (!EVP_DecryptUpdate(ctx, plaintext.data(), &len, reinterpret_cast<const unsigned char*>(ciphertext.data()), ciphertext.length())) {
            EVP_CIPHER_CTX_free(ctx);
            return "";
            throw std::runtime_error("DecryptUpdate failed");
        }
        plaintext_len = len;

        // 结束解密操作
        if (!EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len)) {
            EVP_CIPHER_CTX_free(ctx);
            return "";
            throw std::runtime_error("DecryptFinal failed");
        }
        plaintext_len += len;

        // 清理
        EVP_CIPHER_CTX_free(ctx);

        return std::string(plaintext.begin(), plaintext.begin() + plaintext_len);
    }

}
