#pragma once

#include <memory>
#include <queue>

#include "DDSDataObjectAddress.h"
#include "DDSRoutingTable.h"
#include "DDSCoordinatorNetworkService.h"
#include "DDSSharedObjectBase.h"
#include "DDSDataObjectAddress.h"
#include "DDSTimerSystem.h"
#include "DDSHttpClient.h"
#include "DDSResolver.h"
#include "DDSDatabaseConnection.h"
#include "DDSDatabaseConnectionPool.h"
#include "DDSLoadBalancerNetworkService.h"

#include "DDSCoordinatorProtocolMessages.refl.h"

class DDSCoordinatorState
{
public:

  template <typename DataTypeList, typename SharedObjectList>
  DDSCoordinatorState(
    DataTypeList && data_list, 
    SharedObjectList && shared_object,
    const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
    const StormSockets::StormSocketClientFrontendHttpSettings & http_client_settings,
    const DDSDatabaseSettings & database_settings) :
    DDSCoordinatorState(backend_settings, node_server_settings, http_client_settings, database_settings)
  {
    m_NumDataObjects = std::decay_t<DataTypeList>::NumTypes;
    data_list(m_DataObjectNameHashes, m_DatabaseObjectNameHashes);
    shared_object(m_SharedObjectNameHashes);
    shared_object(*this, m_SharedObjects, m_NumDataObjects);
  }

  ~DDSCoordinatorState();

  int GetDataObjectTypeIdForNameHash(uint32_t name_hash) const;
  int GetDatabaseObjectTypeIdForNameHash(uint32_t name_hash) const;
  int GetSharedObjectTypeIdForNameHash(uint32_t name_hash) const;
  int GetTargetObjectIdForNameHash(uint32_t name_hash) const;

  void InitializeSharedObjects();
  void InitializeLoadBalancerServer(
    const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings, int endpoint_id);

  void ProcessEvents();

  void CreateTimer(std::chrono::system_clock::duration duration, DDSCoordinatorResponderCallData && responder_data);
  void CreateHttpRequest(const DDSHttpRequest & request, DDSCoordinatorResponderCallData && responder_data);

  DDSRoutingTableNodeInfo GetNodeInfo(DDSKey key);

  std::string QueryDatabaseSingleton(const char * collection_name);
  void UpsertDatabaseSingleton(const char * collection_name, const char * document);

  time_t GetNetworkTime() const;

  void * GetLocalObject(int target_object_type, DDSKey target_key);
private:

  friend class DDSCoordinatorServerProtocol;
  friend class DDSCoordinatorNetworkService;
  friend class DDSSharedObjectInterface;

  template <class DataType>
  friend class DDSSharedObject;

  DDSCoordinatorState(const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
    const StormSockets::StormSocketClientFrontendHttpSettings & http_client_settings,
    const DDSDatabaseSettings & database_settings);

  void GotMessageFromServer(DDSNodeId server_id, DDSCoordinatorProtocolMessageType type, const char * data);
  bool SendTargetedMessage(DDSDataObjectAddress addr, DDSCoordinatorProtocolMessageType type, std::string && message, bool force_process = false);
  void SendToAllConnectedClients(std::string && message);

  void SyncRoutingTable();
  void CheckForAllClear();

  void QueryObjectData(int object_type_id, DDSKey key, const char * collection);
  void QueryObjectData(const char * collection, DDSKey key, DDSCoordinatorResponderCallData && responder_call);
  void QueryObjectData(const char * collection, const char * query, DDSCoordinatorResponderCallData && responder_call);
  void QueryObjectDataMultiple(const char * collection, const char * query, DDSCoordinatorResponderCallData && responder_call);

  void InsertObjectData(int object_type_id, DDSKey key, const char * collection, const char * data, DDSCoordinatorResponderCallData && responder_call);
  void DeleteObjectData(const char * collection, DDSKey key);

  void DestroyDeferredCallback(DDSDeferredCallback * callback);

  void HandleQueryByKey(int object_type_id, DDSKey key, const char * result_data, int ec);
  void HandleInsertResult(int ec, DDSCoordinatorResponderCallData & responder_call);

  void BeginQueueingMessages();
  void EndQueueingMessages();

  DDSCoordinatorNetworkService & GetNetworkService();
  const DDSRoutingTable & GetRoutingTable() const;

  DDSNodeId GetNodeIdForKey(DDSKey key) const;

  DDSNodeId CreateNode(uint32_t addr, uint16_t port, const std::vector<DDSNodePort> & endpoint_ports, const std::vector<DDSNodePort> & website_ports);
  void SetNodeDefunct(DDSNodeId id);
  void DestroyNode(DDSNodeId id);

  uint64_t GetClientSecret() const;
  uint64_t GetServerSecret() const;

  const void * GetSharedObjectPointer(int shared_object_type);
private:

  DDSNetworkBackend m_Backend;
  DDSCoordinatorNetworkService m_NetworkService;

  std::vector<std::unique_ptr<DDSLoadBalancerNetworkService>> m_LoadBalancerServices;

  DDSTimerSystem m_TimerSystem;
  DDSHttpClient m_HttpClient;
  DDSResolver m_Resolver;
  std::set<std::unique_ptr<DDSDeferredCallback>> m_DeferredCallbackList;

  DDSRoutingTable m_RoutingTable;
  std::vector<std::pair<DDSNodeId, DDSKeyRange>> m_RoutingKeyRanges;
  std::map<DDSNodeId, int> m_RoutingTableAck;


  DDSNodeId m_NextNodeId;
  int m_NumDataObjects;

  std::queue<std::tuple<DDSDataObjectAddress, DDSCoordinatorProtocolMessageType, std::string>> m_QueuedTargetedMessages;
  int m_QueueMessageDepth = 0;

  std::vector<uint32_t> m_DataObjectNameHashes;
  std::vector<uint32_t> m_DatabaseObjectNameHashes;
  std::vector<uint32_t> m_SharedObjectNameHashes;
  std::vector<std::unique_ptr<DDSSharedObjectBase>> m_SharedObjects;

  std::unique_ptr<DDSDatabaseConnectionPool> m_Database;
  std::unique_ptr<DDSDatabaseConnection> m_ImmediateDatabase;

  uint64_t m_ClientSecret;
  uint64_t m_ServerSecret;

  time_t m_LastLoadBalancerSync;
  time_t m_LastUpdate;
};
