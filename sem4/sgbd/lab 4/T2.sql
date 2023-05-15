USE Motorshop;
GO

----------------------------------------------------------------------

-- Scenariu NEREZOLVAT DirtyReads (BAD)
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
	BEGIN TRAN
		SELECT * FROM Clienti
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Clienti
		COMMIT TRAN

-- Scenariu REZOLVAT DirtyReads (GOOD)
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
	BEGIN TRAN
		SELECT * FROM Clienti
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Clienti
		COMMIT TRAN

----------------------------------------------------------------------

-- Scenariu NEREZOLVAT Non-repeatable reads (BAD)
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
	BEGIN TRAN
		SELECT * FROM Clienti
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Clienti
		COMMIT TRAN

-- Scenariu REZOLVAT Non-repeatable reads (GOOD)
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
	BEGIN TRAN
		SELECT * FROM Clienti
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Clienti
		COMMIT TRAN

----------------------------------------------------------------------

-- Scenariu NEREZOLVAT Phantom reads (BAD)
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
	BEGIN TRAN
		SELECT * FROM Clienti
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Clienti
		COMMIT TRAN

	DELETE FROM Clienti WHERE CNP='1234567891234'
	SELECT * FROM Clienti

-- Scenariu REZOLVAT Phantom reads (GOOD)
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
	BEGIN TRAN
		SELECT * FROM Clienti
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Clienti
		COMMIT TRAN

	DELETE FROM Clienti WHERE CNP='1234567891234'
	SELECT * FROM Clienti

----------------------------------------------------------------------

-- Scenariu NEREZOLVAT Deadlock (BAD)
	BEGIN TRAN
		UPDATE ClientiMoto SET Tip='Chopper' WHERE CNP='1234567891234'
		WAITFOR DELAY '00:00:05'
		UPDATE Clienti SET Nume='Deadlock2' WHERE CNP='1234567891234'
		COMMIT TRAN
		SELECT 'Transaction commited'

	SELECT * FROM Clienti
	SELECT * FROM ClientiMoto
	DELETE FROM ClientiMoto WHERE CNP='1234567891234'
	DELETE FROM Clienti WHERE CNP='1234567891234'
	SELECT * FROM Clienti
	SELECT * FROM ClientiMoto

-- Scenariu REZOLVAT Deadlock (GOOD)
	BEGIN TRAN
		UPDATE ClientiMoto SET Tip='Chopper' WHERE CNP='1234567891234'
		WAITFOR DELAY '00:00:05'
		UPDATE Clienti SET Nume='Deadlock2' WHERE CNP='1234567891234'
		COMMIT TRAN
		SELECT 'Transaction commited'

----------------------------------------------------------------------

CREATE OR ALTER PROCEDURE [dbo].[DeadLockProc2]
AS
BEGIN
	BEGIN TRAN
		UPDATE ClientiMoto SET Tip='Chopper' WHERE CNP='1234567891234'
		WAITFOR DELAY '00:00:05'
		UPDATE Clienti SET Nume='Deadlock2' WHERE CNP='1234567891234'
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