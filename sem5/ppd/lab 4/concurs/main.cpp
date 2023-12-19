#include "pch.h"
#include "SynchPrimitive.hpp"
#include "OrderedList.hpp"
#include "Participant.hpp"

#define COUNTRY_COUNT   5
#define TASKS_COUNT     10

int gProducersCount = 1;
int gConsumersCount = 4;
bool gIsSecquential = false;
std::mutex gMutex;

VOID
PrintResults(_In_ const OrderedList<Participant>& Participants)
{
    char outputFileName[MAX_PATH] = "D:\\ppd\\lab 4\\output\\Clasament.txt";
    if (gIsSecquential)
    {
        strcat_s(outputFileName, ".sequential");
    }
    std::ofstream fout(outputFileName);
    for (const Participant& participant : Participants)
    {
        if (participant.GetScore() == -1)
        {
            continue;
        }

        fout << participant.GetId() << ' ' << participant.GetScore() << '\n';
    }
    fout.flush();
    fout.close();
}

VOID
ProducerWorker(
    _Inout_ ProducerConsumerQueue<Participant>& PcQueue,
    _In_ const OrderedList<Participant>&        Participants,
    _In_ int ThreadIndex = 0
)
{
    for (int i = 1; i <= COUNTRY_COUNT; ++i)
    {
        for (int j = 1 + (ThreadIndex % (gProducersCount + 1)); j <= TASKS_COUNT; j += gProducersCount)
        {
            CHAR filePath[MAX_PATH] = { 0 };
            _snprintf_s(filePath, MAX_PATH, _TRUNCATE, "D:\\ppd\\lab 4\\inputs\\RezultateC%d_P%d.txt", i, j);

            std::ifstream fin(filePath);
            if (!fin.is_open())
            {
                continue;
            }

            int participantId, participantScore;
            while (fin >> participantId >> participantScore)
            {
                Participant participant;
                participant.SetId(participantId);
                participant.SetScore(participantScore);
                PcQueue.Produce(participant);
            }
            fin.close();
        }
    }

    PcQueue.UnregisterProducer();

    if (ThreadIndex == 0 && !gIsSecquential)
    {
        while (PcQueue.IsAnyConsumerActive())
        {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }

        PrintResults(Participants);
    }
}

VOID
ConsumerWorker(
    _Inout_ ProducerConsumerQueue<Participant>& PcQueue,
    _Inout_ OrderedList<Participant>&           Participants
)
{
    while (true)
    {
        if (!PcQueue.IsAnyProducerActive() && PcQueue.IsAllConsumed())
        {
            break;
        }

        std::optional<Participant> participant = PcQueue.Consume();
        if (!participant.has_value())
        {
            continue;
        }

        {
            std::lock_guard<std::mutex> lockGuard(gMutex);

            std::optional<Participant> existingParticipant = Participants.Get(participant.value());
            if (!existingParticipant.has_value())
            {
                if (participant.value().GetScore() == -1)
                {
                    participant.value().SetBlacklisted();
                }

                Participants.Insert(participant.value());
            }
            else
            {
                if (existingParticipant.value().IsBlacklisted())
                {
                    continue;
                }

                if (participant.value().GetScore() == -1)
                {
                    participant.value().SetBlacklisted();
                    Participants.Update(participant.value());
                }
                else if (participant.value().GetScore() > 0)
                {
                    participant.value().SetScore(participant.value().GetScore() + existingParticipant.value().GetScore());
                    Participants.Update(participant.value());
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::nanoseconds(1)); // try to prevent starvation
    }

    PcQueue.UnregisterConsumer();
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Use <p> <p_r>\n";
        return -1;
    }

    int threadsCount = atoi(argv[1]);
    gProducersCount = atoi(argv[2]);
    gConsumersCount = threadsCount - gProducersCount;

    ProducerConsumerQueue<Participant> pcQueue(gProducersCount, gConsumersCount);
    OrderedList<Participant> participants;

    if (gProducersCount == 1 && gConsumersCount == 1) // sequential
    {
        gIsSecquential = true;
        ProducerWorker(pcQueue, participants);
        ConsumerWorker(pcQueue, participants);
        PrintResults(participants);
    }
    else
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < gProducersCount; ++i)
        {
            threads.push_back(std::move(std::thread(ProducerWorker, std::ref(pcQueue), std::ref(participants), i)));
        }

        for (int i = 0; i < gConsumersCount; ++i)
        {
            threads.push_back(std::move(std::thread(ConsumerWorker, std::ref(pcQueue), std::ref(participants))));
        }

        for (std::thread& thread : threads)
        {
            thread.join();
        }
    }

    return 0;
}