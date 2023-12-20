#ifndef _LIST_HPP_
#define _LIST_HPP_

template <class T>
class Node
{
public:
    T Data;
    Node* Flink = nullptr;
    std::mutex Mutex;

    explicit Node(_In_ const T& Data) : Data{ Data }, Flink{ nullptr } { }
    Node() = delete;
    ~Node() = default;

    Node(_In_ const Node& Other) = delete;
    Node& operator=(_In_ const Node& Other) = delete;

    Node(_Inout_ Node&& Other) = delete;
    Node& operator=(_Inout_ Node&& Other) = delete;
};

template <class T>
class List
{
public:
    List()
    {
        this->Head = new Node<T>(T{}); // sentinel
        this->Tail = new Node<T>(T{}); // sentinel
        this->Head->Flink = Tail;
    }

    ~List() noexcept
    {
        Node<T>* current = this->Head;
        while (current)
        {
            Node<T>* next = current->Flink;
            delete current;
            current = next;
        }
    }

    _Requires_exclusive_lock_held_(LastNode->Mutex)
    VOID
    EmplaceBack(_Inout_ T& Data, _Inout_ Node<T>* LastNode)
    {
        if (Data.GetScore() == -1)
        {
            Data.SetBlacklisted();
        }

        Node<T>* newNode = new Node<T>(Data);
        newNode->Flink = this->Tail;
        LastNode->Flink = newNode;
    }

    VOID
    Process(_Inout_ T& Data)
    {
        std::unique_lock<std::mutex> lockCurrent(this->Head->Mutex);
        Node<T>* current = this->Head;
        Node<T>* prev = current;

        while (current != this->Tail)
        {
            Node<T>* next = current->Flink;
            if (next != this->Tail)
            {
                next->Mutex.lock();
            }

            if (current != this->Head && current->Data.GetId() == Data.GetId())
            {
                if (!current->Data.IsBlacklisted())
                {
                    if (Data.GetScore() == -1)
                    {
                        current->Data.SetBlacklisted();
                    }
                    else if (Data.GetScore() > 0)
                    {
                        current->Data.SetScore(current->Data.GetScore() + Data.GetScore());
                    }
                }

                if (next != this->Tail)
                {
                    next->Mutex.unlock();
                }
                return;
            }

            if (next != this->Tail)
            {
                lockCurrent.unlock(); // do not release the lock for the last element as we want to perform an update on it
                lockCurrent = std::unique_lock<std::mutex>(next->Mutex, std::adopt_lock);
            }
            prev = current;
            current = next;
        }

        this->EmplaceBack(Data, prev);
    }

    _No_competing_thread_
    VOID
    GetResults(_Inout_ std::vector<T>& Results) const
    {
        Node<T>* current = this->Head;
        while (current && current->Flink != this->Tail)
        {
            Node<T>* next = current->Flink;
            Results.emplace_back(next->Data);
            current = next;
        }

        std::sort(Results.begin(), Results.end());
    }

private:
    Node<T>* Head = nullptr;
    Node<T>* Tail = nullptr;
};


#endif//_LIST_HPP_