ALTER FUNCTION dbo.VerificaTip(@Tip varchar(MAX)) RETURNS int
AS
BEGIN
	DECLARE @r int = 1;

	IF @Tip IN (SELECT Tip FROM Categorii_moto)
	BEGIN
		SET @r = 0
	END;

	RETURN @r;
END;
GO

ALTER FUNCTION dbo.VerificaCNP(@CNP varchar(MAX)) RETURNS int
AS
BEGIN
	DECLARE @r int = 0;

	IF LEN(@CNP) != 13
	BEGIN
		SET @r = 0
		RETURN @r;
	END;

	IF NOT @CNP LIKE '%[^0-9]%'
	BEGIN
		SET @r = 1
	END;

	IF (SELECT COUNT(*) FROM Clienti WHERE @CNP = CNP) = 1
	BEGIN
		SET @r = 0
		RETURN @r;
	END

	RETURN @r;
END;
GO

ALTER FUNCTION dbo.VerificaExista(@CNP varchar(MAX), @Tip varchar(MAX)) RETURNS int
AS
BEGIN
	DECLARE @r int = 1;

	if EXISTS (SELECT CNP, Tip FROM ClientiMoto WHERE CNP = @CNP AND Tip = @Tip)
	BEGIN
		SET @r = 0
	END

	RETURN @r;
END;
GO

ALTER FUNCTION dbo.VerificaTelefonEmail(@telefon varchar(MAX), @email varchar(MAX)) RETURNS int
AS
BEGIN
	DECLARE @r int = 1;

	IF LEN(@telefon) != 10
	BEGIN
		SET @r = 0
		RETURN @r;
	END;

	IF NOT @telefon LIKE '%[^0-9]%'
	BEGIN
		SET @r = 1
	END;

	IF NOT @email LIKE '%[@]%'
	BEGIN
		SET @r = 0
		RETURN @r;
	END
	RETURN @r;
END;
GO

ALTER PROCEDURE [dbo].[ClientiMotoProc] @nume varchar(50), @prenume varchar(50), @adresa varchar(MAX), @telefon varchar(10), @email varchar(50)
AS
BEGIN
	SET NOCOUNT ON;
	
	DECLARE @randomTip varchar(255) = SUBSTRING(CONVERT(varchar(40), NEWID()),0,9)

	BEGIN TRAN
		BEGIN TRY
			if dbo.VerificaTip(@randomTip) = 0
			BEGIN
				RAISERROR('Tip-ul exista deja',14,1)
			END

			INSERT INTO Categorii_moto(Tip) VALUES (@randomTip);


			DECLARE @CNP varchar(13) = CAST(RIGHT(CAST(CAST(NEWID() AS VARBINARY(36)) AS BIGINT), 13) as varchar(13))

			if dbo.VerificaCNP(@CNP) = 0
			BEGIN
				RAISERROR('CNP-ul nu este valid',14,1)
			END

			if dbo.VerificaTelefonEmail(@telefon, @email) = 0
			BEGIN
				RAISERROR('Telefon sau email invalide',14,1)
			END

			INSERT INTO Clienti(CNP, Nume, Prenume, Adresa, Telefon, Email) VALUES (@CNP, @nume, @prenume, @adresa, @telefon, @email);


			if dbo.VerificaExista(@CNP, @randomTip) = 0
			BEGIN
				RAISERROR('Exista deja aceste valori',14,1)
			END

			INSERT INTO ClientiMoto(CNP, Tip) VALUES (@CNP, @randomTip);

			COMMIT TRAN
			SELECT 'Transaction commited'
		END TRY

		BEGIN CATCH
			ROLLBACK TRAN
			SELECT 'Transaction rollbacked'
		END CATCH

	SELECT * FROM ClientiMoto
END;
GO

SELECT * FROM Clienti
EXEC ClientiMotoProc 'testNume', 'testPrenume', 'testAdresa', '0700000000', 'test.com'
SELECT * FROM Clienti

ALTER PROCEDURE [dbo].[ClientiMotoProc2] @nume varchar(50), @prenume varchar(50), @adresa varchar(MAX), @telefon varchar(10), @email varchar(50)
AS
BEGIN
	SET NOCOUNT ON;
	
	DECLARE @randomTip varchar(255) = SUBSTRING(CONVERT(varchar(40), NEWID()),0,9)

	BEGIN TRAN
		BEGIN TRY
			if dbo.VerificaTip(@randomTip) = 0
			BEGIN
				RAISERROR('Tip-ul exista deja',14,1)
			END

			INSERT INTO Categorii_moto(Tip) VALUES (@randomTip);

			COMMIT TRAN
			SELECT 'Transaction1 commited'
		END TRY
		BEGIN CATCH
			ROLLBACK TRAN
			SELECT 'Transaction1 rollbacked'
		END CATCH

	BEGIN TRAN
		BEGIN TRY
			DECLARE @CNP varchar(13) = CAST(RIGHT(CAST(CAST(NEWID() AS VARBINARY(36)) AS BIGINT), 13) as varchar(13))

			if dbo.VerificaCNP(@CNP) = 0
			BEGIN
				RAISERROR('CNP-ul nu este valid',14,1)
			END

			if dbo.VerificaTelefonEmail(@telefon, @email) = 0
			BEGIN
				RAISERROR('Telefon sau email invalide',14,1)
			END

			INSERT INTO Clienti(CNP, Nume, Prenume, Adresa, Telefon, Email) VALUES (@CNP, @nume, @prenume, @adresa, @telefon, @email);

			COMMIT TRAN
			SELECT 'Transaction2 commited'
		END TRY
		BEGIN CATCH
			ROLLBACK TRAN
			SELECT 'Transaction2 rollbacked'
		END CATCH

	BEGIN TRAN
		BEGIN TRY
			if dbo.VerificaExista(@CNP, @randomTip) = 0
			BEGIN
				RAISERROR('Exista deja aceste valori',14,1)
			END

			INSERT INTO ClientiMoto(CNP, Tip) VALUES (@CNP, @randomTip);

			COMMIT TRAN
			SELECT 'Transaction3 commited'
		END TRY

		BEGIN CATCH
			ROLLBACK TRAN
			SELECT 'Transaction3 rollbacked'
		END CATCH

	SELECT * FROM ClientiMoto
END;
GO

SELECT * FROM Categorii_moto
EXEC ClientiMotoProc2 'testNume', 'testPrenume', 'testAdresa', '0700000000', 'test.com'
SELECT * FROM Categorii_moto