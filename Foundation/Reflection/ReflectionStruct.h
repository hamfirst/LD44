#pragma once

#include "Foundation\Reflection\Reflection.h"


// A helper metafunction for adding const to a type
template<class M, class T>
struct make_const
{
  typedef T type;
};

#define MEMBER_EAT(__VAR_ARGS__) __VAR_ARGS__

#define MEMBER_OP (
#define MEMBER_CP )
#define MEMBER_DECL(x) MEMBER_DECL_EXCTRACT x
#define MEMBER_TYPE(x) MEMBER_TYPE_EXCTRACT x 
#define MEMBER_NAME(x) MEMBER_NAME_EXCTRACT x 
#define MEMBER_TYPE_STR(x) MEMBER_TYPE_EXCTRACT_STR x
#define MEMBER_NAME_STR(x) MEMBER_NAME_EXCTRACT_STR x 

#define MEMBER_DECL_EXCTRACT(X, Y, ...) Y X
#define MEMBER_TYPE_EXCTRACT(X, Y, ...) Y
#define MEMBER_NAME_EXCTRACT(X, Y, ...) X
#define MEMBER_TYPE_EXCTRACT_STR(X, Y, ...) BOOST_PP_STRINGIZE(Y)
#define MEMBER_NAME_EXCTRACT_STR(X, Y, ...) BOOST_PP_STRINGIZE MEMBER_OP X MEMBER_CP

template<class M, class T>
struct make_const<const M, T>
{
  typedef typename std::add_const<T>::type type;
};

template <class M, class T>
struct match_const
{
  typedef typename std::conditional<std::is_const<M>::value, typename std::add_const<T>::type, typename std::remove_const<T>::type>::type type;
};

#define REFL_MEMBERS(...) \
static constexpr int fields_n = BOOST_PP_VARIADIC_SIZE(__VA_ARGS__); \
static constexpr bool is_reflectable = true; \
auto & GetDefault() { static std::remove_reference<decltype(*this)>::type def; return def; } \
uint32_t GetTypeNameHash() const { return crc32(typeid(*this).name()); }\
friend struct reflector; \
REFLECTION_PARENT_INFO \
template<int N>\
struct field_data_static {}; \
template<int N, class Self> \
struct field_data {}; \
BOOST_PP_SEQ_FOR_EACH_I(REFLECT_EACH, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))


#define REFLECT_EACH(r, data, i, x) \
MEMBER_DECL(x) = {}; \
template<> \
struct field_data_static<i> \
{ \
    const char * GetName() const \
    {\
        return MEMBER_NAME_STR(x); \
    }\
    constexpr uint32_t GetNameHash() const \
    {\
      return COMPILE_TIME_CRC32_STR(MEMBER_NAME_STR(x)); \
    }\
    const char * GetType() const \
    {\
        return MEMBER_TYPE_STR(x); \
    }\
};\
template<class Self> \
struct field_data<i, Self> : field_data_static<i> \
{ \
    Self & self; \
    typedef MEMBER_TYPE(x) member_type; \
    field_data(Self & self) : self(self) {} \
    \
    typename make_const<Self, MEMBER_TYPE(x)>::type & Get() \
    { \
        return self.MEMBER_NAME(x); \
    }\
    typename std::add_const<MEMBER_TYPE(x)>::type & Get() const \
    { \
        return self.MEMBER_NAME(x); \
    }\
    void SetDefault() \
    {\
      self.MEMBER_NAME(x) = self.GetDefault().MEMBER_NAME(x); \
    }\
};\

#define REFL_MEMBERS_DERIVED(BaseClass, ...) \
using MyBase = BaseClass; \
static constexpr int fields_n = MyBase::fields_n + BOOST_PP_VARIADIC_SIZE(__VA_ARGS__); \
auto & GetDefault() { static std::remove_reference<decltype(*this)>::type def; return def; } \
uint32_t GetTypeNameHash() const { return crc32(typeid(*this).name()); }\
friend struct reflector; \
template<int N> \
struct field_data_static \
{ \
  MyBase::field_data_static<N> parent_val; \
  const char * GetName() const { return parent_val.GetName(); } \
  constexpr uint32_t GetNameHash() const { return parent_val.GetNameHash(); } \
  const char * GetType() const { return parent_val.GetType(); } \
}; \
template<int N, class Self> \
struct field_data : public field_data_static<N> \
{ \
  MyBase::field_data<N, typename match_const<Self, MyBase>::type> parent_val; \
  typedef typename MyBase::field_data<N, MyBase>::member_type member_type; \
  field_data(Self & self) : parent_val(self) {} \
  auto Get() { return parent_val.Get(); } \
  auto Get() const { return parent_val.Get(); } \
  void SetDefault() { parent_val.SetDefault(); } \
}; \
BOOST_PP_SEQ_FOR_EACH_I(REFLECT_EACH_DERIVED, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))


#define REFLECT_EACH_DERIVED(r, data, i, x) \
MEMBER_DECL(x) = {}; \
template<> \
struct field_data_static<MyBase::fields_n + i> \
{ \
    const char * GetName() const \
    {\
        return MEMBER_NAME_STR(x); \
    }\
    constexpr uint32_t GetNameHash() const \
    {\
      return COMPILE_TIME_CRC32_STR(MEMBER_NAME_STR(x)); \
    }\
    const char * GetType() const \
    {\
        return MEMBER_TYPE_STR(x); \
    }\
};\
template<class Self> \
struct field_data<MyBase::fields_n + i, Self> : field_data_static<MyBase::fields_n + i> \
{ \
    Self & self; \
    typedef MEMBER_TYPE(x) member_type; \
    field_data(Self & self) : self(self) {} \
    \
    typename make_const<Self, MEMBER_TYPE(x)>::type & Get() \
    { \
        return self.MEMBER_NAME(x); \
    }\
    typename std::add_const<MEMBER_TYPE(x)>::type & Get() const \
    { \
        return self.MEMBER_NAME(x); \
    }\
    void SetDefault() \
    {\
      self.MEMBER_NAME(x) = self.GetDefault().MEMBER_NAME(x); \
    }\
};\

template <class C, class Visitor, int I>
struct FieldIterator
{
  void operator()(C& c, Visitor & v)
  {
    auto f = C::field_data<C::fields_n - I, C>(c);
    v(f);
    FieldIterator <C, Visitor, I - 1>() (c, v);
  }
};

template <class C, class Visitor>
struct FieldIterator<C, Visitor, 0>
{
  void operator()(C& c, Visitor & v)
  {

  }
};

template <class C, class Visitor, int I>
struct FieldSelector
{
  void operator()(C& c, Visitor & v, uint32_t field_name_hash)
  {
    auto f = C::field_data<C::fields_n - I, C>(c);

    if (f.GetNameHash() == field_name_hash)
    {
      v(f);
      return;
    }

    FieldSelector <C, Visitor, I - 1>() (c, v, field_name_hash);
  }
};

template <class C, class Visitor>
struct FieldSelector<C, Visitor, 0>
{
  void operator()(C& c, Visitor & v, uint32_t field_name_hash)
  {

  }
};

template <class C, class Visitor, int I>
struct FieldExaminer
{
  void operator()(Visitor & v)
  {
    auto f = C::field_data_static<C::fields_n - I>();
    v(f);
    FieldExaminer <C, Visitor, I - 1>() (v);
  }
};

template <class C, class Visitor>
struct FieldExaminer<C, Visitor, 0>
{
  void operator()(Visitor & v)
  {

  }
};

template<class C, class Visitor>
void VisitEach(C & c, Visitor & v)
{
  FieldIterator<C, Visitor, C::fields_n> itr;
  itr(c, v);
}

template<class C, class Visitor>
void VisitField(C & c, Visitor & v, uint32_t field_name_hash)
{
  FieldSelector<C, Visitor, C::fields_n> itr;
  itr(c, v, field_name_hash);
}

template<class C, class Visitor>
void ExamineFields(Visitor & v)
{
  FieldExaminer<C, Visitor, C::fields_n> itr;
  itr(v);
}

template <class C>
void SetValueDefault(C & c, uint32_t field_name_hash)
{
  VisitField(c, [](auto field_data) { field_data.SetDefault(); }, field_name_hash);
}

template <class C>
std::vector<std::string> GetFields()
{
  std::vector<std::string> fields;
  auto visitor = [&](auto field_data) { fields.push_back(field_data.GetName()); };

  ExamineFields<C, decltype(visitor)>(visitor);
  return fields;
}
