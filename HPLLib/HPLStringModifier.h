#ifndef _HPL_STRING_MODIFIER_
#define _HPL_STRING_MODIFIER_

#include <string>
#include <vector>

namespace hpl{
namespace string{
    /**
	    •¶Žš—ñ‚Ì•ªŠ„
    */
    std::vector<std::string> Split( std::string src, const char* key);

    /*
    */
    std::string appendFrontString(std::string &src,
                                           int power,
                                           std::string& appender);

    /**
        ƒtƒ@ƒCƒ‹‚©‚ç“Ç‚Ý‚±‚Ý
        @return vector<string>
    */
    std::vector<std::string> loadFromFile(const char* path);
};
};

#endif
