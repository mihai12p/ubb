package moto.client.gui;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import moto.Motorcycle;
import moto.Participant;
import moto.User;
import moto.services.IMotoObserver;
import moto.services.IMotoService;
import moto.services.MotoException;

import java.net.URL;
import java.util.*;

public class MotoController implements Initializable, IMotoObserver
{
    private IMotoService server = null;
    private User currentUser = null;

    @FXML
    TextField motorcycleBrand;
    @FXML
    TextField motorcycleCapacity;
    @FXML
    TextField participantName;
    @FXML
    TextField motorcycleRaceBrand;
    @FXML
    ListView<Integer> capacities;
    @FXML
    ListView<Participant> participantsByBrand;
    @FXML
    ListView<Participant> raceParticipants;
    @FXML
    ListView<Motorcycle> motorcycles;
    @FXML
    Label participantsCount;

    public MotoController() { }

    public MotoController(IMotoService server)
    {
        this.server = server;
        this.currentUser = null;
    }

    @FXML
    public void initialize(URL url, ResourceBundle resourceBundle)
    {
        this.capacities.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) ->
        {
            if (newValue == null)
            {
                return;
            }

            List<Participant> participantList = new ArrayList<>();
            this.listMotorcyclesByCapacity(newValue).forEach(motorcycle ->
            {
                List<Participant> participants = this.findParticipantForRace(motorcycle.getId());
                if (participants != null)
                {
                    participantList.addAll(participants);
                }
            });
            this.raceParticipants.setItems(FXCollections.observableArrayList(participantList));
            this.participantsCount.setText(String.valueOf(this.raceParticipants.getItems().size()));
        });

        participantsByBrand.setCellFactory(listCell -> new ListCell<>()
        {
            @Override
            protected void updateItem(Participant item, boolean empty)
            {
                super.updateItem(item, empty);
                if (item == null || empty)
                {
                    setText(null);
                }
                else
                {
                    Motorcycle motorcycle = findMotorcycleById(item.getMotorcycleID());
                    setText("Nume: " + item.getName() + " | Capacitate motocicleta: " + motorcycle.getCapacity());
                }
            }
        });

        participantsByBrand.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) ->
        {
            if (newValue == null)
            {
                return;
            }

            Motorcycle motorcycle = this.findMotorcycleById(newValue.getMotorcycleID());
            motorcycleCapacity.setText(String.valueOf(motorcycle.getCapacity()));
            participantName.setText(newValue.getName());
            motorcycleRaceBrand.setText(motorcycle.getBrand());
        });
    }

    public void setServer(IMotoService server)
    {
        this.server = server;
    }

    public void login(String username, String password) throws MotoException
    {
        User user = new User();
        user.setUsername(username);
        user.setPassword(password);
        this.server.login(user, this);
        System.out.println("Login succeeded...");
        this.currentUser = user;
        System.out.println("Current user " + user);
    }

    public void logout()
    {
        try
        {
            System.out.println("Controller logout");
            this.server.logout(this.currentUser, this);
            this.currentUser = null;
        }
        catch (MotoException exception)
        {
            System.err.println("Logout error " + exception);
        }
    }

    public void handleLogout(ActionEvent actionEvent)
    {
        this.logout();
        ((Node)(actionEvent.getSource())).getScene().getWindow().hide();
    }

    public Map<Integer, List<Motorcycle>> listRaces()
    {
        try
        {
            System.out.println("List races");
            return this.server.listRaces(this);
        }
        catch (MotoException exception)
        {
            System.err.println("List races error " + exception);
        }
        return null;
    }

    public Iterable<Motorcycle> listMotorcycles()
    {
        try
        {
            System.out.println("List motorcycles");
            return this.server.listMotorcycles(this);
        }
        catch (MotoException exception)
        {
            System.err.println("List motorcycles error " + exception);
        }
        return null;
    }

    public List<Motorcycle> listMotorcyclesByCapacity(Integer capacity)
    {
        try
        {
            System.out.println("List motorcycles by capacity");
            return this.server.listMotorcyclesByCapacity(capacity, this);
        }
        catch (MotoException exception)
        {
            System.err.println("List motorcycles by capacity error " + exception);
        }
        return null;
    }

    public List<Participant> findParticipantForRace(Integer motorcycleId)
    {
        try
        {
            System.out.println("Find participant for race");
            return this.server.findParticipantForRace(motorcycleId, this);
        }
        catch (MotoException exception)
        {
            System.err.println("Find participant for race error " + exception);
        }
        return null;
    }

    public List<Motorcycle> listMotorcyclesByBrand(String brand)
    {
        try
        {
            System.out.println("List motorcycles by brand");
            return this.server.listMotorcyclesByBrand(brand, this);
        }
        catch (MotoException exception)
        {
            System.err.println("List motorcycles by brand error " + exception);
        }
        return null;
    }

    public Motorcycle findMotorcycleById(Integer motorcycleId)
    {
        try
        {
            System.out.println("Find motorcycle");
            return this.server.findMotorcycleById(motorcycleId, this);
        }
        catch (MotoException exception)
        {
            System.err.println("Find motorcycle error " + exception);
        }
        return null;
    }

    public void addParticipant(String participantName, String motorcycleBrand, Integer motorcycleCapacity)
    {
        try
        {
            System.out.println("Add participant");
            this.server.addParticipant(participantName, motorcycleBrand, motorcycleCapacity, this);
        }
        catch (MotoException exception)
        {
            System.err.println("Add participant error " + exception);
        }
    }

    public void participantAdded(Participant participant)
    {
        Platform.runLater(() ->
        {
            this.raceParticipants.getItems().add(participant);
            this.participantsCount.setText(String.valueOf(this.raceParticipants.getItems().size()));
            System.out.println("Participant added " + participant.getName());
        });
    }

    public void findParticipantsByBrand(ActionEvent actionEvent)
    {
        List<Participant> participantList = new ArrayList<>();
        this.listMotorcyclesByBrand(motorcycleBrand.getText()).forEach(motorcycle ->
        {
            List<Participant> participants = this.findParticipantForRace(motorcycle.getId());
            if (participants != null)
            {
                participantList.addAll(participants);
            }
        });
        this.participantsByBrand.setItems(FXCollections.observableArrayList(participantList));
    }

    public void addParticipant(ActionEvent actionEvent)
    {
        this.addParticipant(this.participantName.getText(), this.motorcycleRaceBrand.getText(), Integer.parseInt(this.motorcycleCapacity.getText()));

        List<Participant> participantList = new ArrayList<>();
        this.listMotorcyclesByBrand(this.motorcycleBrand.getText()).forEach(motorcycle ->
        {
            List<Participant> participants = this.findParticipantForRace(motorcycle.getId());
            if (participants != null)
            {
                participantList.addAll(participants);
            }
        });
        this.participantsByBrand.setItems(FXCollections.observableArrayList(participantList));
    }

    public void init()
    {
        List<Integer> capacityList = new ArrayList<>();
        this.listRaces().forEach((capacity, motorcycles) -> capacityList.add(capacity));
        this.capacities.setItems(FXCollections.observableArrayList(capacityList));

        List<Motorcycle> motorcyclesList = new ArrayList<>();
        this.listMotorcycles().forEach(motorcyclesList::add);
        this.motorcycles.setItems(FXCollections.observableArrayList(motorcyclesList));
    }
}