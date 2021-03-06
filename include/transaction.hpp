#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <vector>
#include <map>

#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"

#include "block.pb.h"

#include "utils.hpp"

using namespace CryptoPP;

class BlockChain;

// Reward for mining
const int subsidy = 10;

/*
 * TXInput
 */
class TXInput {
public:
    // TXInput Constructors
    TXInput(std::string txid, int vout, std::string scriptSig);
    // Serialize Helper Functions
    TXInput(CryptoProtobuf::TXInput* d_txin);
    void loadTXInput(CryptoProtobuf::TXInput* s_txin);
    // Methods for TXInput class
    bool canUnlockOutputWith(std::string unlockingData);
    bool usesKey(std::string pubKeyHash);
    void printTXInput();

    // Instance Variables
    std::string txid;
    int         vout;
    std::string signature;
    std::string pubKey;
};

namespace TXInputSerialize {
    std::string serialize(TXInput* txin);
    TXInput     deserialize(std::string& serialTXInput);
}

/*
 * TXOuput
 */
class TXOutput {
public:
    TXOutput(int value, std::string scriptPubKey);
    // Serialize Helper Functions
    TXOutput(CryptoProtobuf::TXOutput* d_txout);
    void loadTXOutput(CryptoProtobuf::TXOutput* s_txout);
    // Methods for TXOuput class
    void lock(std::string address);
    bool isLockedWithKey(std::string pubKeyHash);
    bool canBeUnlockedWith(std::string unlockingData);
    void printTXOutput();

    int         value;
    std::string pubKeyHash;
};

namespace TXOutputSerialize {
    std::string serialize(TXOutput* txout);
    TXOutput    deserialize(std::string& serialTXOutput);
}

/*
 * Transaction
 */
class Transaction {
public:
    // Coinbase Transaction
    Transaction(std::string to, std::string data);
    // UTXO Transaction
    Transaction(std::string from, std::string to, int amount, BlockChain* bc);
    // For serialization
    Transaction(CryptoProtobuf::Transaction* d_trans);
    void loadTransaction(CryptoProtobuf::Transaction* s_trans);
    bool isCoinbase();
    void printTransaction();

    std::string           id;
    std::vector<TXInput>  vin;
    std::vector<TXOutput> vout;
private:
    void setID();
};

namespace TransactionSerialize {
    std::string serialize(Transaction* transaction);
    Transaction deserialize(std::string& serialTransaction);
}

typedef Transaction CoinbaseTX;
typedef Transaction newUTXO;

#endif