
#pragma once


#include "StormRefl/StormRefl.h"

#include "Foundation/Script/ScriptClassRef.h"
#include "Foundation/Script/ScriptClassDelegate.h"
#include "Foundation/Script/ScriptInterface.h"

#include "Engine/Input/TextInputContext.h"

class UIClickable;

class UITextInput : public ScriptClassInstanceBase<UITextInput>
{
public:
  STORM_REFL;
  STORM_REFL_FUNCS;
  STORM_REFL_NO_BASE;

  STORM_REFL_NODEFAULT;

public:

  UITextInput(std::shared_ptr<TextInputContext> && context);

  ScriptClassDelegate<bool, std::string> IsInvalidInput;

  void STORM_REFL_FUNC MakeCurrent(ScriptClassRef<UIClickable> container);
  std::string STORM_REFL_FUNC GetText();

private:

  friend class UIScriptInterface;

  std::shared_ptr<TextInputContext> m_TextInput;

};