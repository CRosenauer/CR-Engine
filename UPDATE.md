# Update
 This file contains the changelogs for all (or most) of the
 updates to the CR-Engine. For a more general overview see
 repository notes.
 
# January, 1, 2020
 Happy new year!
 
 In this update I've mostly added a framework for creating
 and implementing scripts. Scripts in this sense are a
 sequence of commands that effect a specific entity.
 Scripts in the CR-Engine work similarly to a list list;
 in each script contains an ID for referencing specific
 entities based on ID, an SDL event to be queued on a given
 frame, an integer to determine how many frames delay there
 will be between two given events in a script, and a
 pointer to the next script container in the script.
 
 A frame count of 0 frames means that the next script
 containers event will be queued right after the current
 script event is queued. 
 
 If the pointer to the next script is NULL then there is no
 "next" script to play.
 
 If the script's internal reference ID is NULL then a
 specific entity will not be effected by the event. This
 may be used in passing events like "pause game" or
 "kill player" that would effect more than one entity.
 Entity ID's should not be set in the internal SDL event's
 void pointers as the as the ID needed may be indetermined
 until game run time, such as determining which enemines
 are hit by a given hitbox in a beat 'em up game.
 
 Scripts should be made in rom memory during game
 development and be passed through to the script handler
 class during run time.
 
 Now that that's all out of the way lets delve into how
 scripts are handled in this iteration of the CR-Engine.
 
 Scripts are loaded and interpreted by the class
 scriptHandler. This class loads scripts via the function
 loadScript, and for queueing the events in loaded scripts
 via the function processScripts.
 
 loadScript take two arguements: a script, eScripts and and
 an unsigned integer, ID. The script is loaded to the
 scriptHandler object's internal script linked list and the
 loaded scripts entity referency ID is replaced with the
 passed reference ID. The loaded script's event is then
 loaded to SDL's internal event queue. It should be noted
 that script's events are only played when the script is
 loaded to the script handler. Each frame the script is
 altered afterwards either by decrementing the frame count
 or by replacing the current script frame with the next
 script frame.
 
 proccesScripts should be called near the end of each frame
 before video rendering and audio handling and takes no
 arguements. The function cycles through each stored script
 frame. For each loaded script frame, if the script's
 internal frame counter is 0 the next script is loaded (if
 any) and the next scripts event is queued, otherwise the
 frame count is decremented.
 
 Please note that the current scripting functions still
 need to be tested. Scripting implementation may change
 drastically in the near future, so if you are for some
 reason using this engine to make a game, well first don't,
 you're shooting yourself in the foot, and secondly wait a
 bit for me to validate script handling before using this
 code.
 
 
# December, 29, 2019
 Allot of new things have been included. Firstly, a frame
 cap of 60 FPS has been implemented. Testing for this
 feature is still in the works.
 
 The framework for applying animations to entities has also
 been implemented and tested. Included in this update is 
 test animation of an orange circle that spells out th
 letters "LUL". The graphical files for this test have been
 included. Prior texture drawing has been retained and can
 still be used along side animations.
 
 The implementation of graphics rendering and texture
 retrieval from entities has been altered slightly to fix
 bugs in animation handling.
 
 Entities are now assigned an internal ID number that is
 used by the the video handler for rendering and in the
 future will be used in internal game events for entity
 referencing and verification. This ID number is
 automatically set upon entity initialization and
 re-initialization via constructors. Entities also have an
 internal definition variable. This definition variable
 is set to false upon initialization and the function
 void entity::define() must be used for external handlers
 to be able to interact with the entity.
 
 Entities no longer need to be pushed to the video
 rendering queue. Instead entities have been given an
 internal flag for if said entity should be rendered as a
 sprite, foreground image, or background image. When the
 video handler is called to render it will load every
 defined entity to the rendering queues depending on the
 entity's internal flags.
 
 On a lesser note, the input bus, entity block, video handler
 and audio handler have been redefined in certain files as an
 extern variable rather than passing addresses and assigning
 them to pointers.