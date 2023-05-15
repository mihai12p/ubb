USE Motorshop;
GO

----------------------------------------------------------------------

-- Scenariu NEREZOLVAT DirtyReads (BAD)
	BEGIN TRAN
		UPDATE Clienti SET nume='DirtyReads' WHERE CNP='1930207167896'
		WAITFOR DELAY '00:00:05'
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked'

-- Scenariu REZOLVAT DirtyReads (GOOD)
	BEGIN TRAN
		UPDATE Clienti SET nume='DirtyReads' WHERE CNP='1930207167896'
		WAITFOR DELAY '00:00:05'
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked'

----------------------------------------------------------------------

-- Scenariu NEREZOLVAT Non-repeatable reads (BAD)
	INSERT INTO Clienti(CNP, Nume, Prenume, Adresa, Telefon, Email) VALUES ('1234567891234', 'Nume', 'Prenume', 'Adresa', 'Telefon', 'Email');
	BEGIN TRAN
		WAITFOR DELAY '00:00:05'
		UPDATE Clienti SET Nume='NonRepeatableReads' WHERE CNP='1234567891234'
		COMMIT TRAN
		SELECT 'Transaction commited'

	SELECT * FROM Clienti
	DELETE FROM Clienti WHERE CNP='1234567891234'
	SELECT * FROM Clienti

-- Scenariu REZOLVAT Non-repeatable reads (GOOD)
	INSERT INTO Clienti(CNP, Nume, Prenume, Adresa, Telefon, Email) VALUES ('1234567891234', 'Nume', 'Prenume', 'Adresa', 'Telefon', 'Email');
	BEGIN TRAN
		WAITFOR DELAY '00:00:05'
		UPDATE Clienti SET Nume='NonRepeatableReads' WHERE CNP='1234567891234'
		COMMIT TRAN
		SELECT 'Transaction commited'

	SELECT * FROM Clienti
	DELETE FROM Clienti WHERE CNP='1234567891234'
	SELECT * FROM Clienti

----------------------------------------------------------------------

-- Scenariu NEREZOLVAT Phantom reads (BAD)
	BEGIN TRAN
		WAITFOR DELAY '00:00:05'
		INSERT INTO Clienti(CNP, Nume, Prenume, Adresa, Telefon, Email) VALUES ('1234567891234', 'Nume', 'Prenume', 'Adresa', 'Telefon', 'Email');
		COMMIT TRAN
		SELECT 'Transaction commited'

-- Scenariu REZOLVAT Phantom reads (GOOD)
	BEGIN TRAN
		WAITFOR DELAY '00:00:05'
		INSERT INTO Clienti(CNP, Nume, Prenume, Adresa, Telefon, Email) VALUES ('1234567891234', 'Nume', 'Prenume', 'Adresa', 'Telefon', 'Email');
		COMMIT TRAN
		SELECT 'Transaction commited'

----------------------------------------------------------------------

-- Scenariu NEREZOLVAT Deadlock (BAD)
	INSERT INTO Clienti(CNP, Nume, Prenume, Adresa, Telefon, Email) VALUES ('1234567891234', 'Nume', 'Prenume', 'Adresa', 'Telefon', 'Email');
	INSERT INTO ClientiMoto(CNP, Tip) VALUES ('1234567891234', 'Enduro')
	BEGIN TRAN
		UPDATE Clienti SET Nume='Deadlock1' WHERE CNP='1234567891234'
		WAITFOR DELAY '00:00:05'
		UPDATE ClientiMoto SET Tip='Cruiser' WHERE CNP='1234567891234'
		COMMIT TRAN
		SELECT 'Transaction commited'

-- Scenariu REZOLVAT Deadlock (GOOD)
	INSERT INTO Clienti(CNP, Nume, Prenume, Adresa, Telefon, Email) VALUES ('1234567891234', 'Nume', 'Prenume', 'Adresa', 'Telefon', 'Email');
	INSERT INTO ClientiMoto(CNP, Tip) VALUES ('1234567891234', 'Enduro')
	SET DEADLOCK_PRIORITY HIGH
	BEGIN TRAN
		UPDATE Clienti SET Nume='Deadlock1' WHERE CNP='1234567891234'
		WAITFOR DELAY '00:00:05'
		UPDATE ClientiMoto SET Tip='Cruiser' WHERE CNP='1234567891234'
		COMMIT TRAN
		SELECT 'Transaction commited'

	SELECT * FROM Clienti
	SELECT * FROM ClientiMoto
	DELETE FROM ClientiMoto WHERE CNP='1234567891234'
	DELETE FROM Clienti WHERE CNP='1234567891234'
	SELECT * FROM Clienti
	SELECT * FROM ClientiMoto

----------------------------------------------------------------------

CREATE OR ALTER PROCEDURE [dbo].[DeadLockProc1]
AS
BEGIN
	INSERT INTO Clienti(CNP, Nume, Prenume, Adresa, Telefon, Email) VALUES ('1234567891234', 'Nume', 'Prenume', 'Adresa', 'Telefon', 'Email');
	INSERT INTO ClientiMoto(CNP, Tip) VALUES ('1234567891234', 'Enduro')
	--SET DEADLOCK_PRIORITY HIGH
	BEGIN TRAN
		UPDATE Clienti SET Nume='Deadlock1' WHERE CNP='1234567891234'
		WAITFOR DELAY '00:00:05'
		UPDATE ClientiMoto SET Tip='Cruiser' WHERE CNP='1234567891234'
		COMMIT TRAN
		SELECT 'Transaction commited'

	SELECT * FROM Clienti
	SELECT * FROM ClientiMoto
	DELETE FROM ClientiMoto WHERE CNP='1234567891234'
	DELETE FROM Clienti WHERE CNP='1234567891234'
	SELECT * FROM Clienti
	SELECT * FROM ClientiMoto
END;
GO

----------------------------------------------------------------------