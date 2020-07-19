#GameManager
Description of the GameManager class and the compiler generated classes for the IEnumerator types used in coroutines

# # Function descriptions

##SetLevel()

##SetLevelInternal(GameMap map)
* Assign map to GameManager.map
* Get difficulty
* Checks that GameManager.gameplayDB is not null and gets the enemyAttackDelays array, checks this is not null too
* Check that entry for given difficulty exists in enemyAttackDelays.
* Gets the entry for the given difficulty in enemyAttackDelays
* I think it assigns the enemyAttackInterval[difficulty] to the enemyAttackDelay property
* Tries to get enemyAttackIntervals from GameManager.gameplayDB

enemyAttackInterval

# # #OnStartButton()
Seems to be the same as StartGame()
* Checks that playing is false and that map is not null.
* Create coroutine for PrepAndStartGame and assigns the state to 0 and the "this" field of the coroutine.
* Start coroutine for PrepAndStart Game

# # # PrepAndStartGame() 
This assumes functionality is placed in the MoveNext() function
What PrepAndStartGame() does depends on the state.
if State = 0
* Set state = 0xFFFFFFFF
* Checks that GameManager is not null 
* Set modifiers
* Get instance of Messenger
* Sends the messege Messsege.ResetPlayer
* Creates a System.Action
* Create a KeyGeneratedEventHandler (MulticastDelegate) on the GameManager.OnPlayerDeath() function and assigns it to the action
* Registers the action to be called with Messeger.Register(Messeges.PlayerHitDie())
* Create a System.Action<Messeges.SongStartEvent>
* Create a KeyGeneratedEventHandler (MulticastDelegate) on the GameManager.OnSongStart() function and assigns it to the action. (Unsure if it also regiserts to System.Action<Messages.SongStartEvent>..ctor())
* * Mono.Security.Cryptography.RSAManaged.KeyGeneratedEventHandler$$.ctor(System.Action<Messeges.SongStartEvent>,gameManager,Method.GameManager.OnSongStart(), Method.System.Action<Messages.SongStartEvent>..ctor());
* Registers the action to be called with Messeger.Register(Messages.SongStartEvent())
* Gets gameManager.map and creates and Message.LoadLevelRequest() with said GameMap
* Sends the Messege.LoadLevelRequest with Messeger.Send<Messege.LoadLevelRequest>
* Sets state = 1, current = null and returns
if State is not 0
if State is 1
* Set State = 0xFFFFFFFF
* Gets current time
* Checks that GameManager is not null
* Set GameManager.gameStartTime to current time
* Checks that GameManager.map is not null, gets GameManager.map.data(LevelData) and checks that it is not null
* Gets LevelData.songLength
* Sets GameManager.gameProgress to 0
* Sets GameManager.gameLength to songLength
* Sets GameManager.player to 0x101 (i assume true)
* Gets Messenger instance and sends a Message.GameStartEvent
* Raises the GameManager.gameStartEvent (GameEvent) if it is not null
* * ScriptableObjectArchitecture.GameEventBase$$Raise(GameManager.gameStartEvent,0)
* Sets state = 2, current = null and returns
if State is 2
* Set State = 0xFFFFFFFF
* if GameMap.map is null, return
* Check that GameManager.proceedToEndResultsEvent is not null
* Gets difficulty of the map
* Check that GameManager.levels.koreoSets (WwiseKoreographySet) is not null
* Checks that koreoSets + 0x18 (index? size?) is less than difficulty
* * If not throw IndexOutOfRangeException
* Gets the songSwitch from map.data.songSwitch (Switch)
* Calls MusicManager.PlaySong(GameManager.levels.koreoSets[difficulty], map.data.songSwitch, GameManager.songSeekTime)
* * I assume it is diffulty that is used as the index for koreoSets. 

