package com.shabanov.lab2.Controller;

import com.shabanov.lab2.Module.Utils.LevelSelect;
import com.shabanov.lab2.Module.Pages.SceneSwitch;
import javafx.scene.layout.Pane;

import java.io.IOException;

public class MenuController {

    public void setLevel(int i) {
        LevelSelect.level = i;
    }

    public void viewSwitch(Pane pane, String s) throws IOException {
        new SceneSwitch(pane, s);
    }
}
