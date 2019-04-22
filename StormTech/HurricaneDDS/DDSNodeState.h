#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <queue>
#include <tuple>
#include <optional>

#include "DDSNodeId.h"
#include "DDSConnectionId.h"
#include "DDSNodeInterface.h"
#include "DDSDataObjectAddress.h"
#include "DDSDataObjectStoreBase.h"
#include "DDSSharedObjectBase.h"
#include "DDSEndpointFactoryBase.h"
#include "DDSWebsiteFactoryBase.h"
#include "DDSRoutingTable.h"
#include "DDSDatabaseTypes.h"
#include "DDSTimerSystem.h"
#include "DDSHttpClient.h"
#include "DDSResolver.h"
#include "DDSTokenBroker.h"
#include "DDSTokenValidator.h"
#include "DDSNetworkBackend.h"
#include "DDSNodeNetworkService.h"
#include "DDSCoordinatorClientProtocol.h"
#include "DDSDatabaseConnectionPool.h"
#include "DDSIncomingKeyspaceTransferManager.h"
#include "DDSOutgoingKeyspaceTransferManager.h"
#include "DDSNodeSharedObjectResolver.h"
#include "DDSSharedLocalCopyDatabase.h"
#include "DDSWebsiteFilesystem.h"
#include "DDSWebsiteFilesystemBuilder.h"

#include "DDSServerToServerMessages.refl.h"

struct DDSResponder;
struct DDSResponderCallData;

class DDSSharedLocalCopyPtrBase;

class DDSNodeState
{
public:

  template <typename DataTypeList, typename SharedObjectTypeList, typename ... ConnectionFactoryTypes>
  DDSNodeState(
    const DataTypeList & data_objects,
    const SharedObjectTypeList & shared_objects,
    const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
    const StormSockets::StormSocketClientFrontendWebsocketSettings & node_client_settings,
    const StormSockets::StormSocketClientFrontendHttpSettings & http_client_settings,
    const DDSCoordinatorClientSettings & coordinator_settings,
    const DDSDatabaseSettings & database_settings,
    ConnectionFactoryTypes && ... connection_factory_types) :
    DDSNodeState(DataTypeList::NumTypes, backend_settings, node_server_settings, node_client_settings, http_client_settings, coordinator_settings, database_settings)
  {
    data_objects(*this, m_DataObjectList);
    shared_objects(*this, m_SharedObjects, DataTypeList::NumTypes);

    InitConnectionFactories(std::forward<ConnectionFactoryTypes>(connection_factory_types)...);
  }

  ~DDSNodeState();

  void ProcessEvents();

  void Shutdown();
  bool IsFullyShutdown();

  int GetDataObjectTypeIdForNameHash(uint32_t name_hash) const;
  int GetDatabaseObjectTypeIdForNameHash(uint32_t name_hash) const;
  int GetSharedObjectTypeIdForNameHash(uint32_t name_hash) const;
  int GetTargetObjectIdForNameHash(uint32_t name_hash) const;

  bool IsDatabaseObjectType(uint32_t name_has) const;

  template <typename DataType>
  int GetDataObjectTypeId() const
  {
    return GetDataObjectTypeIdForNameHash(StormReflTypeInfo<DataType>::GetNameHash());
  }

  template <typename DatabaseType>
  int GetDatabaseObjectTypeId() const
  {
    return GetDataObjectTypeIdForNameHash(StormReflTypeInfo<DatabaseType>::GetNameHash());
  }

  bool IsReadyToCreateObjects();
  bool CreateNewDataObject(int object_type_id, DDSKey & output_key);
  bool DestroyDataObject(int object_type_id, DDSKey key);

  template <typename DataType, typename ... Args, typename ... FuncArgs>
  bool CallObjectLocal(DDSKey key, void (DataType::* func)(FuncArgs...), Args && ... args)
  {
    int data_type = GetDataObjectTypeId<DataType>();
    if (data_type == -1)
    {
      return false;
    }

    auto & data_store = GetDataObjectStore(data_type);
    auto data_val = static_cast<DataType *>(data_store.GetDataObjectForKey(key));

    if (data_val == nullptr)
    {
      return false;
    }

    data_store.BeginObjectModification(key);
    (data_val->*func)(std::forward<Args>(args)...);
    data_store.EndObjectModification();
    return true;
  }

  template <typename DataType, typename ... Args, typename ... FuncArgs>
  void CallObjectRemote(DDSKey key, void (DataType::* func)(FuncArgs...), Args && ... args)
  {
    int data_type = GetDataObjectTypeId<DataType>();
    if (data_type == -1)
    {
      return;
    }

    DDSNodeInterface node_interface(*this, &GetDataObjectStore(data_type), key);
    node_interface.Call(func, key, std::forward<Args>(args)...);
  }

  void CreateTimer(std::chrono::system_clock::duration duration, DDSDeferredCallback & callback, std::function<void()> && function);
  void CreateTimer(std::chrono::system_clock::duration duration, DDSResponderCallData && responder_data);

  void CreateHttpRequest(const DDSHttpRequest & request, DDSDeferredCallback & callback, std::function<void(bool, const std::string &, const std::string &)> && function);
  void CreateHttpRequest(const DDSHttpRequest & request, DDSResponderCallData && responder_data);

  void CreateResolverRequest(const char * hostname, bool reverse_lookup, DDSDeferredCallback & callback, std::function<void(const DDSResolverRequest &)> && function);

  void CreateTokenValidatorRequest(uint64_t token, int type, DDSDeferredCallback & callback, std::function<void(bool, const std::string &)> && function);

  uint64_t RequestToken(std::string && token_data, int type, int timeout);
  bool ValidateToken(uint64_t token, int type, std::string & out_token_data);

  void SendTargetedMessage(DDSDataObjectAddress addr, DDSServerToServerMessageType type, std::string && message, bool force_process = false);

  DDSRoutingTableNodeInfo GetNodeInfo(DDSKey key);

  time_t GetNetworkTime() const;
  void * GetLocalObject(int target_object_type, DDSKey target_key);
private:

  friend class DDSCoordinatorClientProtocol;
  friend class DDSOutgoingKeyspaceTransfer;
  friend class DDSOutgoingKeyspaceTransferManager;
  friend class DDSServerToServerReceiver;
  friend class DDSServerToServerSender;
  friend class DDSNodeNetworkService;
  friend class DDSNodeInterface;
  friend class DDSEndpointFactoryBase;
  friend class DDSWebsiteFactoryBase;
  friend class DDSWebsiteFactoryStaticContent;
  friend class DDSConnectionInterface;
  friend class DDSEndpointInterface;
  friend class DDSHttpClient;
  friend class DDSAggregateSubscription;
  friend class DDSSharedLocalCopy;
  friend struct DDSResponder;

  template <class DataType, class DatabaseBackedType>
  friend class DDSDataObjectStore;

  template <typename DataType>
  friend class DDSSharedObjectCopy;

  friend void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallData & call_data);
  friend void * DDSGetSharedLocalCopyPtr(DDSNodeState * node_state, DDSKey shared_local_copy_key, int data_gen, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());
  friend void DDSSetSharedLocalCopyVersion(DDSSharedLocalCopyPtrBase & ptr, int data_gen, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());

  DDSNodeState(
    int num_data_object_types,
    const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
    const StormSockets::StormSocketClientFrontendWebsocketSettings & node_client_settings,
    const StormSockets::StormSocketClientFrontendHttpSettings & http_client_settings,
    const DDSCoordinatorClientSettings & coordinator_settings,
    const DDSDatabaseSettings & database_settings);


  template <typename EndpointFactoryType, typename ... Remaining>
  void InitConnectionFactories(EndpointFactoryType && factory_type, Remaining && ... remaining)
  {
    factory_type(*this, m_EndpointFactoryList, m_WebsiteFactoryList);
    InitConnectionFactories(std::forward<Remaining>(remaining)...);
  }

  void InitConnectionFactories()
  {

  }

  void SendSubscriptionCreate(DDSCreateSubscription && req);
  void SendSubscriptionDestroy(const DDSDestroySubscription & destroy);
  void ExportSharedSubscriptions(DDSDataObjectAddress addr, std::vector<std::pair<int, std::vector<DDSExportedSubscription>>> & exported_list);
  void ImportSharedSubscriptions(DDSDataObjectAddress addr, std::vector<std::pair<int, std::vector<DDSExportedSubscription>>> & exported_list, int routing_table_gen);

  void GotInitialCoordinatorSync(DDSNodeId node_id, const DDSRoutingTable & routing_table, bool initial_node, uint64_t server_secret, uint64_t client_secret);
  void GotNewRoutingTable(const DDSRoutingTable & routing_table);

  bool GotMessageFromCoordinator(DDSServerToServerMessageType type, DDSCoordinatorProtocolMessageType coordinator_type, const char * data);
  bool GotMessageFromCoordinator(DDSCoordinatorProtocolMessageType coordinator_type, const char * data);
  void GotMessageFromServer(DDSNodeId node_id, DDSServerToServerMessageType type, const char * data);

  void QueryObjectData(int object_type_id, DDSKey key, const char * collection);
  void QueryObjectData(const char * collection, DDSKey key, DDSResponderCallData && responder_call);
  void QueryObjectData(const char * collection, const char * query, DDSResponderCallData && responder_call);
  void QueryObjectDataMultiple(const char * collection, const char * query, DDSResponderCallData && responder_call);

  void InsertObjectData(int object_type_id, DDSKey key, const char * collection, const char * data, DDSResponderCallData && responder_call);
  void UpdateObjectData(int object_type_id, DDSKey key, const char * collection, const char * data, DDSResponderCallData * responder_call);
  void DeleteObjectData(int object_type_id, DDSKey key, const char * collection, DDSResponderCallData * responder_call);
  void DeleteObjectData(const char * collection, DDSKey key);

  void BeginQueueingMessages();
  void EndQueueingMessages();

  void UpdateCPUUsage();
  void UpdateObjects();
  void ProcessPendingExportedObjects();

  void HandleAllClear();
  bool IsAllClear() const;

  DDSNodeId GetNodeIdForKey(DDSKey key) const;

  DDSDataObjectStoreBase & GetDataObjectStore(int object_type_id);

  DDSNodeId GetLocalNodeId() const;
  const DDSRoutingTable & GetRoutingTable() const;
  DDSKeyRange GetLocalKeyRange() const;

  void GetConnectionFactoryPorts(std::vector<DDSNodePort> & endpoint_ports, std::vector<DDSNodePort> & website_ports) const;

  void PrepareObjectsForMove(DDSKeyRange requested_range);

  bool SendToLocalConnection(DDSConnectionId connection_id, const std::string & data);
  void DisconnectLocalConnection(DDSConnectionId connection_id);

  void RecheckOutgoingTargetedMessages();

  void HandleQueryByKey(int object_type_id, DDSKey key, const char * result_data, int ec);
  void HandleInsertResult(int ec, DDSResponderCallData & responder_call);
  void HandleSharedObjectDelta(const char * data);
  void HandleIncomingTargetedMessage(DDSDataObjectAddress addr, DDSServerToServerMessageType type, std::string & message);
  void DestroyDeferredCallback(DDSDeferredCallback * callback);

  const void * GetSharedObjectPointer(int shared_object_type);

  std::string GetMemoryReport();

private:

  bool m_IsReady = false;
  bool m_IsDefunct = false;
  bool m_IsShuttingDown = false;

  DDSNetworkBackend m_Backend;
  DDSNodeNetworkService m_NodeNetwork;
  DDSCoordinatorClientProtocol m_CoordinatorConnection;

  DDSIncomingKeyspaceTransferManager m_IncomingKeyspace;
  DDSOutgoingKeyspaceTransferManager m_OutgoingKeyspace;
  DDSNodeSharedObjectResolver m_SharedResolver;
  DDSSharedLocalCopyDatabase m_SharedLocalCopyDatabase;

  std::vector<DDSDataObjectListSync> m_PendingIncomingExportedObjects;

  DDSTimerSystem m_TimerSystem;
  DDSHttpClient m_HttpClient;
  DDSResolver m_Resolver;
  DDSTokenBroker m_TokenBroker;
  DDSTokenValidator m_TokenValidator;
  std::set<std::unique_ptr<DDSDeferredCallback>> m_DeferredCallbackList;

  std::optional<DDSNodeId> m_LocalNodeId;
  std::optional<DDSRoutingTable> m_RoutingTable;
  std::optional<DDSKeyRange> m_LocalKeyRange;
  std::vector<std::pair<DDSNodeId, DDSKeyRange>> m_RoutingKeyRanges;
  int m_LastRoutingTableAck = 0;
  int m_LastRoutingTableAllClear = 0;

  std::map<DDSDataObjectAddress, std::vector<std::pair<DDSServerToServerMessageType, std::string>>> m_PendingTargetedMessages;

  std::queue<std::tuple<DDSDataObjectAddress, DDSServerToServerMessageType, std::string>> m_QueuedTargetedMessages[(int)DDSDataObjectPriority::kCount];
  int m_QueueMessageDepth = 0;

  std::vector<std::unique_ptr<DDSDataObjectStoreBase>> m_DataObjectList;
  std::vector<std::unique_ptr<DDSSharedObjectCopyBase>> m_SharedObjects;
  std::vector<std::unique_ptr<DDSEndpointFactoryBase>> m_EndpointFactoryList;
  std::vector<std::unique_ptr<DDSWebsiteFactoryBase>> m_WebsiteFactoryList;

  std::unique_ptr<DDSDatabaseConnectionPool> m_Database;

  uint32_t m_LocalInterface = 0;
  int m_LocalPort = 0;

  uint64_t m_ClientSecret = 0;
  uint64_t m_ServerSecret = 0;

  time_t m_LastCPUUsageSync;
  time_t m_LastUpdate;
};

