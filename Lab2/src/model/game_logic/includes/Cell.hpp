#pragma once

class Cell {
private:
  bool m_isAlive;
  bool m_requestToChange;

public:
  Cell();
  Cell(bool alive);
  ~Cell();
  bool GetState();
  void ChangeState();
  void RequestToChange();
  bool ExistedRequest();
};
