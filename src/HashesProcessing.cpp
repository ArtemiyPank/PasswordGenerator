#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <iostream>
#include <string>
#include <iomanip>
#include "HashesProcessing.h"

using namespace CryptoPP;

static const std::string FILE_NAME = "HashesProcessing";


std::string GetHash_HSA_512(const std::string &master) {
    HexEncoder encoder(new FileSink(std::cout));

    std::string digest;

    SHA3_512 hash;
    hash.Update(reinterpret_cast<const byte *>(master.data()), master.size());
    digest.resize(hash.DigestSize());
    hash.Final(reinterpret_cast<byte *>(&digest[0]));

    return digest;
}



