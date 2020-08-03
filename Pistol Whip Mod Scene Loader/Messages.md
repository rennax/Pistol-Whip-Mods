#Messages
Messages can be sent through the Messenger class. Classes can register to listen for certain events, while other classes can send events, without the two classes needing to know about each other.
Messages may contain additional infomation.

##LevelSelectEvent
Following classes register to this message.
###SceneAppearanceManager.OnEnable()
Registers to call `private void OnLevelSelect(Messages.LevelSelectEvent e)`


###LevelSelectTrigger.Awake()
Registers to call `private void OnLevelSelect(Messages.LevelSelectEvent e)`
See more about LevelSelectTrigger here


Following class send this message
* GameManager.SetLevelInternal(GameMap map)



##GameStartEvent
Following classes register to this message.
###PlayerActionManager.OnEnable()
Registers to call to `PlayerActionManager.OnGameStart()`


###LevelSelectTrigger.Awake()
Registers to call `private void OnLevelSelect(Messages.LevelSelectEvent e)`
See more about LevelSelectTrigger her
