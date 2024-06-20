#pragma once

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define FunLoc (std::string(__FILE__) + ":"  + TOSTRING(__LINE__) + \
				":0: function: " + __FUNCTION__)
