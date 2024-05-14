#include "rsa.h"

#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <exception>

void RSA::generateKeys(BigInt& publicKey, BigInt& privateKey, BigInt& modulus, const int bitLenght) {
	BigInt p = generatePrime(bitLenght);
	BigInt q = generatePrime(bitLenght);

	modulus = p * q;

	BigInt phi = eulerFunc(p, q);

	BigInt e = 65537;

	privateKey = modInverse(e, phi);

	if (privateKey == -1)
		std::runtime_error("PrivateKey::Inverse doesn't exist");

	publicKey = e;
}

BigInt RSA::encrypt(BigInt& message, BigInt& publicKey, BigInt& modulus) {
	return modPow(message, publicKey, modulus);
}

BigInt RSA::decrypt(BigInt& cipher, BigInt& privateKey, BigInt& modulus) {
	return modPow(cipher, privateKey, modulus);
}

BigInt RSA::modPow(BigInt base, BigInt exponent, BigInt modulus) {
	BigInt result = 1;
	base %= modulus;

	while (exponent > 0) {
		if (exponent & 1)
			result = (result * base) % modulus;
		exponent >>= 1;
		base = (base * base) % modulus;
	}

	return result;
}

BigInt RSA::generatePrime(const int& bitLenght) {
	boost::random::mt19937 gen(std::random_device{}());

	boost::random::uniform_int_distribution<BigInt> dist(1, (BigInt(1) << bitLenght) - 1);

	BigInt num;
	do {
		num = dist(gen);
	} while (!miller_rabin_test(num, 20));

	return num;
}

BigInt RSA::eulerFunc(BigInt& p, BigInt& q) {
	return (p - 1) * (q - 1);
}

BigInt RSA::gcdExtended(BigInt a, BigInt b, BigInt* x, BigInt* y) {
	if (a == 0) {
		*x = 0, *y = 1;
		return b;
	}

	BigInt x1, y1;
	BigInt gcd = gcdExtended(b % a, a, &x1, &y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

BigInt RSA::modInverse(BigInt A, BigInt M) {
	BigInt x, y;
	BigInt g = gcdExtended(A, M, &x, &y);

	if (g != 1)
		return -1;
	else
		return (x % M + M) % M;
}
