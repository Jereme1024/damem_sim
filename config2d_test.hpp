#ifndef __CONFIG2D_TEST_HPP__
#define __CONFIG2D_TEST_HPP__

#include "config2d.hpp"

class Config2d_test
{
public:
	void main()
	{
		config2d qq = {2, 3};
		config2d &pp = qq;

		std::cout << "** same values\n";
		std::cout << "qq " << qq.height << ", " << qq.width << "\n";
		std::cout << "pp " << pp.height << ", " << pp.width << "\n";
	}
};

#endif
