/*
    Just for studing
    Author: Tj
*/

#ifndef _STRINGUTIL_H_
#define _STRINGUTIL_H_

#include <string>
#include <vector>

// static class
class StringUtil
{
public:
    static void url_decode(std::string& str);
    static std::string url_encode(const std::string& str);
    static std::string url_encode_component(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char sep);
    static std::string strip(const std::string& str);
    static bool start_with(const std::string& str, const std::string& prefix);
    // this will filter any empty result
    static std::vector<std::string> split_filter_empty(const std::string& str, char sep);
};

#endif