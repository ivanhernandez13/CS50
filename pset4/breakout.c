//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
#define PHEIGHT 10
#define PWIDTH 100

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    double velocity = 4;
    double hvelocity = drand48() * 10;
    
    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        updateScoreboard(window,label,points);
        // looks for the mouse to be moved and then sets paddles location to mouses X location only
        GEvent pmove = getNextEvent(MOUSE_EVENT);
        if (pmove != NULL)
        {
            if(getEventType(pmove) == MOUSE_MOVED)
            {
                double x = getX(pmove) - getWidth(paddle) / 2;
                double y = getY(paddle);
                setLocation(paddle, x, y);
            }
        }

        // moves the ball across the screen
        move(ball,hvelocity,velocity);
        
        // checks if ball is touching the right, left, top, or bottom then bounces off
        if (getY(ball) <= 0)
        {
            velocity = -velocity;
        }
        else if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            hvelocity = -hvelocity;
        }
        else if (getX(ball) <= 0)
        {
            hvelocity = -hvelocity;
        }
        
        // checks if ball hit paddle, then bounces off
        GObject hit = detectCollision(window,ball);
        if (hit != NULL)
        {
            if (hit == paddle)
            {
                velocity = -velocity;
            }
            else if (strcmp(getType(hit),"GRect") == 0)
            {
                removeGWindow(window,hit);
                velocity = -velocity;
                points++;
                bricks--;
            }
        }
        
        
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            setLocation(ball,(getWidth(window) / 2) - RADIUS, (getHeight(window) / 2) + 20);
            waitForClick();
        }
        
        pause(10);
    }
    
    

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            GRect brick = newGRect (10 + (c * 39) ,10 + (r * 15),30,10);
            setFilled(brick, true);
            if (r == 0)
            {
                setColor(brick, "BLUE");
            }
            if (r == 1)
            {
                setColor(brick, "GREEN");
            }
            if (r == 2)
            {
                setColor(brick, "RED");
            }
            if (r == 3)
            {
                setColor(brick, "YELLOW");
            }
            if (r == 4)
            {
                setColor(brick, "ORANGE");
            }
            add(window,brick);
            
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval ( (getWidth(window) / 2) - RADIUS, (getHeight(window) / 2) + 20, RADIUS * 2, RADIUS * 2);
    setFilled(ball,true);
    setColor(ball, "BLUE"); 
    add(window,ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    /* gets the width of the window and width of paddle to determine the center horrizontally
     * gets the hieght of the window and subtracts the paddles height to determine where paddle should go to be at the bottom
     */
    GRect paddle = newGRect((getWidth(window) / 2) - (PWIDTH / 2), (getHeight(window) - PHEIGHT - 20),PWIDTH,PHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window,paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-14");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 if (x=0)
 
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
