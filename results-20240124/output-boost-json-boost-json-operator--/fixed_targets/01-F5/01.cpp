#include <boost/json.hpp>
#include <iostream>

extern "C" {
std::istream * boost::json::operator>>(std::istream * is, boost::json::value * jv) {
    error_code ec;
    *jv = parse(*is, ec);
    if (ec) {
        is->setstate(std::ios_base::failbit);
    }
    return is;
}
}