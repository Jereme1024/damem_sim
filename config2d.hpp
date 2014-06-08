#ifndef __CONFIG2D_HPP__
#define __CONFIG2D_HPP__

struct config2d
{
	const int height;
	const int width;

	config2d(const int h, const int w) : height(h), width(w)
	{}

	config2d(config2d &c) : height(c.height), width(c.width)
	{}
};

#endif
