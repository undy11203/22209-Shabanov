package com.shabanov.lab2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.IOException;

public class Game extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        stage.setTitle("Game");
        stage.getIcons().add(new Image(getClass().getResourceAsStream("/assets/icons.jpg")));
        stage.setScene(new Scene(StartScene()));
        stage.show();
    }

    private Parent StartScene() throws IOException {
        return FXMLLoader.load(getClass().getResource("/fxml/Menu.fxml"));
    }

    public static void main(String[] args) {
        launch();
    }

}