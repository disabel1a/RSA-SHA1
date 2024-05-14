#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "rsa.h"
#include "sha1.h"
#include "wiener.h"

void checkWiener() {
    BigInt publicKey = 17993, privateKey = 5, modulus = 90581;
    //RSA::generateKeys(publicKey, privateKey, modulus, bitLenght);

    std::cout << "[" << std::endl;
    std::cout << "Public key: " << publicKey << std::endl;
    std::cout << "Private key: " << privateKey << std::endl;
    std::cout << "Modulus: " << modulus << std::endl;
    std::cout << "]" << std::endl;

	BigInt message = 5678;
	std::cout << "Message: " << message << std::endl;

	BigInt cipher = RSA::encrypt(message, publicKey, modulus);
	std::cout << "Encrypted: " << cipher << std::endl;

	BigInt decrypt = RSA::decrypt(cipher, privateKey, modulus);
	std::cout << "Decrypted: " << decrypt << std::endl;						

}

int main() {
	int bitLenght = 512;
	BigInt publicKey, privateKey, modulus;
	RSA::generateKeys(publicKey, privateKey, modulus, bitLenght);

	std::cout << "[" << std::endl;
	std::cout << "Public key: " << publicKey << std::endl;
	std::cout << "Private key: " << privateKey << std::endl;
	std::cout << "Modulus: " << modulus << std::endl;
	std::cout << "]" << std::endl;

	//	-------------------------------- Cipher --------------------------------------

	BigInt message = 123321;
	std::cout << "Message: " << message << std::endl;

	BigInt cipher = RSA::encrypt(message, publicKey, modulus);
	std::cout << "Encrypted: " << cipher << std::endl;

	BigInt decrypt = RSA::decrypt(cipher, privateKey, modulus);
	std::cout << "Decrypted: " << decrypt << std::endl;

	//	------------------------------- Signature ------------------------------------

	std::string filePath = "C:/Users/ivmak/OneDrive/Рабочий стол/БД вариант.txt";
	std::string hash = SHA1::from_file(filePath);
	
	std::cout << std::endl << "Hash (HEX): " << hash << std::endl;

	std::stringstream ss;
	ss << std::hex << hash;

	BigInt value;

	ss >> value;
	std::cout << "Hash (DEC): "  << value << std::endl;

	BigInt cipher = RSA::encrypt(value, privateKey, modulus);

	std::cout << std::endl << "Encrypted Hash (DEC): " << cipher << std::endl << std::endl;

	BigInt decipher = RSA::decrypt(cipher, publicKey, modulus);

	std::cout << "Decrypted Hash (DEC): " << decipher << std::endl;
	

	/*wiener();
	checkWiener();*/
}
