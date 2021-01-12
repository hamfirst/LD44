
#include "Foundation/Common.h"
#include "Foundation/Json/Json.h"
#include "Foundation/Json/JsonDictionaryIterator.h"

#include "StormRefl/StormReflJsonStd.h"

struct JsonParentAndPath
{
  NullOptPtr<Json> m_Json;
  NullOptPtr<Json> m_Parent;
};

Json::Json()
{

}

Json::Json(const Json & rhs)
{
  m_JsonData = rhs.m_JsonData;
}

Json::Json(Json && rhs)
{
  m_JsonData = std::move(rhs.m_JsonData);
}

Json::~Json()
{

}

Json & Json::operator = (const Json & rhs)
{
  m_JsonData = rhs.m_JsonData;
  return *this;
}

Json & Json::operator = (Json && rhs)
{
  m_JsonData = std::move(rhs.m_JsonData);
  return *this;
}

void Json::Encode(std::string & sb)
{
  switch (GetType())
  {
  case JsonType::kNull:
    sb += "null";
    return;
  case JsonType::kBool:
    sb += m_JsonData.GetAs<bool>() ? "true" : "false";
    break;
  case JsonType::kUnsignedIntegerNumber:
    {
      uint64_t val = m_JsonData.GetAs<uint64_t>();
      sb += std::to_string(val);
    }
    break;
  case JsonType::kSignedIntegerNumber:
    {
      int64_t val = m_JsonData.GetAs<int64_t>();
      sb += std::to_string(val);
    }
    break;
  case JsonType::kFloatingNumber:
    {
      float val = m_JsonData.GetAs<float>();
      sb += std::to_string(val);
    }
    break;
  case JsonType::kString:
    {
      StormReflEncodeJson(m_JsonData.GetAs<std::string>(), sb);
    }
    break;
  case JsonType::kArray:
    {
      auto & vec = m_JsonData.GetAs<ArrayType>();

      sb += '[';
      for (std::size_t index = 0, end = vec.size(); index < end; ++index)
      {
        vec[index].Encode(sb);
        if (index < end - 1)
        {
          sb += ',';
        }
      }
      sb += ']';
    }
    break;

  case JsonType::kObject:
    {
      auto & dict = m_JsonData.GetAs<ObjectType>();
      auto itr = dict.begin();

      if (itr == dict.end())
      {
        sb += "{}";
        break;
      }

      sb += '{';
      while (true)
      {
        auto elem = *itr;

        sb += '\"';
        sb += elem.first;
        sb += "\":";
        elem.second.Encode(sb);
        ++itr;

        if (itr == dict.end())
        {
          break;
        }

        sb += ',';
      }

      sb += '}';
    }
    break;
  }
}

void Json::EncodePretty(std::string & sb, int base_indent, int advance, bool do_indent)
{
  if (do_indent)
  {
    StormReflJsonHelpers::StormReflEncodeIndent(base_indent, sb);
  }

  switch (GetType())
  {
  case JsonType::kObject:
    {
      auto & dict = m_JsonData.GetAs<ObjectType>();
      auto itr = dict.begin();

      if (itr == dict.end())
      {
        sb += "{ }";
        break;
      }


      sb += "{\n";
      while (true)
      {
        auto elem = *itr;

        StormReflJsonHelpers::StormReflEncodeIndent(base_indent + advance, sb);
        sb += '\"';
        sb += elem.first;
        sb += "\": ";
        elem.second.EncodePretty(sb, base_indent + advance, advance, false);
        ++itr;

        if (itr == dict.end())
        {
          break;
        }

        sb += ",\n";
      }

      sb += '\n';
      StormReflJsonHelpers::StormReflEncodeIndent(base_indent, sb);
      sb += "}";
    }
    break;
  default:
    Encode(sb);
    break;
  }

}

JsonParseResult Json::Parse(czstr data)
{
  return Parse(data, data, false);
}

JsonParseResult Json::Parse(czstr data, czstr & result, bool allow_null)
{
  auto & json_data = m_JsonData;
  StormReflJsonAdvanceWhiteSpace(data);
  if (*data == '{')
  {
    ObjectType dict;

    data++;
    StormReflJsonAdvanceWhiteSpace(data);
    if (*data == '}')
    {
      data++;
      result = data;

      json_data = std::move(dict);
      return JsonParseResult::kNone;
    }

    while (true)
    {
      std::string id;
      if (!StormReflParseJson(id, data, data))
      {
        return JsonParseResult::kSyntaxError;
      }

      StormReflJsonAdvanceWhiteSpace(data);

      if (*data != ':')
      {
        return JsonParseResult::kSyntaxError;
      }

      data++;

      Json new_json;

      auto parse_result = new_json.Parse(data, data, true);
      if (parse_result == JsonParseResult::kNone)
      {
        dict.emplace(id, std::move(new_json));
        StormReflJsonAdvanceWhiteSpace(data);
      }
      else
      {
        return parse_result;
      }

      if (*data == ',')
      {
        data++;
      }
      else if (*data == '}')
      {
        data++;
        result = data;

        json_data = std::move(dict);
        return JsonParseResult::kNone;
      }
      else
      {
        return JsonParseResult::kSyntaxError;
      }
    }
  }
  else if (*data == '[')
  {
    ArrayType arr;

    data++;
    StormReflJsonAdvanceWhiteSpace(data);
    if (*data == ']')
    {
      data++;
      result = data;

      json_data = std::move(arr);
      return JsonParseResult::kNone;
    }

    while (true)
    {
      Json new_json;

      auto parse_result = new_json.Parse(data, data, true);
      if (parse_result == JsonParseResult::kNone)
      {
        arr.emplace_back(std::move(new_json));
        StormReflJsonAdvanceWhiteSpace(data);
      }
      else
      {
        return parse_result;
      }

      if (*data == ',')
      {
        data++;
        StormReflJsonAdvanceWhiteSpace(data);
      }
      else if (*data == ']')
      {
        data++;
        result = data;

        json_data = std::move(arr);
        return JsonParseResult::kNone;
      }
      else
      {
        return JsonParseResult::kSyntaxError;
      }
    }
  }
  else if (*data == '\"')
  {
    std::string str;
    if (!StormReflJson<std::string>::Parse(str, data, result, false))
    {
      return JsonParseResult::kSyntaxError;
    }

    json_data = str;
    return JsonParseResult::kNone;
  }
  else if ((*data <= '9' && *data >= '0') || *data == '-' || *data == '+' || *data == '.')
  {
    auto str = data;
    bool is_negative = false;

    if (*str == '-')
    {
      is_negative = true;
      str++;
    }

    bool is_floating_point = false;
    while (true)
    {
      if (*str == '.' || *str == 'e' || *str == 'E')
      {
        is_floating_point = true;
        break;
      }

      if (*str < '0' || *str > '9')
      {
        break;
      }

      str++;
    }

    uint64_t unsigned_val;
    int64_t signed_val;

    float float_val;

    if (is_floating_point)
    {
      if (StormReflParseJson(float_val, data, result))
      {
        json_data = float_val;
        return JsonParseResult::kNone;
      }
    }
    else if (is_negative)
    {
      if (StormReflParseJson(signed_val, data, result))
      {
        json_data = signed_val;
        return JsonParseResult::kNone;
      }
    }
    else
    {
      if (StormReflParseJson(unsigned_val, data, result))
      {
        json_data = unsigned_val;
        return JsonParseResult::kNone;
      }
    }

    return JsonParseResult::kSyntaxError;
  }
  else if (*data == 't')
  {
    if (!StormReflJsonParseOverTrue(data, result))
    {
      return JsonParseResult::kSyntaxError;
    }

    json_data = true;
    return JsonParseResult::kNone;
  }
  else if (*data == 'f')
  {
    if (!StormReflJsonParseOverFalse(data, result))
    {
      return JsonParseResult::kSyntaxError;
    }

    json_data = false;
    return JsonParseResult::kNone;
  }
  else if (*data == 'n')
  {
    if (!StormReflJsonParseOverNull(data, result))
    {
      return JsonParseResult::kSyntaxError;
    }

    json_data = (void *)nullptr;
    return JsonParseResult::kNull;
  }

  return JsonParseResult::kSyntaxError;
}

void Json::ApplyChange(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change)
{
  czstr created_node_end = nullptr;
  std::string_view parent_key;
  auto result = GetJsonAndParentAtPath(change.m_Path.data(), nullptr, created_node_end, parent_key);

  std::string created_node_path;
  if (created_node_end)
  {
    created_node_path = std::string(change.m_Path.data(), created_node_end);
  }

  if (result.m_Json == nullptr)
  {
    ASSERT(false, "Could not find json at location for change");
  }

  result.m_Json->ApplyChangeDirect(change, reverse_change, result.m_Parent, parent_key, created_node_path);
}

void Json::ApplyJson(const Json & rhs)
{
  if(rhs.m_JsonData.GetCurrentTypeIndex() == (int)JsonType::kObject && m_JsonData.GetCurrentTypeIndex() == (int)JsonType::kObject)
  {
    auto & rhs_dict = rhs.m_JsonData.GetAs<ObjectType>();
    auto & this_dict = m_JsonData.GetAs<ObjectType>();

    for (auto elem : rhs_dict)
    {
      auto itr = this_dict.find(elem.first);
      if (itr == this_dict.end())
      {
        if (elem.second.GetType() != JsonType::kNull)
        {
          this_dict.emplace(elem.first, elem.second);
        }
      }
      else
      {
        if (elem.second.GetType() == JsonType::kNull)
        {
          this_dict.erase(itr);
        }
        else
        {
          auto & json = (*itr).second;
          json.ApplyJson(elem.second);
        }
      }
    }
  }
  else
  {
    m_JsonData = rhs.m_JsonData;
  }
}

NullOptPtr<Json> Json::GetJsonAtPath(czstr path, bool create_nodes)
{
  if (*path == 0)
  {
    return this;
  }

  if (m_JsonData.GetCurrentTypeIndex() != (int)JsonType::kObject)
  {
    if (create_nodes)
    {
      m_JsonData = ObjectType{};
    }
    else
    {
      return nullptr;
    }
  }

  std::string index;

  if (*path == '.')
  {
    path++;

    while (*path != 0 && *path != '.' && *path != '[')
    {
      index += *path;
      path++;
    }
  }
  else if (*path == '[')
  {
    path++;

    while (*path != 0 && *path != ']')
    {
      index += *path;
      path++;
    }

    if(*path == ']')
    { 
      path++;
    }
  }

  auto & obj = m_JsonData.GetAs<ObjectType>();
  auto json = obj.try_find(index);

  if (json == nullptr)
  {
    if (!create_nodes)
    {
      return nullptr;
    }

    auto & new_json = obj.emplace(index, CreateEmptyObject());
    return new_json.GetJsonAtPath(path, create_nodes);
  }

  return json->GetJsonAtPath(path, create_nodes);
}

JsonParentAndPath Json::GetJsonAndParentAtPath(czstr path, NullOptPtr<Json> parent, czstr & created_node_path_end, std::string_view & parent_key)
{
  if (*path == 0)
  {
    return JsonParentAndPath{ this, parent };
  }

  if (m_JsonData.GetCurrentTypeIndex() != (int)JsonType::kObject)
  {
    m_JsonData = ObjectType{};
  }

  std::string index;

  if (*path == '.')
  {
    path++;
    czstr path_start = path;

    while (*path != 0 && *path != '.' && *path != '[')
    {
      index += *path;
      path++;
    }

    parent_key = std::string_view(path_start, path - path_start);
  }
  else if (*path == '[')
  {
    path++;
    czstr path_start = path;
    while (*path != 0 && *path != ']')
    {
      index += *path;
      path++;
    }

    parent_key = std::string_view(path_start, path - path_start);
    if (*path == ']')
    {
      path++;
    }
  }

  auto & obj = m_JsonData.GetAs<ObjectType>();
  auto itr = obj.find(index);

  if (itr == obj.end())
  {
    if (created_node_path_end == nullptr)
    {
      created_node_path_end = path;
    }

    if (*path == 0)
    {
      auto & json = obj.emplace(index, Json());
      return JsonParentAndPath{ &json, this };
    }
    else
    {
      auto & json = obj.emplace(index, CreateEmptyObject());
      return json.GetJsonAndParentAtPath(path, this, created_node_path_end, parent_key);
    }
  }

  if (*path == 0)
  {
    return JsonParentAndPath{ &(*itr).second, this };
  }
  else
  {
    return (*itr).second.GetJsonAndParentAtPath(path, this, created_node_path_end, parent_key);
  }

  return JsonParentAndPath{ this, parent };
}


void Json::ApplyChangeDirect(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change,
  NullOptPtr<Json> parent_node, const std::string_view & parent_key, const std::string & created_node_path)
{
  if (created_node_path.size() > 0 && reverse_change)
  {
    reverse_change->m_Type = ReflectionNotifyChangeType::kRevert;
    reverse_change->m_Path = created_node_path;
    reverse_change = nullptr;
  }

  switch (change.m_Type)
  {
  case ReflectionNotifyChangeType::kSet:
    {
      if(reverse_change)
      {
        reverse_change->m_Type = ReflectionNotifyChangeType::kSet;
        reverse_change->m_Path = change.m_Path;
        Encode(reverse_change->m_Data);
      }

      if (Parse(change.m_Data.data()) == JsonParseResult::kSyntaxError)
      {
        ASSERT(false, "Syntax error parsing json change");
      }
    }
    break;
  case ReflectionNotifyChangeType::kClear:
    {
      auto type = GetType();
      if (type == JsonType::kObject)
      {
        if(reverse_change)
        {
          reverse_change->m_Type = ReflectionNotifyChangeType::kSet;
          reverse_change->m_Path = change.m_Path;
          Encode(reverse_change->m_Data);
        }

        auto & obj = m_JsonData.GetAs<ObjectType>();
        obj.clear();
      }
      else
      {
        ASSERT(false, "Attempting to clear a non-object json type");
      }
    }
    break;
  case ReflectionNotifyChangeType::kCompress:
    {
      auto type = GetType();
      if (type == JsonType::kObject)
      {
        if(reverse_change)
        {
          reverse_change->m_Type = ReflectionNotifyChangeType::kSet;
          reverse_change->m_Path = change.m_Path;
          Encode(reverse_change->m_Data);
        }

        auto & obj = m_JsonData.GetAs<ObjectType>();
        std::map<uint64_t, Json> sorted;

        for (auto val : obj)
        {
          if (val.second.GetType() != JsonType::kNull)
          {
            uint64_t index = std::strtoull(val.first.data(), nullptr, 10);
            sorted.emplace(std::make_pair(index, std::move(val.second)));
          }
        }

        obj.clear();
        uint64_t index = 0;
        for (auto & val : sorted)
        {
          obj.emplace(std::to_string(index), std::move(val.second));
          index++;
        }
      }
    }
    break;
  case ReflectionNotifyChangeType::kInsert:
    {
      if(reverse_change)
      {
        reverse_change->m_Type = ReflectionNotifyChangeType::kRemove;
        reverse_change->m_Path = change.m_Path;
        reverse_change->m_SubIndex = change.m_SubIndex;
      }

      auto type = GetType();
      if (type != JsonType::kObject)
      {
        m_JsonData = ObjectType{};
      }

      auto & obj = m_JsonData.GetAs<ObjectType>();
      auto num_str = std::to_string(change.m_SubIndex);

      Json json;
      if (json.Parse(change.m_Data.data()) == JsonParseResult::kSyntaxError)
      {
        ASSERT(false, "Syntax error while applying json insert");
      }

      obj.emplace(num_str, std::move(json));
    }
    break;
  case ReflectionNotifyChangeType::kRemove:
    {
      auto type = GetType();
      if (type == JsonType::kObject)
      {
        auto & obj = m_JsonData.GetAs<ObjectType>();
        auto num_str = std::to_string(change.m_SubIndex);

        auto itr = obj.find(num_str);
        if (itr != obj.end())
        {
          if (reverse_change)
          {
            reverse_change->m_Type = ReflectionNotifyChangeType::kInsert;
            reverse_change->m_Path = change.m_Path;
            reverse_change->m_SubIndex = change.m_SubIndex;
            (*itr).second.Encode(reverse_change->m_Data);
          }

          obj.erase(itr);
        }
      }
    }
    break;
  case ReflectionNotifyChangeType::kRevert:
    {
      if (reverse_change)
      {
        reverse_change->m_Type = ReflectionNotifyChangeType::kSet;
        reverse_change->m_Path = change.m_Path;
        Encode(reverse_change->m_Data);
      }

      if (parent_node)
      {
        ObjectType & obj = parent_node->m_JsonData.GetAs<ObjectType>();
        obj.erase(parent_key);
      }
    }
    break;
  }
}

Json Json::CreateEmptyObject()
{
  Json json;
  json.m_JsonData = ObjectType{};
  return json;
}
