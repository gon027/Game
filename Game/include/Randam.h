#ifndef RANDAM_H
#define RANDAM_H

#include <random>

namespace gnGame {

	namespace Randama {

		namespace {
			std::random_device rDevice;
			std::mt19937 mt{ rDevice() };
		}

		int getRandomRange(int _min, int _max) {
			std::uniform_int_distribution<> dist(_min, _max);
			return dist(mt);
		}
	}
}

#endif // !RANDAM_H