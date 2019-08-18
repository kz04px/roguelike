#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace cprof {

using tp = std::chrono::time_point<std::chrono::high_resolution_clock>;
using dur = std::chrono::duration<int64_t, std::micro>;

struct Data {
    dur duration_;
    int calls_;
};

class Profiler {
   public:
    static Profiler *get() {
        static Profiler p;
        return &p;
    }

    void add(const std::string id, const dur duration) {
        std::unique_lock<std::mutex> lock(mtx_);
        data_[id].duration_ += duration;
        data_[id].calls_ += 1;
    }

    void write(const std::string &path) {
        std::ofstream file(path);

        if (!file.is_open()) {
            return;
        }

        file << "id,calls,μs,μs/call" << std::endl;
        for (const auto &[id, data] : data_) {
            file << '\"' << id << '\"';
            file << "," << data.calls_;
            file << "," << data.duration_.count();
            file << "," << data.duration_.count() / data.calls_;
            file << std::endl;
        }
    }

   private:
    std::mutex mtx_;
    std::unordered_map<std::string, Data> data_;
};

class Timer {
   public:
    Timer(const std::string &id)
        : id_{id}, start_{std::chrono::high_resolution_clock::now()} {
    }

    ~Timer() {
        end_ = std::chrono::high_resolution_clock::now();
        const dur duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end_ -
                                                                  start_);
        Profiler::get()->add(id_, duration);
    }

   private:
    std::string id_;
    tp start_;
    tp end_;
};

}  // namespace cprof

#endif
