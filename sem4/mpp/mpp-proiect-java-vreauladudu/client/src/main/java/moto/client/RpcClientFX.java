package moto.client;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import moto.client.gui.LoginController;
import moto.client.gui.MotoController;
import moto.network.rpcprotocol.MotoServicesRpcProxy;
import moto.services.IMotoService;

import java.io.IOException;
import java.util.Properties;

public class RpcClientFX extends Application
{
    public void start(Stage stage) throws Exception
    {
        Properties clientProperties = new Properties();
        try
        {
            clientProperties.load(RpcClientFX.class.getResourceAsStream("/motoclient.properties"));
            System.out.println("Client properties set.");
            clientProperties.list(System.out);
        }
        catch (IOException exception)
        {
            System.err.println("Cannot find motoclient.properties " + exception);
            return;
        }

        IMotoService server = new MotoServicesRpcProxy(clientProperties.getProperty("client.host"), Integer.parseInt(clientProperties.getProperty("client.port")));

        FXMLLoader loader = new FXMLLoader(getClass().getClassLoader().getResource("loginwindow.fxml"));
        Parent root = loader.load();

        FXMLLoader cloader = new FXMLLoader(getClass().getClassLoader().getResource("motowindow.fxml"));
        Parent croot = cloader.load();

        MotoController motoController = cloader.<MotoController>getController();
        motoController.setServer(server);

        LoginController loginController = loader.<LoginController>getController();
        loginController.setMotoClientController(motoController);
        loginController.setParent(croot);

        stage.setTitle("Moto Login");
        stage.setScene(new Scene(root, 300, 200));
        stage.show();
    }
}