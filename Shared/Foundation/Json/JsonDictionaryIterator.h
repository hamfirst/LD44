
#pragma once

#include "Foundation/Common.h"
#include "Foundation/Variant/Variant.h"
#include "Foundation/Json/Json.h"

struct JsonDictionaryElement;

class JsonDictionaryIterator
{
public:
  explicit JsonDictionaryIterator(const std::vector<JsonDictionaryElement>::iterator & itr);
  explicit JsonDictionaryIterator(const std::unordered_map<std::string, Json>::iterator & itr);
  JsonDictionaryIterator(const JsonDictionaryIterator& rhs) = default;

  JsonDictionaryIterator& operator = (const JsonDictionaryIterator& rhs) = default;
  bool operator == (const JsonDictionaryIterator& rhs) const;
  bool operator != (const JsonDictionaryIterator& rhs) const;

  std::pair<const std::string&, Json &> operator *() const;

  JsonDictionaryIterator& operator++();

private:
  friend class JsonDictionary;

  Variant<std::vector<JsonDictionaryElement>::iterator, std::unordered_map<std::string, Json>::iterator> m_Itr;
};

class JsonDictionaryConstIterator
{
public:
  explicit JsonDictionaryConstIterator(const std::vector<JsonDictionaryElement>::const_iterator & itr);
  explicit JsonDictionaryConstIterator(const std::unordered_map<std::string, Json>::const_iterator & itr);
  JsonDictionaryConstIterator(const JsonDictionaryConstIterator& rhs) = default;

  JsonDictionaryConstIterator& operator = (const JsonDictionaryConstIterator & rhs) = default;
  bool operator == (const JsonDictionaryConstIterator & rhs) const;
  bool operator != (const JsonDictionaryConstIterator & rhs) const;

  std::pair<const std::string&, const Json &> operator *() const;

  JsonDictionaryConstIterator & operator++();

private:
  friend class JsonDictionary;

  Variant<std::vector<JsonDictionaryElement>::const_iterator, std::unordered_map<std::string, Json>::const_iterator> m_Itr;
};