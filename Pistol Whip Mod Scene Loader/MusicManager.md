MusicManager
#Function description

##PlayMusic(WwiseKoreographySet koreoSet, State song, float seekTime = 0f)
* First check if MusicManager.visor (WwiseMusicVisor) is not null
* Then calls visor.LoadKoreoSet(koreoSet)
* Gets instance to MusicManager again
* Get the seekTime with Mathf.Max(0, seekTime)
* Check if instance is null
* Sets instance.seekTime
* Check if instance.state is not null
* Calls instance.state.SetValue
If instance.seekTime > 0
* Get Messenger instance
* Create Message.SongSeekEvent
* Set the seekTime of the newly created message
* Get musicController from instance of MusicManager
* Call musicController.SeekMusic(seekTime*1000) (takes int of time as ms)
If instance.songTimeRoutine is not null
* Debug.Log error if it is enabled
* Stop the currently running coroutine songTimeRoutine
Get instance from MusicManager again
If instance is not null (why do we keep making this check?)
* Begin preparation for all to IEnumerator DelaySendSongTime()
* Assign the instance to "this" field in coroutine object
* set state to 0 in coroutine object
* Assign the coroutine to instance.songTimeRoutine
* Start the coroutine


##IEnumerator DelaySendSongTime()
* Gets coroutine state
* Get instance of MusicManager
If state is 0 or 1  
* Get playing koreography from MusicManager.playingKoreo
* Get the equality between playingKoreo and some other object
* If equality is false
* Grap the playingKoreo again, and if it is null, return
* Else get playingKoreo.lastUpdateEnd
* Get samplerate of the playingKoreo
* Get the result of lastUpdateEnd/samplerate and set this to songTime
* If songTime is not 0 set musicManager.seekTime
* * Get Messenger and create a SongTimeEvent and assign the songTime
* * Send message
* Set current inside the coroutine to null and state to 2
* If equality is true
* Set current inside the coroutine to null and state to 1
Else  
* If state is 2
* Get playing koreography from MusicManager.playingKoreo
* Get the equality between playingKoreo and some other object
* If it is 0 go back to previous statement for state 0 or 1
* Else we log the error message "PlayingKoreo is null - aborting DelaySendSongTime"
* We stop the coroutine
* Create a new SongTimeEvent message and set songTime
* Send message.