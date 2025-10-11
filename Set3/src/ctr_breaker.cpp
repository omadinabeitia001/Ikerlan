#include "ctr_breaker.hpp"
#include "utils_set3.hpp"
#include "ctr_mode.hpp"

#include <iostream>
#include <algorithm>
#include <map>

namespace ctr_breaker {

std::vector<std::vector<uint8_t>> loadPlaintexts() {
    std::vector<std::string> base64_lines = {
        "SSBoYXZlIG1ldCB0aGVtIGF0IGNsb3NlIG9mIGRheQ==",
        "Q29taW5nIHdpdGggdml2aWQgZmFjZXM=",
        "RnJvbSBjb3VudGVyIG9yIGRlc2sgYW1vbmcgZ3JleQ==",
        "RWlnaHRlZW50aC1jZW50dXJ5IGhvdXNlcy4=",
        "SSBoYXZlIHBhc3NlZCB3aXRoIGEgbm9kIG9mIHRoZSBoZWFk",
        "T3IgcG9saXRlIG1lYW5pbmdsZXNzIHdvcmRzLA==",
        "T3IgaGF2ZSBsaW5nZXJlZCBhd2hpbGUgYW5kIHNhaWQ=",
        "UG9saXRlIG1lYW5pbmdsZXNzIHdvcmRzLA==",
        "QW5kIHRob3VnaHQgYmVmb3JlIEkgaGFkIGRvbmU=",
        "T2YgYSBtb2NraW5nIHRhbGUgb3IgYSBnaWJl",
        "VG8gcGxlYXNlIGEgY29tcGFuaW9u",
        "QXJvdW5kIHRoZSBmaXJlIGF0IHRoZSBjbHViLA==",
        "QmVpbmcgY2VydGFpbiB0aGF0IHRoZXkgYW5kIEk=",
        "QnV0IGxpdmVkIHdoZXJlIG1vdGxleSBpcyB3b3JuOg==",
        "QWxsIGNoYW5nZWQsIGNoYW5nZWQgdXR0ZXJseTo=",
        "QSB0ZXJyaWJsZSBiZWF1dHkgaXMgYm9ybi4=",
        "VGhhdCB3b21hbidzIGRheXMgd2VyZSBzcGVudA==",
        "SW4gaWdub3JhbnQgZ29vZCB3aWxsLA==",
        "SGVyIG5pZ2h0cyBpbiBhcmd1bWVudA==",
        "VW50aWwgaGVyIHZvaWNlIGdyZXcgc2hyaWxsLg==",
        "V2hhdCB2b2ljZSBtb3JlIHN3ZWV0IHRoYW4gaGVycw==",
        "V2hlbiB5b3VuZyBhbmQgYmVhdXRpZnVsLA==",
        "U2hlIHJvZGUgdG8gaGFycmllcnM/",
        "VGhpcyBtYW4gaGFkIGtlcHQgYSBzY2hvb2w=",
        "QW5kIHJvZGUgb3VyIHdpbmdlZCBob3JzZS4=",
        "VGhpcyBvdGhlciBoaXMgaGVscGVyIGFuZCBmcmllbmQ=",
        "V2FzIGNvbWluZyBpbnRvIGhpcyBmb3JjZTs=",
        "SGUgbWlnaHQgaGF2ZSB3b24gZmFtZSBpbiB0aGUgZW5kLA==",
        "U28gc2Vuc2l0aXZlIGhpcyBuYXR1cmUgc2VlbWVkLA==",
        "U28gZGFyaW5nIGFuZCBzd2VldCBoaXMgdGhvdWdodC4=",
        "VGhpcyBvdGhlciBtYW4gSSBoYWQgZHJlYW1lZA==",
        "QSBkcnVua2VuLCB2YWluLWdsb3Jpb3VzIGxvdXQu",
        "SGUgaGFkIGRvbmUgbW9zdCBiaXR0ZXIgd3Jvbmc=",
        "VG8gc29tZSB3aG8gYXJlIG5lYXIgbXkgaGVhcnQs",
        "WWV0IEkgbnVtYmVyIGhpbSBpbiB0aGUgc29uZzs=",
        "SGUsIHRvbywgaGFzIHJlc2lnbmVkIGhpcyBwYXJ0",
        "SW4gdGhlIGNhc3VhbCBjb21lZHk7",
        "SGUsIHRvbywgaGFzIGJlZW4gY2hhbmdlZCBpbiBoaXMgdHVybiw=",
        "VHJhbnNmb3JtZWQgdXR0ZXJseTo=",
        "QSB0ZXJyaWJsZSBiZWF1dHkgaXMgYm9ybi4="
    };

    std::vector<std::vector<uint8_t>> plaintexts;
    for (const auto& line : base64_lines) {
        plaintexts.push_back(utils_set3::base64Decode(line));
    }
    return plaintexts;
}

std::vector<std::vector<uint8_t>> encryptWithFixedNonce(const std::vector<std::vector<uint8_t>>& plaintexts, const std::string& key) {
    std::vector<std::vector<uint8_t>> ciphertexts;
    for (const auto& pt : plaintexts) {
        ciphertexts.push_back(ctr::aesCTR(pt, key, 0));
    }
    return ciphertexts;
}

std::vector<uint8_t> recoverKeystream(const std::vector<std::vector<uint8_t>>& ciphertexts) {
    size_t maxLen = 0;
    for (const auto& c : ciphertexts) maxLen = std::max(maxLen, c.size());

    std::vector<uint8_t> keystream(maxLen, 0);

    for (size_t i = 0; i < maxLen; ++i) {
        std::map<uint8_t, int> score;
        for (uint8_t k = 0; k < 255; ++k) {
            int count = 0;
            for (const auto& c : ciphertexts) {
                if (i < c.size()) {
                    char ch = c[i] ^ k;
                    if (isalpha(ch) || ch == ' ') count++;
                }
            }
            score[k] = count;
        }

        keystream[i] = std::max_element(score.begin(), score.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; })->first;
    }

    return keystream;
}

std::vector<std::string> decryptWithKeystream(const std::vector<std::vector<uint8_t>>& ciphertexts, const std::vector<uint8_t>& keystream) {
    std::vector<std::string> results;
    for (const auto& c : ciphertexts) {
        std::string line;
        for (size_t i = 0; i < c.size(); ++i) {
            line += static_cast<char>(c[i] ^ keystream[i]);
        }
        results.push_back(line);
    }
    return results;
}

}
