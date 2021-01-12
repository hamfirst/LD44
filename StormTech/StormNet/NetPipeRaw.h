#pragma once

#include <functional>

#include "NetSerialize.h"
#include "NetDeserialize.h"
#include "NetTransmitter.h"

class NetBitWriter;
class NetBitReader;

class NetPipeRawSender
{
public:

  void Initialize(NetTransmitter * transmitter, NetPipeMode mode, int channel_index, int channel_bits)
  {
    m_Transmitter = transmitter;
    m_Mode = mode;
    m_ChannelIndex = channel_index;
    m_ChannelBits = channel_bits;
  }

  void Sync()
  {
    if(m_Sync)
    {
      NetBitWriter & writer = m_Transmitter->CreateMessage(m_Mode, m_ChannelIndex, m_ChannelBits);
      m_Sync(writer);
      m_Transmitter->SendMessage(writer);
    }
  }

  void GotAck(NetBitReader & reader)
  {
    if(m_Ack)
    {
      m_Ack(reader);
    }
  }

  void RegisterSyncCallback(std::function<void (NetBitWriter &)> && callback)
  {
    m_Sync = callback;
  }

  void RegisterAckCallback(std::function<void (NetBitReader &)> && callback)
  {
    m_Ack = callback;
  }

private:
  NetTransmitter * m_Transmitter;
  NetPipeMode m_Mode;
  int m_ChannelIndex;
  int m_ChannelBits;

  std::function<void (NetBitWriter &)> m_Sync;
  std::function<void (NetBitReader &)> m_Ack;
};

class NetPipeRawReceiver
{
public:
  void Initialize(NetTransmitter * transmitter, NetPipeMode mode, int channel_index, int channel_bits)
  {
    m_Transmitter = transmitter;
    m_Mode = mode;
    m_ChannelIndex = channel_index;
    m_ChannelBits = channel_bits;
  }

  void SendAck()
  {
    if(m_Ack)
    {
      NetBitWriter & writer = m_Transmitter->CreateAck(m_Mode, m_ChannelIndex, m_ChannelBits);
      m_Ack(writer);
      m_Transmitter->SendMessage(writer);
    }
  }

  void GotMessage(NetBitReader & reader)
  {
    if(m_Sync)
    {
      m_Sync(reader);
    }
  }

  void RegisterSyncCallback(std::function<void (NetBitReader &)> && callback)
  {
    m_Sync = callback;
  }

  void RegisterAckCallback(std::function<void (NetBitWriter &)> && callback)
  {
    m_Ack = callback;
  }

private:

  NetTransmitter * m_Transmitter;
  NetPipeMode m_Mode;
  int m_ChannelIndex;
  int m_ChannelBits;

  std::function<void (NetBitReader &)> m_Sync;
  std::function<void (NetBitWriter &)> m_Ack;
};

template <NetPipeMode Mode = NetPipeMode::kReliable>
struct NetPipeRaw
{
  using SenderType = NetPipeRawSender;
  using ReceiverType = NetPipeRawReceiver

  static const NetPipeMode PipeMode = Mode;
};
