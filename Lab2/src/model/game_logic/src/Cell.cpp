#include "../includes/Cell.hpp"

Cell::Cell() : m_isAlive{false}, m_requestToChange{false} {}
Cell::Cell(bool alive) : m_isAlive{alive}, m_requestToChange{false} {}

Cell::~Cell() {}

bool Cell::GetState() { return m_isAlive; }

void Cell::ChangeState() { m_isAlive = !m_isAlive; }

void Cell::RequestToChange() { m_requestToChange = !m_requestToChange; }

bool Cell::ExistedRequest() {
    bool result = m_requestToChange;
    m_requestToChange = false;
    return result;
}