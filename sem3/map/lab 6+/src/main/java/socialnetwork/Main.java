package socialnetwork;

import javafx.application.Application;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.collections.FXCollections;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.scene.text.TextFlow;
import javafx.stage.Stage;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.domain.validator.ValidationException;
import socialnetwork.service.Service;

import java.util.Optional;

public class Main extends Application
{
    Stage stage;
    Scene loginScene;

    Service service = new Service();

    TextField usernameTextField = new TextField();
    PasswordField passwordField = new PasswordField();

    private void createUserAccount()
    {
        GridPane userInformation = new GridPane();
        userInformation.setHgap(10d);
        userInformation.setVgap(5d);
        userInformation.setAlignment(Pos.CENTER);

        TextField usernameTextField = new TextField();
        PasswordField passwordField = new PasswordField();
        TextField firstNameTextField = new TextField();
        TextField lastNameTextField = new TextField();
        TextField ageTextField = new TextField();
        TextField emailTextField = new TextField();

        userInformation.add(new Label("Username"), 0, 0);
        userInformation.add(usernameTextField, 1, 0);
        userInformation.add(new Label("Password"), 0, 1);
        userInformation.add(passwordField, 1, 1);
        userInformation.add(new Label("Nume"), 0, 2);
        userInformation.add(lastNameTextField, 1, 2);
        userInformation.add(new Label("Prenume"), 0, 3);
        userInformation.add(firstNameTextField, 1, 3);
        userInformation.add(new Label("Varsta"), 0, 4);
        userInformation.add(ageTextField, 1, 4);
        userInformation.add(new Label("Email"), 0, 5);
        userInformation.add(emailTextField, 1, 5);

        Button createAccountButton = new Button("Create account");

        VBox createAccountAll = new VBox();
        createAccountAll.setSpacing(8d);
        createAccountAll.setAlignment(Pos.CENTER);
        createAccountAll.getChildren().addAll(userInformation, createAccountButton);

        createAccountButton.setOnAction(event ->
        {
            try
            {
                if (service.addUser(firstNameTextField.getText(), lastNameTextField.getText(), Integer.parseInt(ageTextField.getText()), emailTextField.getText(), usernameTextField.getText(), passwordField.getText()))
                {
                    this.usernameTextField.setText(usernameTextField.getText());
                    this.passwordField.setText(passwordField.getText());
                    this.stage.setScene(this.loginScene);
                    this.stage.show();
                }
                else
                {
                    throw new IllegalArgumentException("Username is already taken.");
                }
            }
            catch (IllegalArgumentException | ValidationException exception)
            {
                Alert alert = new Alert(Alert.AlertType.ERROR, exception.toString());
                alert.show();
            }
        });

        BorderPane borderPane = new BorderPane();
        borderPane.setCenter(createAccountAll);

        Scene createAccountScene = new Scene(borderPane, 250, 250);
        this.stage.setScene(createAccountScene);
        this.stage.show();
    }

    private void updateMessages(TextArea messages, User loggedUser, User friend)
    {
        messages.clear();

        service.getMessagesBetweenUsers(loggedUser, friend).forEach(message ->
        {
            if (loggedUser.getId() == message.getIdUser1() && friend.getId() == message.getIdUser2())
            {
                messages.appendText(loggedUser.getUsername() + " | " + message.getDate_sent() + "\n" + message.getContent() + "\n\n");
            }
            else if (friend.getId() == message.getIdUser1() && loggedUser.getId() == message.getIdUser2())
            {
                messages.appendText(friend.getUsername() + " | " + message.getDate_sent() + "\n" + message.getContent() + "\n\n");
            }
        });
    }

    private void loggedInUser(User loggedUser)
    {
        BooleanProperty booleanProperty = new SimpleBooleanProperty(false);
        ListView<User> friends = new ListView<>(FXCollections.observableArrayList());

        GridPane userInformation = new GridPane();
        userInformation.setHgap(10d);
        userInformation.setVgap(5d);
        userInformation.setAlignment(Pos.TOP_LEFT);

        userInformation.add(new Label("Username:"), 0, 0);
        userInformation.add(new Label(loggedUser.getUsername()), 1, 0);
        userInformation.add(new Label("Password:"), 0, 1);
        userInformation.add(new Label(loggedUser.getPassword()), 1, 1);
        userInformation.add(new Label("Nume:"), 0, 2);
        userInformation.add(new Label(loggedUser.getLastName()), 1, 2);
        userInformation.add(new Label("Prenume:"), 0, 3);
        userInformation.add(new Label(loggedUser.getFirstName()), 1, 3);
        userInformation.add(new Label("Varsta:"), 0, 4);
        userInformation.add(new Label(String.valueOf(loggedUser.getAge())), 1, 4);
        userInformation.add(new Label("Email:"), 0, 5);
        userInformation.add(new Label(loggedUser.getEmail()), 1, 5);

        Button addFriendToUserButton = new Button("Adauga prieten");
        Button addFriendRequestToUserButton = new Button("Accepta cerere prietenie");
        Button removeFriendFromUserButton = new Button("Sterge prieten");
        Button removeFriendRequestFromUserButton = new Button("Sterge cerere prietenie");
        Button listFriendRequests = new Button("Show friend requests");
        Button searchUserButton = new Button("Cauta utilizator");
        Button messageUserButton = new Button("Mesaj");
        TextField searchedUserUsername = new TextField();
        searchedUserUsername.setPromptText("Username");
        searchUserButton.setOnAction(event ->
        {
            try
            {
                User searchedUser = service.searchUser(searchedUserUsername.getText());
                if (searchedUser != null)
                {
                    friends.setItems(FXCollections.observableArrayList(searchedUser));
                }
                else
                {
                    friends.setItems(FXCollections.observableArrayList(service.getFriendsOfUser(loggedUser)));
                    throw new IllegalArgumentException("User not found.");
                }
            }
            catch (IllegalArgumentException | ValidationException exception)
            {
                Alert alert = new Alert(Alert.AlertType.ERROR, exception.toString());
                alert.show();
            }
        });

        addFriendToUserButton.setOnAction(event ->
        {
            try
            {
                service.addFriendToUser(loggedUser.getUsername(), friends.getSelectionModel().getSelectedItem().getUsername());
            }
            catch (IllegalArgumentException | ValidationException exception)
            {
                Alert alert = new Alert(Alert.AlertType.ERROR, exception.toString());
                alert.show();
            }
        });
        addFriendRequestToUserButton.onActionProperty().bind(addFriendToUserButton.onActionProperty());

        removeFriendFromUserButton.setOnAction(event ->
        {
            try
            {
                service.removeFriendFromUser(loggedUser.getUsername(), friends.getSelectionModel().getSelectedItem().getUsername());
                service.removeFriendFromUser(friends.getSelectionModel().getSelectedItem().getUsername(), loggedUser.getUsername());
            }
            catch (IllegalArgumentException | ValidationException exception)
            {
                Alert alert = new Alert(Alert.AlertType.ERROR, exception.toString());
                alert.show();
            }
        });

        removeFriendRequestFromUserButton.setOnAction(event ->
        {
            try
            {
                service.removeFriendFromUser(loggedUser.getUsername(), friends.getSelectionModel().getSelectedItem().getUsername());
            }
            catch (IllegalArgumentException | ValidationException exception)
            {
                Alert alert = new Alert(Alert.AlertType.ERROR, exception.toString());
                alert.show();
            }
        });

        messageUserButton.setOnAction(event ->
        {
            try
            {
                Stage messageWindow = new Stage();

                VBox messagesWindow = new VBox();
                TextArea messages = new TextArea();
                messages.setEditable(false);
                ScrollPane scrollMessages = new ScrollPane(messages);

                User friend = friends.getSelectionModel().getSelectedItem();

                TextField typeMessage = new TextField();
                typeMessage.setPromptText("Type your message");
                typeMessage.setMinHeight(30d);
                typeMessage.setOnAction(messageEvent ->
                {
                    service.addMessage(loggedUser, friend, typeMessage.getText());
                    updateMessages(messages, loggedUser, friend);
                    typeMessage.clear();
                });

                messagesWindow.getChildren().addAll(scrollMessages, typeMessage);

                updateMessages(messages, loggedUser, friend);

                Scene messageScene = new Scene(messagesWindow, 400, messagesWindow.getMaxHeight());
                messageWindow.setTitle("Message Window");
                messageWindow.setScene(messageScene);
                messageWindow.show();
            }
            catch (IllegalArgumentException | ValidationException exception)
            {
                Alert alert = new Alert(Alert.AlertType.ERROR, exception.toString());
                alert.show();
            }
        });

        HBox searchUserLayout = new HBox();
        searchUserLayout.setSpacing(5d);
        searchUserLayout.getChildren().addAll(searchUserButton, searchedUserUsername);

        VBox createAccountAll = new VBox();
        createAccountAll.setPadding(new Insets(10, 10, 10, 10));
        createAccountAll.setSpacing(8d);
        createAccountAll.setAlignment(Pos.TOP_LEFT);
        createAccountAll.getChildren().addAll(userInformation, searchUserLayout, listFriendRequests);

        friends.setItems(FXCollections.observableArrayList(service.getFriendsOfUser(loggedUser)));
        friends.setMaxHeight(120d);
        friends.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) ->
        {
            searchUserLayout.getChildren().remove(addFriendToUserButton);
            searchUserLayout.getChildren().remove(addFriendRequestToUserButton);
            searchUserLayout.getChildren().remove(removeFriendFromUserButton);
            searchUserLayout.getChildren().remove(removeFriendRequestFromUserButton);
            searchUserLayout.getChildren().remove(messageUserButton);

            if (newValue == null)
            {
                return;
            }

            Friendship friendshipRequest = service.searchFriendshipRequest(loggedUser.getUsername(), newValue.getUsername());
            if (friendshipRequest != null)
            {
                Friendship friendshipRequestInversed = service.searchFriendshipRequest(newValue.getUsername(), loggedUser.getUsername());
                if (friendshipRequestInversed != null)
                {
                    if (!searchUserLayout.getChildren().contains(removeFriendFromUserButton))
                    {
                        searchUserLayout.getChildren().add(removeFriendFromUserButton);
                    }

                    if (!searchUserLayout.getChildren().contains(messageUserButton))
                    {
                        searchUserLayout.getChildren().add(messageUserButton);
                    }
                }
                else
                {
                    if (!searchUserLayout.getChildren().contains(removeFriendRequestFromUserButton))
                    {
                        searchUserLayout.getChildren().add(removeFriendRequestFromUserButton);
                    }
                }
            }
            else
            {
                Friendship friendshipRequestInversed = service.searchFriendshipRequest(newValue.getUsername(), loggedUser.getUsername());
                if (friendshipRequestInversed != null)
                {
                    if (!searchUserLayout.getChildren().contains(addFriendRequestToUserButton))
                    {
                        searchUserLayout.getChildren().add(addFriendRequestToUserButton);
                    }
                }
                else
                {
                    if (!searchUserLayout.getChildren().contains(addFriendToUserButton))
                    {
                        searchUserLayout.getChildren().add(addFriendToUserButton);
                    }
                }
            }
        });
        friends.setCellFactory(listCell -> new ListCell<>()
        {
            @Override
            protected void updateItem(User item, boolean empty)
            {
                super.updateItem(item, empty);
                if (item == null || empty)
                {
                    setText(null);
                }
                else
                {
                    if (booleanProperty.get())
                    {
                        Friendship friendshipRequest = service.searchFriendshipRequest(loggedUser.getUsername(), item.getUsername());
                        if (friendshipRequest != null)
                        {
                            setText(item.getUsername() + " | " + item.getFirstName() + " " + item.getLastName() + " | Varsta: " + String.valueOf(item.getAge()) + " | " + item.getEmail() + "\nData trimiterii: " + friendshipRequest.getFriendsFrom().toString() + " | Status: Pending");
                            return;
                        }
                        friendshipRequest = service.searchFriendshipRequest(item.getUsername(), loggedUser.getUsername());
                        if (friendshipRequest != null)
                        {
                            setText(item.getUsername() + " | " + item.getFirstName() + " " + item.getLastName() + " | Varsta: " + String.valueOf(item.getAge()) + " | " + item.getEmail() + "\nData trimiterii: " + friendshipRequest.getFriendsFrom().toString() + " | Status: Pending");
                        }
                    }
                    else
                    {
                        setText(item.getUsername() + " | " + item.getFirstName() + " " + item.getLastName() + " | Varsta: " + String.valueOf(item.getAge()) + " | " + item.getEmail());
                    }
                }
            }
        });

        listFriendRequests.setOnAction(event ->
        {
            booleanProperty.set(!booleanProperty.get());
            if (booleanProperty.get())
            {
                friends.setItems(FXCollections.observableArrayList(service.getFriendRequestsOfUser(loggedUser)));
            }
            else
            {
                friends.setItems(FXCollections.observableArrayList(service.getFriendsOfUser(loggedUser)));
            }
        });
        listFriendRequests.underlineProperty().bind(booleanProperty);

        BorderPane borderPane = new BorderPane();
        borderPane.setCenter(createAccountAll);
        borderPane.setBottom(friends);

        Scene loggedInScene = new Scene(borderPane, 470, 320);
        this.stage.setScene(loggedInScene);
        this.stage.show();
    }

    private VBox loginSetup()
    {
        GridPane loginInformation = new GridPane();
        loginInformation.setHgap(10d);
        loginInformation.setVgap(5d);
        loginInformation.setAlignment(Pos.CENTER);

        loginInformation.add(new Text("Username"), 0, 0);
        loginInformation.add(this.usernameTextField, 1, 0);
        loginInformation.add(new Text("Password"), 0, 1);
        loginInformation.add(this.passwordField, 1, 1);

        Button loginButton = new Button("Log In");
        Hyperlink createAccount = new Hyperlink("Create an account");
        createAccount.setOnAction(event -> this.createUserAccount());

        TextFlow notHavingAccount = new TextFlow(new Text("\nDon't have an account?"), createAccount);
        notHavingAccount.setTextAlignment(TextAlignment.CENTER);

        VBox login = new VBox();
        login.setSpacing(8d);
        login.setAlignment(Pos.CENTER);
        login.getChildren().addAll(loginInformation, loginButton, notHavingAccount);

        loginButton.setOnAction(event ->
        {
            Optional<User> user = service.verifyUserDetails(this.usernameTextField.getText());
            if (user.isPresent() && user.get().getPassword().equals(this.passwordField.getText()))
            {
                this.loggedInUser(user.get());
            }
            else
            {
                Alert alert = new Alert(Alert.AlertType.ERROR, "User could not be found.");
                alert.show();
            }
        });

        return login;
    }

    public static void main(String[] args)
    {
        launch();
    }

    @Override
    public void start(Stage stage)
    {
        this.stage = stage;

        BorderPane borderPane = new BorderPane();
        borderPane.setCenter(this.loginSetup());

        Scene scene = new Scene(borderPane, 320, 250);
        stage.setTitle("Socialnetwork");
        stage.setScene(scene);
        this.loginScene = stage.getScene();
        stage.show();
    }
}