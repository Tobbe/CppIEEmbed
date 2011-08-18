#ifndef _URL_CODE_H__
#define _URL_CODE_H__

/*
 * Original C-code can be found here: http://www.geekhideout.com/urlcode.shtml
 */

#include <string>

class UrlCode {
private:
	static char FromHex(char ch); // Converts a hex character to its integer value
	static char ToHex(char code); // Converts an integer value to its hex character
public:
	static std::string Decode(std::string url);
	static std::string Encode(std::string url);
};
#endif