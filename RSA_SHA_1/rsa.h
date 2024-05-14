#pragma once

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
using BigInt = boost::multiprecision::cpp_int;

class RSA {
public:
	static void generateKeys(BigInt& publicKey, BigInt& privateKey, BigInt& modulus, int bitLenght);

	static BigInt encrypt(BigInt& message, BigInt& publicKey, BigInt& modulus);
	static BigInt decrypt(BigInt& cipher, BigInt& privateKey, BigInt& modulus);

private:
	static BigInt modPow(BigInt base, BigInt exponent, BigInt modulus);
	static BigInt generatePrime(const int& bitLenght);
	static BigInt eulerFunc(BigInt& p, BigInt& q);

	static BigInt gcdExtended(BigInt a, BigInt b, BigInt* x, BigInt* y);
	static BigInt modInverse(BigInt A, BigInt M);
};