# designPattern
----mp3--------
  song.mp3       Works fine with mp3 class
-----------------   
------mp3-----
**song.mp4**   mp3 does not know how to play it, hence it is non-compatible.
----------------


Pass mp4 song to mp4 with help of adapter class which has information of both the entity.
Adapter is a mp3 class and has a mp4.
------mp3-----                                                     --------mp4---------
pass song.mp4      pass this to mp4 class    =======>                play song.mp4
----------------                                                 -----------------------
