#pragma once

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/SkipField/SkipFieldIterator.h"

class ClientComponentIteratorBase
{
protected:
  SkipFieldIterator m_Iterator;

  void * (*m_Deref)(const SkipFieldIterator & itr);
  void(*m_AdvanceIterator)(SkipFieldIterator & itr);
  bool(*m_CompareIterator)(const SkipFieldIterator & itr1, const SkipFieldIterator & itr2);
};

template <typename ClientComponentType>
class ClientComponentIterator : public ClientComponentIteratorBase
{
public:

  NullOptPtr<ClientComponentType> operator *()
  {
    return static_cast<ClientComponentType>(m_Deref(m_Iterator));
  }

  NullOptPtr<const ClientComponentType> operator *() const
  {
    return static_cast<ClientComponentType>(m_Deref(m_Iterator));
  }

  NullOptPtr<ClientComponentType> operator ->()
  {
    return static_cast<ClientComponentType>(m_Deref(m_Iterator));
  }

  NullOptPtr<const ClientComponentType> operator ->() const
  {
    return static_cast<ClientComponentType>(m_Deref(m_Iterator));
  }

  ClientComponentIterator<ClientComponentType> & operator++()
  {
    m_AdvanceIterator(m_Iterator);
  }

  bool operator == (const SkipFieldIterator & itr1, const SkipFieldIterator & itr2)
  {
    return m_CompareIterator(itr1, itr2);
  }

private:
  friend class ComponentType;

};

