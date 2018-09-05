#define TOTAL_PAGES 2

// Include the CustomUI header
#include "CustomUI.h"
#include <stdio.h>

// Create two pages with their names
static CustomUI::Page home("Home");
static CustomUI::Page fileView("Explore");

static IO::Button button(400, 400, 100, 100, {255, 0, 0, 255}, {0, 0, 0, 255}, "Button!");

string text = "Not Set";

std::function<void()> loadFunctions[2];

//Page loading functions
void homeLoad()
{
    text = "CustomUI.h is by XorTroll";
    
}

void fileViewLoad()
{
    IO::file f("sdmc:/text.txt");
    text = f.read();
}

// Rendering functions
void homeRender()
{
    home.renderText(text, 0, 0, {0, 0, 0, 255}, 50);
}

void fileViewRender()
{
    //Render text to the screen
    fileView.renderText(text, 0, 0, {0, 0, 0, 255}, 50);
    //Render the button
    button.Render();
}


int main()
{
    // Initialise CustomUI with the title, footer, and theme struct
    CustomUI::init("Sample Header", "by Will Cooke", CustomUI::HorizonLight());


    // Set their rendering functions (what will be called every time the UI renders)
    home.onRender(homeRender);
    fileView.onRender(fileViewRender);
    
    
    // Add both pages to our UI
    CustomUI::addPage(home);
    loadFunctions[1] = homeLoad;
    CustomUI::addPage(fileView);
    loadFunctions[0] = fileViewLoad;

    // Main loop starts
    while(appletMainLoop())
    {
        // Reset the graphics for the next frame
        CustomUI::flushGraphics();

        // CustomUI already pulls input data so we can just use that
        int keysDown = CustomUI::PressedInput;
         
        
        //Used to run the load functions for pages
        if(keysDown & KEY_LSTICK_UP || keysDown & KEY_LSTICK_DOWN)
        {
            loadFunctions[CustomUI::spage]();
        }

        //If Button is tapped return to homebrew
        if(button.CheckPress()) break;
        //Return to homebrew menu on press of plus
        if(keysDown & KEY_PLUS) break;

        //Render what has been drawn to the screen at the end of the frame
        CustomUI::renderGraphics();
        
    }

    CustomUI::exitApp();
}