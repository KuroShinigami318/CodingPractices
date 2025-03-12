#pragma once

namespace hackerrank
{
class HRMLAttributesParser
{
private:
    using PropertiesMap = std::unordered_map<std::string, std::string>;
    using HRMLStructure = std::unordered_map<std::string, PropertiesMap>;

public:
    HRMLAttributesParser();
    void DoParse();
    void DoQueries();

private:
    void DoQuery(const std::string& queryString);
    void SetProperty(std::string::const_iterator& startIter, std::string::const_iterator& endIter, const std::string& tagPath);

    HRMLStructure HRML;
    std::vector<std::string> tagStack;
    int N, Q;
};
}
