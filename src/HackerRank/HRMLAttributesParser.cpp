#include "stdafx.h"
#include "HackerRank/HRMLAttributesParser.h"

bool IsDelimiter(char ch)
{
    return ch == '<' || ch == '>' || ch == '=' || ch == '\"' || ch == '~' || std::isspace(ch);
};

std::string GetWord(std::string::const_iterator& startIter, std::string::const_iterator& endIter, std::function<bool(char)> predicate)
{
    std::string word;
    std::string::const_iterator originEndIter = endIter;
    startIter = std::find_if_not(startIter, endIter, predicate);
    endIter = std::find_if(startIter, endIter, predicate);

    std::copy(startIter, endIter, std::back_inserter(word));
    startIter = endIter;
    endIter = originEndIter;
    return word;
}

std::string BuildHRMLTagPath(std::vector<std::string>& tagStack, const std::string& tag)
{
    std::string buildPath;
    for (const std::string& currentTag : tagStack)
    {
        buildPath.append(currentTag);
        buildPath.push_back('.');
    }
    buildPath.append(tag);
    tagStack.push_back(tag);
    return buildPath;
}

namespace hackerrank
{
HRMLAttributesParser::HRMLAttributesParser()
{
    std::cin >> N >> Q;
    std::cin.ignore();
}

void HRMLAttributesParser::DoQueries()
{
    std::string QueriesString;
    for (int i = 0; i < Q; ++i)
    {
        std::getline(std::cin, QueriesString);
        DoQuery(QueriesString);
    }
}

void HRMLAttributesParser::DoParse()
{
    std::string HRMLString;
    std::string::const_iterator startIter, endIter;
    for (int i = 0; i < N; ++i)
    {
        std::getline(std::cin, HRMLString);
        startIter = HRMLString.cbegin();
        endIter = HRMLString.cend();
        std::string word = GetWord(startIter, endIter, IsDelimiter);

        if (word.empty())
        {
            continue;
        }
        else if (word[0] == '/')
        {
            tagStack.pop_back();
        }
        else
        {
            std::string tagPath = BuildHRMLTagPath(tagStack, word);
            SetProperty(startIter, endIter, tagPath);
        }
    }
}

void HRMLAttributesParser::DoQuery(const std::string& queryString)
{
    std::string::const_iterator startIter = queryString.cbegin();
    std::string::const_iterator endIter = queryString.cend();

    std::string word = GetWord(startIter, endIter, IsDelimiter);
    auto foundTagIt = HRML.find(word);
    if (foundTagIt != HRML.cend())
    {
        word = GetWord(startIter, endIter, IsDelimiter);
        auto foundProIter = foundTagIt->second.find(word);
        if (foundProIter != foundTagIt->second.cend())
        {
            std::cout << foundProIter->second << std::endl;
            return;
        }
    }

    std::cout << "Not Found!" << std::endl;
}

void HRMLAttributesParser::SetProperty(std::string::const_iterator& startIter, std::string::const_iterator& endIter, const std::string& tagPath)
{
    std::string prop;
    while (!(prop = GetWord(startIter, endIter, IsDelimiter)).empty())
    {
        std::string value = GetWord(startIter, endIter, IsDelimiter);
        if (!value.empty())
        {
            HRML[tagPath][prop] = value;
        }
    }
}
}