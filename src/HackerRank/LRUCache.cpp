#include "stdafx.h"
#include "HackerRank/LRUCache.h"

namespace hackerrank
{
Cache::Cache(size_t i_cp)
    : head(nullptr), tail(nullptr), sz(0), cp(i_cp)
{
}

Cache::~Cache()
{
    mp.clear();
    for (Node* current = head; current != nullptr;)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

Cache::Node::Node(int i_key, int i_value)
    : key(i_key), value(i_value)
    , next(nullptr), prev(nullptr)
{
}

void Cache::push_cache(int key, int value)
{
    Node* newCache = new Node(key, value);
    if (!head)
    {
        head = tail = newCache;
    }
    else
    {
        head->prev = newCache;
        newCache->next = head;
        head = newCache;
    }
    if (sz++ == cp)
    {
        pop_cache();
    }

    mp[key] = head;
}

void Cache::pop_cache()
{
    if (!tail)
    {
        return;
    }
    Node* prevCache = tail->prev;
    if (prevCache)
    {
        prevCache->next = nullptr;
    }
    sz--;
    mp.erase(tail->key);
    delete tail;
    tail = prevCache;
}

int Cache::use_cache(Node* cacheNode)
{
    if (!cacheNode)
    {
        return -1;
    }
    if (cacheNode != head)
    {
        Node* prev = cacheNode->prev;
        Node* next = cacheNode->next;

        if (prev)
        {
            prev->next = next;
        }
        if (next)
        {
            next->prev = prev;
        }

        head->prev = cacheNode;
        cacheNode->next = head;
        cacheNode->prev = nullptr;
        head = cacheNode;
    }

    return head->value;
}

LRUCache::LRUCache(int i_cp)
    : Cache(i_cp)
{
}

int LRUCache::get(int key)
{
    if (auto foundCacheIt = mp.find(key); foundCacheIt != mp.end())
    {
        return use_cache(foundCacheIt->second);
    }

    return -1;
}

void LRUCache::set(int key, int value)
{
    if (auto foundCacheIt = mp.find(key); foundCacheIt != mp.end())
    {
        foundCacheIt->second->value = value;
    }
    else
    {
        push_cache(key, value);
    }
}

void DoCommand(const std::string& command, Cache& cache)
{
    if (command == "set")
    {
        int key, value;
        std::cin >> key >> value;
        std::cin.ignore();
        cache.set(key, value);
    }
    else if (command == "get")
    {
        int key;
        std::cin >> key;
        std::cin.ignore();
        std::cout << cache.get(key) << std::endl;
    }
}

void QueryCache(Cache& cache, int n)
{
    std::string command;
    for (int i = 0; i < n; i++)
    {
        std::cin >> command;
        DoCommand(command, cache);
    }
}

void DoLRUCacheQueries()
{
    int n, cp;
    std::cin >> n >> cp;
    std::cin.ignore();

    LRUCache cache(cp);
    QueryCache(cache, n);
}
}