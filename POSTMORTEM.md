# CR-Engine Post-Mortem

# Intro

 This post-mortem will cover the lessons learned and short comings
 of the CR-Engine. If you happen to be a future employer
 I urge you to focus moreso on the lessons learned section
 rather than the project short comings, as from the getgo
 I intended this project to be a test and a learning
 experience.

 Overall, I'd consider this project a failure. The two
 sentence breakdown is that I didn't plan out developing
 a game ontop of the engine backend and the entire engine
 got too unweildy to use well. 

# Lessons Learned and What Went Wrong

 On the plus side, the CR-Engine game me alot of experience
 and insight into low-level memory management. Throught this
 project I gained a fair bit of trial-and-error expereince
 with memory leak debugging, and developing psuedo-automatic
 memory garbage disposal. While this project was a good
 introduction to working with memeory management I know I
 still have lots to learn.

 By far the largest pit-fall of the CR-Engine was poor
 project design. Things seemed to start out well with
 "compartmentalizing" different components such as video,
 audio, entity management, etc, however I failed to plan
 far enough into the future for building an actual game ontop
 of the backend. This problem manifested itself mostly in the
 core game logic loop. The original idea for the game logic
 loop was that the game would pass various events to cause
 things to happen, however having different game logic systems
 working within one-another while in seperate compartments quickly
 lead to difficult to manage code. Overall I feel that when I
 work on a future project I will need to focus more on the
 overall project design before any code is written. I hope
 to improve through program design courses this coming semester
 and through reviewing program design resources in my spare time
 before taking on my next large(ish) programming project.  

 A large missed opportunity in the CR-Engine was the use of 
 polymorphism in C++. At the beginning of the project I was
 reluctant to use virtual functions and child classes as I
 didn't fully see their use and was not particularly familiar
 with their advantages. However in hind-sight, I realize that
 polymorphism could have beeen used to great effect with the
 event system and with entities to reduce the ammount that a
 developer would need to consider when developing a game.
 (e.g. not needing to set an entity's internal type flag, or 
 refer to the formatting of specific events types). Additionally,
 polymorphism could have made the implementation of different
 texture layers very easy (ex. background, foreground textures).

 I suppose as the final major thing I learned during the CR-Engine,
 program optimization isn't always straight forwards. As an example,
 when I initially started work on the rop-off of Pac-Man I noticed
 terrible frame rate issues in the game (2-3 FPS). I figured that
 the engine's rendering was being done in software rather than hardware,
 or that SDL just very bad as rendering quickly, or that the rendering
 couldn't effectively handle 500+ objects on screen at once. However,
 after doing some rearanging in how rendering is performed I was able
 to change which functions were called and was able to reduce the number
 of functions falled per frame by a large margin. From this I realized a
 couple things.

 1.) Function calls are really slow. Not bad practice, just slow.

 2.) Program Optimization can take place in unexpected places (not just
 making a function run a few clock cycles faster).

 Last, but certainly not least, building a game engine from scratch is
 not a good idea. This project was a mix of fun, frustrating, and rewarding,
 and while the goal wasn't only to develop games entirely in my own software,
 I hoped that by the end of this I would be able to create some sort
 of game that wasn't as simple as pong or asteroids. I knew going into
 this project that I would not create something of high quality. If you
 are reading this and are thinking about making your own game engine,
 don't. There is a wide array of professional game engines that should
 work well enough for almost any project you have in mind. Don't 
 re-invent the wheel.