
#pragma once

#include "Foundation/Common.h"
#include "Foundation/Json/Json.h"

#include "hash/Hash.h"

struct JsonDictionaryElement
{
  Hash m_Hash;
  std::string m_Key;
  Json m_Json;
};

struct JsonDictionaryMap
{
  std::unordered_map<std::string, Json> m_Map;
};