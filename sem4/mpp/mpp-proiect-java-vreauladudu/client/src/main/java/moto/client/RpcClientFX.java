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

public class RpcClientFX extends Application
{
    private static int port = 55001;
    private static String host = "localhost";

    public void start(Stage stage) throws Exception
    {
        IMotoService server = new MotoServicesRpcProxy(this.host, this.port);

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