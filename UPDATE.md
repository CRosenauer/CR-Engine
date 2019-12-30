# Update
 This file contains the changelogs for all (or most) of the
 updates to the CR-Engine. For a more general overview see
 repository notes.
 
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