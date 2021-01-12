
#include "Foundation/Common.h"
#include "Foundation/Json/Json.h"
#include "Foundation/Json/JsonDictionary.h"
#include "Foundation/Json/JsonDictionaryElement.h"
#include "Foundation/Json/JsonDictionaryIterator.h"

JsonDictionaryIterator::JsonDictionaryIterator(const std::vector<JsonDictionaryElement>::iterator & itr) :
  m_Itr(itr)
{

}

JsonDictionaryIterator::JsonDictionaryIterator(const std::unordered_map<std::string, Json>::iterator & itr) :
  m_Itr(itr)
{

}

bool JsonDictionaryIterator::operator == (const JsonDictionaryIterator & rhs) const
{
  if(auto itr1 = m_Itr.Get<std::vector<JsonDictionaryElement>::iterator>())
  {
    if(auto itr2 = rhs.m_Itr.Get<std::vector<JsonDictionaryElement>::iterator>())
    {
      return *itr1 == *itr2;
    }
  }
  else if(auto itr1 = m_Itr.Get<std::unordered_map<std::string, Json>::iterator>())
  {
    if(auto itr2 = rhs.m_Itr.Get<std::unordered_map<std::string, Json>::iterator>())
    {
      return *itr1 == *itr2;
    }
  }
  return false;
}

bool JsonDictionaryIterator::operator!=(const JsonDictionaryIterator & rhs) const
{
  return !operator==(rhs);
}

std::pair<const std::string&, Json &> JsonDictionaryIterator::operator*() const
{
  if(auto itr1 = m_Itr.Get<std::vector<JsonDictionaryElement>::iterator>())
  {
    return std::pair<const std::string&, Json &>((*itr1)->m_Key, (*itr1)->m_Json);
  }
  else
  {
    auto itr2 = m_Itr.Get<std::unordered_map<std::string, Json>::iterator>();
    return std::pair<const std::string&, Json &>((*itr2)->first, (*itr2)->second);
  }
}

JsonDictionaryIterator & JsonDictionaryIterator::operator++()
{
  if(auto itr1 = m_Itr.Get<std::vector<JsonDictionaryElement>::iterator>())
  {
    (*itr1)++;
  }
  else
  {
    auto itr2 = m_Itr.Get<std::unordered_map<std::string, Json>::iterator>();
    (*itr2)++;
  }

  return *this;
}

JsonDictionaryConstIterator::JsonDictionaryConstIterator(const std::vector<JsonDictionaryElement>::const_iterator & itr) :
  m_Itr(itr)
{

}

JsonDictionaryConstIterator::JsonDictionaryConstIterator(const std::unordered_map<std::string, Json>::const_iterator & itr) :
  m_Itr(itr)
{

}

bool JsonDictionaryConstIterator::operator == (const JsonDictionaryConstIterator & rhs) const
{
  if(auto itr1 = m_Itr.Get<std::vector<JsonDictionaryElement>::const_iterator>())
  {
    if(auto itr2 = rhs.m_Itr.Get<std::vector<JsonDictionaryElement>::const_iterator>())
    {
      return *itr1 == *itr2;
    }
  }
  else if(auto itr1 = m_Itr.Get<std::unordered_map<std::string, Json>::const_iterator>())
  {
    if(auto itr2 = rhs.m_Itr.Get<std::unordered_map<std::string, Json>::const_iterator>())
    {
      return *itr1 == *itr2;
    }
  }
  return false;
}

bool JsonDictionaryConstIterator::operator!=(const JsonDictionaryConstIterator & rhs) const
{
  return !operator==(rhs);
}

std::pair<const std::string&, const Json &> JsonDictionaryConstIterator::operator*() const
{
  if(auto itr1 = m_Itr.Get<std::vector<JsonDictionaryElement>::const_iterator>())
  {
    return std::pair<const std::string&, const Json &>((*itr1)->m_Key, (*itr1)->m_Json);
  }
  else
  {
    auto itr2 = m_Itr.Get<std::unordered_map<std::string, Json>::const_iterator>();
    return std::pair<const std::string&, const Json &>((*itr2)->first, (*itr2)->second);
  }
}

JsonDictionaryConstIterator & JsonDictionaryConstIterator::operator++()
{
  if(auto itr1 = m_Itr.Get<std::vector<JsonDictionaryElement>::const_iterator>())
  {
    (*itr1)++;
  }
  else
  {
    auto itr2 = m_Itr.Get<std::unordered_map<std::string, Json>::const_iterator>();
    (*itr2)++;
  }

  return *this;
}

