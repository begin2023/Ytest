#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace Frame {
using CaseName = std::string;
using CaseFunc = std::function<void()>;
using YCase = std::pair<CaseName, CaseFunc>;

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
    auto iter = testCases_.begin();
    while (iter != testCases_.end()) {
      if ((*iter).first == caseName) {
        std::cout << "[RUN     ]" << caseName << std::endl;
        ((*iter).second)();
        std::cout << "[FINISH  ]" << caseName << std::endl;
        return;
      }
      iter++;
    }

    std::cout << "Error, no case named: " << caseName << std::endl;
  }

  void AddCase(CaseName caseName, CaseFunc caseFunc) {
    testCases_.emplace_back(YCase{caseName, caseFunc});
  }

private:
  FrameWork() = default;
  ~FrameWork() = default;
  FrameWork(const FrameWork &) = delete;
  FrameWork &operator=(const FrameWork &) & = delete;
  FrameWork(const FrameWork &&) = delete;
  FrameWork &operator=(const FrameWork &&) & = delete;
  std::vector<YCase> testCases_;
};

#define FUNCTION_NAME(name) #name
#define _CONCATE(x, y) x##y
#define CONCATE(x, y) _CONCATE(x, y)
#define ADD_LINENUMBER(x) CONCATE(x, __LINE__)

#define REGISTER_CASE(name, func)                                              \
  namespace {                                                                  \
  int ADD_LINENUMBER(register_case_) = []() {                                  \
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
      std::cout << "[TRUE    ]" << std::endl;                                  \
    } else {                                                                   \
      std::cout << "[FALSE   ]" << std::endl;                                  \
    }                                                                          \
  } while (false);

#define EXPECT_FALSE(express)                                                   \
  do {                                                                         \
    if (!express) {                                                             \
      std::cout << "[TRUE    ]" << std::endl;                                  \
    } else {                                                                   \
      std::cout << "[FALSE   ]" << std::endl;                                  \
    }                                                                          \
  } while (false);

#define EXPECT_EQ(v1, v2)                                                      \
  do {                                                                         \
    if (v1 == v2) {                                                            \
      std::cout << "[EQAUL   ]" << std::endl;                                  \
    } else {                                                                   \
      std::cout << "[NOT_EQ  ]" << std::endl;                                  \
    }                                                                          \
  } while (false);

#define EXPECT_NE(v1, v2)                                                      \
  do {                                                                         \
    if (v1 != v2) {                                                            \
      std::cout << "[EQAUL   ]" << std::endl;                                  \
    } else {                                                                   \
      std::cout << "[NOT_EQ  ]" << std::endl;                                  \
    }                                                                          \
  } while (false);
} // namespace Frame