#pragma once

#include <iostream>


class ITexture
{
private:
	virtual void generate() = 0;
public:
	virtual unsigned int getid() = 0;
	virtual int getwidth() = 0;
	virtual int getheight() = 0;
	virtual void setfiltering(int flag) = 0;

};