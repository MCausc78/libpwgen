#ifndef CXX_LIBPWGEN_PWGEN_HPP
#define CXX_LIBPWGEN_PWGEN_HPP 1

#include <cstdint>
#include <random>

namespace pwgen::flags {
	extern const uint8_t
		ALL,
		DEFAULT,
		DIGITS,
		LOWER_ASCII,
		NONE,
		UPPER_ASCII,
		SPECIAL_SYMBOLS;
}

namespace pwgen {
	class pwgen {
	private:
		std::random_device rd;
		std::mt19937 gen;
		uint8_t fs;
		std::string exclude, include;
		void init();
	public:
		pwgen();
		pwgen(uint8_t, std::string = "", std::string = "");
		virtual ~pwgen();
		pwgen& set_flags(uint8_t);
		std::string generate(uint32_t);
		std::string generate(uint32_t, uint8_t);
	};
}
#endif /* CXX_LIBPWGEN_PWGEN_HPP */