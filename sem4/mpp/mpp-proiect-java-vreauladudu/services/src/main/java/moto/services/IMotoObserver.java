package moto.services;

import moto.Participant;

public interface IMotoObserver
{
    void participantAdded(Participant participant) throws MotoException;
}