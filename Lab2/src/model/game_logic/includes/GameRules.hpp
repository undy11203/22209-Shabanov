#pragma once

#include <vector>

class GameRules {
private:
  std::vector<int> m_cellForBirth;
  std::vector<int> m_cellForSurvive;

public:
  GameRules();
  GameRules(std::vector<int> cellForBirth, std::vector<int> cellForSurive);
  ~GameRules();
  std::vector<int> GetRuleAboutBirth() const;
  std::vector<int> GetRuleAboutSurvive() const;
};
