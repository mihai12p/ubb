#ifndef _SYNCH_PRIMITIVE_HPP_
#define _SYNCH_PRIMITIVE_HPP_

template <typename T>
class ProducerConsumerQueue
{
public:
    ProducerConsumerQueue(_In_ int ProducersCount, _In_ int ConsumersCount) : ActiveProducers(ProducersCount), ActiveConsumers(ConsumersCount), FullCount(0) {}

    VOID
    Produce(_In_ const T& Item)
    {
        {
            std::lock_guard<std::mutex> lockGuard(this->Mutex);
            this->Queue.push(std::move(Item));
        }
        this->FullCount.release();
    }

    std::optional<T>
    Consume()
    {
        bool status = this->FullCount.try_acquire_for(std::chrono::nanoseconds(1));
        if (!status)
        {
            return std::nullopt;
        }
        std::lock_guard<std::mutex> lockGuard(this->Mutex);
        T item = std::move(this->Queue.front());
        this->Queue.pop();
        return item;
    }

    VOID
    UnregisterProducer()
    {
        --this->ActiveProducers;
    }

    VOID
    UnregisterConsumer()
    {
        --this->ActiveConsumers;
    }

    bool
    IsAnyProducerActive()
    {
        return this->ActiveProducers.load() > 0;
    }

    bool
    IsAnyConsumerActive()
    {
        return this->ActiveConsumers.load() > 0;
    }

    bool
    IsAnyProduced()
    {
        std::lock_guard<std::mutex> lockGuard(this->Mutex);
        return !this->Queue.empty();
    }

    bool
    IsAllConsumed()
    {
        std::lock_guard<std::mutex> lockGuard(this->Mutex);
        return this->Queue.empty();
    }

private:
    std::atomic<int> ActiveProducers;
    std::atomic<int> ActiveConsumers;
    std::queue<T> Queue;
    std::mutex Mutex;
    std::counting_semaphore<> FullCount;
};

#endif//_SYNCH_PRIMITIVE_HPP_