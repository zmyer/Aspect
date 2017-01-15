//
// Created by StevensChew on 17/1/15.
//

#ifndef ASPECT_AOPTEST_H
#define ASPECT_AOPTEST_H

#include "../src/Aspect.h"
#include "../../../../../../Library/Developer/CommandLineTools/usr/include/c++/v1/functional"

using namespace std;

namespace aspect {
    struct AA {
        void Before(int i) {
            std::cout << "Before from AA" << i << std::endl;
        }

        void After(int i) {
            std::cout << "After from AA" << i << std::endl;
        }
    };

    struct BB {
        void Before(int i) {
            std::cout << "Before from BB" << i << std::endl;
        }

        void After(int i) {
            std::cout << "After from BB" << i << std::endl;
        }
    };

    struct CC {
        void Before(int i) {
            std::cout << "Before from CC" << i << std::endl;
        }

        void After(int i) {
            std::cout << "After from CC" << i << std::endl;
        }
    };

    struct TimeElapsedAspect {
        void Before(int i) {
            m_lastTime = m_t.elapsed();
        }

        void After(int i) {
            std::cout << "time elapsed:" << m_t.elapsed() - m_lastTime << std::endl;
        }

    private:
        double m_lastTime;
        Timer m_t;
    };

    struct LoggingAspect {
        void Before(int i) {
            std::cout << "entering" << std::endl;
        }

        void After(int i) {
            std::cout << "leaving" << std::endl;
        }
    };

    void foo(int a) {
        std::cout << "real HT function:" << a << std::endl;
    }

    void GT() {
        std::cout << "real GT function" << std::endl;
    }

    void HT(int a) {
        std::cout << "real HT function:" << a << endl;
    }

    void TestAop() {
        std::function<void(int)> func = std::bind(&HT, std::placeholders::_1);
        Invoke<AA, BB>(std::function<void(int)>(std::bind(&HT, std::placeholders::_1)), 1);

        Invoke<AA, BB>(func, 1);
        Invoke<CC, BB>(&GT);
        Invoke<AA, BB>(&HT, 1);
        Invoke<AA, BB>([](int i) { }, 1);
        Invoke<CC, AA>([] { });
    }

    int main() {
        Invoke<LoggingAspect, TimeElapsedAspect>(&foo, 1);
        Invoke<TimeElapsedAspect, LoggingAspect>(&foo, 1);
    }
}

#endif //ASPECT_AOPTEST_H
