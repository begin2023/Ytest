#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

namespace Frame {
using CaseName = std::string;
using CaseFunc = std::function<void()>;
class FrameWork {
public:
  static FrameWork &Instance() {
    static FrameWork frame;
    return frame;
  }

  void RunAllCases() {
    if (testCases_.size() == 0U) {
      std::cout << "Warn, there is no any case!" << std::endl;
      return;
    }
    for (const auto &testCase : testCases_) {
      std::cout << "[RUN     ]" << testCase.first << std::endl;
      (testCase.second)();
      std::cout << "[FINISH  ]" << testCase.first << std::endl;
    }
  }

  void RunCase(CaseName caseName) {
    if (testCases_.find(caseName) != testCases_.end()) {
      std::cout << "[RUN     ]" << caseName << std::endl;
      (testCases_[caseName])();
      std::cout << "[FINISH  ]" << caseName << std::endl;
      return;
    }
    std::cout << "Error, no case named: " << caseName << std::endl;
  }

  void AddCase(CaseName caseName, CaseFunc caseFunc) {
    testCases_[caseName] = caseFunc;
  }

private:
  FrameWork() = default;
  ~FrameWork() = default;
  FrameWork(const FrameWork &) = delete;
  FrameWork &operator=(const FrameWork &) & = delete;
  FrameWork(const FrameWork &&) = delete;
  FrameWork &operator=(const FrameWork &&) & = delete;
  std::unordered_map<CaseName, CaseFunc> testCases_;
};

#define FUNCTION_NAME(name) #name
#define _CONCATE(x, y) x##y
#define CONCATE(x, y) _CONCATE(x, y)
#define ADD_LINENUMBER(x) CONCATE(x, __LINE__)

#define REGISTER_CASE(name, func)                                              \
  namespace {                                                                  \
  int ADD_LINENUMBER(register_case_) = []() {                                  \
    std::cout << (name) << std::endl;                                          \
    FrameWork::Instance().AddCase(name, func);                                 \
    return 0;                                                                  \
  }();                                                                         \
  }

#define TEST(test_suite_name, case_name)                                       \
  void CONCATE(test_suite_name, case_name)();                                  \
  REGISTER_CASE(FUNCTION_NAME(test_suite_name##_##case_name),                  \
                CONCATE(test_suite_name, case_name))                           \
  void CONCATE(test_suite_name, case_name)()

#define EXPECT_TRUE(express)                                                   \
  do {                                                                         \
    if (express) {                                                             \
      std::cout << "[OK      ]" << std::endl;                                  \
    } else {                                                                   \
      std::cout << "[FAILED  ]" << std::endl;                                  \
    }                                                                          \
  } while (false);
} // namespace Frame