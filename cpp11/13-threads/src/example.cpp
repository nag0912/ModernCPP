// std::thread & concurrency basics — real-time example
// Compile: g++ -std=c++11 -O2 -Wall example.cpp -o example -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <vector>
#include <queue>

std::mutex coutMutex; // protects std::cout from interleaved output across threads

void worker(int id) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "Worker thread " << id << " running on thread id "
              << std::this_thread::get_id() << "\n";
}

// --- atomic counter demo ---
std::atomic<int> atomicCounter{0};
void incrementAtomic(int times) {
    for (int i = 0; i < times; ++i) atomicCounter++;
}

// --- producer/consumer with condition_variable ---
std::mutex queueMutex;
std::condition_variable cv;
std::queue<int> dataQueue;
bool finished = false;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            dataQueue.push(i);
        }
        cv.notify_one(); // wake the consumer
    }
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        finished = true;
    }
    cv.notify_one();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [] { return !dataQueue.empty() || finished; });

        while (!dataQueue.empty()) {
            int val = dataQueue.front();
            dataQueue.pop();
            lock.unlock();
            {
                std::lock_guard<std::mutex> coutLock(coutMutex);
                std::cout << "Consumed: " << val << "\n";
            }
            lock.lock();
        }
        if (finished && dataQueue.empty()) break;
    }
}

int main() {
    std::cout << "--- Basic std::thread, must join or detach ---\n";
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) threads.emplace_back(worker, i);
    for (auto& t : threads) t.join(); // REQUIRED -- forgetting this calls std::terminate()

    std::cout << "\n--- std::atomic: lock-free counter from multiple threads ---\n";
    std::thread t1(incrementAtomic, 100000);
    std::thread t2(incrementAtomic, 100000);
    t1.join();
    t2.join();
    std::cout << "Expected 200000, got: " << atomicCounter << " (always correct with atomic)\n";

    std::cout << "\n--- producer/consumer with condition_variable ---\n";
    std::thread prod(producer);
    std::thread cons(consumer);
    prod.join();
    cons.join();

    std::cout << "\n--- end of main ---\n";
    return 0;
}
