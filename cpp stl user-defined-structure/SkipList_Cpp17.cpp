#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <type_traits>
#include <sstream>
#include <chrono>

template <typename Key, typename V, typename Comp = std::less<Key>,
          typename = std::enable_if_t<std::is_default_constructible_v<Key> and std::is_default_constructible_v<V>>,
          typename = std::void_t<decltype(std::declval<Key>() == std::declval<Key>())>>
class SkipList
{
private:
    struct SkipListNode
    {
        const Key key;
        V value;
        int level;
        std::vector<SkipListNode *> forward;
        SkipListNode(Key key, V value, int level, SkipListNode *nxt = nullptr)
            : key(key), value(value), forward(level, nxt) {}
        SkipListNode() : key(Key()), value(V()), level(MAX_LEVEL), forward(MAX_LEVEL, nullptr) {}
        bool operator==(const SkipListNode &b) const { return key == b.key && value == b.value; }
        bool operator!=(const SkipListNode &b) const { return !(*this == b); }
    };
    typedef SkipListNode node;
    typedef SkipListNode *node_ptr;
    typedef Key key_type;
    typedef V value_type;
    typedef Comp key_compare;

    class iterator
    {

    private:
        node_ptr p;

    public:
        typedef std::input_iterator_tag iterator_category;
        typedef node value_type;
        typedef ptrdiff_t difference_type;
        typedef node *pointer;
        typedef node &reference;
        typedef iterator self;
        iterator(node_ptr _p = nullptr) : p(_p) {}
        iterator(const iterator &it) : p(it.p) {}
        iterator &operator=(const iterator &it)
        {
            p = it.p;
            return *this;
        }
        reference operator*() const { return *p; }
        pointer operator->() const { return p; }
        self &operator++()
        {
            p = p->forward[0];
            return *this;
        }
        self operator++(int)
        {
            self tmp = *this;
            p = p->forward[0];
            return tmp;
        }
        bool operator==(const self &it) const { return p == it.p; }
        bool operator!=(const self &it) const { return p != it.p; }
    };

private:
    int level;
    node_ptr head, tail;
    key_compare less;
    size_t length;
    inline static const int MAX_LEVEL = 32;
    inline static const double P_FACTOR = 0.25;

    static int random_level()
    {
        int lv = 1;
        static std::default_random_engine e(time(nullptr));
        static std::uniform_real_distribution<double> u(0, 1);
        while (u(e) < P_FACTOR && lv < MAX_LEVEL)
            ++lv;
        return lv;
    }

    node_ptr findimpl(const Key &key, std::vector<node_ptr> &prev) const
    {
        node_ptr p = head;
        for (int i = level - 1; i >= 0; --i)
        {
            while (p->forward[i] != tail && less(p->forward[i]->key, key))
                p = p->forward[i];
            prev[i] = p;
        }
        p = p->forward[0];
        return p;
    }

public:
    SkipList() : level(0), head(new node()), tail(new node()), length(0), less(Comp())
    {
        for (int i = 0; i < MAX_LEVEL; ++i)
            head->forward[i] = tail;
        tail->forward.resize(0);
    }

    SkipList(const key_compare &cmp) : level(0), head(new node()), tail(new node()), less(cmp), length(0)
    {
        for (int i = 0; i < MAX_LEVEL; ++i)
            head->forward[i] = tail;
        tail->forward.resize(0);
    }

    void insert(const Key &_key, const V &_value)
    {
        std::vector<node_ptr> prev(MAX_LEVEL, head);
        node_ptr p = findimpl(_key, prev);
        if (p != tail && p->key == _key)
        {
            p->value = _value;
            return;
        }
        int lv = random_level();
        this->level = std::max(this->level, lv);
        node_ptr newnode = new node(_key, _value, lv);
        for (int i = 0; i < lv; ++i)
        {
            newnode->forward[i] = prev[i]->forward[i];
            prev[i]->forward[i] = newnode;
        }
        ++length;
    }

    bool erase(const Key &_key)
    {
        std::vector<node_ptr> prev(MAX_LEVEL, nullptr);
        node_ptr p = findimpl(_key, prev);
        if (p == tail || p->key != _key)
            return false;
        for (int i = 0; i < level; ++i)
        {
            if (prev[i]->forward[i] != p)
                break;
            prev[i]->forward[i] = p->forward[i];
        }
        delete p;
        while (level > 0 && head->forward[level - 1] == tail)
            --level;
        --length;
        return true;
    }

    iterator begin() const { return iterator(head->forward[0]); }
    iterator end() const { return iterator(tail); }

    iterator find(const Key &_key) const
    {
        std::vector<node_ptr> prev(MAX_LEVEL, nullptr);
        node_ptr p = findimpl(_key, prev);
        if (p == tail || p->key != _key)
            return end();
        return iterator(p);
    }

    bool count(const Key &_key) const
    {
        std::vector<node_ptr> prev(MAX_LEVEL, nullptr);
        node_ptr p = findimpl(_key, prev);
        if (p == tail || p->key != _key)
            return false;
        return true;
    }

    size_t size() const { return length; }

    bool empty() const { return length == 0; }

    int getlevel() const { return level; }
};

class SkipListManager
{
private:
    SkipListManager() = delete;
    ~SkipListManager() = delete;

public:
    template <typename K, typename V, typename Comp>
    static void load(SkipList<K, V, Comp> &list, const std::string &filepath)
    {
        std::ifstream in(filepath);
        if (!in)
            throw std::runtime_error("open file failed");
        std::string line;
        while (std::getline(in, line))
        {
            std::istringstream iss(line);
            K key;
            V value;
            iss >> key >> value;
            list.insert(key, value);
        }
        in.close();
    };
    template <typename K, typename V, typename Comp>
    static void save(const SkipList<K, V, Comp> &list, const std::string &filepath)
    {
        std::ofstream out(filepath);
        if (!out)
            throw std::runtime_error("open file failed");
        for (auto it = list.begin(); it != list.end(); it++)
        {
            out << it->key << " " << it->value << std::endl;
        }
        out.close();
    };
};

struct SkipListTest
{
    template <typename K, typename V>
    static void test(int counts, bool israndom = false)
    {
        static std::default_random_engine e(time(nullptr));
        static std::uniform_int_distribution<int> u(0, counts);
        auto list = SkipList<K, V>();
        std::vector<K> keys;
        if constexpr (std::is_same_v<K, std::string>)
        {
            std::vector<std::string> strlist{"xccc", "dfsf", "ergetgt", "4dfsgg"};
            for (int i = 0; i < counts; i++)
            {
                K key;
                if (israndom)
                    key = strlist[u(e) % 4];
                else
                    key = strlist[i % 4];
                keys.push_back(key);
            }
        }
        else if constexpr (std::is_same_v<K, int>)
        {
            for (int i = 0; i < counts; i++)
            {
                K key;
                if (israndom)
                    key = u(e);
                else
                    key = i;
                keys.push_back(key);
            }
        }
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        std::chrono::milliseconds d;
        {
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            for (int i = 0; i < counts; i++)
            {
                list.insert(keys[i], V());
                // if (i % 50000 == 0)
                //     std::cout << "insert " << i << std::endl;
            }
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "level: " << list.getlevel() << std::endl;
            std::cout << "insert time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
            d += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        }

        {
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            for (int i = 0; i < counts; i++)
            {
                list.find(keys[i]);
                // if (i % 50000 == 0)
                //     std::cout << "find " << i << std::endl;
            }
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "find time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
            d += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        }

        {
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            for (int i = 0; i < counts; i++)
            {
                list.erase(keys[i]);
                // if (i % 50000 == 0)
                //     std::cout << "erase " << i << std::endl;
            }
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "erase time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
            d += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        }

        std::cout << "total time: " << d.count() << "ms" << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
    };
};

class NoDefaultConstructible
{
    NoDefaultConstructible() = delete;
    NoDefaultConstructible(const NoDefaultConstructible &) = delete;
    NoDefaultConstructible(NoDefaultConstructible &&) = delete;
};

int main()
{
    SkipListTest::test<int, int>(1000000, false);
    SkipListTest::test<std::string, int>(1000000, false);
    SkipListTest::test<NoDefaultConstructible, int>(1000000, true);

    system("pause");
    return 0;
}