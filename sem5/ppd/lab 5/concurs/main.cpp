#include "pch.h"
#include "SynchPrimitive.hpp"
#include "List.hpp"
#include "Participant.hpp"

#define COUNTRY_COUNT   5
#define TASKS_COUNT     10
#define QUEUE_SIZE      50

int gProducersCount = 4;
int gConsumersCount = 4;

VOID
PrintResults(_In_ const List<Participant>& Participants)
{
    char outputFileName[MAX_PATH] = "D:\\ppd\\lab 5\\output\\Clasament.txt";
    std::ofstream fout(outputFileName);

    std::vector<Participant> results;
    Participants.GetResults(results);
    for (const Participant& participant : results)
    {
        fout << participant.GetId() << ' ' << participant.GetScore() << ' ' << participant.GetCountry() << '\n';
    }
    fout.flush();
    fout.close();
}

VOID
ProducerWorker(
    _Inout_ ProducerConsumerQueue<Participant>& PcQueue,
    _In_ const List<Participant>&               Participants,
    _In_ int ThreadIndex = 0
)
{
    for (int i = 1; i <= COUNTRY_COUNT; ++i)
    {
        for (int j = 1 + ThreadIndex; j <= TASKS_COUNT; j += gProducersCount)
        {
            CHAR filePath[MAX_PATH] = { 0 };
            _snprintf_s(filePath, MAX_PATH, _TRUNCATE, "D:\\ppd\\lab 5\\inputs\\RezultateC%d_P%d.txt", i, j);

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
                participant.SetCountry(i);
                PcQueue.Produce(participant);
            }
            fin.close();
        }
    }

    PcQueue.UnregisterProducer();

    if (ThreadIndex == 0)
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
    _Inout_ List<Participant>&                  Participants
)
{
    while (true)
    {
        std::optional<Participant> participant = PcQueue.Consume();
        if (!participant.has_value())
        {
            break;
        }

        Participants.Process(participant.value());
    }

    PcQueue.UnregisterConsumer();
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Use <p_r> <p_w>\n";
        return -1;
    }

    gProducersCount = atoi(argv[1]);
    gConsumersCount = atoi(argv[2]);

    ProducerConsumerQueue<Participant> pcQueue(QUEUE_SIZE, gProducersCount, gConsumersCount);
    List<Participant> participants;

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

    return 0;
}