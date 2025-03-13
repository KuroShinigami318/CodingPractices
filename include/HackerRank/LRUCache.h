#pragma once

namespace hackerrank
{
class Cache
{
public:
    Cache(size_t i_cp);
    virtual ~Cache();
    virtual int get(int) = 0;
    virtual void set(int, int) = 0;

protected:
    struct Node
    {
        Node(int i_key, int i_value);
        int key, value;
        Node *next, *prev;
    };

    virtual void push_cache(int key, int value) = 0;
    virtual void pop_cache() = 0;
    virtual int use_cache(Node* cacheNode) = 0;

protected:
    Node *head, *tail;
    std::unordered_map<int, Node*> mp;
    size_t sz, cp;
};

// least recently used cache system
class LRUCache final : public Cache
{
public:
    LRUCache(int i_cp);

    int get(int key) override;
    void set(int key, int value) override;

private:
    void push_cache(int key, int value) override;
    void pop_cache() override;
    int use_cache(Node* cacheNode) override;
};

void DoLRUCacheQueries();
}