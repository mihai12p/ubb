package moto.client.gui;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import moto.services.MotoException;

public class LoginController
{
    private MotoController motoController;

    @FXML
    TextField username;
    @FXML
    TextField password;

    Parent mainParent;

    public void setParent(Parent parent)
    {
        this.mainParent = parent;
    }

    public void pressLogin(ActionEvent actionEvent)
    {
        try
        {
            this.motoController.login(this.username.getText(), this.password.getText());

            Stage stage = new Stage();
            stage.setTitle("Moto Window for " + this.username.getText());
            stage.setScene(new Scene(this.mainParent));

            stage.setOnCloseRequest(event ->
            {
                this.motoController.logout();
                System.exit(0);
            });

            stage.show();
            this.motoController.init();
            ((Node)(actionEvent.getSource())).getScene().getWindow().hide();
        }
        catch (MotoException exception)
        {
            Alert alert = new Alert(Alert.AlertType.ERROR, exception.getMessage());
            alert.show();
        }
    }

    public void pressCancel(ActionEvent actionEvent)
    {
        System.exit(0);
    }

    public void setMotoClientController(MotoController motoController)
    {
        this.motoController = motoController;
    }
}