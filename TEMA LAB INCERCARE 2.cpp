#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;
class Transaction {
private:
	string txSender;
	string txRecipient;
	double txQuantity;
public:
	Transaction(string sender="", string recipient="", double quantity=0) {
		txSender = sender;
		txRecipient = recipient;
		txQuantity = quantity;
	}
	string getTxSender() { return txSender; }
	string getTxRecipient() { return txRecipient; }
	double getTxQuantity() { return txQuantity; }
};

class CryptoBlock {
private:
	Transaction tx{};
	string calculateHash() {
		hash<string> str_hash;
		return to_string(str_hash(timeStamp + previousBlockHash
			+ getTx().getTxSender() + getTx().getTxRecipient()
			+ to_string(getTx().getTxQuantity())));
	}
	string now() {
		time_t t = time(0);
		string str = ctime(&t);
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		return str;
	}
	int index;
	string timeStamp = now();
	string previousBlockHash{};
	string blockHash = calculateHash();

public:
	CryptoBlock(int ix, string prevHash, string sender, string recipient, double quantity) {
		static int ixe = 0;
		ixe++;
		index = ixe;
		previousBlockHash = prevHash;
		cout << "PREVIUS BLOCK HASH DEBUG: " << previousBlockHash << endl;
		tx = Transaction(sender, recipient, quantity);
	}
	int getIndex() { return index; }
	string getTimeStamp() { return timeStamp; }
	string getPreviousBlockHash() { return previousBlockHash; }
	string getBlockHash() { return blockHash; }
	Transaction getTx() { return tx; }
};

class CryptoBlockchain {
private:
	vector<CryptoBlock> chain;
	string getLastHash() { return (chain.at(getLastIndex()-1)).getBlockHash();}
	int getLastIndex() { return chain.size(); }
public:
	
	CryptoBlockchain() {
		CryptoBlock block0(0, "0", "", "", 0);
		chain.push_back(block0);
	}

	void addNewBlock(string sender, string recipient, double quantity) {	
		cout << "DEBUG BLOCK HASH: " << getLastHash() << endl;
		CryptoBlock* block = new CryptoBlock(getLastIndex(), getLastHash(), sender, recipient, quantity);
		chain.push_back(*block);
	}
	vector<CryptoBlock> getChain() { return chain; }
};

ostream& operator<<(ostream& o, CryptoBlock b) {
	o << "{" << endl;
	o << "  BlockId: " << b.getIndex()-1<<"," << endl;
	o << "  Time_Stamp: " << b.getTimeStamp() << "," << endl;
	o << "  Previous_Block_Hash: " << b.getPreviousBlockHash() << "," << endl;
	o << "  Block_Hash: " << b.getBlockHash() << "," << endl;
	o << "  Sender: " << b.getTx().getTxSender() << "," << endl;
	o << "  Recipient: " << b.getTx().getTxRecipient() << "," << endl;
	o << "  Quantity: " << b.getTx().getTxQuantity() << endl;
	o << "}," << endl;
	return o;
}
ostream& operator<<(ostream& o, CryptoBlockchain bc) {
	for (int i = 0; i < bc.getChain().size(); i++) {
		o << bc.getChain().at(i);
	}
	return o;
}

int main()
{
	CryptoBlockchain myChain;
	myChain.addNewBlock("John", "Bob", 10);
	myChain.addNewBlock("Bob", "Sandra", 15.5);
	cout << myChain;

	return 0;
}

