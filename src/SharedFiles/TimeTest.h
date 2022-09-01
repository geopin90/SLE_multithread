#pragma once
#include <any>
#include <chrono>

namespace s21{

struct TimeTest{
    template<typename Algorithm,typename time>
    static int startest(Algorithm& alg, bool isMulti, int cycleNumber){
        try {
            auto begin = std::chrono::steady_clock::now();
            for (int i = 0; i < cycleNumber; i++) {
                try {
                    alg.start(isMulti);
                } catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                    break;
                }
            }
            auto end = std::chrono::steady_clock::now();
            int result = std::chrono::duration_cast<time>(end - begin).count();
            return result;
        } catch (const std::exception& e) {
            throw e;
        }
    }
};
}