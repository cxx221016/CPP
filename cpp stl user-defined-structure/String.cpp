#include <cstring>

class String
{
    char *str;
    size_t len;
    size_t capacity;
    inline static constexpr size_t default_capacity = 36;

    void base_init()
    {
        this->len = 0;
        this->capacity = default_capacity;
        str = new char[this->capacity];
    }

    void update_capacity()
    {
        auto tmp = new char[this->capacity];
        strcpy(tmp, this->str);
        delete[] this->str;
        this->str = tmp;
    }

    void double_space()
    {
        this->capacity = 2 * this->capacity;
        update_capacity();
    }

public:
    using iterator = char *;
    using const_iterator = const char *;
    iterator begin()
    {
        return str;
    }

    iterator end()
    {
        return str + this->len;
    }

    const_iterator begin() const
    {
        return str;
    }

    const_iterator end() const
    {
        return str + this->len;
    }

    String(const char *ano = nullptr)
    {
        if (ano == nullptr)
        {
            base_init();
        }
        this->len = strlen(ano);
        this->capacity = 2 * (this->len + 1);
        str = new char[this->len + 1];
        strcpy(this->str, ano);
    }

    String(const String &ano)
    {
        this->len = ano.len;
        str = new char[this->len + 1];
        strcpy(this->str, ano.str);
    }

    String(String &&ano)
    {
        this->len = ano.len;
        this->str = ano.str;
        ano.base_init();
    }

    String &operator=(const String &ano)
    {
        if (this != &ano)
        {
            delete[] this->str;
            this->str = new char[ano.capacity];
            strcpy(this->str, ano.str);
        }
        return *this;
    }

    ~String()
    {
        delete[] this->str;
        this->len = 0;
    }

    char &operator[](const size_t &idx)
    {
        return this->str[idx];
    }

    const char &operator[](const size_t &idx) const
    {
        return this->str[idx];
    }

    String &operator+=(const String &ano)
    {
        return *this;
    }
};

#include <iostream>

int main()
{
    const char *s = "hello";
    auto p = s;
    // for (int i = 0; i < 5; ++i)
    // {
    //     std::cout << *p++;
    // }

    std::cout << strlen(s) << std::endl;

    char *tmp = new char[10];
    strcpy(tmp, s);
    delete[] tmp;

    std::cout << tmp << std::endl;
    system("pause");
    return 0;
}