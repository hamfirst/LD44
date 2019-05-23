#pragma once

#include <memory>

#include <QTabWidget>
#include <QGridLayout>

#include "Runtime/ServerEntity/ServerEntityDef.refl.h"

#include "DocumentEditorWidgetBase.h"
#include "GenericFrame.h"
#include "PropertyEditor.h"

class ServerEntityEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  ServerEntityEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, ServerEntityDef & entity,
    DocumentChangeLinkDelegate && change_link_callback,  DocumentBeginTransactionDelegate && begin_transaction_callback, 
    DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

private:

  ServerEntityDef & m_ServerEntity;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<GenericFrame> m_ServerEntityProperties;

  PropertyEditor * m_PropertyEditor;
};
