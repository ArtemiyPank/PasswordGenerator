#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <iostream>
#include <string>
#include <bitset>

#include "HashesProcessing.h"
#include "BitsProcessing.h"

using namespace CryptoPP;

static const std::string FILE_NAME = "HashesProcessing";

// Computes the SHA3-512 hash of `master` and returns it as a 512-bit bitset.
std::bitset<512> GetHash_HSA_512(const std::string &master) {
    // (Optional) set up hex encoder to print the hash to stdout
    HexEncoder encoder(new FileSink(std::cout));

    // Compute raw SHA3-512 digest
    SHA3_512 hash;
    hash.Update(reinterpret_cast<const byte*>(master.data()), master.size());
    std::string digest(hash.DigestSize(), '\0');
    hash.Final(reinterpret_cast<byte*>(&digest[0]));

    // Convert the binary digest into a bitset
    return getBitset512FromString(digest);
}
