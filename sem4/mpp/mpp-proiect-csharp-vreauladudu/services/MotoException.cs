using System;

namespace services
{
    public class MotoException : Exception
    {
        public MotoException() { }
        public MotoException(string message) : base(message) { }
        public MotoException(string message, Exception innerException) : base(message, innerException) { }
    }
}