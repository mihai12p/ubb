#ifndef _ORDERED_LIST_HPP_
#define _ORDERED_LIST_HPP_

template <class T>
class OrderedList
{
public:
    VOID
    Insert(_In_ const T& Value)
    {
        std::lock_guard<std::mutex> lockGuard(this->Mutex);
        auto it = std::lower_bound(this->Data.begin(), this->Data.end(), Value);
        this->Data.insert(it, Value);
    }

    VOID
    Update(_In_ const T& NewValue)
    {
        std::lock_guard<std::mutex> lockGuard(this->Mutex);
        for (T& item : this->Data)
        {
            if (item.GetId() != NewValue.GetId())
            {
                continue;
            }

            item = NewValue;
            std::sort(this->Data.begin(), this->Data.end());
            return;
        }
    }

    std::optional<T>
    Get(_In_ const T& Value)
    {
        std::lock_guard<std::mutex> lockGuard(this->Mutex);
        for (const T& item : this->Data)
        {
            if (item.GetId() != Value.GetId())
            {
                continue;
            }

            return item;
        }

        return std::nullopt;
    }

    typename std::vector<T>::iterator begin()
    {
        return this->Data.begin();
    }

    typename std::vector<T>::iterator end()
    {
        return this->Data.end();
    }

    typename std::vector<T>::const_iterator begin() const
    {
        return this->Data.begin();
    }

    typename std::vector<T>::const_iterator end() const
    {
        return this->Data.end();
    }

private:
    std::vector<T> Data;
    std::mutex Mutex;
};


#endif//_ORDERED_LIST_HPP_