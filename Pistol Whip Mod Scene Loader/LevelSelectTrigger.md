#LevelSelectTrigger

##OnLevelSelect(Messages.LevelSelectEvent e)
* Checks if event is not null
* Check if event.gameMap is null and if this.ActOnNull is false
* Check that the UnityEvent onLevelSelect is not null
* * If not invoke the event
* Check that LevelSelectTrigger.oneShot is not null
* * Destory the object

##Awake()
* Get the Messenger
* Register OnLevelSelect() to be called on Messages.LevelSelectEvent messages

##OnDestroy()
* Get Messenger
* Deregister for calls on Messages.LevelSelectEvent messages

##.ctor()
TODO figureout what classes creates this object and what functions they register to the event

