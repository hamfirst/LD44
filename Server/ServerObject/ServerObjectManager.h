#pragma once

#include "Server/ServerCommon.h"
#include "Server/ServerObject/ServerObjectUpdate.h"

#include "Foundation/SparseList/SparseList.h"

class ServerObject;
class ServerObjectInitData;
class ServerObjectHandle;

struct ServerObjectStaticInitData
{
  std::size_t m_TypeIndex;
  NullOptPtr<ServerObjectInitData> m_InitData;
};


class ServerObjectManager
{
public:

  ServerObjectManager(const std::vector<ServerObjectStaticInitData> & static_objects, int max_dynamic_objects, int num_reserved_slots);

  ServerObjectManager(const ServerObjectManager & rhs);
  ServerObjectManager(ServerObjectManager && rhs);

  ~ServerObjectManager();

  ServerObjectManager & operator = (const ServerObjectManager & rhs);
  ServerObjectManager & operator = (ServerObjectManager && rhs);

  template <typename T>
  NullOptPtr<T> CreateDynamicObject()
  {
    auto ptr = CreateDynamicObjectInternal(T::TypeIndex);
    return static_cast<T *>(ptr);
  }

  template <typename T>
  NullOptPtr<T> CreateDynamicObject(std::size_t reserved_slot)
  {
    auto ptr = CreateDynamicObjectInternal(T::TypeIndex, reserved_slot);
    return static_cast<T *>(ptr);
  }

  template <typename Visitor>
  void VisitObjects(Visitor && visitor)
  {
    std::size_t object_index = 0;
    for (std::size_t end = m_StaticObjects.size(); object_index < end; ++object_index)
    {
      visitor(object_index, m_StaticObjects[object_index]);
    }

    for (auto elem : m_DynamicObjects)
    {
      visitor(elem.first + object_index, elem.second.m_ServerObject);
    }
  }

  void CreateUpdateList(ServerObjectUpdateList & update_list);

  int GetHandleBits();

  void Serialize(NetBitWriter & writer) const;
  void Deserialize(NetBitReader & reader);

protected:

  friend class ServerObject;
  friend class ServerObjectHandle;

  int GetNewDynamicObjectId();
  NullOptPtr<ServerObject> CreateDynamicObjectInternal(int type_index);
  NullOptPtr<ServerObject> CreateDynamicObjectInternal(int type_index, int slot_index);
  void DestroyDynamicObjectInternal(NotNullPtr<ServerObject> ptr);

  void FinalizeHandles();
  NullOptPtr<ServerObject> ResolveHandle(int slot_index, int gen) const;

  struct DynamicObjectInfo
  {
    NullOptPtr<ServerObject> m_ServerObject;
    std::size_t m_TypeIndex;
  };

private:

  std::vector<NotNullPtr<ServerObject>> m_StaticObjects;
  std::vector<int> m_DynamicObjectGen;
  SparseList<DynamicObjectInfo> m_DynamicObjects;
  int m_ReservedSlots;
};
