#pragma once

#include "StormNetSys/NetServerSystemHandler.h"

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

template <typename State>
void NetServerSystemStateProcessor<State>::SerializeState(
    std::size_t target_client, const State & state, NetBitWriter & writer) const
{
  NetSerializer<State, NetBitWriter> serializer;
  serializer(state, writer);
}

template <typename State>
void NetServerSystemStateProcessor<State>::DeserializeState(
    State & state, NetBitReader & reader) const
{
  NetDeserializer<State, NetBitReader> deserializer;
  deserializer(state, reader);
}

template <typename State>
void NetServerSystemClientLocalDataProcessor<State>::SerializeClientLocalData(
    std::size_t target_client, const State & state, NetBitWriter & writer) const
{
  NetSerializer<State, NetBitWriter> serializer;
  serializer(state, writer);
}

template <typename State>
void NetServerSystemClientLocalDataProcessor<State>::DeserializeClientLocalData(
    State & state, NetBitReader & reader) const
{
  NetDeserializer<State, NetBitReader> deserializer;
  deserializer(state, reader);
}

template <typename Input, int MaxClients>
void NetServerSystemInputProcessor<Input, MaxClients>::SerializeInput(
    const Input & input, NetBitWriter & writer) const
{
  NetSerializer<Input, NetBitWriter> serializer;
  serializer(input, writer);
}

template <typename Input, int MaxClients>
void NetServerSystemInputProcessor<Input, MaxClients>::SerializeInput(
    std::size_t target_client, const Input & input, NetBitWriter & writer) const
{
  NetSerializer<Input, NetBitWriter> serializer;
  serializer(input, writer);
}

template <typename Input, int MaxClients>
void NetServerSystemInputProcessor<Input, MaxClients>::DeserializeInput(
    Input & input, NetBitReader & reader) const
{
  NetDeserializer<Input, NetBitReader> deserializer;
  deserializer(input, reader);
}

template <typename Event>
void NetServerSystemEffectEventProcessor<Event>::SerializeEffectEvent(
    std::size_t target_client, const Event & event, NetBitWriter & writer) const
{
  NetSerializer<Event, NetBitWriter> serializer;
  serializer(event, writer);
}

template <typename Event>
void NetServerSystemEffectEventProcessor<Event>::DeserializeEffectEvent(
    Event & event, NetBitReader & reader) const
{
  NetDeserializer<Event, NetBitReader> deserializer;
  deserializer(event, reader);
}

template <typename Event>
void NetServerSystemAuthorityEventProcessor<Event>::SerializeAuthorityEvent(
    std::size_t target_client, const Event & event, NetBitWriter & writer) const
{
  NetSerializer<Event, NetBitWriter> serializer;
  serializer(event, writer);
}

template <typename Event>
void NetServerSystemAuthorityEventProcessor<Event>::DeserializeAuthorityEvent(
    Event & event, NetBitReader & reader) const
{
  NetDeserializer<Event, NetBitReader> deserializer;
  deserializer(event, reader);
}

template <typename Event>
void NetServerSystemClientLocalEventProcessor<Event>::SerializeClientLocalEvent(
    std::size_t target_client, const Event & event, NetBitWriter & writer) const
{
  NetSerializer<Event, NetBitWriter> serializer;
  serializer(event, writer);
}

template <typename Event>
void NetServerSystemClientLocalEventProcessor<Event>::DeserializeClientLocalEvent(
    Event & event, NetBitReader & reader) const
{
  NetDeserializer<Event, NetBitReader> deserializer;
  deserializer(event, reader);
}

template <typename Event>
void NetServerSystemExternalEventProcessor<Event>::SerializeExternalEvent(
    std::size_t target_client, const Event & event, NetBitWriter & writer) const
{
  NetSerializer<Event, NetBitWriter> serializer;
  serializer(event, writer);
}

template <typename Event>
void NetServerSystemExternalEventProcessor<Event>::DeserializeExternalEvent(
    Event & event, NetBitReader & reader) const
{
  NetDeserializer<Event, NetBitReader> deserializer;
  deserializer(event, reader);
}

