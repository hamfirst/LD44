
#include <StormData/StormDataParent.h>

#include "Runtime/ServerEntity/ServerEntityDef.refl.meta.h"

#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "ServerEntityEditor.h"


ServerEntityEditor::ServerEntityEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, ServerEntityDef & server_entity,
  DocumentChangeLinkDelegate && change_link_callback,  DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  DocumentEditorWidgetBase(editor_container, property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
    m_ServerEntity(server_entity),
  m_Layout(std::make_unique<QGridLayout>()),
  m_ServerEntityProperties(std::make_unique<GenericFrame>("Server Entity Properties", this))
{
  m_Layout->setColumnStretch(0, 3);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 1);
  m_Layout->setColumnMinimumWidth(1, 300);

  m_Layout->addWidget(m_ServerEntityProperties.get(), 0, 1);

  m_PropertyEditor = m_ServerEntityProperties->CreateWidget<PropertyEditor>();
  m_PropertyEditor->LoadStruct(this, m_ServerEntity, true);

  setLayout(m_Layout.get());
}

REGISTER_EDITOR("ServerEntity", ServerEntityEditor, ServerEntityDef, ".serverent", "Gameplay");
