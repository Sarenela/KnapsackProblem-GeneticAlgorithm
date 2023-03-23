#ifndef Exception_H
#define Exception_H
#include <iostream>
class Exception : public std::exception
{
public:
	Exception(const std::string& except);
	const char* what() const noexcept;
private:
	std::string exceptType;
};
#endif
//random device 