#include <pwgen/pwgen.hpp>
#include <sstream>

namespace pwgen::flags {
	const uint8_t
		ALL				= 0b00001111,
		DEFAULT			= flags::DIGITS | flags::LOWER_ASCII | flags::UPPER_ASCII,
		DIGITS			= 0b00000100,
		LOWER_ASCII		= 0b00000010,
		NONE			= 0b00000000,
		UPPER_ASCII		= 0b00000001,
		SPECIAL_SYMBOLS = 0b00001000;
}

namespace pwgen {
	pwgen::pwgen() {
		fs = flags::DEFAULT;
		init();
	}
	pwgen::pwgen(uint8_t fs, std::string exclude, std::string include) {
		this->fs = fs & flags::ALL;
		this->exclude = exclude;
		this->include = include;
		init();
	}
	pwgen::~pwgen() {
		
	}
	void pwgen::init() {
		gen = std::mt19937(rd());
	}
	pwgen& pwgen::set_flags(uint8_t fs) {
		this->fs = fs & flags::ALL;
		return *this;
	}
	std::string pwgen::generate(uint32_t len) {
		return this->generate(len, fs);
	}
	std::string pwgen::generate(uint32_t len, uint8_t fs) {
		if(!len) {
			return "";
		}
		std::stringstream ss;
		std::string kit;
		if(fs & flags::DIGITS)			{ kit += "0123456789"; }
		if(fs & flags::LOWER_ASCII)		{ kit += "abcdefghijklmnopqrstuvwxyz"; }
		if(fs & flags::UPPER_ASCII)		{ kit += "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; }
		if(fs & flags::SPECIAL_SYMBOLS)	{ kit += "!@#$%^&*()"; }
		for(char c : include) {
			if(kit.find(c) != std::string::npos) {
				continue;
			}
			kit += c;
		}
		for(char c : exclude) {
			std::string::size_type pos = 0;
			while((pos = kit.find(c)) != std::string::npos) {
				kit.erase(pos, 1);
			}
		}
		for(char c : kit) {
			std::string::size_type pos = 0, pos2 = 0;
			while((pos = kit.find(c)) != (pos2 = kit.rfind(c))) {
				kit.erase(pos2, 1);
			}
		}
		std::string::size_type kitlen = kit.length();
		if(!kitlen) {
			return generate(len, flags::DEFAULT);
		}
		for(uint32_t i = 0; i < len; i++) {
			ss << kit[gen() % kitlen];
		}
		return ss.str();
	}
}