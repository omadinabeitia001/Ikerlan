#include <gtest/gtest.h>
#include "padding_oracle.hpp"

// helper: cambia un byte concreto en un vector (no modifica el original)
static std::vector<uint8_t> modify_byte(const std::vector<uint8_t>& data, size_t pos, uint8_t newval) {
    std::vector<uint8_t> out = data;
    if (pos < out.size()) out[pos] = newval;
    return out;
}

TEST(PaddingOracleTest, OriginalCiphertextHasValidPadding) {
    auto r = pad_oracle::encryption_oracle();
    ASSERT_FALSE(r.iv.empty());
    ASSERT_FALSE(r.ciphertext.empty());

    // El oracle debe aceptar el ciphertext intacto
    bool ok = pad_oracle::padding_oracle_check(r.iv, r.ciphertext);
    EXPECT_TRUE(ok);
}

TEST(PaddingOracleTest, TamperedCiphertextUsuallyFailsPadding) {
    auto r = pad_oracle::encryption_oracle();

    // Construimos la concatenación IV || ciphertext para modificar el último byte
    std::vector<uint8_t> full;
    full.insert(full.end(), r.iv.begin(), r.iv.end());
    full.insert(full.end(), r.ciphertext.begin(), r.ciphertext.end());

    ASSERT_GE(full.size(), static_cast<size_t>(16)); // al menos 1 bloque + IV
    // cambia un byte en el último bloque (último byte del mensaje cifrado)
    size_t pos_to_modify = full.size() - 1;
    uint8_t old = full[pos_to_modify];
    uint8_t newv = static_cast<uint8_t>(old ^ 0x01u); // cambia ligeramente

    // reconstruimos iv y ciphertext a partir de full modificado
    std::vector<uint8_t> full_mod = modify_byte(full, pos_to_modify, newv);
    std::string iv_mod(full_mod.begin(), full_mod.begin() + 16); // convertir a string
    std::vector<uint8_t> ct_mod(full_mod.begin() + 16, full_mod.end());

    // Es muy probable que el padding ahora sea inválido. Si por improbable casualidad sigue válido,
    // el test seguirá verde, pero el objetivo es detectar comportamientos obvios.
    bool ok_original = pad_oracle::padding_oracle_check(r.iv, r.ciphertext);
    bool ok_modified = pad_oracle::padding_oracle_check(iv_mod, ct_mod);

    EXPECT_TRUE(ok_original);
    EXPECT_FALSE(ok_modified) << "El ciphertext modificado aún tiene padding válido (raro, reintenta el test).";
}
