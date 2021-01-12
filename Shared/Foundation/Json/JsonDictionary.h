#pragma once

#include <memory>

#include "Foundation/Variant/Variant.h"

class Json;
class JsonDictionary;
class JsonDictionaryIterator;
class JsonDictionaryConstIterator;
struct JsonDictionaryElement;
struct JsonDictionaryMap;

class JsonDictionary
{
public:
  JsonDictionary();
  JsonDictionary(const JsonDictionary & rhs);
  JsonDictionary(JsonDictionary && rhs);

  ~JsonDictionary();

  JsonDictionaryIterator begin();
  JsonDictionaryConstIterator begin() const;

  JsonDictionaryIterator end();
  JsonDictionaryConstIterator end() const;

  JsonDictionary & operator = (const JsonDictionary & rhs);
  JsonDictionary & operator = (JsonDictionary && rhs) noexcept;

  NullOptPtr<Json> try_find(const std::string_view & key);
  NullOptPtr<const Json> try_find(const std::string_view & key) const;

  JsonDictionaryIterator find(const std::string_view & key);
  JsonDictionaryConstIterator find(const std::string_view & key) const;

  Json & emplace(const std::string_view & key, const Json & json);
  Json & emplace(const std::string_view & key, Json && json);

  bool erase(const std::string_view & key);
  void erase(const JsonDictionaryIterator & iterator);
  void erase(const JsonDictionaryConstIterator & iterator);
  void clear();

private:

  void ConvertToLargeListIfNeeded();

private:

  using SmallList = std::vector<JsonDictionaryElement>;
  using LargeList = std::unique_ptr<JsonDictionaryMap>;

  Variant<SmallList, LargeList> m_List;
};


