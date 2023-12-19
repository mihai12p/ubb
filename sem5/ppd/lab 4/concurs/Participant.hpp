#ifndef _PARTICIPANT_HPP_
#define _PARTICIPANT_HPP_

class Participant
{
public:
    Participant() = default;
    ~Participant() = default;

    int
    GetId() const
    {
        return this->Id;
    }

    VOID
    SetId(_In_ int NewId)
    {
        this->Id = NewId;
    }

    int
    GetScore() const
    {
        return this->Score;
    }

    VOID
    SetScore(_In_ int NewScore)
    {
        this->Score = NewScore;
    }

    bool
    IsBlacklisted() const
    {
        return this->Blacklisted;
    }

    VOID
    SetBlacklisted()
    {
        this->Blacklisted = true;
    }

    bool operator<(_In_ const Participant& Other) const
    {
        return this->Score > Other.Score || (this->Score == Other.Score && this->Id < Other.Id); // decreasing order
    }

private:
    int Id = -1;
    int Score = 0;
    bool Blacklisted = false;
};

#endif//_PARTICIPANT_HPP_