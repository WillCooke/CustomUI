#define TOTAL_PAGES 2

// Include the CustomUI header
#include "CustomUI.h"
#include <stdio.h>

// Create two pages with their names
static CustomUI::Page page1("Page 1");
static CustomUI::Page page2("Page 2");

static IO::Button button(400, 400, 100, 100, {255, 0, 0, 255}, {0, 0, 0, 255}, "Button!", 30);

string text = "Not Set";

std::function<void()> loadFunctions[TOTAL_PAGES];

//Page loading functions
void page1Load()
{
    text = IO::readFile("sdmc:/text.txt");
}

void page2Load()
{
    text = "CustomUI.h is by XorTroll";
}

// Rendering functions
void page1Render()
{
    page1.renderText(text, 0, 0, {0, 0, 0, 255}, 50);
}

void page2Render()
{
    //Render text to the screen
    page2.renderText(text, 0, 0, {0, 0, 0, 255}, 50);
    //Render the button
    button.Render();
}


int main()
{
    // Initialise CustomUI with the title, footer, and theme struct
    CustomUI::init("Sample Header", "by Will Cooke", CustomUI::HorizonLight());


    // Set their rendering functions (what will be called every time the UI renders)
    page1.onRender(page1Render);
    page2.onRender(page2Render);
    
    
    // Add both pages to our UI
    CustomUI::addPage(page1);
    loadFunctions[1] = page1Load;
    CustomUI::addPage(page2);
    loadFunctions[0] = page2Load;

    loadFunctions[0]();
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
        if(button.CheckPress()) 
        {
            //Write to the file
            IO::write("sdmc:/text.txt", "...is from 1919!");
            //Reload the page!
            page1Load();
        }
        //Return to homebrew menu on press of plus
        if(keysDown & KEY_PLUS) break;

        //Render what has been drawn to the screen at the end of the frame
        CustomUI::renderGraphics();
        
    }

    CustomUI::exitApp();
}