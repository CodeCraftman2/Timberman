#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Add this line for audio support
#include <iostream>
using namespace sf;

// Function declaration
void updateBranches(int seed);

// Constants and variables for branches
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main()
{
    // Initialize random seed once
    srand((unsigned int)time(0));

    // Step 1: Create a video mode object (resolution)
    VideoMode vm(1920, 1080);

    // Debugging: Print the video mode (screen size)
    std::cout << "Screen size: " << vm.width << "x" << vm.height << std::endl;

    // Step 2: Create and open the window for the game
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    // Step 3: Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // Step 4: Load a graphic into the texture
    if (!textureBackground.loadFromFile("../graphics/background.png"))
    {
        std::cerr << "Error: Could not load background image!" << std::endl;
        return -1;
    }

    // Debugging: Print the size of the background texture
    std::cout << "Background texture size: " << textureBackground.getSize().x << "x" << textureBackground.getSize().y << std::endl;

    // Step 5: Create a sprite for the background
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // Step 13: Standing Tree
    Texture textureTree;
    if (!textureTree.loadFromFile("../graphics/tree.png"))
    {
        std::cerr << "Error: Could not load tree image!" << std::endl;
        return -1;
    }

    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);  // Adjust position to be inside the screen
				    // Taking tree in center from x-axis


    // Debugging: Print the size of the tree texture
    std::cout << "Tree texture size: " << textureTree.getSize().x << "x" << textureTree.getSize().y << std::endl;
	
    // Step 14: Adding Bee
    Texture textureBee;
    if (!textureBee.loadFromFile("../graphics/bee.png"))
    {
        std::cerr << "Error: Could not load bee image!" << std::endl;
        return -1;
    }

    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    // Is the bee currently moving?
    bool beeActive = false;

    // How fast can the bee fly
    float beeSpeed = 0.05f; // Adjusted speed

    // Debugging: Print the size of the bee texture
    std::cout << "The bee size: " << textureBee.getSize().x << "x" << textureBee.getSize().y << std::endl;

    // Step 15: Creating cloud class for 3 cloud objects
    Texture textureCloud;
    if (!textureCloud.loadFromFile("../graphics/cloud.png"))
    {
        std::cerr << "Error: Could not load cloud image!" << std::endl;
        return -1;
    }

    // Debugging: Print the size of the cloud texture
    std::cout << "Cloud texture size: " << textureCloud.getSize().x << "x" << textureCloud.getSize().y << std::endl;

    Sprite spriteCloud1, spriteCloud2, spriteCloud3;
    Sprite spriteCloud4, spriteCloud5, spriteCloud6; // New clouds

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    spriteCloud4.setTexture(textureCloud); // New cloud
    spriteCloud5.setTexture(textureCloud); // New cloud
    spriteCloud6.setTexture(textureCloud); // New cloud

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 150);
    spriteCloud3.setPosition(0, 300);
    spriteCloud4.setPosition(0, 450); // New cloud position
    spriteCloud5.setPosition(0, 600); // New cloud position
    spriteCloud6.setPosition(0, 750); // New cloud position

    // Creating cloud on screen
    bool cloud1Active = false, cloud2Active = false, cloud3Active = false;
    bool cloud4Active = false, cloud5Active = false, cloud6Active = false; // New clouds

    // Speed of clouds
    float cloud1Speed = 0.05f, cloud2Speed = 0.05f, cloud3Speed = 0.05f;
    float cloud4Speed = 0.05f, cloud5Speed = 0.05f, cloud6Speed = 0.05f; // New clouds

    // Declare Pause variable and set initial state to true
    bool Pause = true;

    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
    Time gameTimeTotal;
    float timeRemaining = 10.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // Step 18: Moving Bee
    Clock clock;

    // Step 19: Draw some text
    int score = 0;

    Text messageText;
    Text scoreText;

    // We need to choose a font
    Font font;
    if (!font.loadFromFile("../fonts/KOMIKAP_.ttf"))
    {
        std::cerr << "Error: Could not load font!" << std::endl;
        return -1;
    }

    // Debugging: Print the font file path
    std::cout << "Font file path: ../fonts/KOMIKAP_.ttf" << std::endl;

    // Set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);

    // Assign the actual message
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");

    // Make it really big
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    // Choose a color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    // Position the text
    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left + 
		    textRect.width / 2.0f,
		    textRect.top +
		    textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    // Debugging: Print the message text details
    std::cout << "Message text: " << messageText.getString().toAnsiString() << std::endl;
    std::cout << "Message text position: (" << messageText.getPosition().x << ", " << messageText.getPosition().y << ")" << std::endl;
    std::cout << "Message text size: " << messageText.getCharacterSize() << std::endl;

    // Debugging: Print the score text details
    std::cout << "Score text: " << scoreText.getString().toAnsiString() << std::endl;
    std::cout << "Score text position: (" << scoreText.getPosition().x << ", " << scoreText.getPosition().y << ")" << std::endl;
    std::cout << "Score text size: " << scoreText.getCharacterSize() << std::endl;

    // Prepare 6 branches
    Texture textureBranch;
    if (!textureBranch.loadFromFile("../graphics/branch.png"))
    {
        std::cerr << "Error: Could not load branch image!" << std::endl;
        return -1;
    }

    // Set the texture for each branch sprite
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
    }

    // Prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("../graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    // The player starts on the left side
    side playerSide = side::LEFT;

    // Prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("../graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    // Prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile("../graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    // Line the axe up with the tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // Prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile("../graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    // Some other useful log related variables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    // Control the player input
    bool acceptInput = false;

    // Make all the branches disappear -
    // starting in the second position
    for (int i = 1; i < NUM_BRANCHES; i++)
    {
        branchPositions[i] = side::NONE;
    }

    // Make sure the gravestone is hidden
    spriteRIP.setPosition(675, 2000);

    // Move the player into position
    spritePlayer.setPosition(580, 720);
    acceptInput = true;

    // Prepare the sounds
    // The player chopping sound
    SoundBuffer chopBuffer;
    if (!chopBuffer.loadFromFile("../sound/chop.wav"))
    {
        std::cerr << "Error: Could not load chop sound!" << std::endl;
        return -1;
    }
    Sound chop;
    chop.setBuffer(chopBuffer);

    // The player has met his end under a branch
    SoundBuffer deathBuffer;
    if (!deathBuffer.loadFromFile("../sound/death.wav"))
    {
        std::cerr << "Error: Could not load death sound!" << std::endl;
        return -1;
    }
    Sound death;
    death.setBuffer(deathBuffer);

    // Out of time
    SoundBuffer ootBuffer;
    if (!ootBuffer.loadFromFile("../sound/out_of_time.wav"))
    {
        std::cerr << "Error: Could not load out of time sound!" << std::endl;
        return -1;
    }
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    // FPS Counter setup
    Font fpsFont;
    if (!fpsFont.loadFromFile("../fonts/arial.ttf")) {
        std::cerr << "Failed to load font for FPS counter\n";
        return -1;
    }

    Text fpsText;
    fpsText.setFont(fpsFont);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(Color::White);
    fpsText.setPosition(10.f, 10.f);

    Clock fpsClock;
    int frameCount = 0;
    float fps = 0.f;
    Time timeElapsed;

    // Game loop
    while (window.isOpen())
    {
        // Step 8: Event handling (user input)
        Event event;
        while (window.pollEvent(event))
        {
            //To Exit the game on pressing 'ESC'
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                window.close();
            }
            //To Pause/Unpause the Game on Pressing 'ENTER'
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                Pause = !Pause;
                if (!Pause)
                {
                    // Restart the clock when the game starts
                    clock.restart();
                    // Reset the gravestone and player positions
                    spriteRIP.setPosition(675, 2000);
                    spritePlayer.setPosition(580, 720);
                    acceptInput = true;
                    
                    // Reset the time and the score
                    score = 0;
                    timeRemaining = 10.0f;
                    
                    // Reset the branches
                    for (int i = 1; i < NUM_BRANCHES; i++)
                    {
                        branchPositions[i] = side::NONE;
                    }
                }
            }
            if (event.type == Event::KeyReleased && !Pause)
            {
                // Listen for key presses again
                acceptInput = true;
                // Hide the axe
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
        }

        if (!Pause)
        {
            // Measure time
            Time dt = clock.restart();
            
            // Subtract from the amount of time remaining
            timeRemaining -= dt.asSeconds();
            
            // Check if time has run out
            if (timeRemaining <= 0.0f)
            {
                // Pause the game
                Pause = true;
                
                // Reset the time and the score
                score = 0;
                timeRemaining = 10.0f;

                // Change the message shown to the player
                messageText.setString("Out of time!! Press Enter to restart.");
                
                // Reposition the text based on its new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

                // Play the out of time sound
                outOfTime.play();
            }

            // Size up the time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            // Update the bee
            if (!beeActive)
            {
                // Bee's Speed
                beeSpeed = (rand() % 200) + 200;

                // Bee's position
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                // Move the bee
                spriteBee.setPosition(
                    spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y
                );

                // Check if bee has reached the left hand edge
                if (spriteBee.getPosition().x < -100)
                {
                    // Reset the bee
                    beeActive = false;
                }
            }

            // Step 19: Creating cloud
            // Moving the 3 Clouds
            // Manage the clouds

            // Cloud 1
            if (!cloud1Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);

                // How high is the cloud
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;
            }
            else
            {
                spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);

                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud1.getPosition().x > 1920)
                {
                    // Set it up ready to be a whole new cloud next frame
                    cloud1Active = false;
                }
            }

            // Cloud 2
            if (!cloud2Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                // How high is the cloud
                srand((int)time(0) * 20);
                float height = (rand() % 150);
                spriteCloud2.setPosition(-150, height);
                cloud2Active = true;
            }
            else
            {
                spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);

                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud2.getPosition().x > 1920)
                {
                    // Set it up ready to be a whole new cloud next frame
                    cloud2Active = false;
                }
            }

            // Cloud 3
            if (!cloud3Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);

                // How high is the cloud
                srand((int)time(0) * 30);
                float height = (rand() % 150);
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            }
            else
            {
                spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);

                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud3.getPosition().x > 1920)
                {
                    // Set it up ready to be a whole new cloud next frame
                    cloud3Active = false;
                }
            }

            // Cloud 4 (New)
            if (!cloud4Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 40);
                cloud4Speed = (rand() % 200);

                // How high is the cloud
                srand((int)time(0) * 40);
                float height = (rand() % 150);
                spriteCloud4.setPosition(-200, height);
                cloud4Active = true;
            }
            else
            {
                spriteCloud4.setPosition(spriteCloud4.getPosition().x + (cloud4Speed * dt.asSeconds()), spriteCloud4.getPosition().y);

                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud4.getPosition().x > 1920)
                {
                    // Set it up ready to be a whole new cloud next frame
                    cloud4Active = false;
                }
            }

            // Cloud 5 (New)
            if (!cloud5Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 50);
                cloud5Speed = (rand() % 200);

                // How high is the cloud
                srand((int)time(0) * 50);
                float height = (rand() % 150);
                spriteCloud5.setPosition(-200, height);
                cloud5Active = true;
            }
            else
            {
                spriteCloud5.setPosition(spriteCloud5.getPosition().x + (cloud5Speed * dt.asSeconds()), spriteCloud5.getPosition().y);

                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud5.getPosition().x > 1920)
                {
                    // Set it up ready to be a whole new cloud next frame
                    cloud5Active = false;
                }
            }

            // Cloud 6 (New)
            if (!cloud6Active)
            {
                // How fast is the cloud
                srand((int)time(0) * 60);
                cloud6Speed = (rand() % 200);

                // How high is the cloud
                srand((int)time(0) * 60);
                float height = (rand() % 150);
                spriteCloud6.setPosition(-200, height);
                cloud6Active = true;
            }
            else
            {
                spriteCloud6.setPosition(spriteCloud6.getPosition().x + (cloud6Speed * dt.asSeconds()), spriteCloud6.getPosition().y);

                // Has the cloud reached the right hand edge of the screen?
                if (spriteCloud6.getPosition().x > 1920)
                {
                    // Set it up ready to be a whole new cloud next frame
                    cloud6Active = false;
                }
            }

            // Update the branch sprites
            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT)
                {
                    branches[i].setPosition(610, height);
                    branches[i].setRotation(180);
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                }
                else
                {
                    branches[i].setPosition(3000, height);
                }
            }

            // Spawn new branches only when the player chops a tree
            if (acceptInput) {
                // First handle pressing the right cursor key
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    // Make sure the player is on the right
                    playerSide = side::RIGHT;
                    score++; // Increment score when player chops a tree
                    // Add to the amount of time remaining
                    timeRemaining += (2 / score) + .15;
                    spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                    spritePlayer.setPosition(1200, 720);
                    // Update the branches
                    updateBranches(score);
                    // Set the log flying to the left
                    spriteLog.setPosition(810, 720);
                    logSpeedX = -5000;
                    logActive = true;
                    acceptInput = false;
                    // Play a chop sound
                    chop.play();
                }

                // Handle the left cursor key
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    // Make sure the player is on the left
                    playerSide = side::LEFT;
                    score++; // Increment score when player chops a tree
                    // Add to the amount of time remaining
                    timeRemaining += (2 / score) + .15;
                    spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                    spritePlayer.setPosition(580, 720);
                    // Update the branches
                    updateBranches(score);
                    // Set the log flying to the right
                    spriteLog.setPosition(810, 720);
                    logSpeedX = 5000;
                    logActive = true;
                    acceptInput = false;
                    // Play a chop sound
                    chop.play();
                }
            }

            // Handle a flying log
            if (logActive)
            {
                spriteLog.setPosition(
                    spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                    spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
                );

                // Has the log reached the right hand edge?
                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
                {
                    // Set it up ready to be a whole new log next frame
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }

            // Has the player been squished by a branch?
            if (branchPositions[5] == playerSide)
            {
                // Death
                Pause = true;
                acceptInput = false;
                // Draw the gravestone
                spriteRIP.setPosition(525, 760);
                // Hide the player
                spritePlayer.setPosition(2000, 660);
                // Change the text of the message
                messageText.setString("SQUISHED!! Press Enter to restart.");
                // Center it on the screen
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
                // Play the death sound
                death.play();
            }

            // Update the score text
            scoreText.setString("Score = " + std::to_string(score));

            // FPS Counter update
            frameCount++;
            timeElapsed += fpsClock.restart();
            if (timeElapsed.asSeconds() >= 1.0f) {
                fps = frameCount / timeElapsed.asSeconds();
                frameCount = 0;
                timeElapsed = Time::Zero;

                std::ostringstream ss;
                ss.precision(2);
                ss << std::fixed << "FPS: " << fps;
                fpsText.setString(ss.str());
            }
        }
        else
        {
            // If the game is paused, do not update the clock
            clock.restart();
        }

        // Step 9: Clear the previous frame
        window.clear();

        // Step 10: Draw the background sprite
        window.draw(spriteBackground);

        // Step 11: Draw the tree sprite
        window.draw(spriteTree);

        // Step 16: Draw the bee sprite
        window.draw(spriteBee);

        // Step 17: Draw 3 Cloud sprites
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteCloud4); // New cloud
        window.draw(spriteCloud5); // New cloud
        window.draw(spriteCloud6); // New cloud

        // Draw the time bar
        window.draw(timeBar);

        // Step 20: Draw the score
        window.draw(scoreText);

        // Step 21: Draw the message
        if (Pause)
        {
            window.draw(messageText);
        }

        // Draw the branches
        for (int i = 0; i < NUM_BRANCHES; i++) {
            window.draw(branches[i]);
        }

        // Draw the player
        window.draw(spritePlayer);

        // Draw the axe
        window.draw(spriteAxe);

        // Draw the flying log
        window.draw(spriteLog);

        // Draw the gravestone
        window.draw(spriteRIP);

        // Draw the FPS counter
        window.draw(fpsText);

        // Step 12: Display the current frame (swap buffers)
        window.display();
    }

    return 0;
}


// Function definition
void updateBranches(int seed)
{
    // Move all the branches down one place
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
    {
        branchPositions[j] = branchPositions[j - 1];
    }

    // Spawn a new branch at position 0
    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }

    // Adjust branch positions based on player height
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        float height = i * 150; // Adjust the height spacing as needed
        if (branchPositions[i] == side::LEFT)
        {
            branches[i].setPosition(610, height);
            branches[i].setRotation(180);
        }
        else if (branchPositions[i] == side::RIGHT)
        {
            branches[i].setPosition(1330, height);
            branches[i].setRotation(0);
        }
        else
        {
            branches[i].setPosition(3000, height);
        }
    }
}

