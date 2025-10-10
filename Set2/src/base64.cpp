#include <openssl/bio.h>
#include <openssl/evp.h>
#include <stdexcept>
#include <vector>
#include <string>

std::vector<uint8_t> base64Decode(const std::string& input) {
    BIO* bio = BIO_new_mem_buf(input.data(), input.size());
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    // ❌ No activar BIO_FLAGS_BASE64_NO_NL — permite saltos de línea
    // BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); ← esto debe estar comentado o eliminado

    std::vector<uint8_t> buffer((input.size() * 3) / 4);
    int decodedLen = BIO_read(bio, buffer.data(), buffer.size());
    BIO_free_all(bio);

    if (decodedLen <= 0) {
        throw std::runtime_error("Base64 decoding failed");
    }

    buffer.resize(decodedLen);
    return buffer;
}
