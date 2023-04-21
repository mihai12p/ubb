using System;

namespace mpp_proiect_csharp_vreauladudu
{
    public enum UserEvent
    {
        ParticipantAdded
    }

    public class MotoUserEvent : EventArgs
    {
        private readonly UserEvent userEvent;
        private readonly Object data;

        public MotoUserEvent(UserEvent userEvent, object data)
        {
            this.userEvent = userEvent;
            this.data = data;
        }

        public UserEvent UserEventType { get { return userEvent; } }

        public object Data { get { return data; } }
    }
}