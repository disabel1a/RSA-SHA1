#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <string>

using namespace boost::multiprecision;
using BigInt = boost::multiprecision::cpp_int;

class Signature {
public:
	static BigInt sign();
	static bool checkSignature();
private:
	static BigInt hexStringToBigInt(std::string hexString);
};