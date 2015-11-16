#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <chrono>

/* example use:
#include <iostream>

#include "Random.hpp"

int main()
{
	std::cout << math::rand(0, 10) << '\n';
	std::cout << math::rand(-0.5, 0.5) << '\n';
	
	return 0;
}
*/

namespace math
{
	class Random
	{
		public:
			template<typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
			T operator()(T low, T high)
			{
				return std::uniform_int_distribution<T>(low, high)(generator);
			}
			
			template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
			T operator()(T low, T high)
			{
				return std::uniform_real_distribution<T>(low, high)(generator);
			}
			
		private:
			friend Random& get();
			
			Random() = default;
			
			static Random rand;
			static std::mt19937 generator;
	};
	
	extern Random& rand;
}

#endif
