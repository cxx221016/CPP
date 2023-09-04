#include <iostream>
#include<variant>
#include<vector>
#include<map>
#include<unordered_map>
#include<optional>
#include<string>
#include<fstream>
#include <sstream>
//#include<unordered_map>

namespace json
{
    struct Node;
    using Null=std::monostate;
    using Bool=bool;
    using Int=long long int;
    using Float=double;
    using String=std::string;
    using Array=std::vector<Node>;
    using Object=std::map<std::string,Node>;
    using Value=std::variant<Null,Bool,Int,Float,String,Array,Object>;

    struct Node
    {
        Value value;
        Node():value(Null{}){}
        Node(Value value):value(value){}

        auto& operator[](const std::string& key)
        {
            if(auto object=std::get_if<Object>(&value))
            {
                return (*object)[key];
            }
            else
            {
                throw std::runtime_error("Not an object");
            }
        }

        auto operator[](size_t index)
        {
            if(auto array=std::get_if<Array>(&value))
            {
                return (*array)[index];
            }
            else
            {
                throw std::runtime_error("Not an array");
            }
        }

        void push(const Node& rhs)
        {
            if(auto array=std::get_if<Array>(&value))
            {
                array->push_back(rhs);
            }
            else
            {
                throw std::runtime_error("Not an array");
            }
        }
    };

    struct JsonParser
    {
        std::string_view json_str;
        size_t pos=0;

        void parse_whitespace()
        {
            while(pos<json_str.size() && std::isspace(json_str[pos]))
            {
                pos++;
            }
        }

        auto parse_null()->std::optional<Value>
        {
            if(json_str.substr(pos,4)=="null")
            {
                pos+=4;
                return Null{};
            }
            return {};
        }

        auto parse_true()->std::optional<Value>
        {
            if(json_str.substr(pos,4)=="true")
            {
                pos+=4;
                return true;
            }
            return {};
        }

        auto parse_false()->std::optional<Value>
        {
            if(json_str.substr(pos,5)=="false")
            {
                pos+=5;
                return false;
            }
            return {};
        }

        auto parse_number()->std::optional<Value>
        {
            size_t endpos=pos;
            while(endpos<json_str.size()&& (std::isdigit(json_str[endpos])||json_str[endpos]=='.'||json_str[endpos]=='e'||json_str[endpos]=='E'))
            {
                endpos++;
            }
            std::string number_str=static_cast<std::string>(json_str.substr(pos,endpos-pos));
            pos=endpos;
            static auto is_Float=[](std::string& number_str)
            {
                return number_str.find('.')!=std::string::npos||number_str.find('e')!=std::string::npos||number_str.find('E')!=std::string::npos;
            };

            if(is_Float(number_str))
            {
                try{
                    Float res=std::stod(number_str);
                    return res;
                }
                catch(...)
                {
                    return {};
                }
            }
            else
            {
                try{
                    Int res=std::stol(number_str);
                    return res;
                }
                catch(...)
                {
                    return {};
                }
            }
        }

        auto parse_string()->std::optional<Value>
        {
            pos++;
            size_t endpos=pos;
            while(endpos<json_str.size() && json_str[endpos]!='"')
            {
                endpos++;
            }
            std::string string_str=static_cast<std::string>(json_str.substr(pos,endpos-pos));
            pos=endpos+1;
            return string_str;
        }

        auto parse_value()->std::optional<Value>
        {
            parse_whitespace();
            switch(json_str[pos])
            {
                case 'n':return parse_null();
                case 't':return parse_true();
                case 'f':return parse_false();
                case '"':return parse_string();
                case '[':return parse_array();
                case '{':return parse_object();
                default:return parse_number();
            }
        }

        auto parse_array()->std::optional<Value>
        {
            pos++;
            Array array;
            while(pos<json_str.size() && json_str[pos]!=']')
            {
                auto value=parse_value();
                array.push_back(value.value());
                parse_whitespace();
                if(pos<json_str.size()  &&json_str[pos]==',')
                {
                    pos++;
                }
                parse_whitespace();
            }
            pos++;
            return array;
        }

        auto parse_object()->std::optional<Value>
        {
            pos++;
            Object object;
            while(pos<json_str.size() && json_str[pos]!='}')
            {
                auto key=parse_value();
                parse_whitespace();
                if(!std::holds_alternative<String>(key.value()))
                {
                    return {};
                }
                if(pos<json_str.size() && json_str[pos]==':')
                {
                    pos++;
                }
                parse_whitespace();
                auto val=parse_value();
                object[std::get<String>(key.value())]=val.value();
                parse_whitespace();
                if(pos<json_str.size() && json_str[pos]==',')
                {
                    pos++;
                }
                parse_whitespace();
            }
            pos++;
            return object;
        }

        auto parse()->std::optional<Node>
        {
            parse_whitespace();
            auto value=parse_value();
            if(value)
            {
                return Node(value.value());
            }
            return {};
        }

    };

    auto parser(const std::string_view& json_str)->std::optional<Node>
    {
        JsonParser parser{json_str};
        return parser.parse();
    }

    class JsonGenerator
    {
        friend inline auto generate(const Node& node)->std::string;
        friend auto  operator << (std::ostream& out, const Node& t) ->std::ostream&;
    private:
        static auto generate(const Node& node)->std::string
        {
            return std::visit(
                [](auto&& arg)->std::string
                {
                    using T=std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T,Null>)
                    {
                        return "null";
                    }
                    else if constexpr(std::is_same_v<T,Bool>)
                    {
                        return arg?"true":"false";
                    }
                    else if constexpr(std::is_same_v<T,Int>)
                    {
                        return std::to_string(arg);
                    }
                    else if constexpr(std::is_same_v<T,Float>)
                    {
                        return std::to_string(arg);
                    }
                    else if constexpr(std::is_same_v<T,String>)
                    {
                        return generate_string(arg);
                    }
                    else if constexpr(std::is_same_v<T,Array>)
                    {
                        return generate_array(arg);
                    }
                    else if constexpr(std::is_same_v<T,Object>)
                    {
                        return generate_object(arg);
                    }
                },

            node.value);
        }

        static auto generate_string(const String& str)->std::string
        {
            std::string json_str="\"";
            json_str+=str;
            json_str+="\"";
            return json_str;
        }

        static auto generate_array(const Array& array)->std::string
        {
            std::string json_str="[";
            for(const auto& value:array)
            {
                json_str+=generate(value);
                json_str+=",";
            }
            if(!array.empty())
            {
                json_str.pop_back();
            }
            json_str+="]";
            return json_str;
        }

        static auto generate_object(const Object& object)->std::string
        {
            std::string json_str="{";
            for(const auto& [key,value]:object)
            {
                json_str+=generate_string(key);
                json_str+=":";
                json_str+=generate(value);
                json_str+=",";
            }
            if(!object.empty())
            {
                json_str.pop_back();
            }
            json_str+="}";
            return json_str;
        }

    };

    std::string getLevelStr(int level)
    {
	    std::string levelStr = "";
	    for (int i = 0; i < level; i++)
	    {
		    levelStr += "\t"; //这里可以\t换成你所需要缩进的空格数
	    }
	    return levelStr;

    }

    std::string formatJson(const std::string& json)
    {
	    std::string result = "";
	    int level = 0;
	    for (std::string::size_type index = 0; index < json.size(); index++)
	    {
		    char c = json[index];

		    if (level > 0 && '\n' == json[json.size() - 1])
		    {
		    	result += getLevelStr(level);
		    }

		    switch (c)
		    {
		    case '{':
		    case '[':
		    	result = result + c + "\n";
		    	level++;
		    	result += getLevelStr(level);
		    	break;
		    case ',':
			    result = result + c + "\n";
			    result += getLevelStr(level);
			    break;
		    case '}':
		    case ']':
			    result += "\n";
			    level--;
			    result += getLevelStr(level);
			    result += c;
			    break;
		    default:
			    result += c;
			    break;
		    }

	    }
	    return result;
    }




    
    inline auto generate(const Node& node)->std::string
    {
        return formatJson(JsonGenerator::generate(node));
    }

    auto  operator << (std::ostream& out, const Node& t) ->std::ostream& {
        out <<formatJson(JsonGenerator::generate(t));
        return out;
    }

}

using namespace std::string_literals;

using namespace json;
int main()
{
    std::ifstream fin("D:/MY_CODE/CPP/cpp stl user-defined-structure/test.json");
    std::ofstream fout("D:/MY_CODE/CPP/cpp stl user-defined-structure/testout.json");
    std::stringstream ss;
    ss<<fin.rdbuf();
    std::string s{ss.str()};
    try 
    {
        auto x=parser(s).value();
        //std::string name="name";
        //std::cout<<x[name]<<std::endl;
        auto usr=x["usrinfos"];
        std::cout<<usr[0]["name"]<<std::endl;
        std::string res=generate(x);
        ss.str(res);
        fout<<ss.rdbuf()<<std::flush;
    }
    catch(std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    system("pause");
    
    return 0;
}