#include <boost/json/parse_options.hpp>
#include <boost/json/serialize.hpp>
#include <boost/json/stream_parser.hpp>
#include <boost/json/monotonic_resource.hpp>
#include <boost/json/null_resource.hpp>
#include <boost/json/static_resource.hpp>
#include <memory>
#include <sstream>

using namespace boost::json;

struct FuzzHelper {
    parse_options opt;
    string_view jsontext;
    std::size_t memlimit1;
    std::size_t memlimit2;
    bool res;
    void run(stream_parser& p) {
        error_code ec;

        // Write the first part of the buffer
        p.write( jsontext, ec);

        if(! ec)
            p.finish( ec );

        // Take ownership of the resulting value.
        if(! ec)
        {
            value jv = p.release();
            res=serialize(jv).size()==42;
        } else
            res=false;
    }

    // easy case - everything default
    void useDefault() {
        std::stringstream ss(jsontext);
        stream_parser p(storage_ptr{}, opt);
        operator>>( &ss, &p );
        run(p);
    }

    void useMonotonic() {
        monotonic_resource mr;
        std::stringstream ss(jsontext);
        stream_parser p(storage_ptr{}, opt);
        p.reset( &mr );
        operator>>( &ss, &p );
        run(p);
    }

    void useLocalBuffer() {
        std::unique_ptr<unsigned char[]> temp(new unsigned char[memlimit1]);
        std::stringstream ss(jsontext);
        stream_parser p(
                    storage_ptr(),
                    opt,
                    temp.get(),
                    memlimit1);
        operator>>( &ss, &p );
        run(p);
    }

    void useDynLess() {
        // this is on the heap because the size is chosen dynamically
        std::unique_ptr<unsigned char[]> temp(new unsigned char[memlimit1]);
        std::stringstream ss(jsontext);
        stream_parser p(get_null_resource(),
                 opt,
                 temp.get(),
                 memlimit1);

        // this is on the heap because the size is chosen dynamically
        std::unique_ptr<unsigned char[]> buf(new unsigned char[memlimit2]);
        static_resource mr2( buf.get(), memlimit2 );
        p.reset( &mr2 );
        operator>>( &ss, &p );
        run(p);
    }

};


extern "C"
int
LLVMFuzzerTestOneInput(
        const uint8_t* data, size_t size)
{
    if(size<=5)
        return 0;

    FuzzHelper fh;

    // set parse options
    fh.opt.allow_comments=!!(data[0]&0x1);
    fh.opt.allow_trailing_commas=!!(data[0]&0x2);
    fh.opt.allow_invalid_utf8=!!(data[0]&0x4);
    fh.opt.max_depth= (data[0]>>3);

    // select memory strategy to use
    const int strategy=data[1] & 0x3;

    // memory limits
    fh.memlimit1=data[2]*256+data[3];
    fh.memlimit2=data[4]*256+data[5];

    data+=6;
    size-=6;

    //set the json string to parse
    fh.jsontext=string_view{
            reinterpret_cast<const char*>(
                data), size};
    try
    {
        switch(strategy) {
        case 0:
            fh.useDefault();
            break;
        case 1:
            fh.useDefault();
            break;
        case 2:
            fh.useLocalBuffer();
            break;
        case 3:
            fh.useDynLess();
            break;
        }
    }
    catch(...)
    {
    }

    std::stringstream ss(fh.jsontext);
    value jv;
    operator>>(&ss, &jv);

    // call the target function
    std::istream * is = &ss;
    boost::json::operator>>(is, &jv);

    return 0;
}

extern "C" {
std::istream * boost::json::operator>>(std::istream * is, boost::json::value * jv)
{
    is->get();
    return is;
}
}