#pragma once

#include <memory>

#include <QTabWidget>
#include <QGridLayout>

#include "Runtime/ClientEntity/ClientEntityDef.refl.h"

#include "DocumentEditorWidgetBase.h"
#include "GenericFrame.h"
#include "PropertyEditor.h"

class ClientEntityEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  ClientEntityEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, ClientEntityDef & entity, DocumentChangeLinkDelegate && change_link_callback,
    DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

private:

  ClientEntityDef & m_Entity;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<GenericFrame> m_EntityProperties;

  PropertyEditor * m_PropertyEditor;
};
