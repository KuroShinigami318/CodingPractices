#include "stdafx.h"
#include "HackerRank/HRMLAttributesParser.h"
#include "HackerRank/LRUCache.h"

int main()
{
	hackerrank::HRMLAttributesParser parser;
	parser.DoParse();
	parser.DoQueries();

	hackerrank::DoLRUCacheQueries();
	return 0;
}