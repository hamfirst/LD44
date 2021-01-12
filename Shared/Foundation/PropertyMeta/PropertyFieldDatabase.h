#pragma once

#include "Foundation/PropertyMeta/PropertyFieldMetaData.h"

class PropertyFieldDatabase
{
public:
  PropertyFieldDatabase();

  NotNullPtr<PropertyField> GetUnknownField();
  NotNullPtr<PropertyField> GetBasicField(PropertyFieldType type);
  NotNullPtr<PropertyField> GetBasicSignedField(int size);
  NotNullPtr<PropertyField> GetBasicUnsignedField(int size);
  NotNullPtr<PropertyField> GetBasicFloatField(int size);

  NotNullPtr<PropertyField> AllocateField();

  std::pair<bool, NotNullPtr<PropertyField>> GetEnumData(uint32_t enum_hash);
  std::pair<bool, NotNullPtr<PropertyField>> GetPolyData(uint32_t base_type_hash);
  std::pair<bool, NotNullPtr<PropertyField>> GetStructData(uint32_t type_name_hash);

  NotNullPtr<PropertyField> FindStructData(uint32_t type_name_hash) const;

  void RegisterStructWithAlternateName(uint32_t type_name_hash, NotNullPtr<PropertyField> prop);

private:

  PropertyField m_Unknown;
  PropertyField m_BasicBool;
  PropertyField m_BasicInt8;
  PropertyField m_BasicInt16;
  PropertyField m_BasicInt32;
  PropertyField m_BasicInt64;
  PropertyField m_BasicUInt8;
  PropertyField m_BasicUInt16;
  PropertyField m_BasicUInt32;
  PropertyField m_BasicUInt64;
  PropertyField m_BasicFloat;
  PropertyField m_BasicDouble;
  PropertyField m_BasicFloatDeterministic;
  PropertyField m_BasicString;

  std::vector<std::unique_ptr<PropertyField>> m_PropertyAlloc;

  std::unordered_map<uint32_t, NotNullPtr<PropertyField>> m_EnumField;
  std::vector<std::unique_ptr<PropertyFieldEnumData>> m_EnumData;

  std::unordered_map<uint32_t, NotNullPtr<PropertyField>> m_PolyField;
  std::vector<std::unique_ptr<PropertyFieldPolymorphicData>> m_PolyData;

  std::unordered_map<uint32_t, NotNullPtr<PropertyField>> m_StructField;
  std::vector<std::unique_ptr<PropertyFieldStructData>> m_StructData;
};

