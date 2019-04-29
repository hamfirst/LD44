
#include "Engine/EngineCommon.h"
#include "Engine/VisualEffect/VisualEffectFuncs.h"

#include "StormNet/NetMetaUtil.h"
#include "StormExpr/StormExprFunctionReg.h"

float Absf(float a)
{
  return fabs(a);
}

float Biasf(float a, float b)
{
  float x = (a - 0.5f) * 2.0f;
  float r = copysignf(powf(fabs(x), b), x);
  return r * 0.5f + 0.5f;
}

float NormalizeF(float a, float b, float r)
{
  return b * r + a * (1.0f - r);
}

float SymmetricNormalizeF(float a, float b, float r)
{
  return NormalizeF(a, b, 1.0f - fabs(r - 0.5f) * 2.0f);
}

float CircleX(float radius, float ra, float rb)
{
  if (rb < ra)
  {
    std::swap(ra, rb);
  }

  return rb * radius * cosf(2.0f * kPi * ra / rb);
}

float CircleY(float radius, float ra, float rb)
{
  if (rb < ra)
  {
    std::swap(ra, rb);
  }

  return rb * radius * sinf(2.0f * kPi * ra / rb);
}

StormExprFunctionList VisualEffectCreateFunctionList()
{
  StormExprFunctionList function_list;

  StormExprRegisterFunction("sqrt", function_list, sqrtf);
  StormExprRegisterFunction("sin", function_list, sinf);
  StormExprRegisterFunction("cos", function_list, cosf);
  StormExprRegisterFunction("tan", function_list, tanf);
  StormExprRegisterFunction("pow", function_list, powf);
  StormExprRegisterFunction("abs", function_list, Absf);
  StormExprRegisterFunction("bias", function_list, Biasf);
  StormExprRegisterFunction("n", function_list, NormalizeF);
  StormExprRegisterFunction("symn", function_list, SymmetricNormalizeF);
  StormExprRegisterFunction("cx", function_list, CircleX);
  StormExprRegisterFunction("cy", function_list, CircleY);
  return function_list;
}

