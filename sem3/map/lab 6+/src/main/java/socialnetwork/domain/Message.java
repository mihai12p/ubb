package socialnetwork.domain;

import java.sql.Timestamp;
import java.util.Objects;

public class Message extends Entity<Integer>
{
    private int idUser1;
    private int idUser2;
    String content;
    Timestamp date_sent;

    public Message(int idUser1, int idUser2, String content, Timestamp date_sent)
    {
        this.idUser1 = idUser1;
        this.idUser2 = idUser2;
        this.content = content;
        this.date_sent = date_sent;
    }

    public int getIdUser1()
    {
        return this.idUser1;
    }

    public int getIdUser2()
    {
        return this.idUser2;
    }

    public String getContent()
    {
        return this.content;
    }

    public Timestamp getDate_sent()
    {
        return this.date_sent;
    }

    public void setIdUser1(int idUser1)
    {
        this.idUser1 = idUser1;
    }

    public void setIdUser2(int idUser2)
    {
        this.idUser2 = idUser2;
    }

    public void setContent(String content)
    {
        this.content = content;
    }

    public void setDate_sent(Timestamp date_sent)
    {
        this.date_sent = date_sent;
    }

    @Override
    public String toString()
    {
        return "Message{" +
                "idUser1=" + idUser1 +
                ", idUser2=" + idUser2 +
                ", content='" + content + '\'' +
                ", date_sent=" + date_sent +
                '}';
    }

    @Override
    public boolean equals(Object o)
    {
        if (this == o)
        {
            return true;
        }
        if (!(o instanceof Message message))
        {
            return false;
        }

        return getDate_sent().equals(message.getDate_sent());
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(getDate_sent());
    }
}
