#ifndef PICTYPE_H
#define PICTYPE_H

#include<fstream>
#include<sstream>
#include<unordered_map>
#include<utility>
#include<string>
#include<optional>
#include<vector>
#include<iostream>
#include<chrono>
#include<iomanip>

namespace std {
    template<>
    class hash<pair<unsigned char, unsigned char>>
    {
    public:
        size_t operator()(const pair<unsigned char, unsigned char>& p) const {
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };
};

using filehead = std::pair<unsigned char, unsigned char>;

static const std::unordered_map<filehead, std::string> fileheadmap
{
    {filehead{0x42, 0x4D}, "bmp"},
    { filehead{0x47,0x49},"gif" },
    { filehead{0x89,0x50},"png" },
    { filehead{0xFF,0xD8},"jpg" },
    { filehead{0x49,0x49},"tif" },
    { filehead{0x00,0x00},"ico" }
};

static const std::unordered_map<std::string, std::string> base64map
{
    {"bmp","data:image/bmp;base64,"},
    {"gif","data:image/gif;base64,"},
    {"png","data:image/png;base64,"},
    {"jpg","data:image/jpeg;base64,"},
    {"tif","data:image/tiff;base64,"},
    {"ico","data:image/x-icon;base64,"}
};

inline std::optional<std::string> getpictype(const filehead& fh)
{
    auto it = fileheadmap.find(fh);
    if (it != fileheadmap.end())
        return it->second;
    return std::nullopt;
}

inline std::optional<filehead> getfilehead(const std::string& filename)
{
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs)
        return std::nullopt;
    char buf[2];
    ifs.read(buf, 2);
    ifs.close();
    return filehead{ buf[0],buf[1] };
}

inline std::optional<std::string> getpictype(const std::string& filename)
{
    auto fh = getfilehead(filename);
    if (!fh)
        return std::nullopt;
    return getpictype(*fh);
}



//pic2base64
// static const std::vector<char> base64char
// {
//     'A','B','C','D','E','F','G','H',
//     'I','J','K','L','M','N','O','P',
//     'Q','R','S','T','U','V','W','X',
//     'Y','Z','a','b','c','d','e','f',
//     'g','h','i','j','k','l','m','n',
//     'o','p','q','r','s','t','u','v',
//     'w','x','y','z','0','1','2','3',
//     '4','5','6','7','8','9','+','/'
// };

// static std::vector<char> decode_table;

// static const std::vector<int> mod_table{ 0,2,1 };

// inline unsigned char * base64_encode(const unsigned char * bindata, size_t binlength, size_t * base64length)
// {
//     unsigned char * base64;
//     size_t i, j;

//     *base64length = 4 * ((binlength + 2) / 3);

//     base64 = (unsigned char *)malloc(*base64length);
//     if (!base64) return nullptr;
//     if(!bindata) return nullptr;

//     for (i = 0, j = 0; i < binlength; )
//     {
//         uint32_t octet_a = i < binlength ? (unsigned char)bindata[i] : 0;
//         uint32_t octet_b = i  < binlength ? (unsigned char)bindata[i++] : 0;
//         uint32_t octet_c = i  < binlength ? (unsigned char)bindata[i++] : 0;

//         uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

//         base64[j++] = base64char[(triple >> 3 * 6) & 0x3F];
//         base64[j++] = base64char[(triple >> 2 * 6) & 0x3F];
//         base64[j++] = base64char[(triple >> 1 * 6) & 0x3F];
//         base64[j++] = base64char[(triple >> 0 * 6) & 0x3F];
//     }

//     for (i = 0; i < mod_table[binlength % 3]; i++)
//         base64[*base64length - 1 - i] = '=';

//     return base64;
// }

// inline unsigned char* base64_decode(const unsigned char* base64, size_t base64length, size_t* binlength)
// {
//     if(!decode_table.size())
//     {
//         decode_table.resize(256);
//         for (size_t i = 0; i < 64; i++)
//             decode_table[base64char[i]] = i;
//     }
//     unsigned char* bindata;
//     size_t i, j;

//     if (base64length % 4 != 0) return nullptr;

//     *binlength = base64length / 4 * 3;
//     if (base64[base64length - 1] == '=') (*binlength)--;
//     if (base64[base64length - 2] == '=') (*binlength)--;

//     bindata = (unsigned char*)malloc(*binlength);
//     if (!bindata) return nullptr;

//     for (i = 0, j = 0; i < base64length;)
//     {
//         uint32_t sextet_a = base64[i] == '=' ? 0 & i++ : base64char[base64[i++]];
//         uint32_t sextet_b = base64[i] == '=' ? 0 & i++ : base64char[base64[i++]];
//         uint32_t sextet_c = base64[i] == '=' ? 0 & i++ : base64char[base64[i++]];
//         uint32_t sextet_d = base64[i] == '=' ? 0 & i++ : base64char[base64[i++]];
//         uint32_t triple = (sextet_a << 3 * 6)
//             + (sextet_b << 2 * 6)
//             + (sextet_c << 1 * 6)
//             + (sextet_d << 0 * 6);

//         if (j < *binlength) bindata[j++] = (triple >> 2 * 8) & 0xFF;
//         if (j < *binlength) bindata[j++] = (triple >> 1 * 8) & 0xFF;
//         if (j < *binlength) bindata[j++] = (triple >> 0 * 8) & 0xFF;
//     }

//     return bindata;
// }


static const std::vector<char> encoding_table
{
    'A','B','C','D','E','F','G','H',
    'I','J','K','L','M','N','O','P',
    'Q','R','S','T','U','V','W','X',
    'Y','Z','a','b','c','d','e','f',
    'g','h','i','j','k','l','m','n',
    'o','p','q','r','s','t','u','v',
    'w','x','y','z','0','1','2','3',
    '4','5','6','7','8','9','+','/'
};

static std::vector<char> decoding_table;

static const std::vector<int> mod_table{ 0,2,1 };

unsigned char* base64_encode(const unsigned char *data, size_t input_length, size_t *output_length)
{
	*output_length = 4 * ((input_length + 2) / 3);
 
	unsigned char *encoded_data = (unsigned char*)malloc(*output_length);
	if (!encoded_data) return nullptr;
 
	for (int i = 0, j = 0; i < input_length;) {
		uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
		uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
		uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;
 
		uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
 
		encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
	}
 
	for (int i = 0; i < mod_table[input_length % 3]; i++)
		encoded_data[*output_length - 1 - i] = '=';
 
	return encoded_data;
}
 
inline unsigned char* base64_decode(const unsigned char *data, size_t input_length, size_t *output_length)
{
    if(!decoding_table.size())
    {
        decoding_table.resize(256);
        for (size_t i = 0; i < 64; i++)
            decoding_table[encoding_table[i]] = i;
    }
 
	if (input_length % 4 != 0) return NULL;
 
	*output_length = input_length / 4 * 3;
	if (data[input_length - 1] == '=') (*output_length)--;
	if (data[input_length - 2] == '=') (*output_length)--;
 
	unsigned char *decoded_data = (unsigned char*)malloc(*output_length);
	if (decoded_data == NULL) return NULL;
 
	for (int i = 0, j = 0; i < input_length;) {
		uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
		uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
		uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
		uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
 
		uint32_t triple = (sextet_a << 3 * 6)
			+ (sextet_b << 2 * 6)
			+ (sextet_c << 1 * 6)
			+ (sextet_d << 0 * 6);
 
		if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
		if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
		if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
	}
 
	return decoded_data;
}


inline std::string str2base64(const std::string& str)
{
    size_t base64length;
    auto base64 = base64_encode((unsigned char*)str.data(), str.size(), &base64length);
    std::string ret(base64, base64 + base64length);
    //free(base64);
    return ret;
}

inline std::string base642str(const std::string& base64)
{
    size_t binlength;
    auto bin = base64_decode((unsigned char *)base64.data(), base64.size(), &binlength);
    std::string ret(bin, bin + binlength);
    //free(bin);
    return ret;
}

inline std::string pic2base64(const std::string& filename)
{
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs)
        return "";
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    unsigned char buf[size];
    ifs.read((char*) buf, size);
    ifs.close();
    size_t base64length;
    auto base64 = base64_encode((unsigned char*)buf, size, &base64length);
    std::string ret(base64, base64 + base64length);
    //free(base64);
    return ret;
}

inline std::string pic2base64withtype(const std::string& filename)
{
    auto type = getpictype(filename);
    if (!type)
        return "";
    return base64map.at(*type) + pic2base64(filename);
}

inline std::string time2timestamp()
{
    auto tpmicro=std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
    time_t t = std::chrono::system_clock::to_time_t(tpmicro);
    return std::to_string(t);
}

inline std::string timestamp2time(time_t timestamp)
{
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

inline std::string timestamp2time(const std::string& timestamp)
{
    return timestamp2time(std::stoll(timestamp));
}

inline std::string reduceurl(const std::string& url)
{
    std::string ret;
    if (url.find("http://") == 0)
        ret = url.substr(7);
    else if (url.find("https://") == 0)
        ret = url.substr(8);
    else if(ret.find("www.")==0)
        ret=ret.substr(4);
    else
        ret = url;

    auto pos = ret.find("/");
    if (pos != std::string::npos)
        ret = ret.substr(0, pos);
    return ret;
}

// template<typename T>
// inline auto format(T&& t)->std::string
// {
//     std::ostringstream os;
//     os<<t;
//     return os.str();
// }

// template<typename... T>
// inline auto format(const std::string& fmt, T&&... args)->std::string
// {
//     //return fmt+format(args...);
//     std::vector<std::string> vec{format(std::forward<T>(args))...};
//     constexpr size_t n=sizeof...(T);
//     std::ostringstream os;
//     for(size_t i=0;i<fmt.size();++i)
//     {
//        if(fmt[i]=='{')
//        {
//            size_t j=i+1;
//            while(j<fmt.size()&&fmt[j]!='}') ++j;
//            if(j==fmt.size()) throw std::runtime_error("format error");
//            std::string num;
//            if(j==i+1) num="0";
//            else num=fmt.substr(i+1,j-i-1);
//            //if(num.empty()) throw std::runtime_error("format error");
//            size_t idx=std::stoi(num);
//            if(idx>=n) throw std::runtime_error("format error");
//             os<<vec[idx];
//             i=j;
//        }
//        else if(fmt[i]=='}')
//        {
//               throw std::runtime_error("format error");
//        }
//        else os<<fmt[i];
//     }
//     return os.str();
// }

#endif // PICTYPE_H
