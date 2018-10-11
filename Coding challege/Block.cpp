#include "Block.h"

void Block::SetHasPower(bool power)
{
  hasPower = power;
}
bool Block::GetHasPower()
{
  return hasPower;
}

void Block::SetState(States s)
{
  state = s;
}
States Block::GetState()
{
  return state;
}
string Block::GetStateAsString()
{
  string value = "";

  switch (state)
  {
  case And:
    value = "And";
    break;
  case Xor:
    value = "Xor";
    break;
  case Special:
    value = "Special";
    break;
  default:
    value = "Sink";
    break;
  }

  return value;
}

void Block::SetName(int n)
{
  name = n;
}
int Block::GetName()
{
  return name;
}

Block::Block()
{
  Block::SetHasPower(true);
  Block::SetState(Sink);
}

Block::Block(int name, States s, bool power)
{
  Block::SetHasPower(power);
  Block::SetState(s);
  Block::SetName(name);
}
