
#include "DDSNodeInterface.h"
#include "DDSNodeState.h"
#include "DDSServerMessage.h"
#include "DDSEndpointFactoryBase.h"
#include "DDSRandom.h"
#include "DDSSharedLocalCopyDatabase.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

DDSNodeInterface::DDSNodeInterface(DDSNodeState & node_state, DDSDataObjectStoreBase * data_store, DDSKey key) :
  m_NodeState(node_state), m_DataStore(data_store), m_Key(key)
{

}

void DDSNodeInterface::FinalizeObjectLoad()
{
  m_DataStore->FinalizeObjectLoad(m_Key);
}

bool DDSNodeInterface::SendDataToLocalConnection(DDSConnectionId connection_id, const std::string & data)
{
  return m_NodeState.SendToLocalConnection(connection_id, data);
}

void DDSNodeInterface::DisconnectLocalConnection(DDSConnectionId connection_id)
{
  return m_NodeState.DisconnectLocalConnection(connection_id);
}

DDSKey DDSNodeInterface::GetLocalKey()
{
  return m_Key;
}

int DDSNodeInterface::GetObjectTypeId() const
{
  return m_DataStore->GetDataTypeId();
}

int DDSNodeInterface::GetObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetTargetObjectIdForNameHash(object_type_name_hash);
}

int DDSNodeInterface::GetDataObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetDatabaseObjectTypeIdForNameHash(object_type_name_hash);
}

int DDSNodeInterface::GetSharedObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetSharedObjectTypeIdForNameHash(object_type_name_hash);
}

const void * DDSNodeInterface::GetSharedObjectPointer(uint32_t object_type_name_hash)
{
  auto type_id = m_NodeState.GetSharedObjectTypeIdForNameHash(object_type_name_hash);
  if (type_id == -1)
  {
    return nullptr;
  }

  return m_NodeState.GetSharedObjectPointer(type_id);
}

void * DDSNodeInterface::GetLocalObjectPointer(int target_object_type, DDSKey target_key)
{
  return m_NodeState.GetLocalObject(target_object_type, target_key);
}


void DDSNodeInterface::SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message)
{
  assert(target_method_id != -1);

  DDSTargetedMessage packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, DDSServerToServerMessageType::kTargetedMessage, StormReflEncodeJson(packet));
}

void DDSNodeInterface::SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
  int responder_object_type, DDSKey responder_key, int responder_method_id, int err_method_id, std::string && message, std::string && return_arg)
{
  assert(target_method_id != -1);

  DDSTargetedMessageWithResponder packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;
  packet.m_ResponderKey = responder_key;
  packet.m_ResponderObjectType = responder_object_type;
  packet.m_ResponderMethodId = responder_method_id;
  packet.m_ErrorMethodId = err_method_id;
  packet.m_ReturnArg = return_arg;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, DDSServerToServerMessageType::kTargetedMessageResponder, StormReflEncodeJson(packet));
}

void DDSNodeInterface::SendMessageToSharedObject(int target_object_type, int target_method_id, std::string && message)
{
  assert(target_method_id != -1);

  DDSTargetedMessage packet;
  packet.m_Key = 0;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, 0 }, DDSServerToServerMessageType::kTargetedMessage, StormReflEncodeJson(packet));
}

void DDSNodeInterface::SendMessageToSharedObjectWithResponderReturnArg(int target_object_type, int target_method_id,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message, std::string && return_arg)
{
  assert(target_method_id != -1);

  DDSTargetedMessageWithResponder packet;
  packet.m_Key = 0;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;
  packet.m_ResponderKey = responder_key;
  packet.m_ResponderObjectType = responder_object_type;
  packet.m_ResponderMethodId = responder_method_id;
  packet.m_ReturnArg = return_arg;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, 0 }, DDSServerToServerMessageType::kTargetedMessageResponder, StormReflEncodeJson(packet));
}

void DDSNodeInterface::SendResponderCall(const DDSResponderCallBase & call_data)
{
  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(call_data));
}

void DDSNodeInterface::InsertIntoDatabaseWithResponderReturnArg(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  assert(responder_method_id != -1);

  DDSResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_MethodArgs = "[]";
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.InsertObjectData(data_object_type, data_key, collection, data.c_str(), std::move(call_data));
}

void DDSNodeInterface::QueryDatabaseInternal(const char * collection, std::string && query,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  assert(responder_method_id != -1);

  DDSResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_MethodArgs = "[]";
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.QueryObjectData(collection, query.c_str(), std::move(call_data));
}

void DDSNodeInterface::QueryDatabaseMultipleInternal(const char * collection, std::string && query,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  assert(responder_method_id != -1);

  DDSResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_MethodArgs = "[]";
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.QueryObjectDataMultiple(collection, query.c_str(), std::move(call_data));
}

void DDSNodeInterface::QueryDatabaseByKeyInternal(const char * collection, DDSKey key,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  assert(responder_method_id != -1);

  DDSResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_MethodArgs = "[]";
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.QueryObjectData(collection, key, std::move(call_data));
}

void DDSNodeInterface::UpdateDatabaseInternal(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  assert(responder_method_id != -1);

  DDSResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_MethodArgs = "[]";
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.UpdateObjectData(data_object_type, data_key, collection, data.c_str(), &call_data);
}

void DDSNodeInterface::DeleteFromDatabaseInternal(const char * collection, DDSKey key)
{
  m_NodeState.DeleteObjectData(collection, key);
}

void DDSNodeInterface::CreateTimerInternal(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  assert(target_method_id != -1);

  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_MethodArgs = "[]";
  call_data.m_ResponderArgs = return_arg;

  return m_NodeState.CreateTimer(duration, std::move(call_data));
}

void DDSNodeInterface::CreateHttpRequestInternal(const DDSHttpRequest & request, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  assert(target_method_id != -1);

  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_MethodArgs = "[]";
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.CreateHttpRequest(request, std::move(call_data));
}

DDSKey DDSNodeInterface::CreateSubscriptionInternal(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
  DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg, int err_method_id, bool force_load, bool data_sub)
{
  assert(return_method_id != -1);

  DDSKey subscription_id = DDSGetRandomNumber64();

  DDSCreateSubscription sub_data;
  sub_data.m_DataPath = path;
  sub_data.m_Key = target_key;
  sub_data.m_ObjectType = target_object_type;
  sub_data.m_SubscriptionId = subscription_id;
  sub_data.m_ResponderObjectType = return_object_type;
  sub_data.m_ResponderKey = return_key;
  sub_data.m_ResponderMethodId = return_method_id;
  sub_data.m_ErrorMethodId = err_method_id;
  sub_data.m_ReturnArg = return_arg;
  sub_data.m_DeltaOnly = delta_only;
  sub_data.m_ForceLoad = force_load;
  sub_data.m_DataSubscription = data_sub;

  DDSExportedRequestedSubscription req_sub;
  req_sub.m_ObjectType = target_object_type;
  req_sub.m_Key = target_key;
  req_sub.m_SubscriptionId = subscription_id;

  m_DataStore->AssignRequestedSubscription(return_key, req_sub);
  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, 
    DDSServerToServerMessageType::kCreateSubscription, StormReflEncodeJson(sub_data));

  return subscription_id;
}

void DDSNodeInterface::DestroySubscriptionInternal(int return_object_type, DDSKey return_key, DDSKey subscription_id)
{
  DDSDestroySubscription sub_data;
  sub_data.m_Key = return_key;
  sub_data.m_ObjectType = return_object_type;
  sub_data.m_SubscriptionId = subscription_id;

  m_DataStore->RemoveRequestedSubscription(m_Key, subscription_id);
  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ return_object_type, return_key },
    DDSServerToServerMessageType::kDestroySubscription, StormReflEncodeJson(sub_data));
}

std::pair<DDSKey, DDSKey> DDSNodeInterface::CreateSharedLocalCopyInternal(uint32_t target_object_type_name_hash,
  DDSKey target_key, const char * path, int return_object_type,
  DDSKey return_key, int return_method_id, std::string && return_arg, int err_method_id,
  std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)())
{
  bool is_data_type = m_NodeState.IsDatabaseObjectType(target_object_type_name_hash);
  int type_id = is_data_type ? 
    m_NodeState.GetDatabaseObjectTypeIdForNameHash(target_object_type_name_hash) : 
    m_NodeState.GetDataObjectTypeIdForNameHash(target_object_type_name_hash);

  DDSKey subscription_id = DDSGetRandomNumber64();

  auto target_addr = DDSDataObjectAddress{ type_id , target_key };
  auto return_addr = DDSDataObjectAddress{ return_object_type, return_key };
  DDSKey shared_local_copy_key = m_NodeState.m_SharedLocalCopyDatabase.CreateNewSharedLocalCopySubscription(
    target_addr, path, return_arg, return_addr, return_method_id, err_method_id,
    is_data_type, subscription_id, CreateFunc);

  DDSExportedAggregateRequestedSubscription req_sub;
  req_sub.m_SharedLocalCopyKey = shared_local_copy_key;
  req_sub.m_SubscriptionId = subscription_id;
  req_sub.m_Key = target_key;
  req_sub.m_ObjectType = type_id;
  req_sub.m_Path = path;
  req_sub.m_ReturnKey = return_key;
  req_sub.m_ReturnObjectType = return_object_type;
  req_sub.m_ReturnArgs = return_arg;
  req_sub.m_ReturnMethod = return_method_id;
  req_sub.m_ErrorMethod = err_method_id;
  req_sub.m_DataGen = 0;

  m_DataStore->AssignRequestedAggregateSubscription(return_key, req_sub);
  return std::make_pair(shared_local_copy_key, subscription_id);
}

void DDSNodeInterface::DestroySharedLocalCopyInternal(std::pair<DDSKey, DDSKey> subscription_info)
{
  m_NodeState.m_SharedLocalCopyDatabase.DestroySharedLocalCopySubscription(subscription_info.first, subscription_info.second);
  m_DataStore->RemoveRequestedAggregateSubscription(m_Key, subscription_info.first, subscription_info.second);
}

void DDSNodeInterface::GetSharedLocalCopyPtr(DDSSharedLocalCopyPtrBase & ptr, uint32_t target_object_type_name_hash, 
  DDSKey target_key, const char * path, int version, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)())
{
  bool is_data_type = m_NodeState.IsDatabaseObjectType(target_object_type_name_hash);
  int target_object_type = is_data_type ? 
    m_NodeState.GetDatabaseObjectTypeIdForNameHash(target_object_type_name_hash) : m_NodeState.GetDataObjectTypeIdForNameHash(target_object_type_name_hash);

  ptr.m_SharedLocalCopyKey = DDSSharedLocalCopyDatabase::GetSharedLocalCopyKey(DDSDataObjectAddress{ target_object_type, target_key }, crc64(path), is_data_type);
  DDSSetSharedLocalCopyVersion(ptr, version, CreateFunc);
}

void DDSNodeInterface::DestroySelf()
{
  m_NodeState.DestroyDataObject(GetObjectTypeId(), m_Key);
}

DDSRoutingTableNodeInfo DDSNodeInterface::GetNodeInfo(DDSKey key)
{
  return m_NodeState.GetNodeInfo(key);
}

std::string DDSNodeInterface::QueryDatabaseSingleton(const char * collection_name)
{
  //This shouldn't be used from a node, only from the coordinator
  assert(false);
  return "";
}

void DDSNodeInterface::UpsertDatabaseSingleton(const char * collection_name, const char * document)
{
  //This shouldn't be used from a node, only from the coordinator
  assert(false);
}

time_t DDSNodeInterface::GetNetworkTime() const
{
  return m_NodeState.GetNetworkTime();
}

std::string DDSNodeInterface::GetNodeMemoryReport()
{
  return m_NodeState.GetMemoryReport();
}
