#ifndef __CONTEXT__
#define __CONTEXT__

#include "../output/Multiplexer.h"

/** Contains all status variable for the program.
 *
 * It's used to share informations between task and
 * coordinate them creating a simple game.
 */

class Context {
private:
    volatile uint16_t currentDistance;
    volatile bool gameOver;
    volatile bool buttonPressed;
    volatile bool padlockOpen;
    volatile bool padlockDetected;
    uint16_t maxDistance;
    uint8_t delta;
    uint8_t currentlevel;
    uint16_t randomNum;
    uint8_t dangerLevel;
    bool lockpickingState;
    Multiplexer* mux;
public:

    /** @brief ###Construct and initialize the 'Context'
     *
     * Initialize all parameters of the game and set the random seed with
     * analog output entropy
     * @param[in] maxDistance Maximum distance game
     * @param[in] mux         Multiplexer instance
     */
    Context(uint16_t maxDistance, Multiplexer* mux) {
        this->maxDistance = maxDistance;
        this->mux = mux;
        currentDistance = 0;
        delta = 6;
        currentlevel = 1;
        randomNum = 0;
        padlockOpen = false;
        padlockDetected = false;
        gameOver = false;
        lockpickingState = false;
        dangerLevel = 0;
        mux->switchOn(currentlevel);
        randomSeed(analogRead(A0));
    }

    /** @brief ###If the player has guessed and opened the padlock **/
    bool isPadlockOpen() {
        return padlockOpen;
    }

    /** @brief ###Set the padlock's state
     *
     * @param[in] padlockOpen The state of the padlock
     */
    void setPadlockOpen(bool padlockOpen) {
        this->padlockOpen = padlockOpen;
    }

    /** @brief ###If the player has guessed the secret position **/
    bool isPadlockDetected() {
        return padlockDetected;
    }

    /** @brief ###Set the state of the padlock when user guess the secret position
     *
     * @param[in] padlockDetected The state of the guessing part
     */
    void setPadlockDetected(bool padlockDetected) {
        this->padlockDetected = padlockDetected;
    }

    /** @brief ###Set the distance at which the padlock will open
     *
     * @param[in] currentDistance The distance to set
     */
    void setCurrentDistance(uint16_t currentDistance) {
        this->currentDistance = currentDistance;
    }

    /** @brief ###Get the distance at which the padlock will open */
    uint16_t getCurrentDistance() {
        return currentDistance;
    }

    /** @brief ###Set the state of the button if pressed
     *
     * @param[in] buttonPressed The state of the button
     */
    void setButtonPressed(bool buttonPressed) {
        this->buttonPressed = buttonPressed;
    }

    /** @brief ###Get the state of the button */
    bool isButtonPressed() {
        return buttonPressed;
    }

    /** @brief ###Set a new level
     *
     * @param[in] currentlevel The level to create
     */
    void setNewLevel() {
        newRandomNumber();
        this->currentlevel++;
        this->delta--;
        if (this->currentlevel > 6)
            this->gameOver = true;
        else
            mux->switchOn(this->currentlevel);
    }

    /** @brief ###Get the margin of error for the distance */
    uint8_t getDelta() {
        return delta;
    }

    /** @brief ###Get the level to play */
    uint8_t getLevel() {
        return currentlevel;
    }

    /** @brief ###Get the scret distance where the padlock will open */
    uint16_t getSecret() {
        return randomNum;
    }

    /** @brief ###Generate a new random number */
    void newRandomNumber() {
        randomNum = random(6, maxDistance - 1);
    }

    /** @brief ###Set the game state
     *
     * param[in] gameOver The state of the game
     */
    void setGameOver(bool status) {
        this->gameOver = status;
    }

    /** @brief ###Get the stat of the game */
    bool isGameOver() {
        return gameOver;
    }

    /** @brief ###Set the level at which the padlock will starts to break */
    void setDangerLevel(uint8_t dangerLevel) {
        this->dangerLevel = dangerLevel;
    }

    /** @brief ###Get the current level of breakage of padlock */
    uint8_t getDangerLevel() {
        return dangerLevel;
    }

    /** @brief ###Set if the padlock is found and the user starts to pick */
    void setLockpicking(bool state) {
        this->lockpickingState = state;
    }

    /** @brief ###Get if the user start to lock-picking the padlock */
    bool isLockpicking() {
        return lockpickingState;
    }

    /** @brief ###Run a carousel with two led color
     *
     * The carousel activate two circular array of 6 leds.
     * @param[in] delay1 The delay before change position
     * @param[in] delay2 The delay before change position
     */
    void carousel(uint8_t delay1, uint8_t delay2) {
        mux->carouselRed(delay1);
        mux->carouselYellow(delay2);
    }
};

#endif
