#include "utils_set3.hpp"
#include <random>
#include <stdexcept>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

namespace utils_set3 {

std::string generateRandomAESKey() {
    return generateRandomBytes(16);
}

std::string generateRandomBytes(size_t len) {
    std::string result;
    result.resize(len);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    for (size_t i = 0; i < len; ++i) {
        result[i] = static_cast<char>(dis(gen));
    }
    return result;
}

std::vector<uint8_t> base64Decode(const std::string& input) {
    BIO* bio = BIO_new_mem_buf(input.data(), input.size());
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    std::vector<uint8_t> output(input.size());
    int len = BIO_read(bio, output.data(), input.size());
    if (len <= 0) throw std::runtime_error("Error al decodificar base64");

    output.resize(len);
    BIO_free_all(bio);
    return output;
}

}
