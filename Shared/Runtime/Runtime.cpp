
#include "Runtime/RuntimeCommon.h"

#include <StormData/StormDataJson.h>

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/DocumentResource/DocumentResourceManager.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"
#include "Runtime/ClientEntity/ClientEntityDef.refl.meta.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"
#include "Runtime/Atlas/AtlasDef.refl.meta.h"
#include "Runtime/VisualEffect/VisualEffectDef.refl.meta.h"
#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Map/MapEffectLayerTypeRegister.h"
#include "Runtime/Volume/VolumeTypeRegister.h"
#include "Runtime/Path/PathTypeRegister.h"
#include "Runtime/Anchor/AnchorTypeRegister.h"
#include "Runtime/Config/ConfigManager.h"
#include "Runtime/SpriteBase/SpriteAnimationEventRegister.h"
#include "Runtime/Asset/Asset.h"
#include "Runtime/ServerEntity/ServerEntitySystem.h"
#include "Runtime/ServerEntity/ServerEntityInitDataTypeDatabase.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"

void RuntimeInit()
{
  g_TypeDatabaseRegisterCallList.CallAll();
  g_ConfigRegistrationCallList.CallAll();
  g_ServerEntityRegisterCallList.CallAll();
  g_GlobalAssetListRegister.CallAll();
  g_GlobalDependentAssetRegister.CallAll();
  g_ServerEntitySystem.FinalizeTypes();
}

void RuntimeCleanup()
{

}

void RuntimeRegisterTypes(PropertyFieldDatabase & property_db)
{
  GetProperyMetaData<SpriteDef>(property_db);
  GetProperyMetaData<ClientEntityDef>(property_db);
  GetProperyMetaData<ServerEntityDef>(property_db);
  GetProperyMetaData<MapClientEntity>(property_db);
  GetProperyMetaData<MapServerEntity>(property_db);
  GetProperyMetaData<MapParallaxLayerObject>(property_db);
  GetProperyMetaData<MapDef>(property_db);
  GetProperyMetaData<UIDef>(property_db);
  GetProperyMetaData<AtlasDef>(property_db);
  GetProperyMetaData<VisualEffectDef>(property_db);

  g_ConfigTypeManager.RegisterConfigProperties(property_db);
}
