
#include "Foundation/Common.h"
#include "Foundation/Json/JsonDictionary.h"
#include "Foundation/Json/JsonDictionaryElement.h"
#include "Foundation/Json/JsonDictionaryIterator.h"
#include "Foundation/Json/Json.h"


JsonDictionary::JsonDictionary()
{

}

JsonDictionary::~JsonDictionary()
{

}

JsonDictionary::JsonDictionary(const JsonDictionary & rhs):
  m_List(rhs.m_List)
{

}

JsonDictionary::JsonDictionary(JsonDictionary && rhs) :
  m_List(std::move(rhs.m_List))
{

}

JsonDictionaryIterator JsonDictionary::begin()
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    return JsonDictionaryIterator(small_list->begin());
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    return JsonDictionaryIterator((*large_list)->m_Map.begin());
  }
}

JsonDictionaryConstIterator JsonDictionary::begin() const
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    return JsonDictionaryConstIterator(small_list->begin());
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    return JsonDictionaryConstIterator((*large_list)->m_Map.begin());
  }
}

JsonDictionaryIterator JsonDictionary::end()
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    return JsonDictionaryIterator(small_list->end());
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    return JsonDictionaryIterator((*large_list)->m_Map.end());
  }
}

JsonDictionaryConstIterator JsonDictionary::end() const
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    return JsonDictionaryConstIterator(small_list->end());
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    return JsonDictionaryConstIterator((*large_list)->m_Map.end());
  }
}

JsonDictionary & JsonDictionary::operator = (const JsonDictionary & rhs)
{
  if (&rhs == this)
  {
    return *this;
  }

  m_List = rhs.m_List;
  return *this;
}

JsonDictionary & JsonDictionary::operator = (JsonDictionary && rhs) noexcept
{
  if (&rhs == this)
  {
    return *this;
  }

  m_List = std::move(rhs.m_List);
  return *this;
}

NullOptPtr<Json> JsonDictionary::try_find(const std::string_view & key)
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    uint32_t hash = crc32(key);
    for (auto & elem : *small_list)
    {
      if (elem.m_Hash == hash)
      {
        if (elem.m_Key == key)
        {
          return &elem.m_Json;
        }
      }
    }
    return nullptr;
  }
  else if(auto large_list = m_List.TryGet<LargeList>())
  {
    auto & map = (*large_list)->m_Map;
    auto itr = map.find(std::string(key));
    if(itr != map.end())
    {
      return &itr->second;
    }

    return nullptr;
  }

  return nullptr;
}

NullOptPtr<const Json> JsonDictionary::try_find(const std::string_view & key) const
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    uint32_t hash = crc32(key);
    for (auto & elem : *small_list)
    {
      if (elem.m_Hash == hash)
      {
        if (elem.m_Key == key)
        {
          return &elem.m_Json;
        }
      }
    }
    return nullptr;
  }
  else if(auto large_list = m_List.TryGet<LargeList>())
  {
    auto & map = (*large_list)->m_Map;
    auto itr = map.find(std::string(key));
    if(itr != map.end())
    {
      return &itr->second;
    }

    return nullptr;
  }

  return nullptr;
}

JsonDictionaryIterator JsonDictionary::find(const std::string_view & key)
{
  uint32_t hash = crc32(key);
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    auto end = small_list->end();
    for(auto itr = small_list->begin(); itr != end; ++itr)
    {
      if(itr->m_Hash == hash)
      {
        if(itr->m_Key == key)
        {
          return JsonDictionaryIterator(itr);
        }
      }
    }

    return JsonDictionaryIterator(end);
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    auto & map = (*large_list)->m_Map;
    auto itr = map.find(std::string(key));
    return JsonDictionaryIterator(itr);
  }
}

JsonDictionaryConstIterator JsonDictionary::find(const std::string_view & key) const
{
  uint32_t hash = crc32(key);
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    auto end = small_list->end();
    for(auto itr = small_list->begin(); itr != end; ++itr)
    {
      if(itr->m_Hash == hash)
      {
        if(itr->m_Key == key)
        {
          return JsonDictionaryConstIterator(itr);
        }
      }
    }

    return JsonDictionaryConstIterator(end);
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    auto & map = (*large_list)->m_Map;
    auto itr = map.find(std::string(key));
    return JsonDictionaryConstIterator(itr);
  }
}

Json & JsonDictionary::emplace(const std::string_view & key, const Json & json)
{
  ConvertToLargeListIfNeeded();
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    auto test_json = try_find(key);
    if (test_json != nullptr)
    {
      *test_json = json;
      return *test_json;
    }

    return small_list->emplace_back(JsonDictionaryElement{ crc32(key), std::string(key), json }).m_Json;
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    auto & map = (*large_list)->m_Map;
    return map.insert_or_assign(std::string(key), json).first->second;
  }
}

Json & JsonDictionary::emplace(const std::string_view & key, Json && json)
{
  ConvertToLargeListIfNeeded();
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    auto test_json = try_find(key);
    if (test_json != nullptr)
    {
      *test_json = std::move(json);
      return *test_json;
    }

    return small_list->emplace_back(JsonDictionaryElement{ crc32(key), std::string(key), std::move(json) }).m_Json;
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    auto & map = (*large_list)->m_Map;
    return map.insert_or_assign(std::string(key), std::forward<Json>(json)).first->second;
  }
}

bool JsonDictionary::erase(const std::string_view & key)
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    uint32_t hash = crc32(key);
    for (auto itr = small_list->begin(), end = small_list->end(); itr != end; ++itr)
    {
      auto & elem = *itr;
      if (elem.m_Hash == hash)
      {
        if (elem.m_Key == key)
        {
          small_list->erase(itr);
          return true;
        }
      }
    }
  }
  else if(auto large_list = m_List.TryGet<LargeList>())
  {
    auto & map = (*large_list)->m_Map;
    return map.erase(std::string(key)) > 0;
  }

  return false;
}

void JsonDictionary::erase(const JsonDictionaryIterator & iterator)
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    if(auto small_list_iterator = iterator.m_Itr.Get<std::vector<JsonDictionaryElement>::iterator>())
    {
      small_list->erase(*small_list_iterator);
    }
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    if(auto large_list_iterator = iterator.m_Itr.Get<std::unordered_map<std::string, Json>::iterator>())
    {
      (*large_list)->m_Map.erase(*large_list_iterator);
    }
  }
}

void JsonDictionary::erase(const JsonDictionaryConstIterator & iterator)
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    if(auto small_list_iterator = iterator.m_Itr.Get<std::vector<JsonDictionaryElement>::const_iterator>())
    {
      small_list->erase(*small_list_iterator);
    }
  }
  else
  {
    auto large_list = m_List.TryGet<LargeList>();
    if(auto large_list_iterator = iterator.m_Itr.Get<std::unordered_map<std::string, Json>::const_iterator>())
    {
      (*large_list)->m_Map.erase(*large_list_iterator);
    }
  }
}

void JsonDictionary::clear()
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    small_list->clear();
  }
  else if(auto large_list = m_List.TryGet<LargeList>())
  {
    m_List = SmallList {};
  }
}

void JsonDictionary::ConvertToLargeListIfNeeded()
{
  if(auto small_list = m_List.TryGet<SmallList>())
  {
    if(small_list->size() > 128)
    {
      LargeList new_list;
      auto& map = new_list->m_Map;

      for(auto& elem : *small_list)
      {
        map.emplace(std::make_pair(elem.m_Key, std::move(elem.m_Json)));
      }

      m_List = std::move(new_list);
    }
  }
}
