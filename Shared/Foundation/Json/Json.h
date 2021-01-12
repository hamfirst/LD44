
#pragma once

#include "Foundation/Common.h"
#include "Foundation/Variant/Variant.h"
#include "Foundation/Json/JsonType.h"
#include "Foundation/Json/JsonArray.h"
#include "Foundation/Json/JsonDictionary.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormData/StormDataChangeNotifier.h"

struct JsonParentAndPath;
class JsonDictionaryIterator;

enum class JsonParseResult
{
  kNone,
  kSyntaxError,
  kNull,
};


class Json
{
public:
  Json();
  Json(const Json & rhs);
  Json(Json && rhs);

  ~Json();

  Json & operator = (const Json & rhs);
  Json & operator = (Json && rhs);

  JsonType GetType() const
  {
    return (JsonType)m_JsonData.GetCurrentTypeIndex();
  }

  void Encode(std::string & sb);
  void EncodePretty(std::string & sb, int base_indent = 0, int advance = 2, bool do_indent = true);

  JsonParseResult Parse(czstr data);
  void ApplyChange(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change);

  void ApplyJson(const Json & rhs);

  NullOptPtr<Json> GetJsonAtPath(czstr path, bool create_nodes);

  static Json CreateEmptyObject();

protected:

  using ObjectType = JsonDictionary;
  using ArrayType = JsonArray;

  JsonParseResult Parse(czstr data, czstr & result, bool allow_null);

  JsonParentAndPath GetJsonAndParentAtPath(czstr path, NullOptPtr<Json> parent, czstr & created_node_path_end, std::string_view & parent_key);

  void ApplyChangeDirect(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change,
    NullOptPtr<Json> parent_node, const std::string_view & parent_key, const std::string & created_node_path);

private:

  using JsonDataType = Variant<void *, bool, uint64_t, int64_t, float, std::string, ArrayType, ObjectType>;
  JsonDataType m_JsonData;
};
